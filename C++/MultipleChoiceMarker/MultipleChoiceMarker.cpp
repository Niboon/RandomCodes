//Niboon Tangnirunkul
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
    ifstream ansKey("answerKey2012.txt");
    ifstream ansStu("studentAnswers2012.txt");
    
    if(!ansKey || !ansStu)
    {
               cout << "Unable to find file" << endl;
               system("PAUSE");
               return EXIT_FAILURE;           
    }
    
    char correctAns[30] = {0};    
    int numQ = 0;
    
        for( int i = 0; i < 30; i++)
    {
         ansKey >> correctAns[i];
         
         if(correctAns[i] != 0)
                   numQ ++;
    }
    
    
    string school;
    string id;
    char studentAns[30] = {0};
    double marks = 0;

    
    ofstream fout("results.txt");
    fout << setw(7) << "School" << setw(5) << "IDs" 
         << setw(15) << "Marks (%)" << endl;
    

    while(ansStu >> school>> id)
         {
          fout << setw(6) << school << setw(7) << id;
         
          int bCount = 0;
          marks=0;
                for( int j = 0; j < numQ; j++)
                {
                          ansStu >> studentAns[j]; 
                          if(studentAns[j] == correctAns[j])
                          marks += 5;
                          if(studentAns[j] == '0') 
                           {
                               if(bCount < 10)
                               {
                                marks += 2;
                                bCount ++;
                               }
                           }
                }

         fout << fixed << setprecision(1) << setw(10) 
              << marks/125*100 << endl;
   }


    system("PAUSE");
    return EXIT_SUCCESS;
}
