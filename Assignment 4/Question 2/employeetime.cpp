/* File: employeetime.cpp
 * 
 * Illustrates composition of classes
 * 
 * Programmer: Manuel Burnay
 * 
 * Date Created: 08/10/2017
 * 
 * Last Edit: 10/10/2017. Added comments explaining the code
 */


#include <iostream>
#include <string>
using namespace std;

class time24 			// Class that relates to time in 24H format
{
	private:
		int hour_;		// Hour between 0 and 23
		int minute_;	// mHinute between 0 and 59

	public:
		time24(int h, int m); 				// time24 constructor. hour_ = h & minute_ = m
		void write(ostream &out) const;		// Prints our time24 as hour_:minute_
};

class employee 			// Class that relates to an employee's information
{
	private:
		string name;	// Last name
		int id;			// Employee id number
		float salary;	// Employee salary
		time24 start;	// Workday start time

	public:
		employee(string n, int i, float s, const time24 &t); 	// Employee constructor. Takes its Workday start time as variable initialized beforehand
		employee(string n, int i, float s, int h, int m); 		// Employee constructor. Takes its Workday start time as hour and minute values instead of a variable initialized beforehand
		void write(ostream &out) const; 						// Prints out Employee as {Name, ID, Salary, Workday start time}
};

int main(void)
{
	time24 u(8, 0);
	employee x("Jones", 123, 45000.0, u);
	employee y("Smith", 124, 50000.0, 8, 30);

	cout << "x = "; x.write(cout); cout << endl;

	cout << "y = "; y.write(cout); cout << endl;

	return 0;
}

//////////////////// Implementation of time24 ///////////////////////////

time24::time24(int h, int m) 	// time24 constructor. hour_ = h & minute_ = m
{
	hour_ = h;
	minute_ = m;
}

void time24::write(ostream &out) const 	// Prints our time24 as hour_:minute_
{
	out << hour_ /10 << hour_ % 10 << ":" << minute_ / 10 << minute_ %10;
}

////////////////////// implementation of employee /////////////////////

employee::employee(string n, int i, float s, const time24 &t) :start(t) 	// Again before start is a class type variable, it can't be included inside the constructor's body
{
	name = n;
	id = i;
	salary = s;
}

employee::employee(string n, int i, float s, int h, int m) :start(h,m) 		// This is another way to initialize a class parameter that is a class variable, which is to assign values that the class variable needs to initialize
{
	name = n;
	id = i;
	salary = s;
}

void employee::write(ostream &out) const 	// Prints out Employee as {Name, ID, Salary, Workday start time}
{
	out << "{" << name << ", " << id << ", " << salary << ", ";
	start.write(out);
	out << "}";
}