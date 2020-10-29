


#include <iostream>
#include <cstdio>

#include "physics.hpp"

extern RigidBody Airplane;
extern float ThrustForce;
extern bool Stalling;
extern bool Flaps;

const int FRAME_RATE{30}; // frame rate

int main()
{
   std::cout << "Flight Simulator\n";
   const float dt{1.0f / static_cast<float>(FRAME_RATE)};
   float current_time{};

   for(int i{}; i < 10; i++) {
      StepSimulation(dt);
      std::cout << "Simulation time : " << current_time << std::endl;

      std::cout << "Roll   : " << Airplane.vEulerAngles.x << std::endl;
      std::cout << "Pitch  : " << Airplane.vEulerAngles.y << std::endl;
      std::cout << "Yaw    : " << Airplane.vEulerAngles.z << std::endl;
      std::cout << "Alt    : " << Airplane.vPosition.z << std::endl;
      std::cout << "Thrust : " << ThrustForce << std::endl;

      if (Flaps) std::cout << "Flaps!\n";
      if (Stalling) std::cout << "Stall!\n";

      std::cout << "===================================================\n";
      current_time += dt;

   }


   return 0;
}


