
#include <iostream>

#include "Vector.hpp"
#include "Matrix3x3.hpp"

using namespace std;

struct PointMass
{
   float mass{};
   Vector designPosition;
   Vector correctedPosition;
   Vector localInertia;
};

const int NUM_ELEMENTS{20};
PointMass Elements[NUM_ELEMENTS];

void print_vector(const Vector& v)
{
   cout << " v.x:" << v.x << " v.y:" << v.y << " v.z:" << v.z << endl;
}

int main()
{
   float Ixx{}, Iyy{}, Izz{}, Ixy{}, Ixz{}, Iyz{};

   for (int i{}; i < NUM_ELEMENTS; i++) {
      Ixx += Elements[i].localInertia.x +
         Elements[i].mass * (Elements[i].correctedPosition.y *
         Elements[i].correctedPosition.y +
         Elements[i].correctedPosition.z *
         Elements[i].correctedPosition.z);

      Iyy += Elements[i].localInertia.y +
         Elements[i].mass * (Elements[i].correctedPosition.z *
         Elements[i].correctedPosition.z +
         Elements[i].correctedPosition.x *
         Elements[i].correctedPosition.x);

      Izz += Elements[i].localInertia.z +
         Elements[i].mass * (Elements[i].correctedPosition.x *
         Elements[i].correctedPosition.x +
         Elements[i].correctedPosition.y *
         Elements[i].correctedPosition.y);

      Ixy += Elements[i].mass * (Elements[i].correctedPosition.x *
         Elements[i].correctedPosition.y);

      Ixz += Elements[i].mass * (Elements[i].correctedPosition.x *
         Elements[i].correctedPosition.z);

      Iyz += Elements[i].mass * (Elements[i].correctedPosition.y *
         Elements[i].correctedPosition.z);
   }

   Matrix3x3 InertiaTensor;

   // e11 stands for element on row 1 column 1, e12 for row 1 column 2, etc.
   InertiaTensor.e11 = Ixx;
   InertiaTensor.e12 = -Ixy;
   InertiaTensor.e13 = -Ixz;

   InertiaTensor.e21 = -Ixy;
   InertiaTensor.e22 = Iyy;
   InertiaTensor.e23 = -Iyz;

   InertiaTensor.e31 = -Ixz;
   InertiaTensor.e32 = -Iyz;
   InertiaTensor.e33 = Izz;

   return 0; 
}
