
#include "ship.hpp"

void init_exact_displacment(const float s1);
void print_exact_result(const float time);

void euler_basic_method(const float dt);
void euler_adaptive_step_size(const float dt);
void euler_improved(const float dt);
void runge_kutta(const float dt);

void exact_method(Ship*, const float time);
void euler_basic_method(Ship*, const float dt);
void euler_adaptive_step_size(Ship*, const float dt);
void euler_improved(Ship*, const float dt);
void runge_kutta(Ship*, const float dt);
