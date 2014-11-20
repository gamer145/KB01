#include "LevelLoader.h"

const char* levelFolder = "../Level/";
std::string defaultLevel = "Level.txt";

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}

::Scene* LevelLoader::ReadFromFile(Resource_Manager* resourceManager, Scene* currentScene)
{
	std::stringstream ss;
	std::string line, levelLocation;						
	ss << levelFolder << "Level.txt";	

	levelLocation = ss.str();
	
	std::ifstream myfile (levelLocation.c_str());
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			try{

			//vb: Type:Model - tiger.x - Tiger.bmp PosX:0 PosZ:0 Percentage:true
			std::size_t foundT = line.find("Type:"); // find Type
			std::string strT1 = line.substr (foundT+5);// get substring from Type ->  Model - tiger.x - Tiger.bmp PosX:0 PosZ:0 Percentage:true
			std::size_t foundMN = strT1.find("-"); // find ModelName
			std::string strT = strT1.substr (0, foundMN-1);// Type

				if(strT == "Model")
				{
					std::string strMN1 = strT1.substr (foundMN+2);// get substring from Modelname -> tiger.x - Tiger.bmp PosX:0 PosZ:0 Percentage:true


					std::size_t foundTN = strMN1.find("-"); // find TextureName
					std::string strMN = strMN1.substr (0, foundTN-1);// ModelName 
					std::string strTN1 = strMN1.substr (foundTN+2);// get substring from TextureName  -> banana.bmp PosX:0 PosZ:0 Percentage:true
					std::size_t foundX = strTN1.find("PosX:"); // find PosX
					std::string strTN = strTN1.substr (0, foundX);//TextureName
					std::string strX1 = strTN1.substr (foundX+ 5);// get substring from PosX  -> 0 PosZ:0Percentage:true
					std::size_t foundY = strX1.find("PosY:");// find PosZ
					std::string strX = strX1.substr (0, foundY); // pos X
					std::string strY1 = strX1.substr (foundY+ 5);// get substring from PosX  -> 0 PosZ:0Percentage:true
					std::size_t foundZ = strY1.find("PosZ:");// find PosZ
					std::string strY = strY1.substr (0, foundZ); // pos Y
					std::string strZ1 = strY1.substr (foundZ + 5); // get substring from PosZ -> 15 Percentage:true
					std::size_t foundP = strZ1.find("Fly:");// find Percentage
					std::string strZ = strZ1.substr (0, foundP ); //PosZ
					std::string strP1 = strZ1.substr (foundP + 4); // get substring from PosZ -> true
	
					std::cout << strT << '\n';
					std::cout << strMN << '\n';
					std::cout << strTN << '\n';
					std::cout << strX << '\n';
					std::cout << strY << '\n';
					std::cout << strZ << '\n';
					std::cout << strP1 << '\n';

					VisualObject* tempobject1;
					tempobject1 = resourceManager->LoadInModel(strMN, strTN);
					MatrixWrapper* Position1 = new MatrixWrapper();
					float x = 0;
					float y = 0;
					float z = 0;
					sscanf_s(strX.c_str(), "%f", &x);
					sscanf_s(strY.c_str(), "%f", &y);
					sscanf_s(strZ.c_str(), "%f", &z);

					Position1->MatrixTranslation(x, y, z);
					tempobject1->setPosition(Position1);
					currentScene->AddObject(tempobject1);
				}
				else if(strT == "Skybox")
				{

					std::string strMN1 = strT1.substr (foundMN+2);
					std::size_t foundTN = strMN1.find("-"); 
					std::string strMN = strMN1.substr (0, foundTN-1);
					std::string strTN1 = strMN1.substr (foundTN+2);
					std::size_t foundMultiplier = strTN1.find("Multiplier:"); 
					std::string strTN = strTN1.substr (0, foundMultiplier);
					std::string strMultiplier1 = strTN1.substr (foundMultiplier+ 11);

					std::cout << strT << '\n';
					std::cout << strMN << '\n';
					std::cout << strTN << '\n';
					std::cout << strMultiplier1 << '\n';

					MatrixWrapper* SkyboxPosition = new MatrixWrapper();
					VisualObject* skybox;
					skybox = resourceManager->LoadInModel(strMN, strTN);
					SkyboxPosition->MatrixTranslation(0, 0, 0);
					float multiplier = 0;
					sscanf_s(strMultiplier1.c_str(), "%f", &multiplier);
					SkyboxPosition->MatrixScaling( multiplier, multiplier, multiplier);
					skybox->setPosition(SkyboxPosition);
					currentScene->AddObject(skybox);
				}
				else if(strT == "Camera")
				{
					Camera* camera = new Camera();

					//std::size_t foundT = line.find("Type:"); // find Type
					//std::string strT1 = line.substr (foundT+5);// get substring from Type 
					//std::size_t foundMN = strT1.find("-"); // find ModelName
					//std::string strT = strT1.substr (0, foundMN-1);// Type
					std::string strX1 = strT1.substr (foundMN+11);// from X
					std::size_t foundY = strX1.find(","); // find y
					std::string strX = strX1.substr (0, foundY);// X ----------
					std::string strY1 = strX1.substr (foundY+1); // from Y
					std::size_t foundZ = strY1.find(","); //find z
					std::string strZ1 = strY1.substr (foundZ+1); // from Z
					std::string strY = strY1.substr (0, foundZ);// Y ----------
					std::size_t foundLX= strZ1.find("LookAtPoint:"); //find LX
					std::string strZ = strZ1.substr (0, foundLX);// Z ----------
					std::string strLX1 = strZ1.substr (foundLX+12); //
					std::size_t foundLY = strLX1.find(","); //find LY
					std::string strLX = strLX1.substr (0, foundLY);// LX
					std::string strLY1 = strLX1.substr (foundLY+1); // from LY
					std::string strLY = strLY1.substr (0, foundLY);// LY
					std::size_t foundLZ = strLY1.find(","); //find LZ
					std::string strLZ1 = strLY1.substr (foundLZ+1);// from LZ
					std::string strLZ = strLZ1.substr (0, foundLZ);// LZ


					float X,Y,Z,LX,LY,LZ;
					sscanf_s(strX.c_str(), "%f", &X);
					sscanf_s(strY.c_str(), "%f", &Y);
					sscanf_s(strZ.c_str(), "%f", &Z);
					sscanf_s(strLX.c_str(), "%f", &LX);
					sscanf_s(strLY.c_str(), "%f", &LY);
					sscanf_s(strLZ.c_str(), "%f", &LZ);

					VectorWrapper* EyeVector = new VectorWrapper(X, Y, Z);
					VectorWrapper* LookAtVector = new VectorWrapper(LX, LY, LZ);
					VectorWrapper* UpVector = new VectorWrapper(0.0f, 1.0f, 0.0f);
					camera->SetEyePoint(EyeVector);
					camera->SetLookAtPoint(LookAtVector);
					camera->SetUpVector(UpVector); // Hard Coded
					currentScene->setCamera(camera);
				}
			}
			catch(std::exception e){}
		}
		myfile.close();
	}
	else 
		std::cout << "Error: unable to open file '" << levelLocation << "'!" << std::endl;
	return currentScene;
}