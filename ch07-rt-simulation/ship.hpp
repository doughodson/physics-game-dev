
#ifndef __Ship_HPP__
#define __Ship_HPP__

class Ship
{
public:
    float thrust{};       // thrust
    float drag_coef{};    // drag coefficient
    float mass{};         // mass

    float time;           // time
    float velocity{};     // velocity
    float displacement{}; // displacement
};

void init_book_example(Ship* s);
void print_ship(const Ship&);
void print_ship_error(const Ship&, const Ship&);

#endif

