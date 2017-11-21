// File: figurespointer.cpp

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

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
    string type;                      // figure type
    ofstream fout ("figurespointerout.txt");
    location* p;
    
    fout << "The code in the original form wouldn't work properly because the pointer 'p' is type 'location'.";
	fout << " While it can create objects of classes derived from 'location',";
	fout << " in its current state it can only use the methods of 'location'.";
	fout << "\n" << "_________________________________________" << "\n";
    
    while(1)  { // loop until break occurs
        cout << "\n\nType of figure: "; cin >> type;
      
        if(type == "circle") {          
            p = new circle;
            p->read(cin);
            fout << "\nobject is a circle\n";
            p->write(fout);
            delete p;
        } else if (type == "triangle")  {
            p = new triangle;
            p->read(cin);
            fout << "\nobject is a triangle\n";
            p->write(fout);
            delete p;
        } else if (type == "rectangle") {
            p = new rectangle;
            p->read(cin);
            fout << "\nobject is a rectangle\n";
            p->write(fout);
        } else break; // we are done entering data

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
	out << "Angle: " << angle << "\n";
	rectangle::write(out);
}

float triangle::area(void) // area of the figure
{
	return (rectangle::area())*sin(angle)/2 ;
}
	
