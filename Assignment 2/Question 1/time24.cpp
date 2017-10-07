/* 
File: time24.cpp

The class time24 represents time on 24 hour clock

Times are written to a stream in the form hour:minute

When two times are added the minutes are added and if the sum is 60 or
more then 60 is subtracted from the sum but the the hour is increased by
1. If the hour is 24 or more then 24 is subtracted from the hour.

Programmer: Manuel Burnay		Date Created: 22/09/2017
*/

#include <iostream>
#include <fstream>
using namespace std;

class time24
{
	private:
		int hour;
		int minute;
		
	public:
		int get_hour(void) const;
		int get_minute(void) const;
		
		void set_hour(int h);
		void set_minute(int m);
};

void write(ostream &out, const time24 &x);
time24 add(const time24 &x, const time24 &y);

int main(void)
{
	time24 x, y, z;
	
	x.set_hour(18);
	x.set_minute(34);
	
	y.set_hour(10);
	y.set_minute(56);
	
	cout << "The time x is: ";
	write(cout, x);
	
	cout << "\nThe time y is: ";
	write(cout, y);
	
	z = add(x, y);
	
	cout << "\nThe sum of ";
	write(cout, x);
	cout << " and ";
	write(cout, y);
	cout << " is ";
	write(cout, z);
	cout << endl;
	return 0;
}
/////////////////////// Methods of time24 ///////////////////////////
int time24::get_hour(void) const
{
	return hour;
}

int time24::get_minute(void) const
{
	return minute;
}

void time24::set_hour(int h)
{
	hour = h;
}

void time24::set_minute(int m)
{
	minute = m;
}

//////////////////////// time24 functions ////////////////////////

void write(ostream &out, const time24 &x)
{
	out << x.get_hour() << ":" << x.get_minute();
}

time24 add(const time24 &x, const time24 &y)
{
	time24 z;
	
	int m = x.get_minute() + y.get_minute();
	int h = x.get_hour() + y.get_hour();
	
	if(m >= 60)
	{
		m = m - 60;
		h = h + 1;
	}
	if(h >= 24)
	{
		h = h - 24;
	}
	
	z.set_hour(h);
	z.set_minute(m);
	
	return z;
}

