/* File: intializearray.cpp

This program uses a number of different functions to initialize an 
dynamically allocated array

Programmer: Manuel Burnay			Date Created: September 11th 2017			Last Edited: Sept. 18th 2017. Created comments explaining the code
*/

#include <iostream>
#include <fstream>
using namespace std;

// Function prototypes 
float* init();
float* init(int n);
float* init(int n, float val);

int main(void)
{
	float *x;		// Array initialization. Because it's dynamically allocated, it needs to be initialized as a pointer
	float val;		// Variable that dictates the value going into the array
	int n;			// Varaible that dicates the size of the array
	
	n = 1;
	
	x = init();		// Array initialization function called. No specified size or value. The returned value from this function will be passed to the array
	
	cout << "\nx = \n";		// Print out the contents of the array
	for(int i=0; i< n; i++) 
	{
		cout << x[i] << endl;
	}
	
	delete [] x;		// Delete the content inside the array
	
	n = 4;
	
	x = init(n);		// Array initialization function called. Specified size, but no value. The returned value from this function will be passed to the array
	
	cout << "\nx = \n";			// Print out the contents of the array
	for(int i=0; i < n; i++)
	{
		cout << x[i] << endl;
	}
	
	delete [] x;		// Delete the content inside the array
	
	n = 5;
	val = 1.27;
	
	x = init(n, val);		// Array initialization function called. Has a specified size and value. The returned value from this function will be passed to the array
	
	cout << "\nx = \n";			// Print out the contents of the array
	for(int i=0; i< n; i++) 
	{
		cout << x[i] << endl;
	}

	delete [] x;		// Delete the content inside the array
	return 0;
}

float* init()		// Function that doesn't take a specific array size or value to put into the array
{
	float *x;
	x = new float[0];		// Establishes the pointer variable as an array of size 0, since it had no specific size
	x[0] = 0;			// since it has no value to put into the array, it just makes the single entry of the array equal 0
	
	return x;		// returns the array because it wasn't passed to the function
}

float* init(int n)		// Function that takes a specific array size, but no value to put into the array
{
	float *x;
	x = new float[n];		// Establishes the pointer variable as an array of size n
	
	for(int i=0;i<n;i++)		// since it has no value to put into the array, it just makes all the array entries equal 0
	{
		x[i] = 0.0;
	}
	
	return x;		// returns the array because it wasn't passed to the function
}

float* init(int n, float val)		// Function that takes both an array size and a specific value to put into the array
{
		float *x;
	x = new float[n];		// Establishes the pointer variable as an array of size n
	
	for(int i=0;i<n;i++)		// As per request of the exercise, it makes every array entry equal val
	{
		x[i] = val;
	}
	
	return x;		// returns the array because it wasn't passed to the function
}
