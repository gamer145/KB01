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
	void WriteToFile(MessageType newType, const std::string& message); //Writes the specified string to the current messagetype logfile, further handling is decided by the current messagetype of the logger.
	void ReadFromFile(); //Reads the entire logfile from start to finish, the messagetype argument is to fetch the specified log.
	void ReadFromFile(std::string token); //Reads the entire logfile from start to finish, filtering output based upon the specified token string. Token string is case sensitive.
	MessageType GetMessageType(); //Returns the current message type of the logger.
	void RemoveLogFile(); //Deletes the log file.
	static Logger* GetLogger(); //Initializes the logger if it doesnt exist and returns it. If it already exists, simply returns it.
	std::string toString(MessageType type);
private:
	void SetFiles(); //Sets new log files based on when the session started. The created logfiles will be used for all logging that session.
	MessageType Type; //Enum messagetype, the type defines what action the logger should take when writing.
	static Logger* myLogger; //The logger object to be returned after intialization. The logger keeps track of itself, so no other class has to.	
	std::string genericlogfile; //The generic log file that the logger will write to, changes per session.
	std::string succeslogfile; //The succes log file that the logger will write to, changes per session.
	std::string errorlogfile; //The error log file that the logger will write to, changes per session.
	std::string warninglogfile; //The warning log file that the logger will write to, changes per session.
};

#endif