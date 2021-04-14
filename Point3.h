#ifndef POINT3_H
#define POINT3_H

#include <cmath>
#include <vector>
#include <array>

// A point in 3-space
class Point3 {
protected:
  double P[3];

public:
  Point3() { P[0] = P[1] = P[2] = 0.; }
  Point3(double x, double y, double z)
  {
    P[0] = x;
    P[1] = y;
    P[2] = z;
  }
  Point3(const double *p)
  {
    P[0] = p[0];
    P[1] = p[1];
    P[2] = p[2];
  }
  Point3(const Point3 &pt)
  {
    P[0] = pt.P[0];
    P[1] = pt.P[1];
    P[2] = pt.P[2];
  }
  virtual ~Point3() {}
  void setPosition(double xx, double yy, double zz);
  void setPosition(const Point3 &pt, const Point3 &dir, const double dist_)
  {
    P[0] = pt.P[0];
    P[1] = pt.P[1];
    P[2] = pt.P[2];
    Point3 a(dir);
    a *= dist_;
    P[0] += a[0];
    P[1] += a[1];
    P[2] += a[2];
  }
  void getPosition(double *xx, double *yy, double *zz) const;
  void position(double *) const;
  inline double x(void) const;
  inline double y(void) const;
  inline double z(void) const;
  double &operator[](int);
  double operator[](int) const;
  Point3 &operator=(const Point3 &p);
  void operator+=(const Point3 &p);
  void operator-=(const Point3 &p);
  void operator*=(double mult);
  void operator/=(double mult);
  Point3 operator*(double mult);
  operator double *() { return P; }
  double distance(const Point3 &p) const;
  // lexicographic
  bool operator<(const Point3 &p) const
  {
    if(P[0] < p.P[0]) return true;
    if(P[0] > p.P[0]) return false;
    if(P[1] < p.P[1]) return true;
    if(P[1] > p.P[1]) return false;
    if(P[2] < p.P[2]) return true;
    return false;
  }
  const double *data() const { return P; }
  double *data() { return P; }
  bool transform(const std::vector<double> &tfo)
  {
    if(tfo.size() != 16) return false;
    double old[3] = {P[0], P[1], P[2]};
    P[0] = P[1] = P[2] = 0.;
    int idx = 0;
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) P[i] += old[j] * tfo[idx++];
      P[i] += tfo[idx++];
    }
    return true;
  }
  // implicit conversion to std::array<double, 3>
  operator std::array<double, 3>() const { return {{P[0], P[1], P[2]}}; }
};

inline Point3 operator+(const Point3 &a, const Point3 &b)
{
  return Point3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

inline Point3 operator-(const Point3 &a, const Point3 &b)
{
  return Point3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

inline void Point3::setPosition(double xx, double yy, double zz)
{
  P[0] = xx;
  P[1] = yy;
  P[2] = zz;
}

inline void Point3::getPosition(double *xx, double *yy, double *zz) const
{
  *xx = P[0];
  *yy = P[1];
  *zz = P[2];
}

inline void Point3::position(double *p) const
{
  p[0] = P[0];
  p[1] = P[1];
  p[2] = P[2];
}

inline double Point3::x(void) const { return P[0]; }

inline double Point3::y(void) const { return P[1]; }

inline double Point3::z(void) const { return P[2]; }

inline Point3 &Point3::operator=(const Point3 &p)
{
  P[0] = p.P[0];
  P[1] = p.P[1];
  P[2] = p.P[2];
  return *this;
}

inline void Point3::operator+=(const Point3 &p)
{
  P[0] += p.P[0];
  P[1] += p.P[1];
  P[2] += p.P[2];
}

inline void Point3::operator-=(const Point3 &p)
{
  P[0] -= p.P[0];
  P[1] -= p.P[1];
  P[2] -= p.P[2];
}

inline void Point3::operator*=(double mult)
{
  P[0] *= mult;
  P[1] *= mult;
  P[2] *= mult;
}

inline void Point3::operator/=(double div)
{
  P[0] /= div;
  P[1] /= div;
  P[2] /= div;
}

inline Point3 Point3::operator*(double mult)
{
  return Point3(P[0] * mult, P[1] * mult, P[2] * mult);
}

inline double &Point3::operator[](int i) { return P[i]; }

inline double Point3::operator[](int i) const { return P[i]; }

inline double Point3::distance(const Point3 &p) const
{
  double x = P[0] - p.P[0], y = P[1] - p.P[1], z = P[2] - p.P[2];
  return std::sqrt(x * x + y * y + z * z);
}

#endif
