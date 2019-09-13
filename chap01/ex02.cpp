
#include <iostream>

#include "Vector.hpp"
#include "Matrix3x3.hpp"

using namespace std;

struct PointMass
{
   float mass{};
   Vector design_position;
   Vector corrected_position;
   Vector local_inertia;
};

const int NUM_ELEMENTS{20};
PointMass elements[NUM_ELEMENTS];

void print_vector(const Vector& v)
{
   cout << " v.x:" << v.x << " v.y:" << v.y << " v.z:" << v.z << endl;
}

int main()
{
   float Ixx{}, Iyy{}, Izz{}, Ixy{}, Ixz{}, Iyz{};

   for (int i{}; i < NUM_ELEMENTS; i++) {
      Ixx += elements[i].local_inertia.x +
         elements[i].mass * (elements[i].corrected_position.y *
         elements[i].corrected_position.y +
         elements[i].corrected_position.z *
         elements[i].corrected_position.z);

      Iyy += elements[i].local_inertia.y +
         elements[i].mass * (elements[i].corrected_position.z *
         elements[i].corrected_position.z +
         elements[i].corrected_position.x *
         elements[i].corrected_position.x);

      Izz += elements[i].local_inertia.z +
         elements[i].mass * (elements[i].corrected_position.x *
         elements[i].corrected_position.x +
         elements[i].corrected_position.y *
         elements[i].corrected_position.y);

      Ixy += elements[i].mass * (elements[i].corrected_position.x *
         elements[i].corrected_position.y);

      Ixz += elements[i].mass * (elements[i].corrected_position.x *
         elements[i].corrected_position.z);

      Iyz += elements[i].mass * (elements[i].corrected_position.y *
         elements[i].corrected_position.z);
   }

   Matrix3x3 inertia_tensor;

   // e11 stands for element on row 1 column 1, e12 for row 1 column 2, etc.
   inertia_tensor.e11 =  Ixx;
   inertia_tensor.e12 = -Ixy;
   inertia_tensor.e13 = -Ixz;

   inertia_tensor.e21 = -Ixy;
   inertia_tensor.e22 =  Iyy;
   inertia_tensor.e23 = -Iyz;

   inertia_tensor.e31 = -Ixz;
   inertia_tensor.e32 = -Iyz;
   inertia_tensor.e33 =  Izz;

   return 0; 
}
