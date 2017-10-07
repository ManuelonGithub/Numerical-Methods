/* 
File: date.cpp
	A class representing dates in the form: day, month and year

	dates are written to a stream in the form day/month/year

	day_number() returns the number of days since 1/1 of the current year
	including the current day

	days_between() returns the number of days between two dates not
	including the firstday but including the last day.

Programmer: Manuel Burnay			Date Created: 24/09/2017
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

class date
{
	private:
		int day;
		int month;
		int year;
	public:
		date(int d, int m, int y);
		void write(ofstream &out);
		int day_number();
		int days_between(const date &b) const;
};

// number of days in each month
const int DAYS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int main(void)
{
	ofstream fout("date.txt");

	date d(12, 6, 2010);
	date e(14, 9, 2012);

	fout << "For the date is ";
	d.write(fout);
	fout << endl;

	fout << "Day number is " << d.day_number() << endl;

	fout << "\nFor the date is ";
	e.write(fout);
	fout << endl;

	fout << "Day number is " << e.day_number() << endl;

	fout << "\nDays between ";
	d.write(fout);
	fout << " and ";
	e.write(fout);
	fout << " = " << d.days_between(e) << endl;

	fout.close();

	system("date.txt");

	return 0;
}

///////////////////////// Methods of date ////////////////////////////
date::date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;			
}

void date::write(ofstream &out)
{
	out << day << "/" << month << "/" << year;
}

int date::day_number()
{
	int d_n = 0;

	for (int i = 0; i < (month-1); i++)
	{
		d_n += DAYS[i];
	}

	d_n += day;

	return d_n;
}

int date::days_between(const date &b) const
{
	int d_b = 0;

	int y = year - b.year;

	int m = month - b.month;

	d_b = y * 365;

	if (m < 0)
	{
		for (int i = (month-1); i < (b.month-1); i++)
		{
			d_b -= DAYS[i];
		}
	}

	if (m > 0)
	{
		for (int i = (b.month-1); i < (month-1); i++)
		{
			d_b += DAYS[i];
		}
	}
	d_b += day - b.day;

	return abs(d_b);
}