
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
      cout << "Transpose Test: Matrix3x3:";
      print_matrix(m1);
      cout << "Transpose:";
      print_matrix(m2);
      Matrix3x3 m3{m2.Transpose()};
      cout << "Transpose:";
      print_matrix(m3);
   }

   {  // inverse
      Matrix3x3 m(1,2,3,4,5,6,7,8,9);
      cout << "Inverse Test: Matrix3x3:";
      print_matrix(m);
      cout << "Inverse:";
      print_matrix(m.Inverse());
   }

   {  // operator+=
      Matrix3x3 m1(1,2,3,1,2,3,1,2,3);
      Matrix3x3 m2(1,2,3,1,2,3,1,2,3);
      cout << "operator+= Test: Matrix3x3:";
      print_matrix(m1);
      print_matrix(m2);
      m1 += m2;
      cout << "m1 += m2:";
      print_matrix(m1);
   }

   {  // operator+=
      Matrix3x3 m1(1,2,3,1,2,3,1,2,3);
      Matrix3x3 m2(1,2,3,1,2,3,1,2,3);
      cout << "operator-= Test: Matrix3x3:";
      print_matrix(m1);
      print_matrix(m2);
      m1 -= m2;
      cout << "m1 += m2:";
      print_matrix(m1);
   }

   {  // scalar multiplication
      Matrix3x3 m(1,2,3,4,5,6,7,8,9);
      cout << "scalar multiplication Test: Matrix3x3:";
      print_matrix(m);
      m *= 2;
      cout << "m += 2:";
      print_matrix(m);
   }

   {  // scalar division
      Matrix3x3 m(1,2,3,4,5,6,7,8,9);
      cout << "scalar division Test: Matrix3x3:";
      print_matrix(m);
      m /= 2;
      cout << "m /= 2:";
      print_matrix(m);
   }

   cout << "---------------------------\n";
   cout << "Tests: Overloaded operators\n";
   cout << "---------------------------\n";

   return 0;
}
