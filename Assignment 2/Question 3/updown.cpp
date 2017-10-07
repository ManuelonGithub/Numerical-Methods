/* 
File: updown.cpp

Program to illustrate classes with a simple counter which counts to a
maximum value and then counts back down to zero at which point the
process repeats

Programmer:	Manuel Burnay		Date Created: 24/09/2017		Last Edit: 24/09/2017
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

/* this class represents a counter which counts up from 0 to max then back down to 0 and the process repeats */
class updown
{
private:
	int max; // count cycles between 0 and max
	int direction; // 1 means count up, 0 means count down
	int value; // this is the value stored in the counter
public:
	updown(int top); // constructor max is set to top
	void count(void); // increment or decrement value depending on direction
	int getvalue(void) const; // return value 
};

int main(void)
{	
	ofstream fout("updown.txt"); // prepare the output file

	updown c(7); // declare a counter object c
				 // the constructor updown(7) is called which sets
				 // c.value = 0, c.direction = 1 and c.max = 7 */

	int i;

	for (i = 1; i <= 18; i++) 
	{
		cout << "\nc.value = " << c.getvalue(); // display value
		fout << "\nc.value = " << c.getvalue(); // write value to fout
		c.count();
	}

	cout << endl;
	fout.close();

	system("updown.txt");

    return 0;
}

//////////////////////////// Method of updown //////////////////////////

updown::updown(int top)
{
	max = top;
	value = 0;
	direction = 1;
}

void updown::count(void)
{
	while (1)
	{
		if (direction == 1)
		{
			if (value < max)
			{
				value++;

				break;
			}

			else
			{
				direction = 0;
			}
		}

		if (direction == 0)
		{
			if (value > 0)
			{
				value--;

				break;
			}

			else
			{
				direction = 1;
			}
		}
	}
}

int updown::getvalue(void) const
{
	return value;
}