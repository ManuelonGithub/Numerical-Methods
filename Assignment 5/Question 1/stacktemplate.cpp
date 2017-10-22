/*
 * File: stacktemplate.cpp
 * This program implements a stack template class
 *
 * Programmer: Manuel Burnay
 *
 * Date Created: 13/10/2017
 *
 * Last Edit: 13/10/2017
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

template <class T>
class stack
{
	private:
		int max; // maximum size of the stack
		int count; // number of items on the stack
		vector<T> data; // vector holding the stack items
  	public:
		  stack(int sz); // constructor, max = sz
		  void push(const T &item); // push a copy of item onto the stack
		  T &pop(void); // pop an item off the stack
		  void write(ostream &out) const; // send the data stored to out
		  bool empty(void) const; // check for empty stack
		  bool full(void) const; // check for full stack
};
int main(void)
{
	stack<string> mystack(5);
	ofstream fout ("stackout.txt");

	char ch;
	string x;

	while(1)
	{
		cout << "\n\np = push \n";
		cout << "o = pop\n";
		cout << "s = print to screen\n";
		cout << "f = print to file\n";
		cout << "q = quit\n\n";cin >> ch;

		if (ch == 'p')
		{
			cout <<"\ndata to push :";
			cin >> x;

			if(mystack.full())
			{
				cout << "Stack is full" << endl;
			}

			else
			{
				mystack.push(x);
			}
		}

		else if(ch == 'o')
		{
			if(mystack.empty())
			{
			cout << "Stack is empty" << endl;
		}

			else
			{
				x = mystack.pop();
				cout << "\n\ndata popped : " << x;
				}
		}

		else if(ch == 's')
		{
			mystack.write(cout);
		}

		else if(ch == 'f')
		{
			mystack.write(fout);
		}

		else if(ch == 'q')
		{
			break;
		}
	}

	fout.close();

	return 0;
}

template <class T>
stack<T>::stack(int sz) :data(sz)// constructor, max = sz
{
	max = sz;
	count = 0;
}

template <class T>
void stack<T>::push(const T& item) // push a copy of item onto the stack
{
	data[count] = item;
	count++;
}

template <class T>
T& stack<T>::pop(void) // pop an item off the stack
{
	count--;
	return data[count];
}

template <class T>
void stack<T>::write(ostream &out) const // send the data stored to out
{
	for(int i=0; i < count; i++)
	{
		out << data[i] << ", ";
	}

	out << endl;
}

template <class T>
bool stack<T>::empty(void) const // check for empty stack
{
	return(count ==0);
}

template <class T>
bool stack<T>::full(void) const // check for full stack
{
	return(count == max);
}