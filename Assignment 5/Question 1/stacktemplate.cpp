/*
 * File: stacktemplate.cpp
 * 
 * This program implements a stack template class
 *
 * Programmer: Manuel Burnay
 *
 * Date Created: 13/10/2017
 *
 * Last Edit: 17/10/2017. Added comments explaining the code
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

template <class T>		// Initializing a template class. You need this when you can't specify the data type you're utilizing in your class 
class stack
{
	private:
		int max; 			// maximum size of the stack
		int count; 			// number of items on the stack
		vector<T> data; 	// vector holding the stack items
		
  	public:
		  stack(int sz); 						// constructor, max = sz
		  void push(const T &item); 			// push a copy of item onto the stack
		  T &pop(void); 						// pop an item off the stack
		  void write(ostream &out) const; 		// send the data stored to out
		  bool empty(void) const; 				// check for empty stack
		  bool full(void) const; 				// check for full stack
};
int main(void)
{
	stack<string> mystack(5);			// A stack of strings of with size 5. Also indicates that our data type will be, in fact, a string
	ofstream fout ("stackout.txt");		// Output file creation

	char ch;		// Menu character variable. Its contents pertain to the lastest input from the user
	string x;		// Placeholder variable for when the user inputs the data to be pushed to the stack, or when the user recovers data from the stack

	while(1)		// Text-based Menu system, in order to give us proper commands to manipulate the stack
	{
		cout << "\n\np = push \n";
		cout << "o = pop\n";
		cout << "s = print to screen\n";
		cout << "f = print to file\n";
		cout << "q = quit\n\n";cin >> ch;

		if (ch == 'p')		// Push command. It inserts data into the stack
		{
			cout <<"\ndata to push :";		// Prompt for the user to input data
			cin >> x;

			if(mystack.full())
			{
				cout << "Stack is full" << endl;		// Checks if the stack is full. If it is, the user won't be allowed to insert the data just inputted
			}

			else
			{
				mystack.push(x);
			}
		}

		else if(ch == 'o')		// Pop command. It recovers data from the stack to be utilized
		{
			if(mystack.empty())
			{
			cout << "Stack is empty" << endl;		// Checks if the stack is empty. If it is, the user won't be allowed to recover any data from it
		}

			else
			{
				x = mystack.pop();
				cout << "\n\ndata popped : " << x;
				}
		}

		else if(ch == 's')		// Print-to-screen command
		{
			mystack.write(cout);
		}

		else if(ch == 'f')		// Print-to-file command
		{
			mystack.write(fout);
		}

		else if(ch == 'q')		// Command to break the menu loop, and to exit the process
		{
			break;
		}
	}

	fout.close();

	return 0;
}

template <class T>						// When creating a class template, you require this indication for every method pertaining to the class (when you have the method functions outside of the class initialization at least)
stack<T>::stack(int sz) :data(sz) 		// constructor, initializes the max size of our data structure
{
	max = sz;
	count = 0;
}

template <class T>
void stack<T>::push(const T& item) 		// push a copy of item onto the stack
{
	data[count] = item;
	count++;
}

template <class T>
T& stack<T>::pop(void)		// pop an item off the stack
{
	count--;
	return data[count];
}

template <class T>
void stack<T>::write(ostream &out) const 	// send the data stored to out (same process between print-to-screen and print-to-file, but 'out' will be directed differently)
{
	for(int i=0; i < count; i++)
	{
		out << data[i] << ", ";
	}

	out << endl;
}

template <class T>
bool stack<T>::empty(void) const 	// check for empty stack
{
	return(count ==0);
}

template <class T>
bool stack<T>::full(void) const 	// check for full stack
{
	return(count == max);
}
