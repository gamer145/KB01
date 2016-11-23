#include "Logger.h"
#include "EngineTextHandling.h"

Logger* Logger::myLogger = NULL;

Logger::Logger()
{
	SetFiles();
}

Logger::~Logger()
{
}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);	
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
    return buf;
}

void Logger::SetFiles()
{
	std::string formattedDatetime = EngineTextHandling::ReplaceCharsInString(currentDateTime(), ':', '_');	
	genericlogfile = "../Logs/Log " + formattedDatetime + ".txt";
	errorlogfile = "../Logs/Error/Log " + formattedDatetime + ".txt";
	succeslogfile = "../Logs/Success/Log " + formattedDatetime + ".txt";
	warninglogfile = "../Logs/Warning/Log " + formattedDatetime + ".txt";
}

void Logger::WriteToFile(MessageType newType, const std::string& message)
{
	std::fstream theLogfile (genericlogfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (theLogfile.is_open())
	{
		theLogfile << "[" << currentDateTime() << "] " << toString(newType) << ": " << message << std::endl;
		theLogfile.close();
	}
	else
	{
		std::cout << "Error: unable to open logfile '" << genericlogfile << "'!" << std::endl;
	}

	if (newType == Success)
	{
		std::fstream specialisedLog(succeslogfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
		if (specialisedLog.is_open())
		{
			specialisedLog << "[" << currentDateTime() << "] " << toString(newType) << ": " << message << std::endl;
			specialisedLog.close();
		}
		else
		{
			std::cout << "Error: unable to open logfile '" << succeslogfile << "'!" << std::endl;
		}
	}
	else if (newType == Error || newType == FatalError)
	{
		std::fstream specialisedLog(errorlogfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
		if (specialisedLog.is_open())
		{
			specialisedLog << "[" << currentDateTime() << "] " << toString(newType) << ": " << message << std::endl;
			specialisedLog.close();
		}
		else
		{
			std::cout << "Error: unable to open logfile '" << errorlogfile << "'!" << std::endl;
		}
	}
	else if (newType == Warning)
	{
		std::fstream specialisedLog(warninglogfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
		if (specialisedLog.is_open())
		{
			specialisedLog << "[" << currentDateTime() << "] " << toString(newType) << ": " << message << std::endl;
			specialisedLog.close();
		}
		else
		{
			std::cout << "Error: unable to open logfile '" << warninglogfile << "'!" << std::endl;
		}
	}


}

void Logger::ReadFromFile()
{
	std::string line;
	std::ifstream myfile (genericlogfile.c_str(), std::ifstream::in);
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
				std::cout << line << std::endl;
		}
		myfile.close();
	}
	else
	{
		std::cout << "Error: unable to open logfile '" << genericlogfile << "'!" << std::endl; //Veranderen naar messagebox?
	}
}

void Logger::ReadFromFile(std::string token)
{
	std::string line;
	std::ifstream myfile(genericlogfile.c_str(), std::ifstream::in);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.find(token) != std::string::npos)
			{
				std::cout << line << std::endl;
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "Error: unable to open logfile '" << genericlogfile << "'!" << std::endl; //Veranderen naar messagebox?
	}
}

MessageType Logger::GetMessageType()
{
	return Type;
}

void Logger::RemoveLogFile()
{
	remove(genericlogfile.c_str());
}

Logger* Logger::GetLogger()
{
	if (myLogger == NULL)
	{
		myLogger = new Logger();
	}
	return myLogger;
}

std::string Logger::toString(MessageType type)
{
	switch(type)
	{
		case Warning:
			return "Warning";
		case FatalError:
			return "Fatal error";
		case Error:
			return "Error";
		case Load:
			return "Load";
		case Save:
			return "Save";
		case Success:
			return "Success";
		case Custom:
			return "Custom";
		case All:
			return "All";
	}
	return "Unknown";
}