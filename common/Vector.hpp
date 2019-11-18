
#ifndef __Vector_HPP__
#define __Vector_HPP__

#include <cmath>

#include "constants.hpp"

//------------------------------------------------------------------------
// Class: Vector
// Description: a 3D vector
//------------------------------------------------------------------------
class Vector
{
public:
   Vector() = default;
   Vector(const float xi, const float yi, const float zi);

   float magnitude() const;
   void  normalize();
   void  reverse();

   Vector& operator+=(const Vector);
   Vector& operator-=(const Vector);
   Vector& operator*=(const float);
   Vector& operator/=(const float);

   Vector operator-();

   float x{};
   float y{};
   float z{};
};

inline Vector::Vector(const float xi, const float yi, const float zi)
: x(xi), y(yi), z(zi)
{}

inline float Vector::magnitude() const
{
   return static_cast<float>(std::sqrt(x*x + y*y + z*z));
}

inline void Vector::normalize()
{
   float m{static_cast<float>(std::sqrt(x*x + y*y + z*z))};
   if (m <= tol) {
      m = 1.0f;
   }
   x /= m;
   y /= m;
   z /= m;

   if (std::fabs(x) < tol) {
       x = 0.0f;
   }
   if (std::fabs(y) < tol) {
       y = 0.0f;
   }
   if (std::fabs(z) < tol) {
      z = 0.0f;
   }
}

inline void Vector::reverse()
{
   x = -x;
   y = -y;
   z = -z;
}

inline Vector& Vector::operator+=(const Vector u)
{
   x += u.x;
   y += u.y;
   z += u.z;
   return *this;
}

inline Vector& Vector::operator-=(const Vector u)
{
   x -= u.x;
   y -= u.y;
   z -= u.z;
   return *this;
}

inline Vector& Vector::operator*=(const float s)
{
   x *= s;
   y *= s;
   z *= s;
   return *this;
}

inline Vector& Vector::operator/=(const float s)
{
   x /= s;
   y /= s;
   z /= s;
   return *this;
}

inline Vector Vector::operator-()
{
   return Vector(-x, -y, -z);
}

//---------------------------------------------------------
// functions and operator overloads
//---------------------------------------------------------

inline Vector operator+(const Vector u, const Vector v)
{
   return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vector operator-(const Vector u, const Vector v)
{
   return Vector(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vector operator^(const Vector u, const Vector v)
{
   return Vector(u.y*v.z - u.z*v.y,
                -u.x*v.z + u.z*v.x,
                 u.x*v.y - u.y*v.x);
}

// dot product
inline float operator*(const Vector u, const Vector v)
{
   return (u.x*v.x + u.y*v.y + u.z*v.z);
}

inline Vector operator*(const float s, const Vector u)
{
   return Vector(u.x*s, u.y*s, u.z*s);
}

inline Vector operator*(const Vector u, const float s)
{
   return Vector(u.x*s, u.y*s, u.z*s);
}

inline Vector operator/(const Vector u, const float s)
{
   return Vector(u.x/s, u.y/s, u.z/s);
}

#endif

