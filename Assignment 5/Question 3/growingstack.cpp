/* 
 * File: growingstack.cpp
 * 
 * This program implements a simple stack of integers which grows as needed
 * 
 * Programmer: Manuel Burnay
 * 
 * Date Created: 14/10/2017
 * 
 * Last Edit: 17/10/2017. Added comments explaining the code
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class stack
{
	private:
		int max; 			// maximum size of the stack
		int count; 			// number of items on the stack
		int grow; 			// data will grow by this amount when needed
		vector<int> data; 	// vector holding the stack items
		
	public:
		stack(int sz, int growsz); 			// constructor, max = sz, grow = growsz
		void push(int item); 				// push the integer item onto the stack
		int pop(void); 						// pop an item off the stack
		void write(ostream &out) const; 	// send the data stored to out
		bool empty(void) const; 			// check for empty stack
};

int main(void)
{
	stack s(5, 4); 		// Growing stack initialization. its default size is 5, but it can grow up to 9 (5+4)
	
	ofstream fout ("growingstackout.txt");		// Output file creation

	for (int i=1; i <= 15; i++) 	// For-loop at inserts 15 values (1 to 15) into the stack 
	{
		s.push(i);
	}

	cout << "The stack is:\n";		// Prints stack to the screen
	s.write(cout);

	fout << "The stack is:\n";		// Prints stack to the output file
	s.write(fout);

	fout.close();
	return 0;
}

stack::stack(int sz, int growsz) : data(sz)		// constructor, max = sz, grow = growsz. When using the STL library for vectors, you need to initialize the initial vector size like it's a composite class
{
	max = sz;
	grow = growsz;
	count = 0; 		// the stack has no entries yet
}

bool stack::empty(void) const		// check for empty stack. Will be True if the queue is empty
{
	return (count == 0);
}

void stack::push(int item) // push the integer item onto the stack
{
	if(count >= max)		// When we need to increase the stack beyond its default size (i.e. when main is trying to push values after no. 5)
	{
		if(count < (max+grow))		// The stack will not go beyond its growth size
		{
			data.resize(count, item);		// The way resize works is that it will increase the vector by [count - <vector's current size>], and it will place the 'item' data into each one of those added spaces
			count++;
		}

		else
		{
			cout << "Stack is full!" << endl;
		}
	}

	else		// Simple way you push values into a stack
	{
		data[count] = item;
		count++;
	}

	cout << count << endl;
}

int stack::pop(void) // pop an item off the stack
{
	count--;
	return data[count];
}

void stack::write(ostream &out) const // send the data stored to out
{
	for(int i=0; i <(count-1); i++)
	{
		out << data[i] << ", ";
	}

	out << endl;
}
