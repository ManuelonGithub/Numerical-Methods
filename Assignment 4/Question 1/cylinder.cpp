/* File: cylinder.cpp
 * 
 * classes which represents points, circles and cylinders in the plane 
 * 
 * Programmer: Manuel Burnay
 * 
 * Date Created: 08/10/2017
 * 
 * Last Edit: 09/10/2017. Added comments explaining the code
 */


#include <iostream>
#include <fstream>
using namespace std;

class point 		// Class that relates to a point's X-Y position
{
	private:
		float x; 	// X-position	
		float y; 	// Y-position
	public:
		point(float h, float v); 			// The constructor of the point class. h = x-pos, and v = y-pos
		void write(ostream &out) const; 	// Prints out the point in the form (x,y)
};

class circle 			// Class that relates to a circle's radius and its centre's X-Y position
{
	private:
		point centre; 	// The circle's centre, which is a 'point'-type variable
		float radius; 	// The radius of the circle
	public:
		circle(const point &p, float r); 	// The constructor of the circle class. centre = p, and radius = r. p is passed by reference to avoid needless memory usage
		void write(ostream &out) const; 	// Prints out the circle in the form of ("centre ="(point)," radius =" radius)
};

class cylinder 			// Class that relates to a cylinder's base and height
{
	private:
		circle base; 	// The cylinder's base, which is a 'circle'-type variable
		float height; 	// The cylinder's height
	public:
		cylinder(const circle &c, float ht); 	// The constructor of the cylinder class. base = c, and height = ht. c is passed by reference to avoid needless memory usage
		void write(ostream &out) const; 		// Prints out the circle in the form of ("base ="(base)," height =" height)
};

int main(void)
{
	point p(1.0, 2.0);

	cout << "p = ";
	p.write(cout);
	cout << endl;

	circle cir(p, 3.0);

	cout << "cir = ";
	cir.write(cout);
	cout << endl;

	cylinder cyl(cir, 7.0);
	cout << "cyl = ";
	cyl.write(cout);
	cout << endl;

	return 0;
}
//////////////////////////// implementation of point //////////////////////

point::point(float h, float v) 	// The constructor of the circle class. centre = p, and radius = r. p is passed by reference to avoid needless memory usage
{
	x = h;
	y = v;
}
void point::write(ostream &out) const 	// Prints out the point in the form (x,y)
{
	out << "(" << x << "," << y << ")";
}

/////////////////////////// implementation of circle ///////////////////////

circle::circle(const point &p, float r) :centre(p) 	// Because the centre is a class-varialbe, it needs to be assigned this way 
{
	radius = r; 	// Including centre here would result in a compiler error
}

void circle::write(ostream &out) const 	// Prints out the circle in the form of ("centre = "(point)," radius =" radius)
{
	out << "(centre = ";
	centre.write(cout);
	out << ", radius = " << radius << ")";
}

/////////////////////////// implementation of cylinder ///////////////////////

cylinder::cylinder(const circle &c, float ht) :base(c) 	// Same thing as above happens here. Since base is a class variable, it needs to be assigned this way 
{
	height = ht;
}

void cylinder::write(ostream &out) const 	// Prints out the circle in the form of ("base ="(base)," height =" height)
{
	out << "(base = ";
	base.write(cout);
	out << ", height = " << height << ")";
}
