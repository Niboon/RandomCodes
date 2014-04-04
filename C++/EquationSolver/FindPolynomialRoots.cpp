//Find Roots of a Polynomial Using Bernoulli's Method of Approximation

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAXSIZE = 20;
const double epsilon = 10e-6; 

int readPoly(istream & in, double coeff[])
{
    int deg;
    if (in == cin)
       cout << "Enter degree ";
    in >> deg;
    
    for (int i = deg; i>=0; i--)
    {
        if (in == cin)
           cout << "Enter coefficient t^" << i << " ";
        in >> coeff[i];
    }
    return deg;
}

void writePoly(ostream & out, int deg, double coeff[])
{
    out << fixed << setprecision(1) << showpos;
    int eCnt = 0;
    for (int i=deg; i>=0; i--)
    {
        out << coeff[i];
        if (i > 1)
            out << "t^" << i << " ";
        else if (i == 1)
            out << "t ";

        if (eCnt % 8 == 0)
            out << endl;
        eCnt++;
    }
    out << endl;
}

double evaluate(double t, int deg, double coeff[])
{
    double v = 0;
    for (int i=deg; i>=0; i--)
        v = v * t + coeff[i];
     return v;
}


void findDerivative(double dfunction[], double function [], int deg)
{
     for (int i = deg; i > 0; i--)
     {
         dfunction[i - 1] = i * function[i];
     }
     cout << endl;
}

double findRoot(int times, double t0, double dfunction[], double function[], int degree)
 {
        double v = evaluate(t0, degree, function), t = t0 - v/evaluate(t0, degree-1,dfunction);
        t = t0;
        
        if(times==0)
               return t0;
        return findRoot(times -1, t0 - v/evaluate(t0, degree-1,dfunction) , dfunction, function, degree);
 }
 
 
int main()
{
    ifstream fin("coeff.dat");
    if(!fin)
    {
        cout << "File does not exist!";
        cin.get();
        return -1;
    }
    int numOfPoly;
    fin >> numOfPoly;
    for(int i = 0; i < numOfPoly; i++)
    {
        double t0;
        cout << "Enter an approx. of the root: "; 
        cin >> t0;
        int times = 100;
        double function[19]; 
        double dfunction[19];
        double root; 
        int deg = readPoly(fin, function);
        findDerivative(dfunction, function, deg);
        cout << findRoot(times, t0, dfunction, function, deg) << endl;

    }
    system("PAUSE");
    return 0;
    
}

/*CONSOLE OUTPUT
Enter an approx. of the root: -2

-1.38879
Enter an approx. of the root: 6

7.66632
Enter an approx. of the root: 0

-0.925413
Press any key to continue . . .



*/
