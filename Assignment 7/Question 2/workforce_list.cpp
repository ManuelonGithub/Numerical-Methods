/* File: workforce_list.cpp
Manipulate a list of employees */

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

class employee
{
    private:
        string name; // last name
        int id; // employee id number
        float salary; // employee salary
    public:
        employee(string n = "", int i = 0, float s = 0.0);
        string getname(void);
        void updatesalary(float s);

    friend ostream & operator<< (ostream &out, const employee &e);
    friend istream & operator>>(istream &in, employee &e);
    friend bool operator<(const employee &a, const employee &b);
};

int main(void)
{
    list<employee> workforce;
    ifstream fin("workforcein.txt");
    employee x;
    /* read the employees from the file and store them in workforce */
    while(fin >> x)
    {
        workforce.push_back(x);
    }

    /* use an iterator to cycle through the workforce and change employee Black’s salary to 55000 */
    list<employee>::iterator p;
    for(p = workforce.begin(); p != workforce.end(); ++p)
    {
        if(p->getname() == "Black")
        {
            p->updatesalary(55000);
        }
    }

    /* use an iterator to cycle through the workforce and print the workforce employees to the screen */
    for(p = workforce.begin(); p != workforce.end(); ++p)
    {
        cout << *p << endl;
    }

    fin.close();
    return 0;
}
employee::employee(string n, int i, float s)
{
    name = n;
    id = i;
    salary = s;
}
string employee::getname(void)
{
    return name;
}
void employee::updatesalary(float s)
{
    salary = s;
}
ostream &operator<<(ostream &out, const employee &e)
{
    out << e.name << " " << e.id << " " << e.salary << " ";
    return out;
}
istream &operator>>(istream &in, employee &e)
{
    in >> e.name >> e.id >> e.salary;
    return in;
}