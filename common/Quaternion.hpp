
#ifndef __Quaternion_HPP__
#define __Quaternion_HPP__

#include <cmath>

#include "Vector.hpp"
#include "math_utils.hpp"

class Quaternion
{
public:
   float  n{};   // scalar part
   Vector v;     // vector part: v.x, v.y, v.z

   Quaternion() = default;
   Quaternion(const float e0, const float e1, const float e2, const float e3);

   float magnitude() const;
   Vector get_vector() const;
   float  get_scalar() const;
   Quaternion operator+=(const Quaternion);
   Quaternion operator-=(Quaternion);
   Quaternion operator*=(const float);
   Quaternion operator/=(const float);
   Quaternion operator~() const         { return Quaternion(n, -v.x, -v.y,-v.z); }
};

inline Quaternion::Quaternion(const float e0, const float e1, const float e2, const float e3)
: n(e0), v(e1, e2, e3)
{}

inline float Quaternion::magnitude() const
{
   return static_cast<float>(std::sqrt(n*n + v.x*v.x + v.y*v.y + v.z*v.z));
}

inline Vector Quaternion::get_vector() const
{
   return Vector(v.x, v.y, v.z);
}

inline float Quaternion::get_scalar() const
{
   return n;
}

inline Quaternion Quaternion::operator+=(const Quaternion q)
{
   n += q.n;
   v.x += q.v.x;
   v.y += q.v.y;
   v.z += q.v.z;
   return *this;
}

inline Quaternion Quaternion::operator-=(const Quaternion q)
{
   n -= q.n;
   v.x -= q.v.x;
   v.y -= q.v.y;
   v.z -= q.v.z;
   return *this;
}

inline Quaternion Quaternion::operator*=(const float s)
{
   n *= s;
   v.x *= s;
   v.y *= s;
   v.z *= s;
   return *this;
}

inline Quaternion Quaternion::operator/=(const float s)
{
   n /= s;
   v.x /= s;
   v.y /= s;
   v.z /= s;
   return *this;
}

//---------------------------------------------------------
// functions and operator overloads
//---------------------------------------------------------

inline Quaternion operator+(const Quaternion q1, const Quaternion q2)
{
   return Quaternion(q1.n   + q2.n,
                     q1.v.x + q2.v.x,
                     q1.v.y + q2.v.y,
                     q1.v.z + q2.v.z);
}

inline Quaternion operator-(const Quaternion q1, const Quaternion q2)
{
   return Quaternion(q1.n   - q2.n,
                     q1.v.x - q2.v.x,
                     q1.v.y - q2.v.y,
                     q1.v.z - q2.v.z);
}

inline Quaternion operator*(const Quaternion q1, const Quaternion q2)
{
   return Quaternion(q1.n*q2.n - q1.v.x*q2.v.x - q1.v.y*q2.v.y - q1.v.z*q2.v.z,
                     q1.n*q2.v.x + q1.v.x*q2.n + q1.v.y*q2.v.z - q1.v.z*q2.v.y,
                     q1.n*q2.v.y + q1.v.y*q2.n + q1.v.z*q2.v.x - q1.v.x*q2.v.z,
                     q1.n*q2.v.z + q1.v.z*q2.n + q1.v.x*q2.v.y - q1.v.y*q2.v.x);
}

inline Quaternion operator*(const Quaternion q, const float s)
{
   return Quaternion(q.n*s, q.v.x*s, q.v.y*s, q.v.z*s);
}

inline Quaternion operator*(const float s, const Quaternion q)
{
   return Quaternion(q.n*s, q.v.x*s, q.v.y*s, q.v.z*s);
}

inline Quaternion operator*(const Quaternion q, const Vector v)
{
   return Quaternion(-(q.v.x*v.x + q.v.y*v.y + q.v.z*v.z),
                       q.n*v.x + q.v.y*v.z - q.v.z*v.y,
                       q.n*v.y + q.v.z*v.x - q.v.x*v.z,
                       q.n*v.z + q.v.x*v.y - q.v.y*v.x);
}

inline Quaternion operator*(const Vector v, const Quaternion q)
{
   return Quaternion(-(q.v.x*v.x + q.v.y*v.y + q.v.z*v.z),
                       q.n*v.x + q.v.z*v.y - q.v.y*v.z,
                       q.n*v.y + q.v.x*v.z - q.v.z*v.x,
                       q.n*v.z + q.v.y*v.x - q.v.x*v.y);
}

inline Quaternion operator/(const Quaternion q, const float s)
{
   return Quaternion(q.n/s, q.v.x/s, q.v.y/s, q.v.z/s);
}

inline float QGetAngle(const Quaternion q)
{
   return 2.0f * std::acos(q.n);
}

inline Vector QGetAxis(const Quaternion q)
{
   Vector v;
   float m{};

   v = q.get_vector();
   m = v.magnitude();

   if (m <= tol) {
      return Vector();
   }

   return v/m;
}

inline Quaternion QRotate(const Quaternion q1, const Quaternion q2)
{
   return q1*q2*(~q1);
}

inline Vector QVRotate(const Quaternion q, const Vector v)
{
   Quaternion t;

   t = q*v*(~q);

   return t.get_vector();
}

inline float DegreesToRadians(const float deg)
{
   return deg * PI / 180.0f;
}

inline float RadiansToDegrees(const float rad)
{
   return rad * 180.0f / PI;
}

inline Quaternion MakeQFromEulerAngles(const float x, const float y, const float z)
{
   Quaternion q;
   const double roll{DegreesToRadians(x)};
   const double pitch{DegreesToRadians(y)};
   const double yaw{DegreesToRadians(z)};

   const double cyaw{std::cos(0.5f * yaw)};
   const double cpitch{std::cos(0.5f * pitch)};
   const double croll{std::cos(0.5f * roll)};

   const double syaw{std::sin(0.5f * yaw)};
   const double spitch{std::sin(0.5f * pitch)};
   const double sroll{std::sin(0.5f * roll)};

   const double cyawcpitch{cyaw * cpitch};
   const double syawspitch{syaw * spitch};
   const double cyawspitch{cyaw * spitch};
   const double syawcpitch{syaw * cpitch};

   q.n = static_cast<float>(cyawcpitch * croll + syawspitch * sroll);
   q.v.x = static_cast<float>(cyawcpitch * sroll - syawspitch * croll);
   q.v.y = static_cast<float>(cyawspitch * croll + syawcpitch * sroll);
   q.v.z = static_cast<float>(syawcpitch * croll - cyawspitch * sroll);

   return q;
}

inline Vector MakeEulerAnglesFromQ(const Quaternion q)
{
   const double q00{q.n * q.n};
   const double q11{q.v.x * q.v.x};
   const double q22{q.v.y * q.v.y};
   const double q33{q.v.z * q.v.z};

   const double r11{q00 + q11 - q22 - q33};
   const double r21{2 * (q.v.x*q.v.y + q.n*q.v.z)};
   const double r31{2 * (q.v.x*q.v.z - q.n*q.v.y)};
   const double r32{2 * (q.v.y*q.v.z + q.n*q.v.x)};
   const double r33{q00 - q11 - q22 + q33};

   Vector u;
   const double tmp{std::fabs(r31)};
   if (tmp > 0.999999) {
      const double r12 = 2 * (q.v.x*q.v.y - q.n*q.v.z);
      const double r13 = 2 * (q.v.x*q.v.z + q.n*q.v.y);

      u.x = RadiansToDegrees(0.0f);                                           // roll
      u.y = RadiansToDegrees(static_cast<float>(-(PI/2) * r31/tmp));          // pitch
      u.z = RadiansToDegrees(static_cast<float>(std::atan2(-r12, -r31*r13))); // yaw
      return u;
   }

   u.x = RadiansToDegrees(static_cast<float>(std::atan2(r32, r33))); // roll
   u.y = RadiansToDegrees(static_cast<float>(std::asin(-r31)));      // pitch
   u.z = RadiansToDegrees(static_cast<float>(std::atan2(r21, r11))); // yaw
   return u;
}

#endif

