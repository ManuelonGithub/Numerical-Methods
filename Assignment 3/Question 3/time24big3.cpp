/*
 * File: time24big3.cpp
 *
 * The class time24 represents time on 24 hour clock
 * Times are written to a stream in the form hour:minute
 * The big 3 methods are implemented
 *
 * Programmer: Manuel Burnay
 *
 * Date Created: 29/09/2017
 *
 * Last Edit: 03/10/2017. Added comments explaining some aspects of the code
 */


#include <iostream>
#include <fstream>

using namespace std;

class time24
{
private:
    int hour_; // hour between 0 and 23
    int minute_; // minute between 0 and 59

public:
    explicit time24(int h = 0 , int m = 0); // constructor with default args
    time24(const time24 &org);              // Copying constructor. This creates an object with the same parameters as an existing one
    ~time24();                              // Destructor
    time24& operator =(const time24 &rhs);  // Object assignment operator. This associates the values of an object (rhs) to an already created object

    void write(ostream& out) const;     // prints hour:minute to out
};


int main(void) // test the class
{
    time24 x(18, 34);
    time24 y(x);        // Here is the copying constructor in action
    time24 z;
    time24* p;

    p = new time24(5,8);
    cout << "The time x is: ";
    x.write(cout);

    cout << "The time y is: ";
    y.write(cout);

    cout << "The time z is: ";
    z.write(cout);

    cout << "The time *p is: ";
    p->write(cout);

    z = x = *p;                 // Assignment operator in action
    cout << "The time z is: ";
    z.write(cout);

    x = x; // nothing should be printed

    delete p;

    return 0;
}
//////////////////// Implementation of time24 ///////////////////////////
time24::time24(int h, int m)        // Class constructor
{
    hour_ = h;
    minute_ = m;
    cout << "constructing: ";
    write(cout);
}

time24::time24(const time24 &org)       // Copying constructor. This creates an object with the same parameters as an existing one (org)
{
    hour_ = org.hour_;
    minute_ = org.minute_;

    cout << "copying: ";
    org.write(cout);
}

time24::~time24()       // Destructor
{
    cout << "destroying: ";
    write(cout);
}

time24 &time24::operator=(const time24 &rhs)        // Object assignment operator. This associates the values of an object (rhs) to an already created object
{
    if( this != &rhs)
    {
        hour_ = rhs.hour_;
        minute_ = rhs.minute_;
    }

    cout << "Assigning: ";
    write(cout);

    return *this;
}

void time24::write(ostream& out) const      // prints hour:minute to out
{
    out << hour_ /10 << hour_ % 10 << ":" << minute_ / 10 << minute_ %10;

    out << " stored at address " << this << endl;       // 'this' is a hidden pointer found in every object created.
                                                        // It's like the array of the object, where it's associated to an address in the memory,
                                                        // and it points to all the values pertaining to the object.
}