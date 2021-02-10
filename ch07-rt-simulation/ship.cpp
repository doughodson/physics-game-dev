
#include "ship.hpp"
#include <cstdio>

// initialize chapter 4 example parameters
void init_example(Ship* s)
{
    s->thrust = 20000.0;    // propeller thrust units
    s->drag_coef = 1000.0;  // drag coefficient
    s->mass = 10000.0;      // mass units

    s->time = 0.0;          // time starts at 0.0
    s->velocity = 0.0;      // init velocity
    s->displacement = 0.0;  // init displacement
}

void print_ship(const Ship& s)
{
    std::printf("Time:%5.2f: Vel:%5.2f, Dist:%5.2f\n", s.time, s.velocity, s.displacement);
}

