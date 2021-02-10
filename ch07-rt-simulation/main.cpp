
#include <iostream>

#include "methods.hpp"
#include "ship.hpp"

int main(int argc, char** argv)
{
    std::cout << "Integration methods\n";
    const float dt=0.05f; // seconds

    // basic euler method
    Ship s_exact;
    Ship s_method;
    init_example(&s_exact);
    init_example(&s_method);
    for (float time{}; time <= 43.0; time += dt) {
        std::cout << "Exact result  : "; print_ship(s_exact);
        std::cout << "Method result : "; print_ship(s_method);
        exact_method(&s_exact, dt);
        euler_basic_method(&s_method, dt);
        std::cout << std::endl;
    }

    return 0;
}
