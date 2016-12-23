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

/**
* Function:	Logger::currentDateTime()
* Description: Function that creates a datetime and returns it. Used for logging purposes, hence why it's here
*/
std::string Logger::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);	
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
    return buf;
}


/**
* Function:	Logger::currentDateTime()
* Description: Function that creates a datetime and returns it. Used for logging purposes, hence why it's here
*/
void Logger::SetFiles()
{
	std::string formattedDatetime = EngineTextHandling::ReplaceCharsInString(currentDateTime(), ':', '_');	
	genericlogfile = "../Logs/Log " + formattedDatetime + ".txt";
	errorlogfile = "../Logs/Error/Log " + formattedDatetime + ".txt";
	succeslogfile = "../Logs/Success/Log " + formattedDatetime + ".txt";
	warninglogfile = "../Logs/Warning/Log " + formattedDatetime + ".txt";
}


/**
* Function:	Logger::WriteToFile()
* Description: Writes a specific message to a logFile and the generic logfile. 
* Based on the messageType it also writes the message to a specific log file
*/
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


/**
* Function:	Logger::ReadFromFile()
* Description: Reads and displays everything from the generic log file where everything is logged
*/
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
		std::cout << "Error: unable to open logfile '" << genericlogfile << "'!" << std::endl;
	}
}


/**
* Function:	Logger::ReadFromFile()
* Description: Reads from the generic log file where everything is logged, untill it finds the specified string
* Displays the line where the specified string is found
*/
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

/**
* Function:	Logger::GetMessageType()
* Description: Returns the last MessageType processed by the logger
*/
MessageType Logger::GetMessageType()
{
	return Type;
}

/**
* Function:	Logger::RemoveLogFile()
* Description: Deletes the generic log file
*/
void Logger::RemoveLogFile()
{
	remove(genericlogfile.c_str());
}

/**
* Function:	Logger::GetLogger()
* Description: Gets the logger, if it doesn't exist. It creates itself.
* WoW magic
*/
Logger* Logger::GetLogger()
{
	if (myLogger == NULL)
	{
		myLogger = new Logger();
	}
	return myLogger;
}

/**
* Function:	Logger::toString()
* Description: Converts a messageType to string
*/
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