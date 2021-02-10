
#include <iostream>

#include "ship.hpp"
#include "methods.hpp"

// execute basic euler method
void execute_euler_basic()
{
   const float dt = 0.05f; // seconds
   Ship s_exact;
   Ship s_method;

   init_book_example(&s_exact);
   init_book_example(&s_method);
   for (float time{}; time <= 43.0; time += dt) {
      std::cout << "Exact result  : "; print_ship(s_exact);
      std::cout << "Method result : "; print_ship(s_method);
      method_exact(&s_exact, dt);
      method_euler_basic(&s_method, dt);
      std::cout << std::endl;
   }
}

// execute adaptive step size euler method
void execute_euler_adaptive_step_size()
{
   const float dt = 0.4f; // seconds
   Ship s_exact;
   Ship s_method;

   init_book_example(&s_exact);
   init_book_example(&s_method);
   for (float time{}; time <= 43.0; time += dt) {
      std::cout << "Exact result  : "; print_ship(s_exact);
      std::cout << "Method result : "; print_ship(s_method);
      method_exact(&s_exact, dt);
      method_euler_adaptive_step_size(&s_method, 0.5f);
      std::cout << std::endl;
   }
}

int main(int argc, char** argv)
{
    std::cout << "\n\nEuler Basic Integration Method\n";
    execute_euler_basic();
    std::cout << "\n\nEuler Adaptive Step Size Integration Method\n";
    execute_euler_adaptive_step_size();
    return 0;
}
