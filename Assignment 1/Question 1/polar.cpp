/* File: polar.cpp

This is a driver program for the function polar which computes the
polar coordinates of a point in the plane

Programmer: Manuel Burnay			Date Created: September 8th 2017			Last Edit: Sept. 18th 2017. Created comments explaining the code
*/

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

// Function prototypes
void polar(float x, float y, float &r, float &theta);

int main(void)
{
	// Declare variables
	float x, y, r, theta;
	
	// Open files for reading/writing
	ifstream fin ("polar.txt");			 // Open input files for reading
	
	ofstream fout ("Output.txt"); 		// Open output file for writing
	//read data from file
	
	while(fin >> x >> y) 				// Read x and y pairs from input file until EOF is reached (this is used when you don't know how many entries the file has)
	{
		// Call function polar to compute r and theta
		polar( x, y, r, theta);
		
		// Print r and theta into output file
		fout << "r = " << r << "\t \t" << "theta = " << theta << endl;
	}
	
	fin.close();		// Prompts the compiler to stop accessing the input file
	fout.close();		// Prompts the compiler to stop accessing the output file
	
	system("Output.txt");
	
	return 0;
}

// Function definition
void polar(float x, float y, float &r, float &theta)
{
	r = sqrt((x*x) + (y*y));		// Converts the rectangular coordinates into the radial distance. r^2 = x^2 + y^2
	if(r==0)
	{
		theta = 0;		// To determine theta when the coordinates are the origin
	}
	
	else if(r > 0 and y>0)		// To determine theta when we're on the upper portion of the unit circle
	{
		theta = acos(x/r);
	}
	
	else
	{
		theta = -acos(x/r);		// To determine theta when we're on the lower portion of the unit circle
	}
	
}
	
	
