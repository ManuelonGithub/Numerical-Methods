
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
		int data; // this is the data in a stacq element
		node *next; // pointer to the next node on the stack

	public:
		node(int x) {data = x; next = NULL;}
};

class stacq
{
	private:
		node sentinel;	// The data inside the sentinel node will store the stacq count

	public:
		stacq(void); // constructor of an empty stacq
		void store(int x); // store the value x
		int retrieve(void); // retrieve a value
		bool empty(void) const; // check for empty stack
		void write(ostream &out) const; // write stacq to out
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
	char ch;
	int x;

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

stacq::stacq(void) :sentinel(0) // constructor of an empty stacq
{
}

void stacq::store(int x) // store the value x
{
	node * ptr;
	ptr = new node(x);

	ptr->next = sentinel.next;
	sentinel.next = ptr;

	sentinel.data++;
}

int stacq::retrieve(void) // retrieve a value
{
	int temp = 0;
	node * ptr = sentinel.next;


	if((sentinel.data%2) == 0 && sentinel.next != NULL)
	{
		node * cutter = sentinel.next;

		while(ptr->next != NULL)
		{
			cutter = ptr;
			ptr = ptr->next;
		}

		cutter->next = NULL;
		temp = ptr->data;
	}

	else if((sentinel.data%2) == 1 && sentinel.next != NULL)
	{
		temp = sentinel.next->data;
		
		node * ptr = sentinel.next;

		sentinel.next = sentinel.next->next;
	}

	delete ptr;

	if(sentinel.data != 0)
	{
		sentinel.data--;
	}

	return temp;
}

bool stacq::empty(void) const // check for empty stack
{
	return(sentinel.next == NULL);
}

void stacq::write(ostream &out) const // write stacq to out
{
	node * ptr = sentinel.next;

	while(ptr != NULL)
	{
		out << ptr->data << ", ";
		ptr = ptr->next;
	}

	out << endl;
}