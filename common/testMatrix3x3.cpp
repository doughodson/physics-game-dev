
#include <iostream>

#include "Matrix3x3.hpp"

using namespace std;

void print_matrix(Matrix3x3 m)
{
   cout << endl << m.e11 << " " << m.e12 << " " << m.e13 
        << endl << m.e21 << " " << m.e22 << " " << m.e23
        << endl << m.e31 << " " << m.e32 << " " << m.e33 << endl;
}

int main()
{
   cout << "--------------\n";
   cout << "Tests: Methods\n";
   cout << "--------------\n";

   {  // determinant
      Matrix3x3 m(1,2,3,4,5,6,7,8,9);
      cout << "m(1,2,3,4,5,6,7,8,9).det() : " << m.det() << endl;
   }

   {  // transpose
      Matrix3x3 m1(1,2,3,4,5,6,7,8,9);
      Matrix3x3 m2{m1.Transpose()};
      cout << "Matrix3x3: ";
      print_matrix(m1);
      cout << "Transpose: ";
      print_matrix(m2);
   }

   cout << "---------------------------\n";
   cout << "Tests: Overloaded operators\n";
   cout << "---------------------------\n";

   return 0;
}
