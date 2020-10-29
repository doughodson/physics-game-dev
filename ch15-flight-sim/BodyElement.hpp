#ifndef __BodyElement_HPP__
#define __BodyElement_HPP__

#include "common/Vector.hpp"
#include "common/Matrix3x3.hpp"
#include "common/Quaternion.hpp"

//------------------------------------------------------------------------------
// Structure: BodyElement
// Description: Data associated with an element that defines a rigid body
//------------------------------------------------------------------------------
struct BodyElement
{
   BodyElement() = default;

   float mass{};              // mass of element
   Vector dsg_coord;          // design coordinate
   Vector cg_coord;           // center of gravity (CG) coordinate
   Vector local_inertia;
   float incidence_angle{};   // incidence angle
   float dihedral_angle{};    // dihedral angle
   Vector normal;             // normal vector (perpendicular) to lifting surface
   float area{};
   int flap{};                // flap position (0 = not deflected, 1 = flap up, -1 = flap down)
};

#endif
