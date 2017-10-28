/*  FILE: singleserver.cpp

In a single server queueing system jobs arrive at a server for processing. 
The jobs require varying amounts of processing time and the server can only
process one job at a time.  When the server is busy the jobs must wait in a
queue.



                 -----+--+--+--+     +--+
                      |  |  |  |     |  |
arriving jobs --->    |  |  |  | --> |  | ----> finished jobs depart
                      |  |  |  |     |  |
                 -----+--+--+--+     +--+
                  queue of jobs     server     

We observe a single server queue at fixed time periods t = 1, 2, 3, ...

During each time period, the probability of a job arriving is lambda.
At most one job can arrive in a time period.

During each time period, the probability is mu 
that a job currently being processed will finish.

A job has an arrival time, a start time and a finish time.

The server has a queue of jobs waiting to be processed.
The server has a job which is currently being processed. 
The server has an attribute called busy which shows whether the job being processed has finished. 
The server also maintains a list of finished jobs for reporting purposes.
*/

#include <iostream>
#include <list>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

bool bernoulli(float prob);

class job
{
    private:
        int arrive;   // arrival time
        int start;     // start time of processing by server 
        int finish;    // finish time = start + service

    public:
        job(void);     // create a job
        void write(ostream& out);
               
    friend class server;  // server has access to all members of job
};

class server
{
    private:
       // fill in appropriate members
        bool busy;
        queue<job> q;
        list<job> done;
        job current;

    public:
    	server(void);              // set busy = false
        void process(int t);       // process at time t
        void report(ostream& out); // report the jobs completed to the stream out
};

float lambda = 0.4;
float mu = 0.5;

int main(void)
{
    server srv;
    int n = 50;
	unsigned seed = 123456; // good value 8478564
	
	//cout << "Enter a seed and the number of time steps: ";
	//cin >> seed >> n;

    srand(seed);
	
    for (int t = 1; t < n; t++)
    {
		srv.process(t);
    }
    
    srv.report(cout);
        
    return 0;
}
    
job::job(void)
{
    arrive = 0;
    start = 0;
    finish = 0;
}

void job::write(ostream& out)
{
    out << setw(6) << arrive << setw(6) << start 
        << setw(6) << finish << endl;
}

server::server(void)
{
	busy = false;  // server is initially not busy
}


/*
 * The server has a method called process which is carried out during
 * each time consisting of the following steps:
 */
void server::process(int t)
{    
    /*
     * step 1: if the server is busy it checks to see if the current job has
     *         finished (probability is mu) and if so, it fills in the job's finish
     *         time, adds the job to the list of finished jobs and sets the busy
     *         attribute to false.
     */

    if(busy && bernoulli(lambda))
    {
        current.finish = t;
        busy = false;
        done.push_back(current);
    }

    /*
     * step 2: the server then checks to see if a job has arrived (probability is lambda) 
     *         and if so, it sets the job's arrival time and places the job in
     *         the queue of jobs waiting for service.
     */

    if(bernoulli(lambda))
    {
        job *p = new job;
        p->arrive = t;
        q.push(*p);
    }

    /*
     * step 3: at this point, if the server is not busy and the queue is not empty,
     *         it gets a job from the queue, makes it the current job and sets the
     *         start time of the job.
     */

    if(!busy && !q.empty())
    {
        current = q.front();
        q.pop();
    }
}

void server::report(ostream& out)
{
    out << "arrive  start  finish" << endl;
    list<job>::iterator p;
    for(p=done.begin(); p!=done.end();++p)
    {
        p->write(out);
    }
}

bool bernoulli(float prob)
{
    float x = (float) rand() / (float) RAND_MAX;
    return (x < prob);
}