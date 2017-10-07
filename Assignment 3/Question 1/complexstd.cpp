/*
 * File: complexstd.cpp
 *
 * Use the standard complex class
 *
 * Programmer: Manuel Burnay
 *
 * Date Created: 29/09/2017
 *
 * Last edit: 03/10/2017. Added Comments to the code
 *
 * */

#include <iostream>
#include <fstream>
#include <complex>      //Template class, which allows us to choose the type (int, float, etc) for the real and imaginary parts

using namespace std;

int main(void)
{
    complex<float> a, b, c;     // Here you see the above mentioned in play

    cout << "Enter two complex numbers in the form (re, im): ";     //The Library has dictated how the operators work (like >>, +, -, *, /)
    cin >> a >> b;

    c = a+b;
    cout << "The sum of " << a << " and " << b << " is " <<  c << endl;

    c = a-b;
    cout << "The difference of " << a << " and " << b << " is " <<  c << endl;

    c = a*b;
    cout << "The product of " << a << " and " << b << " is " <<  c << endl;

    c = a/b;
    cout << "The division of " << a << " and " << b << " is " <<  c << endl;

    return 0;
}