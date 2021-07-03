#pragma once
//#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <ctime>
#include "screen.h"
class curtime
{
	struct tm newtime;
	time_t now;
	int d, m, y;
public:
	curtime()
	{
		now = time(0);
		localtime_s(&newtime, &now);
		y = 1900 + newtime.tm_year;
		m = 1 + newtime.tm_mon;
		d = newtime.tm_mday;
	}
	void Print();
	int Day();
	int Month();
	int Year();
};
