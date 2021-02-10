
#include <cmath>
#include <cstdio>

#include "globals.hpp"

// compute exact analytical result
void print_exact_result(const float time)
{
   float velocity{};
   float displacement{};
   float acceleration{};
   std::printf("Time:%5.2f: Vel:%5.2f, Dist:%5.2f\n", time, velocity, displacement);
}

// this function progresses the simulation by dt seconds using Euler's basic method
void euler_basic_method(const float dt)
{
    // calculate the total force
    const float F{(T - (C * V))};

    // calculate acceleration
    const float A{F / M};

    // calculate the new velocity at time t + dt, where V is the velocity at time t
    const float Vnew{V + A * dt};

    // calculate the new displacement at time t + dt. where S is the displacement at time t
    const float Snew{S + Vnew * dt};

    // update old velocity and displacement with the new ones
    V = Vnew;
    S = Snew;
}

float eto{};     // truncation error tolerance

// This function progresses the simulation by dt seconds using
// Euler's basic method with an adaptive step size
void euler_adaptive_step_size(const float dt)
{
     float     F;     // total force
     float     A;     // acceleration
     float     Vnew;  // new velocity at time t + dt
     float     Snew;  // new position at time t + dt
     float     V1, V2; // temporary velocity variables
     float     dtnew;  // new time step
     float     et;     // truncation error

     // Take one step of size dt to estimate the new velocity
     F = (T - (C * V));
     A = F / M;
     V1 = V + A * dt;

     // Take two steps of size dt/2 to estimate the new velocity
     F = (T - (C * V));
     A = F / M;
     V2 = V + A * (dt/2);

     F = (T - (C * V2));
     A = F / M;
     V2 = V2 + A * (dt/2);

     // Estimate the truncation error
     et = std::abs(V1 - V2);

     // Estimate a new step size
     dtnew = dt * std::sqrt(eto/et);


     if (dtnew < dt)
     { // take at step at the new smaller step size
          F = (T - (C * V));
          A = F / M;
          Vnew = V + A * dtnew;
          Snew = S + Vnew * dtnew;
     } else
     { // original step size is okay
          Vnew = V1;
          Snew = S + Vnew * dt;
     }

     // Update old velocity and displacement with the new ones
     V = Vnew;
     S = Snew;
}

// This function progresses the simulation by dt seconds using
// the "improved" Euler method
void euler_improved(const float dt)
{
     float     F;     // total force
     float     A;     // acceleration
     float     Vnew;  // new velocity at time t + dt
     float     Snew;  // new position at time t + dt
     float     k1, k2;

     F = (T - (C * V));
     A = F/M;
     k1 = dt * A;

     F = (T - (C * (V + k1)));
     A = F/M;
     k2 = dt * A;

     // Calculate the new velocity at time t + dt
     // where V is the velocity at time t
     Vnew = V + (k1 + k2) / 2;

     // Calculate the new displacement at time t + dt
     // where S is the displacement at time t
     Snew = S + Vnew * dt;

     // Update old velocity and displacement with the new ones
     V = Vnew;
     S = Snew;
}
    
// This function progresses the simulation by dt seconds using
// the Runge-Kutta method
void runge_kutta(const float dt)
{
     float     F;     // total force
     float     A;     // acceleration
     float     Vnew;  // new velocity at time t + dt
     float     Snew;  // new position at time t + dt
     float     k1, k2, k3, k4;

     F = (T - (C * V));
     A = F/M;
     k1 = dt * A;

     F = (T - (C * (V + k1/2)));
     A = F/M;
     k2 = dt * A;

     F = (T - (C * (V + k2/2)));
     A = F/M;
     k3 = dt * A;

     F = (T - (C * (V + k3)));
     A = F/M;
     k4 = dt * A;

     // Calculate the new velocity at time t + dt
     // where V is the velocity at time t
     Vnew = V + (k1 + 2*k2 + 2*k3 + k4) / 6;

     // Calculate the new displacement at time t + dt
     // where S is the displacement at time t
     Snew = S + Vnew * dt;

     // Update old velocity and displacement with the new ones
     V = Vnew;
     S = Snew;
}

