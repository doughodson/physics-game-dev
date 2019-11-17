
#ifndef __math_utils_HPP__
#define __math_utils_HPP__

#include <cmath>

#include "Vector.hpp"
#include "constants.hpp"

//inline float DegreesToRadians(const float deg);
//inline float RadiansToDegrees(const float rad);

//inline float TripleScalarProduct(Vector u, Vector v, Vector w);
//inline Vector VRotate2D(float angle, Vector u);

inline float DegreesToRadians(const float deg)
{
	return deg * pi / 180.0f;
}

inline float RadiansToDegrees(const float rad)
{	
	return rad * 180.0f / pi;
}

// triple scalar product (u dot (v cross w))
inline float TripleScalarProduct(Vector u, Vector v, Vector w)
{
   return float( (u.x * (v.y*w.z - v.z*w.y)) +
                 (u.y * (-v.x*w.z + v.z*w.x)) +
                 (u.z * (v.x*w.y - v.y*w.x)) );
	//return u*(v^w);
}

inline Vector VRotate2D(float angle, Vector u)
{
   float x{ static_cast<float>(u.x * std::cos(DegreesToRadians(-angle)) + u.y * std::sin(DegreesToRadians(-angle))) };
   float y{ static_cast<float>(-u.x * std::sin(DegreesToRadians(-angle)) + u.y * std::cos(DegreesToRadians(-angle))) };

   return Vector(x, y, 0);
}

#endif
