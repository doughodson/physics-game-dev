
#include <iostream>

#include "common/Vector.hpp"
#include "common/Matrix3x3.hpp"

using namespace std;

struct PointMass
{
   float mass{};
   Vector dsg_coord;
   Vector cg_coord;
   Vector local_inertia;
};

const int NUM_ELEMENTS{8};
PointMass elements[NUM_ELEMENTS];

// initialize the element data
void init_element_data()
{
   elements[0].mass = 6.56f;
   elements[0].dsg_coord = Vector(14.5f, 12.0f, 2.5f);
   elements[0].local_inertia = Vector(13.92f, 10.50f, 24.00f);

   elements[1].mass = 7.31f;
   elements[1].dsg_coord = Vector(14.5f, 5.5f, 2.5f);
   elements[1].local_inertia = Vector(21.95f, 12.22f, 33.67f);

   elements[2].mass = 7.31f;
   elements[2].dsg_coord = Vector(14.5f, -5.5f, 2.5f);
   elements[2].local_inertia = Vector(21.95f, 12.22f, 33.67f);

   elements[3].mass = 6.56f;
   elements[3].dsg_coord = Vector(14.5f, -12.0f, 2.5f);
   elements[3].local_inertia = Vector(13.92f, 10.50f, 24.00f);

   elements[4].mass = 2.62f;
   elements[4].dsg_coord = Vector(3.03f, 2.5f, 3.0f);
   elements[4].local_inertia = Vector(0.837f, 0.385f, 1.206f);

   elements[5].mass = 2.62f;
   elements[5].dsg_coord = Vector(3.03f, -2.5f, 3.0f);
   elements[5].local_inertia = Vector(0.837f,0.385f, 1.206f);

   elements[6].mass = 2.93f;
   elements[6].dsg_coord = Vector(2.25f, 0.0f, 5.0f);
   elements[6].local_inertia = Vector(1.262f, 1.942f, 0.718f);

   elements[7].mass = 31.8f;
   elements[7].dsg_coord = Vector(15.25f, 0.0f, 1.5f);
   elements[7].local_inertia = Vector(66.30f, 861.9f, 861.9f);
}

void print_vector(const Vector& v)
{
   cout << " v.x:" << v.x << " v.y:" << v.y << " v.z:" << v.z << endl;
}

int main()
{
   float total_mass{};
   Vector combined_CG;
   Vector first_moment;

   init_element_data();

   for (int i{}; i < NUM_ELEMENTS; i++) {
      total_mass += elements[i].mass;
   }

   for (int i{}; i < NUM_ELEMENTS; i++) {
      first_moment += elements[i].mass * elements[i].dsg_coord;
   }
   combined_CG = first_moment / total_mass;

   for (int i{}; i < NUM_ELEMENTS; i++) {
      elements[i].cg_coord = elements[i].dsg_coord - combined_CG;
   }

   cout << "total_mass   : " << total_mass << endl;
   cout << "combined_CG  : ";
   print_vector(combined_CG);
   cout << "first_moment : ";
   print_vector(first_moment);

   //

   float Ixx{}, Iyy{}, Izz{}, Ixy{}, Ixz{}, Iyz{};

   for (int i{}; i < NUM_ELEMENTS; i++) {
      Ixx += elements[i].local_inertia.x +
         elements[i].mass * (elements[i].cg_coord.y *
         elements[i].cg_coord.y +
         elements[i].cg_coord.z *
         elements[i].cg_coord.z);

      Iyy += elements[i].local_inertia.y +
         elements[i].mass * (elements[i].cg_coord.z *
         elements[i].cg_coord.z +
         elements[i].cg_coord.x *
         elements[i].cg_coord.x);

      Izz += elements[i].local_inertia.z +
         elements[i].mass * (elements[i].cg_coord.x *
         elements[i].cg_coord.x +
         elements[i].cg_coord.y *
         elements[i].cg_coord.y);

      Ixy += elements[i].mass * (elements[i].cg_coord.x *
         elements[i].cg_coord.y);

      Ixz += elements[i].mass * (elements[i].cg_coord.x *
         elements[i].cg_coord.z);

      Iyz += elements[i].mass * (elements[i].cg_coord.y *
         elements[i].cg_coord.z);
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
