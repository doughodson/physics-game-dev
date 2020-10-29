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

   float fMass{};
   Vector vDCoords;
   Vector vCGCoords;
   Vector vLocalInertia;
   float fIncidence{};
   float fDihedral{};
   Vector vNormal;
   float fArea{};
   int iFlap{};
};

#endif
