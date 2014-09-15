#include "Timer.h"

Timer::Timer()
{
	 Reset();
}

void Timer::Start()
{
    GetLocalTime(&start);
    printf(" The local time is: %d:%d:%d.%d\n", start.wHour, start.wMinute, start.wSecond, start.wMilliseconds);
}

void Timer::Reset()
{
	millisecond = 0;
	second = 0;
	minute = 0;
	hour = 0;
}

void Timer::getTime()
{
	std::cout << hour<<":"<<minute<<":"<<second<<"."<<millisecond<< std::endl;
	//std::cout<<currentDateTime();
}



void Timer::Stop()
{
	GetLocalTime(&stop);
	printf(" The local time is: %d:%d:%d.%d\n", stop.wHour, stop.wMinute, stop.wSecond, stop.wMilliseconds);

	millisecond += stop.wMilliseconds;
	second += stop.wSecond ;
	minute += stop.wMinute;
	hour += stop.wHour;
	day += stop.wDay;
	month += stop.wMonth;
	year += stop.wYear;


	if (millisecond - start.wMilliseconds < 0)
	{
		second -= 1;
		millisecond += 1000;
		millisecond -= start.wMilliseconds;
	}
	else
	{
		millisecond -= start.wMilliseconds;
	}
	if (second - start.wSecond < 0)
	{
		minute -= 1;
		second += 60;
		second -= start.wSecond;
	}
	else
	{
		second -= start.wSecond;
	}
	if (minute - start.wMinute < 0)
	{
		hour -= 1;
		minute += 60;
		minute -= start.wMinute;
	}
	else
	{
		minute -= start.wMinute;
	}
	if (hour - start.wHour < 0)
	{
		day -= 1;
		hour += 24;
		hour -= start.wHour;
	}

	else
	{
		hour -= start.wHour;
	}


	if(millisecond > 999)
	{
		millisecond -= 1000;
		second += 1;
	}
	if(second > 59)
	{
		second -= 60;
		minute += 1;
	}
	if(minute > 59)
	{
		minute -= 60;
		hour += 1;
	}

	getTime();
}

// std::string Timer::currentDateTime() {
//    time_t     now = time(0);
//    struct tm  tstruct;
//	struct tm  tstruct2;
//    char       buf[80];
//    localtime_s(&tstruct, &now);
//    strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
//    return buf;
//}

Timer::~Timer()
{
}