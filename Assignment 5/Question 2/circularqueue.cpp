/* 
 * File: circularqueue.cpp
 * 
 * This program implements a circular queue of integers
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

class queue
{
	private:
		int max; 			// maximum size of the queue
		int count; 			// number of items in the queue
		int start; 			// data[start] is the first entry in the queue
		int end; 			// data[end-1] is the last entry in the queue
		vector<int> data; 	// vector holding the queue of items

	public:
		queue(int sz); 						// constructor, max = sz
		void put(int item); 				// put the integer item onto the queue
		int get(void); 						// get an item at the head of the queue
		void write(ostream &out) const; 	// send the data stored to out
		bool empty(void) const; 			// check for empty queue
		bool full(void) const; 				// check for full queue
        void debug(ostream &out) const;		// Programmer-made method. Simply outputs the values for start, end and count whenever it's prompted
};

int main(void)
{
	queue myqueue(5);					// Initilizationg the queue of size 5
	ofstream fout ("queueout.txt"); 	// Output file creation
	
	char ch;	// Menu character variable. Its contents pertain to the lastest input from the user
	int x;		// Placeholder variable for when the user inputs the data to be put to the queue, or when the user get data back from it

	while(1)		// Text-based Menu system, in order to give us proper commands to manipulate the queue
	{
		cout << "\n\np = put \n";
		cout << "g = get\n";
		cout << "s = print to screen\n";
		cout << "f = print to file\n";
		cout << "q = quit\n";
        cout << "v = start and end values\n\n";
		cin >> ch;

		if (ch == 'p') 		// Put command. It inserts data into the queue
		{
			cout <<"\ndata to put : ";		// Prompt for the user to input data
			cin >> x;

			if(myqueue.full())
			{
				cout << "queue is full" << endl;		// Checks if the queue is full. If it is, the user won't be allowed to insert the data just inputted
			}

			else 
			{
				myqueue.put(x);
			}

		}

		else if(ch == 'g')		// Get command. It recovers data from the queue to be utilized
		{
			if(myqueue.empty())
			{
				cout << "queue is empty" << endl;		// Checks if the queue is empty. If it is, the user won't be allowed to recover any data from it
			}

			else
			{
				x = myqueue.get();
				cout << "\n\ndata gotten : " << x;
			}
		}

		else if(ch == 's')		// Print-to-screen command
		{
			myqueue.write(cout);
		}

		else if(ch == 'f')		// Print-to-file command
		{
			myqueue.write(fout);
		}

        else if(ch == 'v')		// Debug command. I have it set as the character 'v' because it outputs values
        {
            myqueue.debug(cout);
        }

		else if(ch == 'q')		// Command to break the menu loop, and to exit the process
		{
			break;
		}
	}

	fout.close();
	return 0;
}

queue::queue(int sz) : data(sz) // Constructor
{
	max = sz;
	count = 0; 		// The queue has no entries yet
	start = 0;		// Start and end are in the same position
	end = 0;		//	when either the count is 0 (no entries), or when count = max-1 (queue is full)
}

bool queue::empty(void) const 	// check for empty queue. Will be True if the queue is empty
{
	return (count == 0);
}

bool queue::full(void) const 	// check for full queue. Will be True if the queue is full
{
	return ((count == max));
}

void queue::put(int item) // put the integer item onto the queue
{
	if(end == max) 		// Here lies the circular nature of the queue (at least half of it). When end increments past the end of the queue, it just loops back to position 0
	{
		end = 0;
	}

	data[end] = item;
	end++;				// The end position changes when you put values in the queue.
						// Because of the nature of the queue, you only put values in when the end of the queue is
						// AFAIK this process is equal to both linear and circular implementations of a queue
						// Also note that the end position is always one location after the latest data placed in the queue (i.e. when queue is full, end is one position after the last data value)

	if(count != max)	// Prevents the count to exceed the max value
	{

		count++;		// Count increases with every added data, until it reaches max capacity of queue
	}
}

int queue::get(void) // get an item at the head of the queue
{
	if(start == (max)) 		// Here lies the circular nature of the queue (at least half of it). When start increments past the end of the queue, it just loops back to position 0
	{
		start = 0;
	}

	int x = data[start];
	start++;				// The start position changes when you get a value out of the queue. 
							// This is due to the nature of a queue, where you can only get values out when they're in the start position. 
							// In a circular queue, you simply change where the start position is, which is far more efficient that a linear queue implementation

	if(count !=0)	// Prevents the count to go below 0
	{
		count--;		// Count decreases for every value gotten, until it reaches 0 
	}

	return x;
}

void queue::write(ostream &out) const 	// send the data stored to out. Currently works just fine, but there's a simpler implementation of it using a while loop with its condition being (count != 0), and a few if statements inside the loop
{
    if(start > end)			// Scenario 1: start is located after the end position
    {
        for(int i=start; i<max; i++)	// Will ouput the queue values up to max
        {
            out << data[i] << ", ";
        }

        for(int i = 0; i<end; i++)		// And then loop back to zero, and output up to end
        {
            out << data[i] << ", ";
        }
    }

    else if(start == end)	// Scenario 2: Stat and end are in the same position
    {
        if(count == max)	// We only care about the 'sub' scenario here that involves us printing values, t/f only when count = is equal to max
        {
            for(int i=start; i<count; i++)	// Vectors and arrays start at position 0, and that's why we go up to count, but not including it
            {
                out << data[i] << ", ";
            }

            for(int i = 0; i<end; i++)
            {
                out << data[i] << ", ";
            }
        }
    }

    else
    {
        for(int i=start; i<end; i++)		// Scenario 3: start is before the end position
        {
            out << data[i] << ", ";
        }
    }

	out << endl;
	cout << "count is: " << count << endl;
}

void queue::debug(ostream &out) const		// Debug method. Simply outputs the start, end, and count values of the system 
{
    out << "Start value: " << start << endl;
    out << "End value: " << end << endl;
    out << "count value: " << count << endl;
}
