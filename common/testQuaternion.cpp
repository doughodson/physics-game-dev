
#include <iostream>

#include "Quaternion.hpp"
#include "Vector.hpp"

using namespace std;

void print_vector(Vector v)
{
   cout << endl << v.x << " " << v.y << " " << v.z << endl;
}

int main()
{
   cout << "--------------\n";
   cout << "Tests: Methods\n";
   cout << "--------------\n";

   {  // Magnitude
      Quaternion q;
      print_vector(q.v);


   }



   cout << "---------------------------\n";
   cout << "Tests: Overloaded operators\n";
   cout << "---------------------------\n";

   return 0;
}
