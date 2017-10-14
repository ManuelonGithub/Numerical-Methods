// File: growingstack.cpp
// This program implements a simple stack of integers which grows as needed

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class stack
{
	private:
		int max; // maximum size of the stack
		int count; // number of items on the stack
		int grow; // data will grow by this amount when needed
		vector<int> data; // vector holding the stack items
	public:
		stack(int sz, int growsz); // constructor, max = sz, grow = growsz
		void push(int item); // push the integer item onto the stack
		int pop(void); // pop an item off the stack
		void write(ostream &out) const; // send the data stored to out
		bool empty(void) const; // check for empty stack
};

int main(void)
{
	stack s(5, 4);
	ofstream fout ("growingstackout.txt");

	for (int i=1; i <= 15; i++) 
	{
		s.push(i);
	}

	cout << "The stack is:\n";
	s.write(cout);

	fout << "The stack is:\n";
	s.write(fout);

	fout.close();
	return 0;
}

stack::stack(int sz, int growsz) : data(sz)
{
	max = sz;
	grow = growsz;
	count = 0; // the stack has no entries yet
}

bool stack::empty(void) const
{
	return (count == 0);
}

void stack::push(int item) // push the integer item onto the stack
{
	if(count >= max)
	{
		if(count < (max+grow))
		{
			data.resize(count, item);
			count++;
		}

		else
		{
			cout << "Stack is full!" << endl;
		}
	}

	else
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