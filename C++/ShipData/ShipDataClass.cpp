#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int MAX=50;

void coorShip(int lat,int latT,int lon,int lonT,double &x,double &y)
{
       y=(lat+latT/60.0)*111;
       x=(lon+lonT/60.0)*111*cos((lat+latT/60.0)*M_PI/180);
}

double distShip(double x1,double y1,double x2,double y2)
{
       return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

class Ship
{
      private:
              string name;
              double x;
              double y;
              double speed;
              
      public:
             //Constructors
             Ship();
             Ship(string name0,int lat,int latT,int lon,int lonT,double speed0);
             
             //Accessor Functions
             string getName() const;
             double getX() const;
             double getY() const;
             double getSpeed() const;
             
             //Other Functions
             bool input(istream & in);
             bool output(ostream & out);
             double eta(double x1,double y1,double speed1);
             
};

Ship::Ship()
{
           name= "None";
           x= 0;
           y= 0;
           speed= 0;
}
Ship::Ship(string name0,int lat,int latT,int lon,int lonT,double speed0)
{
            name=name0;
            coorShip(lat,latT,lon,lonT,x,y);
            speed = speed0;
}

string Ship::getName() const
{
       return name;
}

double Ship::getX() const
{
       return x;
}

double Ship::getY() const
{
       return y;
}

double Ship::getSpeed() const
{
       return speed;
}

bool Ship::input(istream & in)
{
     int lat,latT,lon,lonT;
     in >> name>> lat >> latT >> lon >> lonT >> speed;
     coorShip(lat,latT,lon,lonT,x,y);
     return 1;
}

bool Ship::output(ostream & out)
{
     out << setw(25) << name << setw(8) << x << setw(8) << y 
         << setw(5) << speed << endl;
     return 1;
}
double Ship::eta(double x1,double y1,double speed1)
{
       if(speed+speed1 !=0)
       return distShip(x,y,x1,y1)/(speed+speed1);
       else
       return exp(999);
}



bool ioShips(istream& in,ostream& out,Ship Ships[])
{
   out << fixed << setprecision(1);
   if(!in)
   {
          cout << "UNABLE TO FIND FILE" << endl;
          return 0;
   }
   int n=0;
   while(in.peek()!=-1)
   {
         Ships[n].input(in);
         Ships[n].output(out);
         n++;
   }
   MAX = n;    //Corrects global MAX value of Array to number of Ships in Array
   return 1;
}

bool helpShip(Ship Ships[],int MAX,Ship Sink,Ship& distClose,Ship& timeClose)
{
   double dMin=exp(999);
   double tMin=exp(999);
   for(int n=0;n<MAX;n++)
   {
      if(dMin>distShip(Ships[n].getX(),Ships[n].getY(),Sink.getX(),Sink.getY()))
      {
         dMin=distShip(Ships[n].getX(),Ships[n].getY(),Sink.getX(),Sink.getY());
         distClose=Ships[n];
      }
      if(tMin>Ships[n].eta(Sink.getX(),Sink.getY(),Sink.getSpeed()))
      {
         tMin = Ships[n].eta(Sink.getX(),Sink.getY(),Sink.getSpeed());
         timeClose = Ships[n];
      }
   }
   return 1;

}


int main()
{
   ifstream fin("ships.txt");
   ofstream fout("verify.txt");
   ifstream sinkIn("trouble.txt");
   if(!sinkIn)
   {
          cout << "UNABLE TO FIND FILE" << endl;
          system("PAUSE");
          return EXIT_FAILURE;
   }
   ofstream helpOut("help.txt");
   Ship Ships[MAX],Sink;
   Ship distClose,timeClose;
   ioShips(fin,fout,Ships);
   helpOut << fixed << setprecision(1);
   
   while(sinkIn.peek()!=-1)
   {
    Sink.input(sinkIn);
    helpShip(Ships,MAX,Sink,distClose,timeClose);
    helpOut << "Closest to Troubled " << Sink.getName() << ": \n"
            << setw(25) << "Name" << setw(8) << "x km" << setw(8) << "y km"
            << setw(8) << "km/h" << setw(8) << "Dist" << setw(8) << "Time\n"
            << "Distance-wise: \n";
    helpOut<<setw(25) << distClose.getName() << setw(8) << distClose.getX()
           <<setw(8) << distClose.getY() << setw(8)
           <<distClose.getSpeed() << setw(8) 
           <<distShip(distClose.getX(),distClose.getY(),Sink.getX(),Sink.getY())
           <<setw(8);
    if(distClose.eta(Sink.getX(),Sink.getY(),Sink.getSpeed())==exp(999))
        helpOut<<"Never \n";
    else
        helpOut<<distClose.eta(Sink.getX(),Sink.getY(),Sink.getSpeed()) << endl;
    helpOut<< "Time-wise: \n"
           <<setw(25) << timeClose.getName() << setw(8) << timeClose.getX()
           <<setw(8) << timeClose.getY() << setw(8)
           <<timeClose.getSpeed() << setw(8) 
           <<distShip(timeClose.getX(),timeClose.getY(),Sink.getX(),Sink.getY())
           <<setw(8);
    if(timeClose.eta(Sink.getX(),Sink.getY(),Sink.getSpeed())==exp(999))
        helpOut<<"Never \n";
    else
        helpOut<<timeClose.eta(Sink.getX(),Sink.getY(),Sink.getSpeed()) << endl;
    helpOut << endl << endl;
   }
   
   system("PAUSE");
   return EXIT_SUCCESS;
}
