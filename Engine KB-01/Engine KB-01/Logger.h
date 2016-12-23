#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//Custom set of potential messagetype values.
enum MessageType 
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
	//Only the logger itself can create itself. Use Logger::GetLogger() for Logger usage in different classes.
	Logger(); 
public:
	//Destructor
	~Logger();

	//Writes the specified string to the current messagetype logfile, further handling is decided by the current messagetype of the logger.
	void WriteToFile(MessageType newType, const std::string& message);

	//Reads the entire logfile from start to finish, the messagetype argument is to fetch the specified log.
	void ReadFromFile(); 

	//Reads the entire logfile from start to finish, filtering output based upon the specified token string. Token string is case sensitive.
	void ReadFromFile(std::string token); 

	//Returns the current message type of the logger.
	MessageType GetMessageType(); 

	//Deletes the log file.
	void RemoveLogFile(); 

	//Initializes the logger if it doesnt exist and returns it. If it already exists, simply returns it.
	static Logger* GetLogger(); 

	//Convert the ENUM MessageType to a string
	std::string toString(MessageType type);
private:
	//Function that creates a datetime and returns it.
	std::string currentDateTime();

	//Sets new log files based on when the session started. The created logfiles will be used for all logging that session.
	void SetFiles(); 

	//Enum messagetype, the type defines what action the logger should take when writing.
	MessageType Type; 

	//The logger object to be returned after intialization. The logger keeps track of itself, so no other class has to.	
	static Logger* myLogger; 

	//The generic log file that the logger will write to, changes per session.
	std::string genericlogfile; 

	//The succes log file that the logger will write to, changes per session.
	std::string succeslogfile; 

	//The error log file that the logger will write to, changes per session.
	std::string errorlogfile; 

	//The warning log file that the logger will write to, changes per session.
	std::string warninglogfile;
};

#endif