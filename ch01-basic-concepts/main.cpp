
#include <cstdio>

#include "common/Vector.hpp"
#include "common/Matrix3x3.hpp"

using namespace std;

struct PointMass
{
   float mass{};           // total mass of element
   Vector dsg_coord;       // location within composite
   Vector cg_coord;        // location relative to CG of composite
   Vector local_inertia;   // moment of inertia about CG (for all axes)
};

const int NUM_ELEMENTS{8};
PointMass elements[NUM_ELEMENTS];

// initialize the element data
void init_element_data()
{
   // outboard, port (left) wing section fitted with ailerons
   elements[0].mass = 6.56f;
   elements[0].dsg_coord = Vector(14.5f, 12.0f, 2.5f);
   elements[0].local_inertia = Vector(13.92f, 10.50f, 24.00f);

   // inboard, port wing section fitted with landing flags
   elements[1].mass = 7.31f;
   elements[1].dsg_coord = Vector(14.5f, 5.5f, 2.5f);
   elements[1].local_inertia = Vector(21.95f, 12.22f, 33.67f);

   // inboard, starboard (right) wing section fitted with landing flaps
   elements[2].mass = 7.31f;
   elements[2].dsg_coord = Vector(14.5f, -5.5f, 2.5f);
   elements[2].local_inertia = Vector(21.95f, 12.22f, 33.67f);

   // outboard, port (left) wing section fitted with ailerons
   elements[3].mass = 6.56f;
   elements[3].dsg_coord = Vector(14.5f, -12.0f, 2.5f);
   elements[3].local_inertia = Vector(13.92f, 10.50f, 24.00f);

   // port elevator fitted with flap
   elements[4].mass = 2.62f;
   elements[4].dsg_coord = Vector(3.03f, 2.5f, 3.0f);
   elements[4].local_inertia = Vector(0.837f, 0.385f, 1.206f);

   // starboard elevator fitted with flap
   elements[5].mass = 2.62f;
   elements[5].dsg_coord = Vector(3.03f, -2.5f, 3.0f);
   elements[5].local_inertia = Vector(0.837f,0.385f, 1.206f);

   // vertical tail/rudder (no flap, the entire thing moves)
   elements[6].mass = 2.93f;
   elements[6].dsg_coord = Vector(2.25f, 0.0f, 5.0f);
   elements[6].local_inertia = Vector(1.262f, 1.942f, 0.718f);

   // fuselage
   elements[7].mass = 31.8f;
   elements[7].dsg_coord = Vector(15.25f, 0.0f, 1.5f);
   elements[7].local_inertia = Vector(66.30f, 861.9f, 861.9f);
}

void print_vector(const Vector& v)
{
   printf("x:%5.2f y:%5.2f z:%5.2f", v.x, v.y, v.z);
}

void print_matrix(const Matrix3x3& m)
{
   printf("e11:%8.2f e12:%8.2f e13:%8.2f\n", m.e11, m.e12, m.e13);
   printf("e21:%8.2f e22:%8.2f e23:%8.2f\n", m.e21, m.e22, m.e23);
   printf("e31:%8.2f e32:%8.2f e33:%8.2f\n", m.e31, m.e32, m.e33);
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

   printf("Total Mass   : %5.2f\n", total_mass);
   printf("Combined CG  : ");
   print_vector(combined_CG);
   printf("\n");
   printf("First Moment : ");
   print_vector(first_moment);
   printf("\n");

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

   printf("Inertia Tensor :\n");
   print_matrix(inertia_tensor);

   return 0;
}
