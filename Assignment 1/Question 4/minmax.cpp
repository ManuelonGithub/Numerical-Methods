/* 
File: minmax.cpp

This program takes values from a text file, places them into a statically allocated array, 
then determines how many items entered the array, 
and the max and min values inside the array

Programmer: Manuel Burnay			Date Created: September 11th 2017			Last Edited: Sept. 18th 2017. Created Comments explaining the code 
*/

#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>

using namespace std;

const int N = 100; // Maximum array size i.e. It's a static array

// Function Prototypes
void readdata(int &n, float * x);						// NOTE: Having float * x or float x[] means the exact same thing. You can even use them interchangably. The more used format is * however.
void minmax(float * x, float &max, float &min, int n);

int main(void)
{
	ofstream outfile("minmaxout.txt"); // Creates an output file to write to
	
	float x[N];		// Static Array initialization
	int n;			// The number of of values going into the array
	float max;		 // The maximum value
	float min;		 // The minimum value
	
	readdata(n, x);		// Read the data into the array 
	
	minmax(x, max, min, n);		// Compute the maximum and minimum
	
	outfile << "The array has " << n << " elements\n";		// Prints out the number of elements in the array to the output file
	outfile << "The maximum value in the array is " << max << endl;		//  Prints out the max value in the array to the output file
	outfile << "The minimum value in the array is " << min << endl;		//  Prints out the min value in the array to the output file
	
	outfile.close();		// Closes the output file
	
	system("minmaxout.txt");		// Opens up the output file imidiately when the program ends
	
	return 0;
}


void readdata(int &n, float * x)		// Function reads file input file, registers the number of values in it, and transfers them into the array
{
	ifstream fin("minmax.txt");		// Prompts the input file to be read
	
	fin >> n;		// The first value in the file is the amount of values in the file itself. If this value didn't exist, the way to go about the code it to have (instead of the for loop): while( fin >> x[i]){i++;}, and then make n = i
	
	for(int i = 0; i < n; i++)		// For loop, that will scan through the values in the array
	{
		fin >> x[i];		// Value in the file being transfered to the array
	}
	
	fin.close();		// Closes the input file
}

void minmax(float * x, float &max, float &min, int n)		// Function that determines the min and max values of the array
{
	max = min = x[0];		// Establishes a baseline for these variables, so they have an initial value to compare the several values in the array to

	
	for(int i=0; i<n; i++)		// For loop to scan through all the values in the array
	{
		if(x[i] >= max)		// If a value in the array is bigger than the value stored in the 'max' variable
		{
			max = x[i];		// That value now gets stored in the 'max' variable
		}
		
		else if(x[i] < min)		// If a value in the array is smaller than the value stored in the 'min' variable
		{
			min = x[i];		// That value now gets stored in the 'min' varaible
		}
	}
}
