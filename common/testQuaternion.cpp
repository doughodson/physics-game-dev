
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
      cout << "Magnitude of q(2,2,2,2) : " << q.magnitude() << endl;
   }

   {  // GetVector & GetScalar
      Quaternion q(2,1,2,3);
      cout << "GetVector: q(2,1,2,3) : "; print_vector(q.v);
      cout << "GetScalar: q(2,1,2,3) : " << q.get_scalar() << endl;
   }

   {  // operator+=
      Quaternion q1(2,1,2,3);
      Quaternion q2(3,1,2,3);
      q1 += q2;
      cout << "operator+= : "; print_vector(q1.get_vector());
      cout << "           : " << q1.get_scalar() << endl;
   }

   {  // operator*= scalar multiplication
      Quaternion q(2,1,2,3);
      q *= 3;
      cout << "operator*= : "; print_vector(q.get_vector());
      cout << "           : " << q.get_scalar() << endl;
   }

   {  // operator/= scalar division
      Quaternion q(2,1,2,3);
      q /= 3.0;
      cout << "operator/= : "; print_vector(q.get_vector());
      cout << "           : " << q.get_scalar() << endl;
   }

   {  // operator~ conjugate of the quaternion
      Quaternion q1(2,1,2,3);
      Quaternion q2(~q1);
      cout << "operator~  : "; print_vector(q2.get_vector());
      cout << "           : " << q2.get_scalar() << endl;
   }

   cout << "------------------------------\n";
   cout << "Tests: Functions and Operators\n";
   cout << "------------------------------\n";

   return 0;
}
