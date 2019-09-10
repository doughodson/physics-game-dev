
#ifndef _Vector_HPP_
#define _Vector_HPP_

#include <cmath>

float const tol{0.0001f};

//------------------------------------------------------------------------
// class: Vector
// description: a 3D vector
//------------------------------------------------------------------------
class Vector
{
public:
   float x{};
   float y{};
   float z{};

   Vector() = default;
   Vector(const float xi, const float yi, const float zi);

   float Magnitude();
   void  Normalize();
   void  Reverse();

   Vector& operator+=(const Vector);
   Vector& operator-=(const Vector);
   Vector& operator*=(const float);
   Vector& operator/=(const float);

   Vector operator-();
};

inline Vector::Vector(const float xi, const float yi, const float zi)
: x(xi), y(yi), z(zi)
{}
    
inline float Vector::Magnitude()
{
   return static_cast<float>(std::sqrt(x*x + y*y + z*z));
}
    
inline void Vector::Normalize()
{
   float m{static_cast<float>(std::sqrt(x*x + y*y + z*z));
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
   
inline void Vector::Reverse()
{
   x = -x;
   y = -y;
   z = -z;
}

inline Vector& Vector::operator+=(Vector u)
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
// useful functions (NOT vector methods!)
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
                 u.x*v.y - u.y*v.x );
}

//
// dot product
//
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

inline float TripleScalarProduct(const Vector u, const Vector v, const Vector w)
{
   return static_cast<float>((u.x * (v.y*w.z - v.z*w.y)) +
                             (u.y * (-v.x*w.z + v.z*w.x)) +
                             (u.z * (v.x*w.y - v.y*w.x)));
}
    
#endif

