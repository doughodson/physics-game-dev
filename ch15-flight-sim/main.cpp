
#include <iostream>
#include <cstdio>

#include "BourgFDM.hpp"

const int FRAME_RATE{30}; // frame rate

int main()
{
   std::cout << "Flight Simulator\n";
   const float dt{1.0f / static_cast<float>(FRAME_RATE)};
   float current_time{};

   BourgFDM fdm;

   fdm.zero_rudder();
   fdm.zero_ailerons();
   fdm.zero_elevators();
   fdm.zero_flaps();

   for (int i{}; i < 10; i++) {

      fdm.inc_thrust();

      fdm.step_simulation(dt);
      std::cout << "Simulation time : " << current_time << std::endl;

      std::cout << "Roll   : " << fdm.vEulerAngles.x << std::endl;
      std::cout << "Pitch  : " << -fdm.vEulerAngles.y << std::endl;
      std::cout << "Yaw    : " << fdm.vEulerAngles.z << std::endl;
      std::cout << "Alt    : " << fdm.vPosition.z << std::endl;
      std::cout << "Thrust : " << fdm.thrust_force << std::endl;
      std::cout << "Speed  : " << fdm.fSpeed / 1.688f << std::endl; // divide by 1.688 to convert ft/s to knots

      if (fdm.flaps) std::cout << "Flaps!\n";
      if (fdm.stalling) std::cout << "Stall!\n";

      std::cout << "===================================================\n";
      current_time += dt;

   }

   return 0;
}


