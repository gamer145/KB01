#include "Logger.h"

Logger* Logger::myLogger = NULL;

Logger::Logger()
{
	CreateFile();
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

std::string Logger::ReplaceCharsInString(std::string strChange, char a, char b)
{
	for (int i = 0; i < strChange.length(); ++i)
	{
		if (strChange[i] == a)
			strChange[i] = b;
	}

	return strChange;
}

void Logger::CreateFile()
{
	std::string formattedDatetime = ReplaceCharsInString(currentDateTime(), ':', '_');	
	logfile = "../Logs/Log " + formattedDatetime + ".txt";	
	std::ofstream a_file(logfile);
}

void Logger::WriteToFile(MessageType newType, const std::string& message, const int x)
{
	std::fstream theLogfile (logfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (theLogfile.is_open())
	{
		theLogfile << "[" << currentDateTime() << "] [Ln " << x << "] " << toString(newType) << ": " << message << std::endl;
		theLogfile.close();
	}
	else
	{
		std::cout << "Error: unable to open logfile '" << logfile << "'!" << std::endl;
	}
}

void Logger::ReadFromFile()
{
	std::string line = "";
	std::ifstream myfile (logfile.c_str());
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
				std::cout << line << std::endl; //Veranderen naar messagebox?
		}
		myfile.close();
	}
	else
	{
		std::cout << "Error: unable to open logfile '" << logfile << "'!" << std::endl; //Veranderen naar messagebox?
	}
}

MessageType Logger::GetMessageType()
{
	return Type;
}

void Logger::RemoveLogFile()
{
	remove(logfile.c_str());
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