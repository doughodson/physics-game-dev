
#include <cmath>
#include <cstdio>

#include "ship.hpp"

void method_exact(Ship* s, const float time)
{
   // convenience variables
   const float thrust{s->thrust};
   const float drag_coef{s->drag_coef};
   const float mass{s->mass};
   // calculate values
   const float velocity{ (thrust / drag_coef) - (std::exp(-drag_coef * time / s->mass)) * (thrust / drag_coef) };
   const float displacement{ (thrust / drag_coef) * time + (thrust / drag_coef) * (mass / drag_coef)
               * std::exp(-drag_coef * time / mass) - (thrust / drag_coef) * (mass / drag_coef) };
   // update ship
   s->time = time;
   s->velocity = velocity;
   s->displacement = displacement;
}

// this function progresses the simulation by dt seconds using Euler's basic method
void method_euler_basic(Ship* s, const float dt)
{
   // calculate the total force
   const float total_force{ (s->thrust - (s->drag_coef * s->velocity)) };

   // calculate acceleration
   const float acceleration{ total_force / s->mass };

   // calculate the new velocity at time t + dt, where V is the velocity at time t
   const float velocity_new{ s->velocity + acceleration * dt };

   // calculate the new displacement at time t + dt. where S is the displacement at time t
   const float displacement_new{ s->displacement + velocity_new * dt };

   // update time, velocity and displacement
   s->time += dt;
   s->velocity = velocity_new;
   s->displacement = displacement_new;
}

void method_euler_adaptive_step_size(Ship* s, const float dt)
{
   // convenience variables
   const float thrust{s->thrust};
   const float drag_coef{s->drag_coef};
   const float mass{s->mass};
   const float time{s->time + dt};
   const float velocity{s->velocity};
   const float displacement{s->displacement};

   float eto{0.001f};     // truncation error tolerance

   // take one step of size dt to estimate the new velocity
   float F{(thrust - (drag_coef * velocity))};  // total force
   float A{F / mass};                           // acceleration
   float V1{velocity + A * dt};                 // velocity

   // take two steps of size dt/2 to estimate the new velocity
   F = (thrust - (drag_coef * velocity));
   A = F / mass;
   float V2{ velocity + A * (dt / 2)};   // velocity

   F = (thrust - (drag_coef * V2));
   A = F / mass;
   V2 = V2 + A * (dt / 2);

   // estimate the truncation error
   float et{std::abs(V1 - V2)};

// std::printf("truncation error: %5.2f\n", et);

   // estimate a new step size
   float dtnew{dt * std::sqrt(eto / et)};

// std::printf("dtnew: %5.2f\n", et);


   float Vnew{};   // new velocity at time t + dt
   float Snew{};   // new position at time t + dt

   if (dtnew < dt) { 
      // take at step at the new smaller step size
      F = (thrust - (drag_coef * velocity));
      A = F / mass;
      Vnew = velocity + A * dtnew;
      Snew = displacement + Vnew * dtnew;
   } else {
      // original step size is okay
      Vnew = V1;
      Snew = displacement + Vnew * dt;
   }

   // update time, velocity and displacement
   s->time += dtnew;
   s->velocity = Vnew;
   s->displacement = Snew;
}

void method_euler_improved(Ship* s, const float dt)
{
}

/*
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
*/

void method_runge_kutta(Ship* s, const float dt)
{
   // convenience variables
   const float thrust{ s->thrust };
   const float drag_coef{ s->drag_coef };
   const float mass{ s->mass };
   const float time{ s->time + dt };
   const float velocity{ s->velocity };
   const float displacement{ s->displacement };

   float     F;     // total force
   float     A;     // acceleration
   float     Vnew;  // new velocity at time t + dt
   float     Snew;  // new position at time t + dt
   float     k1, k2, k3, k4;

    F = (thrust - (drag_coef * velocity));
    A = F / mass;
    k1 = dt * A;

    F = (thrust - (drag_coef * (velocity + k1 / 2)));
    A = F / mass;
    k2 = dt * A;

    F = (thrust - (drag_coef * (velocity + k2 / 2)));
    A = F / mass;
    k3 = dt * A;

    F = (thrust - (drag_coef * (velocity + k3)));
    A = F / mass;
    k4 = dt * A;

    // calculate the new velocity at time t + dt where V is the velocity at time t
    Vnew = velocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

    // calculate the new displacement at time t + dt where S is the displacement at time t
    Snew = displacement + Vnew * dt;

    // update time, velocity and displacement
    s->time += dt;
    s->velocity = Vnew;
    s->displacement = Snew;
}

/*
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
*/
