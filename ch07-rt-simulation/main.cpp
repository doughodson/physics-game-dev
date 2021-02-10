
#include <iostream>

#include "globals.hpp"
#include "methods.hpp"

int main(int argc, char** argv)
{
    std::cout << "Integration methods\n";
    const float dt=0.05; // seconds

    // basic euler method
    init_book_example();
    print_initial_conditions();
    for (float time{}; time <= 43.0; time+=dt) {
       std::cout << "Exact result  : "; print_exact_result(time);
       std::cout << "Method result : "; print_globals(time);
       euler_basic_method(dt);
    }
    return 0;
}