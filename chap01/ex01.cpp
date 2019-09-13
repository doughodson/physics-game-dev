
#include <iostream>

#include "Vector.hpp"

using namespace std;

struct PointMass
{
   float mass{1};
   Vector design_position;
   Vector corrected_position;
};

const int NUM_ELEMENTS{20};
PointMass elements[NUM_ELEMENTS];

void print_vector(const Vector& v)
{
   cout << " v.x:" << v.x << " v.y:" << v.y << " v.z:" << v.z << endl;
}

int main()
{
   float total_mass{};
   Vector combined_CG;
   Vector first_moment;

   for (int i{}; i < NUM_ELEMENTS; i++) {
//      TotalMass FAC+= Elements[i].mass;
      total_mass += elements[i].mass;
   }

   for (int i{}; i < NUM_ELEMENTS; i++) {
      first_moment += elements[i].mass * elements[i].design_position;
   }
   combined_CG = first_moment / total_mass;

   for (int i{}; i < NUM_ELEMENTS; i++) {
      elements[i].corrected_position = elements[i].design_position - combined_CG;
   }

   cout << "total_mass   : " << total_mass << endl;
   cout << "combined_CG  : ";
   print_vector(combined_CG);
   cout << "first_moment : ";
   print_vector(first_moment);

   return 0;
}

    
