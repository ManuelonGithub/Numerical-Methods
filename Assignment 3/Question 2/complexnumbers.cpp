/*
 * File: complexnumbers.cpp
 *
 * Implement complex numbers as a class using operators
 *
 * Programmer: Manuel Burnay
 *
 * Date Created: 29/09/2017
 *
 * Last edit: 03/10/2017. Added Comments to the code
 */

#include <iostream>
#include <fstream>

using namespace std;

class complex
{
private:
    float x;        // real part
    float y;        // imaginary part
public:
    explicit complex(float re = 0.0, float im = 0.0);       // Class Constructor with default values

    float real(void) const  {return x;}         // return real part. Placed the method function here as well for simplicity
    float imag(void) const  {return y;}         // return imaginary part. Placed the method function here as well for simplicity
    void real(float re)     {x = re;}           // set real part. Placed the method function here as well for simplicity
    void imag(float im)     {y = im;}           // set imaginary part. Placed the method function here as well for simplicity
};

////////////////////// prototypes of complex operators //////////////////////

void operator >>(istream &in, complex &x);               // The 'in' operator. Dictates how to transfer input information to our class variable
void operator <<(ostream &out, const complex &x);        // The 'out' operator. Dictates how to output information from our variable to screen or file
complex operator +(const complex &x, const complex &y);  // The 'sum' operator. Dictates how we add two class variables together
complex operator -(const complex &x, const complex &y);  // The 'subtraction' operator. Dictates how we subtract two class variables together
complex operator *(const complex &x, const complex &y);  // The 'multiplication' operator. Dictates how we multiply two class variables together
complex operator /(const complex &x, const complex &y);  // The 'division' operator. Dictates how we divide two class variables together


int main(void)
{
    complex a, b, c;
    cout << "Enter two complex numbers in the form (re, im): ";     // Here is the 'in' operator in action
    cin >> a;       // The operators need to be separated like this or they won't work. (can't have cin >> a >> b)
    cin >> b;

    c = a + b;      //Here is the 'sum' operator in action
    cout << "The sum of ";
    cout << a;          // Here is the 'out' operator in action
    cout << " and ";
    cout << b;          // The operators need to be separated like this or they won't work. (can't have cout << a << (...) << b << (...) << c)
    cout << " is ";
    cout << c;
    cout << endl;

    c = a - b;      //Here is the 'subtraction' operator in action
    cout << "The difference of ";
    cout << a;
    cout << " and ";
    cout << b;
    cout << " is ";
    cout << c;
    cout << endl;

    c = a * b;      //Here is the 'multiplication' operator in action
    cout << "The product of ";
    cout << a;
    cout << " and ";
    cout << b;
    cout << " is ";
    cout << c;
    cout << endl;

    c = a / b;      //Here is the 'division' operator in action
    cout << "The division of ";
    cout << a;
    cout << " and ";
    cout << b;
    cout << " is ";
    cout << c;
    cout << endl;

    return 0;
}

///////////////////////// implementation of complex ////////////////////

complex::complex(float re, float im)        // Complex class Constructor
{
    x = re;
    y = im;
}

//////////////////////// implementation of complex operators /////////////

void operator >>(istream &in, complex &x)       // The 'in' operator. Dictates how to transfer input information to our class variable
{
    char discard;
    float re, im;
                                                            // We have the user input their values as '(real, imaginary)'
    in >> discard >> re >> discard >> im >> discard;        // As you see, there will be 3 char-types in their input that we don't need,
                                                            // therefore we assign them to a dummy variable to discard of them.\

    x.real(re);     //Sets the real part of the variable according to the input
    x.imag(im);     //Sets the imaginary part of the variable according to the input
}

void operator <<(ostream &out, const complex &x)        // The 'out' operator. Dictates how to output information from our variable to screen or file
{
    out << "(" << x.real() << "," << x.imag() << ")";       // Sets the output of the class variables as (real, imaginary)
}

complex operator +(const complex &x, const complex &y)        // The 'sum' operator. Dictates how we add two class variables together
{
    complex sum;

    sum.real(( x.real() + y.real() ));      // When adding two complex numbers, you add the real parts together,

    sum.imag(( x.imag() + y.imag() ));      // And the imaginary parts together

    return sum;
}

complex operator -(const complex &x, const complex &y)      // The 'subtraction' operator. Dictates how we subtract two class variables together
{
    complex diff;

    diff.real(( x.real() - y.real() ));     // Subtraction works like Addition, but you subtract instead of add

    diff.imag(( x.imag() - y.imag() ));

    return diff;
}

complex operator *(const complex &x, const complex &y)      // The 'multiplication' operator. Dictates how we multiply two class variables together
{
    complex pdt;
                                                                // When multiplying two complex numbers: (re1, im1) * (re2,im2) = re1*re2 (real value)+ im1*im2 (real value)+ re1*im2 (imag. value)+ im1*re2 (imag. value).
    pdt.real(( x.real()*y.real() - x.imag()*y.imag() ));        // im1*im2 will have i*i, which makes it a negative real value.

    pdt.imag(( x.real()*y.imag() + x.imag()*y.real() ));

    return pdt;
}

complex operator /(const complex &x, const complex &y)      // The 'division' operator. Dictates how we divide two class variables together (PS: <dividend>/<divisor>)
{
    complex div;                                                    // In complex division, you multiply the divisor and dividend by the divisor's conjugate.
                                                                    // this makes the divisor a real number,
                                                                    // that you can easily do division of complex numbers in rectangular form

    complex conj(y.real(), -y.imag());                              // Creating the conjugate of the divisor here, which is just inverting the imaginary part of the number

    float divisor = (( y.real()*y.real() + y.imag()*y.imag() ));    // Here I'm multiplying the divisor with the conjugate,
                                                                    // to create that real value that I will divide the dividend by

    div = x*conj;                           //You need to first multiply the dividend by the conjugate, in order to make this process valid
    div.real(( div.real()/divisor ));
    div.imag(( div.imag()/divisor ));

    return div;
}