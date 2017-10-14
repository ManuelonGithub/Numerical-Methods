// File: circularqueue.cpp
// This program implements a circular queue of integers
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class queue
{
	private:
		int max; // maximum size of the queue
		int count; // number of items in the queue
		int start; // data[start] is the first entry in the queue
		int end; // data[end-1] is the last entry in the queue
		vector<int> data; // vector holding the queue of items

	public:
		queue(int sz); // constructor, max = sz
		void put(int item); // put the integer item onto the queue
		int get(void); // get an item at the head of the queue
		void write(ostream &out) const; // send the data stored to out
		bool empty(void) const; // check for empty queue
		bool full(void) const; // check for full queue
        void debug(ostream &out) const;
};

int main(void)
{
	queue myqueue(5);
	ofstream fout ("queueout.txt");
	char ch;
	int x;

	while(1)
	{
		cout << "\n\np = put \n";
		cout << "g = get\n";
		cout << "s = print to screen\n";
		cout << "f = print to file\n";
		cout << "q = quit\n";
        cout << "v = start and end values\n\n";
		cin >> ch;

		if (ch == 'p') 
		{
			cout <<"\ndata to put : ";
			cin >> x;

			if(myqueue.full())
			{
				cout << "queue is full" << endl;
			}

			else 
			{
				myqueue.put(x);
			}

		}

		else if(ch == 'g')
		{
			if(myqueue.empty())
			{
				cout << "queue is empty" << endl;
			}

			else
			{
				x = myqueue.get();
				cout << "\n\ndata gotten : " << x;
			}
		}

		else if(ch == 's')
		{
			myqueue.write(cout);
		}

		else if(ch == 'f')
		{
			myqueue.write(fout);
		}

        else if(ch == 'v')
        {
            myqueue.debug(cout);
        }

		else if(ch == 'q')
		{
			break;
		}
	}

	fout.close();
	return 0;
}

queue::queue(int sz) : data(sz) // constructor
{
	max = sz;
	count = 0; // the queue has no entries yet
	start = 0;
	end = 0;
}

bool queue::empty(void) const // check for empty queue
{
	return (count == 0);
}

bool queue::full(void) const // check for full queue
{
	return ((count == max));
}

void queue::put(int item) // put the integer item onto the queue
{
	if(end == max)
	{
		end = 0;
	}

	data[end] = item;
	end++;

	if(count != max)
	{

		count++;
	}
}

int queue::get(void) // get an item at the head of the queue
{
	if(start == (max))
	{
		start = 0;
	}

	int x = data[start];

	start++;

	if(count !=0)
	{
		count--;
	}

	return x;
}

void queue::write(ostream &out) const // send the data stored to out
{
    if(start > end)
    {
        for(int i=start; i<max; i++)
        {
            out << data[i] << ", ";
        }

        for(int i = 0; i<end; i++)
        {
            out << data[i] << ", ";
        }
    }

    else if(start == end)
    {
        if(count == max)
        {
            for(int i=start; i<count; i++)
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
        for(int i=start; i<end; i++)
        {
            out << data[i] << ", ";
        }
    }

	out << endl;
	cout << "count is: " << count << endl;
}

void queue::debug(ostream &out) const
{
    out << "Start value: " << start << endl;
    out << "End value: " << end << endl;
    out << "count value: " << count << endl;
}
