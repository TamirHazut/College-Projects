#ifndef _DATE__H
#define _DATE__H

#include <ctime>
#include <iostream>
using namespace std;

class Date
{
private:
	int year;
	int month;
	int day;

public:

	// Constructors
	Date(int day, int month, int year)
	{
		setDay(day);
		setMonth(month);
		setYear(year);
	}

	// Getters / Setters
	int getDay() const { return this->day; }
	int getMonth() const { return this->month; }
	int getYear() const { return this->year; }

	bool setDay(int day)
	{
		if (day < 1 || day > 31)
		{
			this->day = 1;	
			return false;
		}
		this->day = day;
		return true;
	}
	bool setMonth(int month)
	{
		if (month < 1 || month > 12)
		{
			this->month = 1;
			return false;
		}
		this->month = month;
		return true;
	}
	bool setYear(int year) 
	{
		time_t t = time(NULL);
		tm* timePtr = localtime(&t);
		if (year < 1900 || year > (1900 + timePtr->tm_year))
		{
			this->year = (1900 + timePtr->tm_year);
			return false;
		}
		this->year = year;
		return true;
	}

	friend ostream& operator<<(ostream& os, const Date& d)
	{
		os << "(" << d.day << "," << d.month << "," << d.year << ")";
		return os;
	}
};

#endif // !_DATE__H