/* File: intializearraydefaults.cpp

This program uses a function with default arguments to initialize an array

Programmer: Manuel Burnay			Date: September 11th 2017			Last Edited: Sept. 18th 2017. Created Comments explaining the code
*/

#include <iostream>
#include <fstream>
using namespace std;

// Function prototypes 
float* init(int n = 1, float val = 0);		//This function comes with default values. This means that unless otherwise instructed, (i.e. arguments are included when function is called) the function will be executed with the values established in the prototype. therefore they're caleld default values	

int main(void)
{
	float * x;		// Dynamic allocated array pointer variable initialized --> b/c it's a DAA, the variable needs to be initialized as a pointer
	float val;		// Variable that dictates the value going into the array
	int n = 1;		// Varaible that dicates the size of the array
	
	x = init();		// Array initialization function called. No specified size or value. The returned value from this function will be passed to the array
	
	cout << "\nx = \n";			// Print out the contents of the array
	for(int i=0; i < n; i++) 
	{
		cout << x[i] << endl;
	}
	
	delete [] x;		// Delete the content inside the array
	
	n = 4;	
	
	x = init(n);		// Array initialization function called. Specified size, but no value. The returned value from this function will be passed to the array
	
	cout << "\nx = \n";			// Print out the contents of the array
	for(int i=0; i< n; i++)
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

float* init(int n, float val)		// Function that initializes a DAA. Has two parameters: n is the size of the array & val is the value to be placed in the array entries
{
		float *x;
	x = new float[n];		// Establishes the pointer variable as an array of size n
	
	for(int i=0;i<n;i++)		// Makes every entry of the array equal val
	{
		x[i] = val;
	}
	
	return x;		// The array created in the function gets passed to the array created in the main function (Not sure how this works due to being a pointer and all, but I feel that this is kind of unnecessary... not sure though, but this works and I don't care that much to try to figure it out. In the future I'm just gonna *& the array)
}
