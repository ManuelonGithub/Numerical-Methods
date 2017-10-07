/* 
File: time24methods.cpp

The class time24 represents time on 24 hour clock

Times are written to a stream in the form hour:minute

When a time is added to the current time the minutes are added and if
the sum is 60 or more then 60 is subtracted from the sum but the the
hour is increased by 1. If the hour is 24 or more then 24 is subtrated
from the hour.

Programmer: Manuel Burnay		Date Created : 22/09/2017
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class time24
{
	private:
		int hour; // hour between 0 and 23
		int minute; // minute between 0 and 59
		
	public:
		time24(int h = 0 , int m = 00); // constructor with default args
		
		void write(ostream &out); // prints hour:minute to out
		
		time24 add(const time24 &y) const; // add y to current time
};

int main(void)
{
	time24 x(18, 34), y(10,56), z;
	
	cout << "The time x is: ";
	x.write(cout);
	
	cout << "\nThe time y is: ";
	y.write(cout);
	
	// try conversion
	z = 12;
	cout << "\nThe time z is: ";
	z.write(cout);
	
	// try adding
	z = x.add(y);
	
	cout << "\nThe sum of ";
	x.write(cout);
	cout << " and ";
	y.write(cout);
	cout << " is ";
	z.write(cout);
	cout << endl;
	
	return 0;
}

//////////////////////// Methods of time24 ///////////////////////////
time24::time24(int h, int m)
{
	hour = h;
	minute = m;
}

void time24::write(ostream &out)
{
	out << hour << ":" << setw(2) << setfill('0') << minute;
}

time24 time24::add(const time24 &y) const
{
	int h = hour + y.hour;
	int m = minute + y.minute;
	
		if(m >= 60)
	{
		m = m - 60;
		h = h + 1;
	}
	if(h >= 24)
	{
		h = h - 24;
	}
	
	return time24(h,m);
}

