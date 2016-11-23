#include "LevelLoader.h"
#include "EngineTextHandling.h"

const char* levelFolder = "../Level/";
std::string defaultLevel = "Level.txt";

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}

Scene* LevelLoader::ReadFromFile(Resource_Manager* resourceManager, Scene* currentScene)
{
	std::stringstream ss;
	std::string line, levelLocation;						
	ss << levelFolder << "Level.txt";
	std::string dummy;

	levelLocation = ss.str();
	
	std::ifstream myfile (levelLocation.c_str());
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::istringstream iss(line);

			if (line.find("Model") != std::string::npos)
			{
				VisualObject* tempobject1;
				MatrixWrapper* position = new MatrixWrapper();

				std::string modelName;
				std::string textureName;
				std::string posX, posY, posZ;

				float x, y, z;

				iss >> dummy >> modelName >> textureName >> posX >> posY >> posZ;

				std::istringstream posXiss(EngineTextHandling::ReplaceCharsInString(posX, ':', ' '));
				posXiss >> dummy >> x;

				std::istringstream posYiss(EngineTextHandling::ReplaceCharsInString(posY, ':', ' '));
				posYiss >> dummy >> y;

				std::istringstream posZiss(EngineTextHandling::ReplaceCharsInString(posZ, ':', ' '));
				posZiss >> dummy >> z;

				tempobject1 = resourceManager->LoadInModel(modelName, textureName);
				position->MatrixTranslation(x, y, z);
				tempobject1->setPosition(position);
				currentScene->AddObject(tempobject1);
			}		
			else if (line.find("Camera") != std::string::npos)
			{
				Camera* camera = new Camera();

				std::string eyep;
				std::string lap;
				float ex, ey, ez, lx, ly, lz;

				iss >> dummy >> dummy >> eyep >> dummy >> lap;
				
				std::istringstream eyepiss(EngineTextHandling::ReplaceCharsInString(eyep, ',', ' '));
				eyepiss >> ex >> ey >> ez;

				std::istringstream lapiss(EngineTextHandling::ReplaceCharsInString(lap, ',', ' '));
				lapiss >> lx >> ly >> lz;

				VectorWrapper* EyeVector = new VectorWrapper(ex, ey, ez);
				VectorWrapper* LookAtVector = new VectorWrapper(lx, ly, lz);
				VectorWrapper* UpVector = new VectorWrapper(0.0f, 1.0f, 0.0f);
				camera->SetEyePoint(EyeVector);
				camera->SetLookAtPoint(LookAtVector);
				camera->SetUpVector(UpVector); // Hard Coded
				currentScene->setCamera(camera);
			}	
		}
		myfile.close();
	}
	else 
		std::cout << "Error: unable to open file '" << levelLocation << "'!" << std::endl;
	return currentScene;
}