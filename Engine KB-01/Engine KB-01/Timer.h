#ifndef TIMER_H
#define TIMER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Windows.h"

class Timer
{
public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Reset();
	std::string currentDateTime();
	void getTime();
private:
	int millisecond;
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
	SYSTEMTIME start;
	SYSTEMTIME stop;
	SYSTEMTIME pauze;
};

#endif