
#include "ship.hpp"
#include <cstdio>
#include <cmath>

// initialize chapter 4 example parameters
void init_book_example(Ship* s)
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

void print_ship_error(const Ship& exact, const Ship& method)
{
    // calculate difference between exact and numerical method
    float percent_err_vel{};
    float percent_err_dsp{};
    if (exact.velocity != 0.0) {
        percent_err_vel = 100.0f*(std::abs(method.velocity - exact.velocity) / exact.velocity);
    }
    if (exact.displacement != 0.0) {
        percent_err_dsp = 100.0f * (std::abs(method.displacement - exact.displacement) / exact.displacement);
    }
    std::printf("Time:%6.2f: Velocity:%6.2f (exact:%6.2f, err:%6.2f%%), Displacement:%6.2f (exact::%6.2f, err:%6.2f%%)\n",
                method.time,
                method.velocity, exact.velocity, percent_err_vel,
                method.displacement, exact.displacement, percent_err_dsp);
}
