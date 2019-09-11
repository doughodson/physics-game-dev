
#ifndef __Matrix3x3_HPP__
#define __Matrix3x3_HPP__

#include "Vector.hpp"

//------------------------------------------------------------------------
// class: Matrix3x3
// description: a 3x3 matrix
//------------------------------------------------------------------------
class Matrix3x3
{
public:
   // elements eij: i -> row, j -> column
   float e11{}, e12{}, e13{};
   float e21{}, e22{}, e23{};
   float e31{}, e32{}, e33{};

   Matrix3x3() = default;
   Matrix3x3(const float r1c1, const float r1c2, const float r1c3,
             const float r2c1, const float r2c2, const float r2c3,
             const float r3c1, const float r3c2, const float r3c3);

   float det() const;
   Matrix3x3 Transpose() const;
   Matrix3x3 Inverse() const;

   Matrix3x3& operator+=(const Matrix3x3);
   Matrix3x3& operator-=(const Matrix3x3);
   Matrix3x3& operator*=(const float);
   Matrix3x3& operator/=(const float);
};

inline Matrix3x3::Matrix3x3(const float r1c1, const float r1c2, const float r1c3,
                            const float r2c1, const float r2c2, const float r2c3,
                            const float r3c1, const float r3c2, const float r3c3)
: e11(r1c1), e12(r1c2), e13(r1c3),
  e21(r2c1), e22(r2c2), e23(r2c3),
  e31(r3c1), e32(r3c2), e33(r3c3)
{}

inline float Matrix3x3::det() const
{
   return e11*e22*e33 -
          e11*e32*e23 +
          e21*e32*e13 -
          e21*e12*e33 +
          e31*e12*e23 -
          e31*e22*e13;
}

inline Matrix3x3 Matrix3x3::Transpose() const
{
   return Matrix3x3(e11,e21,e31,e12,e22,e32,e13,e23,e33);
}

inline Matrix3x3 Matrix3x3::Inverse() const
{
   float d{e11*e22*e33 -
           e11*e32*e23 +
           e21*e32*e13 -
           e21*e12*e33 +
           e31*e12*e23 -
           e31*e22*e13};

   if (d == 0) {
      d = 1.0f;
   }

   return Matrix3x3((e22*e33-e23*e32)/d,
                   -(e12*e33-e13*e32)/d,
                    (e12*e23-e13*e22)/d,
                   -(e21*e33-e23*e31)/d,
                    (e11*e33-e13*e31)/d,
                   -(e11*e23-e13*e21)/d,
                    (e21*e32-e22*e31)/d,
                   -(e11*e32-e12*e31)/d,
                    (e11*e22-e12*e21)/d);
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3 m)
{
   e11 += m.e11;
   e12 += m.e12;
   e13 += m.e13;
   e21 += m.e21;
   e22 += m.e22;
   e23 += m.e23;
   e31 += m.e31;
   e32 += m.e32;
   e33 += m.e33;
   return *this;
}

inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 m)
{
   e11 -= m.e11;
   e12 -= m.e12;
   e13 -= m.e13;
   e21 -= m.e21;
   e22 -= m.e22;
   e23 -= m.e23;
   e31 -= m.e31;
   e32 -= m.e32;
   e33 -= m.e33;
   return *this;
}

inline Matrix3x3& Matrix3x3::operator*=(const float s)
{
   e11 *= s;
   e12 *= s;
   e13 *= s;
   e21 *= s;
   e22 *= s;
   e23 *= s;
   e31 *= s;
   e32 *= s;
   e33 *= s;
   return *this;
}

inline Matrix3x3& Matrix3x3::operator/=(const float s)
{
   e11 /= s;
   e12 /= s;
   e13 /= s;
   e21 /= s;
   e22 /= s;
   e23 /= s;
   e31 /= s;
   e32 /= s;
   e33 /= s;
   return *this;
}

//---------------------------------------------------------
// operator overloads
//---------------------------------------------------------

inline Matrix3x3 operator+(const Matrix3x3 m1, const Matrix3x3 m2)
{
   return Matrix3x3(m1.e11+m2.e11,
                    m1.e12+m2.e12,
                    m1.e13+m2.e13,
                    m1.e21+m2.e21,
                    m1.e22+m2.e22,
                    m1.e23+m2.e23,
                    m1.e31+m2.e31,
                    m1.e32+m2.e32,
                    m1.e33+m2.e33);
}

inline Matrix3x3 operator-(const Matrix3x3 m1, const Matrix3x3 m2)
{
   return Matrix3x3(m1.e11-m2.e11,
                    m1.e12-m2.e12,
                    m1.e13-m2.e13,
                    m1.e21-m2.e21,
                    m1.e22-m2.e22,
                    m1.e23-m2.e23,
                    m1.e31-m2.e31,
                    m1.e32-m2.e32,
                    m1.e33-m2.e33);
}

inline Matrix3x3 operator/(const Matrix3x3 m, const float s)
{
   return Matrix3x3(m.e11/s, m.e12/s, m.e13/s,
                    m.e21/s, m.e22/s, m.e23/s,
                    m.e31/s, m.e32/s, m.e33/s);
}

inline Matrix3x3 operator*(const Matrix3x3 m1, const Matrix3x3 m2)
{
   return Matrix3x3(m1.e11*m2.e11 + m1.e12*m2.e21 + m1.e13*m2.e31,
                    m1.e11*m2.e12 + m1.e12*m2.e22 + m1.e13*m2.e32,
                    m1.e11*m2.e13 + m1.e12*m2.e23 + m1.e13*m2.e33,
                    m1.e21*m2.e11 + m1.e22*m2.e21 + m1.e23*m2.e31,
                    m1.e21*m2.e12 + m1.e22*m2.e22 + m1.e23*m2.e32,
                    m1.e21*m2.e13 + m1.e22*m2.e23 + m1.e23*m2.e33,
                    m1.e31*m2.e11 + m1.e32*m2.e21 + m1.e33*m2.e31,
                    m1.e31*m2.e12 + m1.e32*m2.e22 + m1.e33*m2.e32,
                    m1.e31*m2.e13 + m1.e32*m2.e23 + m1.e33*m2.e33 );
}

inline Matrix3x3 operator*(const Matrix3x3 m, const float s)
{
   return Matrix3x3(m.e11*s, m.e12*s, m.e13*s,
                    m.e21*s, m.e22*s, m.e23*s,
                    m.e31*s, m.e32*s, m.e33*s);
}

inline Matrix3x3 operator*(const float s, const Matrix3x3 m)
{
   return Matrix3x3(m.e11*s, m.e12*s, m.e13*s,
                    m.e21*s, m.e22*s, m.e23*s,
                    m.e31*s, m.e32*s, m.e33*s);
}

inline Vector operator*(const Matrix3x3 m, const Vector u)
{
   return Vector(m.e11*u.x + m.e12*u.y + m.e13*u.z,
                 m.e21*u.x + m.e22*u.y + m.e23*u.z,
                 m.e31*u.x + m.e32*u.y + m.e33*u.z);
}

inline Vector operator*(const Vector u, const Matrix3x3 m)
{
   return Vector(u.x*m.e11 + u.y*m.e21 + u.z*m.e31,
                 u.x*m.e12 + u.y*m.e22 + u.z*m.e32,
                 u.x*m.e13 + u.y*m.e23 + u.z*m.e33);
}

#endif

