#ifndef VECTOR3_H
#define VECTOR3_H

#include "Point3.h"
#include <string>
#include <stdio.h>
#include <array>

// concrete class for vector of size 3
class Vector3 {
protected:
  Point3 P;

public:
  Vector3() : P() {}
  // Construct from 2 SPoints, vector from p1 to p2
  Vector3(const Point3 &p1, const Point3 &p2) : P(p2 - p1) {}
  // Construct from a single SPoint, vector from origin to p1
  Vector3(const Point3 &p1) : P(p1) {}
  Vector3(double x, double y, double z) : P(x, y, z) {}
  Vector3(double v) : P(v, v, v) {}
  Vector3(const double *array) : P(array) {}
  Vector3(const Vector3 &v) : P(v.P) {}
  double x(void) const { return P.x(); }
  double y(void) const { return P.y(); }
  double z(void) const { return P.z(); }
  double norm() const { return std::sqrt(this->normSq()); }
  double normSq() const { return P[0] * P[0] + P[1] * P[1] + P[2] * P[2]; }

  double normalize()
  {
    double n = norm();
    if(n) {
      P[0] /= n;
      P[1] /= n;
      P[2] /= n;
    }
    return n;
  }
  Vector3 unit() const
  {
    Vector3 y(*this);
    y.normalize();
    return y;
  }
  void negate()
  {
    P[0] = -P[0];
    P[1] = -P[1];
    P[2] = -P[2];
  }
  // why both [] and (), why not
  double &operator[](int i) { return P[i]; }
  double operator[](int i) const { return P[i]; }
  double &operator()(int i) { return P[i]; }
  double operator()(int i) const { return P[i]; }
  Vector3 &operator+=(const Vector3 &a)
  {
    P[0] += a[0];
    P[1] += a[1];
    P[2] += a[2];
    return *this;
  }
  Vector3 &operator-=(const Vector3 &a)
  {
    P[0] -= a[0];
    P[1] -= a[1];
    P[2] -= a[2];
    return *this;
  }
  Vector3 &operator*=(const Vector3 &a)
  {
    P[0] *= a[0];
    P[1] *= a[1];
    P[2] *= a[2];
    return *this;
  }
  Vector3 &operator*=(const double v)
  {
    P[0] *= v;
    P[1] *= v;
    P[2] *= v;
    return *this;
  }
  Vector3 &operator=(const Vector3 &a)
  {
    P[0] = a[0];
    P[1] = a[1];
    P[2] = a[2];
    return *this;
  }
  Vector3 &operator=(double v)
  {
    P[0] = v;
    P[1] = v;
    P[2] = v;
    return *this;
  }
  operator double *() { return P; }
  void print(const std::string &name = "") const
  {
 //   Vector \'%s\':  %f  %f  %f", name.c_str(), P[0], P[1], P[2]);
  }
  Point3 point() const { return P; }
  int getMaxValue(double &val) const
  {
    if((P[0] >= P[1]) && (P[0] >= P[2])) {
      val = P[0];
      return 0;
    }
    else if((P[1] >= P[0]) && (P[1] >= P[2])) {
      val = P[1];
      return 1;
    }
    else {
      val = P[2];
      return 2;
    }
  }
  const double *data() const { return P.data(); }
  double *data() { return P.data(); }
  void axpy(const double a, const Vector3 &y)
  {
    for(int i = 0; i < 3; i++) { P[i] += (a * y[i]); }
  }
  // implicit conversion to std::array<double,3>
  operator std::array<double, 3>() const { return {{P[0], P[1], P[2]}}; }
};

inline double dot(const Vector3 &a, const Vector3 &b)
{
  return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

inline double norm(const Vector3 &v) { return sqrt(dot(v, v)); }

inline double normSq(const Vector3 &v) { return dot(v, v); }

inline Vector3 crossprod(const Vector3 &a, const Vector3 &b)
{
  return Vector3(a.y() * b.z() - b.y() * a.z(),
                  -(a.x() * b.z() - b.x() * a.z()),
                  a.x() * b.y() - b.x() * a.y());
}

inline double angle(const Vector3 &a, const Vector3 &b)
{
  double cosTheta = dot(a, b);
  double sinTheta = norm(crossprod(a, b));
  return atan2(sinTheta, cosTheta);
}

inline double signedAngle(const Vector3 &a, const Vector3 &b,
                          const Vector3 &n)
{
  double cosTheta = dot(a, b);
  double sinTheta = dot(crossprod(a, b), n);
  return atan2(sinTheta, cosTheta);
}

inline Vector3 operator*(double m, const Vector3 &v)
{
  return Vector3(v[0] * m, v[1] * m, v[2] * m);
}

inline Vector3 operator*(const Vector3 &v, double m)
{
  return Vector3(v[0] * m, v[1] * m, v[2] * m);
}

inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
{
  return Vector3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
  return Vector3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

inline Point3 operator+(const Point3 &a, const Vector3 &b)
{
  return Point3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
  return Vector3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline Point3 operator-(const Point3 &a, const Vector3 &b)
{
  return Point3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline Vector3 operator-(const Vector3 &a)
{
  return Vector3(-a[0], -a[1], -a[2]);
}

inline void buildOrthoBasis_naive(Vector3 &dir, Vector3 &dir1, Vector3 &dir2)
{
  dir.normalize();
  if(dir[1] != 0.0 && dir[2] != 0.0) {
    dir1 = Vector3(1.0, 0.0, -dir[0] / dir[2]);
    dir2 =
      Vector3(dir[0] / dir[2],
               -(dir[0] * dir[0] + dir[2] * dir[2]) / (dir[1] * dir[2]), 1.0);
  }
  else if(dir[0] != 0.0 && dir[2] != 0.0) {
    dir1 = Vector3(-dir[1] / dir[0], 1.0, 0.0);
    dir2 = Vector3(1.0, dir[1] / dir[0],
                    -(dir[1] * dir[1] + dir[0] * dir[0]) / (dir[0] * dir[2]));
  }
  else if(dir[0] != 0.0 && dir[1] != 0.0) {
    dir1 = Vector3(0.0, -dir[2] / dir[1], 1.0);
    dir2 = Vector3(-(dir[1] * dir[1] + dir[2] * dir[2]) / (dir[0] * dir[1]),
                    1.0, dir[2] / dir[1]);
  }
  else if(dir[0] == 0.0 && dir[1] == 0.0) {
    dir1 = Vector3(0.0, 1.0, 0.0);
    dir2 = Vector3(1.0, 0.0, 0.0);
  }
  else if(dir[1] == 0.0 && dir[2] == 0.0) {
    dir1 = Vector3(0.0, 1.0, 0.0);
    dir2 = Vector3(0.0, 0.0, 1.0);
  }
  else if(dir[0] == 0.0 && dir[2] == 0.0) {
    dir1 = Vector3(1.0, 0.0, 0.0);
    dir2 = Vector3(0.0, 0.0, 1.0);
  }
  else {
  //  Msg::Error("Problem with computing orthoBasis");
  }
  // printf("XYZ =%g %g %g r=%g dir0 = %g %g %g dir1 = %g %g %g dir2 =%g %g
  // %g\n", 	  x,y,z,d, dir[0], dir[1], dir[2], dir1[0], dir1[1], dir1[2],
  // dir2[0], dir2[1], dir2[2] ); printf("0x1 =%g 1x2=%g 2x1=%g \n", dot(dir,
  // dir1), dot(dir1,dir2), dot(dir2,dir));
  dir1.normalize();
  dir2.normalize();
}

// given a normal, build tangent and binormal
inline void buildOrthoBasis(Vector3 &normal, Vector3 &tangent,
                            Vector3 &binormal)
{
  // pick any Unit-Vector that's not parallel to normal:
  normal.normalize();
  if(fabs(normal[0]) > fabs(normal[1]))
    tangent = Vector3(0.0, 1.0, 0.0);
  else
    tangent = Vector3(1.0, 0.0, 0.0);

  // build a binormal from tangent and normal:
  binormal = crossprod(tangent, normal);
  double t1 = binormal.normalize();

  // and correct the tangent from the binormal and the normal.
  tangent = crossprod(normal, binormal);
  double t2 = tangent.normalize();

  if(t1 == 0.0 || t2 == 0.0) buildOrthoBasis_naive(normal, tangent, binormal);
}

// given a normal and guess tangent, build  binormal
inline void buildOrthoBasis2(Vector3 &normal, Vector3 &tangent,
                             Vector3 &binormal)
{
  normal.normalize();
  tangent.normalize();

  // build a binormal from tangent and normal:
  binormal = crossprod(tangent, normal);
  double t1 = binormal.normalize();

  // and correct the tangent from the binormal and the normal.
  tangent = crossprod(normal, binormal);
  double t2 = tangent.normalize();

  if(t1 == 0.0 || t2 == 0.0) buildOrthoBasis_naive(normal, tangent, binormal);
}

#endif
