
#include <iostream>

#include "Quaternion.hpp"
#include "Vector.hpp"

using namespace std;

void print_vector(Vector v)
{
   cout << v.x << " " << v.y << " " << v.z << endl;
}

int main()
{
   cout << "--------------\n";
   cout << "Tests: Methods\n";
   cout << "--------------\n";

   {  // Magnitude
      Quaternion q(2,2,2,2);
      cout << "Magnitude of q(2,2,2,2) : " << q.Magnitude() << endl;
   }

   {  // GetVector & GetScalar
      Quaternion q(2,1,2,3);
      cout << "GetVector: q(2,1,2,3) : "; print_vector(q.v);
      cout << "GetScalar: q(2,1,2,3) : " << q.GetScalar() << endl;
   }

   {  // operator+=
      Quaternion q1(2,1,2,3);
      Quaternion q2(3,1,2,3);
      q1 += q2;
      cout << "operator+= : "; print_vector(q1.GetVector());
      cout << "           : " << q1.GetScalar() << endl;
   }

   {  // operator*= scalar multiplication
      Quaternion q(2,1,2,3);
      q *= 3;
      cout << "operator*= : "; print_vector(q.GetVector());
      cout << "           : " << q.GetScalar() << endl;
   }

   {  // operator/= scalar division
      Quaternion q(2,1,2,3);
      q /= 3.0;
      cout << "operator/= : "; print_vector(q.GetVector());
      cout << "           : " << q.GetScalar() << endl;
   }

   {  // operator~ conjugate of the quaternion
      Quaternion q1(2,1,2,3);
      Quaternion q2(~q1);
      cout << "operator~  : "; print_vector(q2.GetVector());
      cout << "           : " << q2.GetScalar() << endl;
   }

   cout << "------------------------------\n";
   cout << "Tests: Functions and Operators\n";
   cout << "------------------------------\n";

   return 0;
}
