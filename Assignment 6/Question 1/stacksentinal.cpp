/*
 * File: stacksentinel.cpp
 * 
 * This program implements a simple stack of integers
 * using a linked list with a sentinel
 * 
 * Programmer: Manuel Burnay
 * 
 * Date Created: 21/10/2017
 * 
 * Last Edit: 24/10/2017
 */

#include <iostream>
#include <fstream>
using namespace std;

class node 
{
	friend class stack;	// stack needs access to node's members

	private:
		int data; 		// this is the data in a stack node
		node *next; 	// pointer to the next stack node

	public:
		node(int x);	// data = x, next = NULL
	};

	class stack 
	{
	private:
		node sentinel; // sentinel for the stack

	public:
		stack(void); 					// constructor
		void push(int x);				// Push method: Places a new node in the stack
		int pop(void);					// Pop method: Retrieves the data of the last placed node in the stack
		bool empty(void) const; 		// check for empty stack
		void write(ostream &out) const;	// write the stack to out
		void stackvalue(void) const;	// The data in the sentinel node relates to how many nodes are in the stack, and this methods prints that data to screen
};

int main()
{
	stack mystack;
	
	ofstream fout ("stacksentinelout.txt");

	char ch;		// Menu variable, the keyboard input gets placed into this variable to be compared to the menu options
	int x;			// Variable that either takes in a value inputted from the keyboard to be placed in the stack, or it takes a value from retrieved data in the stack

	cout << "A dynamic stack of integers\n";
	fout << "A dynamic stack of integers\n";

	do 
	{
		// print a little menu
		cout << "\n\np = push \n";
		cout << "o = pop\n";
		cout << "s = print to screen\n";
		cout << "f = print to file\n";
		cout << "q = quit\n";
		cout << "v = how many items in the stack\n\n";

		cin >> ch;

		if (ch == 'p')
		{
			cout <<"\ndata to push: ";
			cin >> x;
			mystack.push(x);
		}

		else if(ch == 'o') 
		{
			if(mystack.empty()) 
			{
				cout << "Stack is empty\n";
			} 

			else 
			{
				cout << "\n\ndata popped : " << mystack.pop();
			}
		}

		else if(ch == 's') { mystack.write(cout); }

		else if(ch == 'f') { mystack.write(fout); }

		else if(ch == 'v') { mystack.stackvalue(); }
	}
	while(ch != 'q');

	fout.close();
	return 0;
}

node::node(int x)	 // Node constructor
{
	data = x;		 // Takes in a int value to be placed in data 
	next = NULL;	 // Creates a pointer, which is set to NULL, but it's to point to the the latest existing node in the stack. The only node that remains pointing to NULL is the very first node created (bottom of the stack)
}

stack::stack() :sentinel(0)		// Stack constructor, simply creates the sentinel node
{}

/* 
	the push function takes an existing stack

	+------+ 	 +------+ 	  +------+ 			+------+
	| 0    | 	 | data | 	  | data |		    | data |
	+------+ 	 +------+ 	  +------+ 			+------+
	| next |---->| next |---->| next |----> ... | next |----> NULL
	+------+ 	 +------+ 	  +------+		    +------+
	sentinel 	  top of 					    bottom of
				  stack 						  stack

	ptr points to a new node object

			 +------+
			 |   x  |
	ptr ---->+------+
			 | next |
			 +------+

	then connect this new node into the list

	+------+ 	 +------+ 	  +------+			+------+
	|  0   | 	 |  x   | 	  | data | 			| data |
	+------+ 	 +------+	  +------+ 			+------+
	| next |---->| next |---->| next |----> ... | next |----> NULL
	+------+ 	 +------+ 	  +------+ 			+------+
	sentinel 	  new top      old top           bottom
*/

void stack::push(int x)			// Simple push method of a linked list type stack. Places a new node in the stack 
{
	node * ptr;					// Cretes a dummy pointer,
	ptr = new node(x);			// That creates a new node 

	ptr->next = sentinel.next;	// Makes the node's pointer point to the latest node in the stack (which is what the sentinel is pointing to)
	sentinel.next = ptr;		// Now sentinel points to the new node 

	sentinel.data++;			// Increments the sentinel data, that represents the amount of nodes in the stack
}

/* 
	The pop function takes an existing stack
	+------+ 	 +------+ 	  +------+ 			+------+
	|   0  | 	 | data | 	  | data | 			| data |
	+------+ 	 +------+ 	  +------+ 			+------+
	| next |---->| next |---->| next |----> ... | next |----> NULL
	+------+ 	 +------+ 	  +------+ 			+------+
	sentinel      top of                        bottom of
				   stack 						  stack

	and picks off the first node object to return it’s data

			 +------+
			 | 1st  |
	ptr ---->+------+
			 | next |
			 +------+

	then reassigns the next pointer to the second node

	+------+ 	 +------+ 		   +------+
	|  0   | 	 | 2nd  | 		   | data |
	+------+ 	 +------+ 		   +------+
	| next |---->| next |----> ... | next |---->NULL
	+------+ 	 +------+ 		   +------+
	sentinel 	  new top		    bottom
*/

int stack::pop(void)						// Simple pop method of a linked list type stack. Retrieves the data of the last placed node in the stack
{
	int temp = 0;							// Dummy variable take will take in the data of the latest node in the stack
	temp = sentinel.next->data;			

	node * ptr = sentinel.next;				// I believe this was to be used to determine where sentinel points to after poping a node, but it ends up unused <- LIE! this pointer deletes the node, as to prevent memory leakage

	sentinel.next = sentinel.next->next;	// Sentinel now points to the node that preceeded the popped node
	delete ptr;

	if(sentinel.data != 0)
	{
		sentinel.data--;					// Lowers the sentinel count to represent the current amount of nodes in the stack. It's within an if statement to ensure the count doesn't misalign by going under 0
	}

	return temp;
}
bool stack::empty(void) const // check for empty stack
{
	return(sentinel.next == NULL);
}

void stack::write(ostream &out) const // write the stack to out
{
	node * ptr = sentinel.next;		// Creates a dummy pointer that goes along the stack, node by node, until the bottom of the stack (which is a node pointing to NULL)

	while(ptr != NULL)
	{
		out << ptr->data << ", ";
		ptr = ptr->next;
	}

	out << endl;
}

void stack::stackvalue(void) const
{
	cout << "\n" << sentinel.data << " data sets in the stack" << endl;		// Prints of the total amount of nodes/data sets in the stack to the screen
}
