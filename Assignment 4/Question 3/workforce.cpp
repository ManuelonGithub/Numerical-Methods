/* 
 * File: workforce.cpp
 * 
 * An employee’s information is stored as an object of type employee
 * consisting of name, employee id and employee salary. The methods
 * read() and write() are defined for employee.
 * 
 * workforce consisting of the workforce size and a dynamically allocated
 * array of employees. The methods read() and write() are defined for
 * workforce
 * 
 * The read() and write methods for workforce uses the read() and write()
 * methods for employee
 * 
 * Programmer: Manuel Burnay
 * 
 * Date Created: 08/10/2017
 * 
 * Last Edit: 10/10/2017. Added comments explaining the code
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class employee 			// Class that relates to an employee's information
{
	private:
		string name; 	// last name
		int id; 		// employee id number
		float salary; 	// employee salary

	public:
		employee(string n = "nobody", int i = 0, float s = 0); 	// Employee constructor with default values. You need default values in order to create arrays of these objects
		void read(istream &in); 								// Takes in employee information of an employee from a text file record
		void write(ostream &out) const; 						// Prints out the employee information
};

class workforce 	// Class that relates to an Employee's information record (i.e. workforce record)
{
	private:
		int size; 		// size of workforce
		employee* list; // array of employees

	public:
		workforce(int n); 							// Workforce constructor. size = n and allocates an array of employees with this size
		workforce(const workforce& other); 			// Workforce constructor. This constructors copies the information of a workforce record into a new record
		~workforce(); 								// Workforce destructor. Important to have it since this class contains pointers
		workforce& operator=(const workforce& rhs); // Workforce assignment operator. Assigns the information inside a workforce record into a pre-exisiting record
		void read(istream &in); 					// Reads the information of all employees from a text file record
		void write(ostream &out) const; 			// Prints out the whole Workforce record
};

int main(void)
{
	workforce w(5); 	// While the class is set up to have a dynamic allocated record, we have pre-determined size set up

	ifstream fin("workforcein.txt"); 	// file containing the list of employees adn their information
	ofstream fout("workforceout.txt"); 	// Output file

	char ch;

	w.read(fin);
	fout << "\nw = \n";
	w.write(fout);

	cout << "C to copy otherwise assign: ";
	cin >> ch;

	if(ch == 'C')
	{
		workforce v(w); // v’s scope is the body of the if
		fout << "\nv = \n";
		v.write(fout);
		// v is destroyed here
	}

	else
	{
		workforce u(10); // u’s scope is the body of the else
		u = w;
		fout << "\nu = \n";
		u.write(fout);
		// u is destroyed here
	}

	fout << "\nw = \n"; // check whether w is still intact
	w.write(fout);

	fin.close();
	fout.close();

	return 0;
}

////////////////////// implementation of employee ////////////////////////

employee::employee(string n, int i, float s) 	// Employee constructor with default values. name = n, id = i, salary = s
{
	name = n;
	id = i;
	salary = s;
}

void employee::read(istream &in) 	// Takes in employee information of an employee from a text file record
{
	in >> name >> id >> salary;
}

void employee::write(ostream &out) const 	// Prints out the employee information
{
	out << name << " " << id << " " << salary << endl;
}

/////////////////////// implementation of workforce //////////////////////

workforce::workforce(int n) 	// Workforce constructor. size = n and allocates an array of employees with this size
{
	size = n;
	list = new employee[size]; 	// Note to self: You may think you can save memory by instead having (size-1) as your array size, but instead you'll break the whole code
}

workforce::workforce(const workforce& other) 	// Workforce constructor. This constructors copies the information of a workforce record into a new record
{
	size = other.size;
	list = new employee[size];

	for(int i = 0; i < size; i++)
	{
		list[i] = other.list[i];
	}
}
workforce::~workforce() 	// Workforce destructor. Important to have it since this class contains pointers
{
	delete [] list;
}

workforce& workforce::operator=(const workforce& rhs) 	// Workforce assignment operator. Assigns the information inside a workforce record into a pre-exisiting record
{
	if(this != &rhs) 	// To make sure we're not assigning  a variable to itself (things might get ugly if so)
	{
		for(int i = 0; i < rhs.size; i++)
		{
			list[i] = rhs.list[i];
		}
	}

	return *this; 	// Returns the data that 'this' is pointing to
}

void workforce::read(istream &in) 	// Reads the information of all employees from a text file record
{
	for(int i = 0; i < size; i++)
	{
		list[i].read(in);
	}
}
void workforce::write(ostream &out) const 	// Prints out the whole Workforce record
{
	for(int i = 0; i < size; i++)
	{
		list[i].write(out);
	}
}