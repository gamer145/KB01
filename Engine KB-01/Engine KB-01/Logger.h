#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum MessageType //Custom set of potential messagetype values.
{ 
	Warning, 
	FatalError, 
	Error, 
	Load, 
	Save, 
	Success, 
	Custom, 
	All
};

class Logger
{
protected:
	Logger(); //Only the logger itself can create itself. Use Logger::GetLogger() for Logger usage in different classes.
public:	
	~Logger();
	void WriteToFile(MessageType newType, const std::string& message, int x); //Writes the specified string to the current messagetype logfile, further handling is decided by the current messagetype of the logger.
	void ReadFromFile(); //Reads the entire logfile from start to finish, the messagetype argument is to fetch the specified log.
	MessageType GetMessageType(); //Returns the current message type of the logger.
	void RemoveLogFile(); //Deletes the log file.
	static Logger* GetLogger(); //Initializes the logger if it doesnt exist and returns it. If it already exists, simply returns it.
	std::string toString(MessageType type);
private:
	void CreateFile(); //Creates a new log file based on when the session started. The created logfile will be used for all logging that session.
	std::string ReplaceCharsInString(std::string strChange, char a, char b); //Replaces characters in a string, used internally to fix some format issues.
	MessageType Type; //Enum messagetype, the type defines what action the logger should take when writing.
	static Logger* myLogger; //The logger object to be returned after intialization. The logger keeps track of itself, so no other class has to.	
	std::string logfile; //The current log file that the logger will write to, changes per session.
};

#endif