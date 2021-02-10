
#include <cstdio>

float T{};     // thrust
float C{};     // drag coefficient
float M{};     // mass
float V{};     // velocity
float S{};     // displacement

// from chapter 4
void init_book_example()
{
    T = 20000.0;  // propeller thrust units
    C = 1000.0;   // drag coefficient
    M = 10000.0;  // mass units
    V = 0.0;      // init velocity
    S = 0.0;      // init displacement
}

void print_initial_conditions()
{
    std::printf("Thrust:%5.2f, Drag Coeff:%5.2f, Mass:%5.2f, Vel:%5.2f, Dist:%5.2f\n", T, C, V, M, S);
}

void print_globals(const float time)
{
    std::printf("Time:%5.2f: Vel:%5.2f, Dist:%5.2f\n", time, V, S);
}

