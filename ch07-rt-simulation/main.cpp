
#include <iostream>

#include "ship.hpp"
#include "methods.hpp"

// execute exact analytical method
void execute_exact()
{
   const float dt = 0.05f; // seconds
   Ship s;

   std::cout << "\n\nExact Integration Method\n";
   init_book_example(&s);
   for (float time{}; time <= 43.0; time += dt) {
      print_ship(s);
      method_exact(&s, time);
   }
}

// execute basic euler method
void execute_euler_basic()
{
   const float dt = 0.05f; // seconds
   Ship s_exact;
   Ship s_method;

   std::cout << "\n\nEuler Basic Integration Method\n";
   init_book_example(&s_exact);
   init_book_example(&s_method);
   for (float time{}; time <= 43.0; time += dt) {
      print_ship_error(s_exact, s_method);
      method_euler_basic(&s_method, dt);
      method_exact(&s_exact, s_method.time);
   }
}

// execute adaptive step size euler method
void execute_euler_adaptive_step_size()
{
   const float dt = 0.05f; // seconds
   Ship s_exact;
   Ship s_method;

   std::cout << "\n\nEuler Adaptive Step Size Integration Method\n";
   init_book_example(&s_exact);
   init_book_example(&s_method);
   for (float time{}; time <= 43.0; time += dt) {
      print_ship_error(s_exact, s_method);
      method_euler_adaptive_step_size(&s_method, dt);
      method_exact(&s_exact, s_method.time);
   }
}

// execute improved euler method
void execute_euler_improved()
{
   const float dt = 0.05f; // seconds
   Ship s_exact;
   Ship s_method;

   std::cout << "\n\nEuler Improved Method\n";
   init_book_example(&s_exact);
   init_book_example(&s_method);
   for (float time{}; time <= 43.0; time += dt) {
      print_ship_error(s_exact, s_method);
      method_euler_improved(&s_method, dt);
      method_exact(&s_exact, s_method.time);
   }
}

// execute runge kutta
void execute_runge_kutta()
{
   const float dt = 0.05f; // seconds
   Ship s_exact;
   Ship s_method;

   std::cout << "\n\nRunge Kutta Method\n";
   init_book_example(&s_exact);
   init_book_example(&s_method);
   for (float time{}; time <= 43.0; time += dt) {
      print_ship_error(s_exact, s_method);
      method_runge_kutta(&s_method, dt);
      method_exact(&s_exact, s_method.time);
   }
}

int main(int argc, char** argv)
{
//   execute_exact();
//   execute_euler_basic();
//   execute_euler_adaptive_step_size();
    execute_euler_improved();
//    execute_runge_kutta();
    return 0;
}
