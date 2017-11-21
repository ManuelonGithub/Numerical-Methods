// File: figstack.cpp

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#define pi 3.1415926535897

using namespace std;

class location {
private:
    float x;  // position of the figure 
    float y;
   
public:
    virtual void read(istream& in) ;
    virtual void write(ostream& out);
    virtual float area(void); // returns 0 
};

class circle : public location {
private:
    float radius;

public:
    void read(istream& in);
    void write(ostream& out);
    float area(void);      // area of the figure;
};

class rectangle : public location {
private:
	float side1, side2;
   
public:
    void read(istream& in);
    void write(ostream& out);
    float area(void);      // area of the figure;
};

class triangle : public rectangle {
private:
    float angle;
   
public:
    void read(istream& in);
    void write(ostream& out);
    float area(void);      // area of the figure;
};

int main()
{
	ofstream fout("figstackout.txt");
	stack<location*> mystack;
	char ch;       // response to prompt
	string type;   // type of figure
	location* ptr; // pointer to object pushed or popped
	
	fout << "Besides suffering from the same issues as the question before (not having the base class methods virtualized), " << "\n" ; 
	fout << "it also suffers from having the derived classes' members/methods sliced when the figure gets pushed into the stack. " << "\n" ; 
	fout << "This is because the stack is storing every figure as a 'location' type and not a 'location' pointer, " << "\n" ; 
	fout << "so when the figures get stored every member/method the base class doesn't support gets sliced off." << "\n" ;
	fout << "_________________________________________" << "\n";
	
	while(1) {
	    // print a little menu
	    cout << "\n\np = push \n";
	    cout << "o = pop\n";
	    cout << "q = quit\n\n";
	  
	    cin >> ch;
	  
	    if (ch == 'p') {
	        cout <<"\nEnter type of data to push : ";
	        cin >> type;
	        ptr = NULL;
	
	        if(type == "circle") ptr = new circle;
	        else if(type == "triangle") ptr = new triangle;
	        else if (type == "rectangle") ptr = new rectangle;
	     
	        if(ptr != NULL) { // got a valid type
	            ptr->read(cin);
	            mystack.push(ptr);
	        }
	    }
	  
	    if(ch == 'o') {
	        if(mystack.empty()) cout << "stack is empty\n";
	        else {
	            ptr = mystack.top();
	            
				cout << "popped:\n"; ptr->write(cout); cout << "\n";
	            fout << "popped:\n"; ptr->write(fout); fout << "\n";   
				   
	            mystack.pop();
	        }
	    }
	    
	    if(ch == 'q') break;
	}
	  
	return 0;
}

////////////////// implementation of location /////// ///////////

void location::read(istream& in)
{
    if(in == cin) cout <<"x coordinate: "; 
    in >> x;
   
    if(in == cin) cout <<"y coordinate: "; 
    in >> y;
}

float location::area(void)
{
    return 0.0;
}

void location::write(ostream& out)
{
    out << "x coordinate: " << x << "\n";
    out << "y coordinate: " << y << "\n";
    out << "area = " << area() << endl;
   
}

////////////////// implementation of circle /////// ///////////

void circle::read(istream& in)
{
	location::read(in);
	if(in == cin) cout <<"Radius: ";
	in >> radius;
}

void circle::write(ostream& out)
{
	out << "Circle " << "\n\n";
	out << "Radius: " << radius << "\n\n";
	out << "Centre of the circle: " << "\n";
	location::write(out);
	out << "_________________________________________" << "\n";
}

float circle::area(void) // area of the figure
{
	return  (radius*radius*pi);
}

////////////////// implementation of rectangle /////// ///////////

void rectangle::read(istream& in)
{
	location::read(in);
	if(in == cin) cout << "side1: ";
	in >> side1;
	if(in == cin) cout << "side2: ";
	in >> side2;
}

void rectangle::write(ostream& out)
{
	out << "Rectangle " << "\n\n";
	out << "Width: " << side1 << "\n";
	out << "Length: " << side2 << "\n\n";
	out << "Position of the bottom left corner: " << "\n";
	location::write(out);
	out << "_________________________________________" << "\n";
}

float rectangle::area(void) // area of the figure
{
	return (side1 * side2);
}
////////////////// implementation of triangle /////// ///////////

void triangle::read(istream& in)
{
	rectangle::read(in);
	if(in == cin) cout << "angle: ";
	in >> angle;
}

void triangle::write(ostream& out)
{
	out << "Triangle " << "\n\n";
	out << "Angle: " << angle << "\n";
	rectangle::write(out);
}

float triangle::area(void) // area of the figure
{
	return (rectangle::area())*sin(angle)/2 ;
}

