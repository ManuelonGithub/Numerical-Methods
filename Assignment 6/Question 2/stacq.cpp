
/*
 * File: stacq.cpp
 * 
 * This program implements a cross between a stack and a queue
 * 
 * Programmer: Manuel Burnay
 *
 * Date Created: 21/10/2017
 * 
 * Last Edit: 21/10/2017
 */

#include <iostream>
#include <fstream>
using namespace std;

class node
{
	friend class stacq;

	private:
		int data; 		// this is the data in a stacq element
		node *next; 	// pointer to the next node on the stack

	public:
		node(int x) {data = x; next = NULL;}
};

class stacq
{
	private:
		node sentinel;						// I noticed that a sentinel node would operate just like this count variable + top pointer did, so I used what I learned in the previous exercise and use a sentinel node instead

	public:
		stacq(void); 						// constructor of an empty stacq
		void store(int x); 					// store the value x
		int retrieve(void); 				// retrieve a value
		bool empty(void) const; 			// check for empty stack
		void write(ostream &out) const; 	// write stacq to out
};

/*
	A stacq looks like

	count =
			 +------+ 	  +------+	   +------+ 		 +------+
			 | data | 	  | data | 	   | data | 		 | data |
	top ---> +------+ 	  +------+ 	   +------+			 +------+
			 | next |---->| next |---->| next |----> ... | next |---->NULL
			 +------+ 	  +------+	   +------+ 		 +------+
*/

int main()
{
	stacq mine;
	ofstream fout ("stacqout.txt");
	
	char ch;		// Menu variable, the keyboard input gets placed into this variable to be compared to the menu options
	int x;			// Variable that either takes in a value inputted from the keyboard to be placed in the stack, or it takes a value from retrieved data in the stack

	cout << "A dynamic stacq of integers\n";
	fout << "A dynamic stacq of integers\n";

	do
	{
		// print a little menu
		cout << "\n\ns = store \n";
		cout << "r = retrieve\n";
		cout << "p = print to screen\n";
		cout << "f = print to file\n";
		cout << "q = quit\n\n";

		cin >> ch;

		if (ch == 's')
		{
			cout <<"\ndata to store :";
			cin >> x;
			mine.store(x);
		}

		else if(ch == 'r') 
		{
			if(mine.empty())
				cout << "empty\n";

			else
				cout << "\n\ndata retrieved :" << mine.retrieve();
		}

		else if(ch == 'p') mine.write(cout);

		else if(ch == 'f') mine.write(fout);
	}
	while(ch != 'q');

	fout.close();
	return 0;
}

stacq::stacq(void) :sentinel(0) // constructor of an empty stacq. The data inside the sentinel node will store the stacq count, and the pointer will point to the latest node inserted in the stacq
{}

void stacq::store(int x) // store the value x. Operates like a push menthod in a linked list stack type
{
	node * ptr;					// Cretes a dummy pointer,
	ptr = new node(x);			// That creates a new node 

	ptr->next = sentinel.next;	// Makes the node's pointer point to the latest node in the stacq (which is what the sentinel is pointing to)
	sentinel.next = ptr;		// Now sentinel points to the new node 

	sentinel.data++;			// Increments the sentinel data, that represents the amount of nodes in the stac1
}

int stacq::retrieve(void) // retrieve a value. The way a stacq operates is that it will alternate between getting the newest node stored, or the oldest one. The way it's set up is if the total amount of nodes in the stacq is odd, then it will take the newest data stored, and it'll take the oldest if the total amount of nodes is even
{
	int temp = 0;					// Dummy variable take will take in the data of the latest node in the stack
	node * ptr = sentinel.next;		// Here this pointer does serve a purpose: When the Node amount is even, this pointer goes down the line to the oldest node in it and retrieves its value 


	if((sentinel.data%2) == 0 && sentinel.next != NULL)		// If the Node amount is even
	{
		node * cutter = sentinel.next;		// Aptly named cutter, it cuts off the last node from the stacq (the node whose data is being retrieved)

		while(ptr->next != NULL)	// ptr goes down the stacq until it reaches the oldest node in the stacq
		{
			cutter = ptr;
			ptr = ptr->next;
		}

		cutter->next = NULL;	// Cutter then points to the node preceeds that node, and has it point to NULL, thus cutting that last node off the stacq
		temp = ptr->data;		// temp then equals the data inside the node
	}

	else if((sentinel.data%2) == 1 && sentinel.next != NULL)	// If the Node amount is odd
	{
		temp = sentinel.next->data;		// temp equals the data of the latest node inserted into the stacq
		
		node * ptr = sentinel.next;

		sentinel.next = sentinel.next->next;	// That node is then cut off the stacq, but having sentinel point to the following node
	}

	delete ptr;		// the node that got cut off from the stacq (regardless if it's the top of bottom node) gets deleted

	if(sentinel.data != 0)
	{
		sentinel.data--;	// the node amount then gets decremented
	}

	return temp;	// data from the node gets retrieved back to main
}

bool stacq::empty(void) const // check for empty stack
{
	return(sentinel.next == NULL);
}

void stacq::write(ostream &out) const // write stacq to out
{
	node * ptr = sentinel.next;		 // Creates a dummy pointer that goes along the stack, node by node, until the bottom of the stack (which is a node pointing to NULL)

	while(ptr != NULL)
	{
		out << ptr->data << ", ";
		ptr = ptr->next;
	}

	out << endl;
}
