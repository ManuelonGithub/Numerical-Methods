/*
 * File: deque.cpp
 *
 * This program implements a double ended queue of integers as a
 * integers as adoubly linked list
 *
 * Programmer: Manuel Burnay
 *
 * Date Created: 21/10/2017
 *
 * Last Edit: 22/10/2017
 */

#include <iostream>
#include <fstream>
using namespace std;

class node
{
	friend class deque;

	private:
		int data; // this is the data in a list element
		node *next; // pointer to the next node in the list
		node *prev; // pointer to the previous node in the list

	public:
		node(int x); // data = x, prev=next = NULL
};

class deque
{
private:
	node* front; // pointer to the front of the list
	node* back; // pointer to the back of the list

public:
	deque(void); // constructor of an empty queue
	void put_front(int x); // put x at the front of the list
	void put_back(int x); // put x at the back of the list
	int get_front(void); // get the node at the front of the list
	int get_back(void); // get the node at the back of the list
	bool empty(void) const; // check for empty deque
	void write(ostream &out) const; // write data stored to out
};

/*
	A deque looks like

		     +------+ 	  +------+ 	   +------+ 		 +------+
		     | data | 	  | data | 	   | data | 		 | data |
		     +------+  	  +------+ 	   +------+ 		 +------+
		   	 | next |---->| next |---->| next |----> ... | next |---->NULL
	NULL<----| prev |<----| prev |<----| prev |... <---- | prev |
			 +------+ 	  +------+ 	   +------+ 		 +------+
				^ 											^
				| 											|
				| 											|
			   back 					  				  front
*/
int main()
{
	deque mydeque;
	ofstream fout ("dequeout.txt");
	char ch;
	int x;

	cout << "A dynamic deque of integers\n";
	fout << "A dynamic deque of integers\n";

	do
	{
		// print a little menu
		cout << "\n\n1 = put front \n";
		cout << "2 = put back \n";
		cout << "3 = get front\n";
		cout << "4 = get back\n";
		cout << "s = print to screen\n";
		cout << "f = print to file\n";
		cout << "q = quit\n\n";
		cin >> ch;

		if (ch == '1')
		{
			cout <<"\ndata to put front:";
			cin >> x;
			mydeque.put_front(x);
		}

		else if (ch == '2')
		{
			cout <<"\ndata to put back:";
			cin >> x;
			mydeque.put_back(x);
		}

		else if(ch == '3')
		{
			if(mydeque.empty())
			{
				cout << "deque is empty\n";
			}

			else
			{
				cout << "\n\ndata gotten : " << mydeque.get_front();
			}
		}

		else if(ch == '4')
		{
			if(mydeque.empty())
			{
				cout << "deque is empty\n";
			}

			else
			{
				cout << "\n\ndata gotten : " << mydeque.get_back();
			}
		}

		else if(ch == 's') mydeque.write(cout);

		else if(ch == 'f') mydeque.write(fout);
	}
	while(ch != 'q');

	fout.close();

	return 0;
}

node::node(int x)
{
	data = x;
	next = NULL;
	prev = NULL;
}

deque::deque(void) // constructor of an empty queue
{
	front = NULL;
	back = front;
}

/*
	the put_back function takes an existing deque

			  +------+ 	   +------+ 		 +------+
			  | last | 	   | data | 		 | 1st  |
			  +------+ 	   +------+ 		 +------+
			  | next |---->| next |----> ... | next |---->NULL
	NULL<---- | prev |<----| prev |<---- ... | prev |
			  +------+ 	   +------+ 		 +------+
				^ 								^
				| 								|
				| 								|
			   back 						  front

	ptr points to a new node

			 +------+
			 |  x   |
	ptr ---->+------+
			 | next |
			 | prev |
			 +------+

	then connect this new node into the list

			 +------+ 	  +------+ 	   +------+ 		 +------+
			 |  x   | 	  | last | 	   | data |			 | 1st  |
			 +------+ 	  +------+	   +------+ 		 +------+
			 | next |---->| next |---->| next |----> ... | next |---->NULL
	NULL<----| prev |<----| prev |<----| prev |<---- ... | prev |
			 +------+ 	  +------+ 	   +------+		 	 +------+
				^ 											^
				| 											|
				| 											|
			   back 									  front
*/

void deque::put_back(int x) // put x at the back of the list
{
	node * ptr;
	ptr = new node(x);

	ptr->next = back;
	ptr->prev = NULL;

    if(back == NULL)
    {
        front = ptr;
    }

    else
    {
        back->prev = ptr;
    }

	back = ptr;
}

/*
	the put_front function takes an existing deque

			  +------+ 	   +------+ 		 +------+
			  | last | 	   | data | 		 | 1st  |
			  +------+ 	   +------+ 		 +------+
			  | next |---->| next |----> ... | next |---->NULL
	NULL<---- | prev |<----| prev |<---- ... | prev |
			  +------+ 	   +------+ 		 +------+
				^ 								^
				| 								|
				| 								|
			   back 						  front

	ptr points to a new node

			 +------+
			 |  x   |
	ptr ---->+------+
			 | next |
			 | prev |
			 +------+

	then connect this new node into the list

			 +------+ 	  +------+ 	  	    +------+ 	 +------+
			 | last | 	  | data | 	   	    | 1st  |	 |  x   |
			 +------+ 	  +------+	   	    +------+ 	 +------+
			 | next |---->| next |----> ... | next |---->| next |---->NULL
	NULL<----| prev |<----| prev | ... <----| prev |<----| prev |
			 +------+ 	  +------+ 	   	    +------+	 +------+
				^ 											^
				| 											|
				| 											|
			   back 								  	  front

*/

void deque::put_front(int x) // put x at the front of the list
{
	node * ptr;
	ptr = new node(x);

	ptr->next = NULL;
	ptr->prev = front;

    if(front == NULL)
    {
        back = ptr;
    }

    else
    {
        front->next = ptr;
    }

	front = ptr;
}

/*
	The get_front function takes an existing deque

			 +------+ 	  +------+ 	  	    +------+ 	 +------+
			 | last | 	  | data | 	   	    | 2nd  |	 | 1st  |
			 +------+ 	  +------+	   	    +------+ 	 +------+
			 | next |---->| next |----> ... | next |---->| next |---->NULL
	NULL<----| prev |<----| prev | ... <----| prev |<----| prev |
			 +------+ 	  +------+ 	   	    +------+	 +------+
				^ 											^
				| 											|
				| 											|
			   back 								  	  front

	and picks off the first data node to be returned

			 +------+
			 | 1st  |
	ptr ---->+------+
			 | next |
			 | prev |
			 +------+

	then reassigns the front pointer

			  +------+ 	   +------+ 		 +------+
			  | last | 	   | data | 		 | 2nd  |
			  +------+ 	   +------+ 		 +------+
			  | next |---->| next |----> ... | next |---->NULL
	NULL<---- | prev |<----| prev |<---- ... | prev |
			  +------+ 	   +------+ 		 +------+
				^ 								^
				| 								|
				| 								|
			   back 						  front
*/

int deque::get_front(void) // get the node at the front of the list
{
	int temp = 0;
	temp = front->data;

	node * ptr = front;

	front = front->prev;

	delete ptr;

	return temp;
}

/*
	The get_back function takes an existing deque

			 +------+ 	  +------+ 	   +------+ 		 +------+
			 | last | 	  | 2nd  | 	   | data |			 | 1st  |
			 +------+ 	  +------+	   +------+ 		 +------+
			 | next |---->| next |---->| next |----> ... | next |---->NULL
	NULL<----| prev |<----| prev |<----| prev |<---- ... | prev |
			 +------+ 	  +------+ 	   +------+		 	 +------+
				^ 											^
				| 											|
				| 											|
			   back 									  front

	and picks off the last data node to be returned

			 +------+
			 | last |
	ptr ---->+------+
			 | next |
			 | prev |
			 +------+

	then reassigns the back pointer

			  +------+ 	   +------+ 		 +------+
			  | 2nd  | 	   | data | 		 | 1st  |
			  +------+ 	   +------+ 		 +------+
			  | next |---->| next |----> ... | next |---->NULL
	NULL<---- | prev |<----| prev |<---- ... | prev |
			  +------+ 	   +------+ 		 +------+
				^ 								^
				| 								|
				| 								|
			   back 						  front
*/

int deque::get_back(void) // get the node at the back of the list
{
	int temp = 0;
	temp = back->data;

	node * ptr = back;

	back = back->next;

	delete ptr;

	return temp;
}

bool deque::empty(void) const // check for empty deque
{
	return (back == NULL && front == NULL);
}

void deque::write(ostream &out) const // write data stored to out
{
	node * ptr = back;

	while(ptr != NULL)
	{
		out << ptr->data << ", ";
		ptr = ptr->next;
	}

	out << endl;
}