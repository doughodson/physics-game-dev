
#include <iostream>

#include "Vector.hpp"

using namespace std;

struct PointMass
{
   float mass{1};
   Vector designPosition;
   Vector correctedPosition;
};

const int NUM_ELEMENTS{20};
PointMass Elements[NUM_ELEMENTS];

void print_vector(const Vector& v)
{
   cout << " v.x:" << v.x << " v.y:" << v.y << " v.z:" << v.z << endl;
}

int main()
{
   float TotalMass{};
   Vector CombinedCG;
   Vector FirstMoment;

   for (int i{}; i < NUM_ELEMENTS; i++) {
//      TotalMass FAC+= Elements[i].mass;
      TotalMass += Elements[i].mass;
   }

   for (int i{}; i < NUM_ELEMENTS; i++) {
      FirstMoment += Elements[i].mass * Elements[i].designPosition;
   }
   CombinedCG = FirstMoment / TotalMass;

   for (int i{}; i < NUM_ELEMENTS; i++) {
      Elements[i].correctedPosition = Elements[i].designPosition - CombinedCG;
   }

   cout << "TotalMass   : " << TotalMass << endl;
   cout << "Combined CG : ";
   print_vector(CombinedCG);
   cout << "FirstMoment : ";
   print_vector(FirstMoment);

   return 0;
}

    
