#ifndef POINT2_H
#define POINT2_H

#include <cmath>

// A point in 2-space
class Point2 {
protected:
  double P[2];

public:
  Point2(double x = 0.0, double y = 0.0)
  {
    P[0] = x;
    P[1] = y;
  }
  Point2(double *p)
  {
    P[0] = p[0];
    P[1] = p[1];
  }
  Point2(const Point2 &pt)
  {
    P[0] = pt.P[0];
    P[1] = pt.P[1];
  }
  virtual ~Point2() {}
  void setPosition(double xx, double yy);
  void getPosition(double *xx, double *yy) const;
  void position(double *) const;
  inline double x(void) const;
  inline double y(void) const;
  double &operator[](int);
  double operator[](int) const;
  double distance(const Point2 &p) const;
  Point2 &operator=(const Point2 &p);
  void operator+=(const Point2 &p);
  void operator-=(const Point2 &p);
  void operator*=(double mult);
  Point2 operator*(double mult) const;
  operator double *() { return P; }
  bool operator<(const Point2 &other) const
  {
    if(other.P[0] < P[0]) return true;
    if(other.P[0] > P[0]) return false;
    if(other.P[1] < P[1]) return true;
    return false;
  }
  const double *data() const { return P; }
  double *data() { return P; }
};

inline Point2 operator+(const Point2 &a, const Point2 &b)
{
  return Point2(a.x() + b.x(), a.y() + b.y());
}

inline Point2 operator-(const Point2 &a, const Point2 &b)
{
  return Point2(a.x() - b.x(), a.y() - b.y());
}

inline void Point2::setPosition(double xx, double yy)
{
  P[0] = xx;
  P[1] = yy;
}

inline void Point2::getPosition(double *xx, double *yy) const
{
  *xx = P[0];
  *yy = P[1];
}

inline void Point2::position(double *p) const
{
  p[0] = P[0];
  p[1] = P[1];
}

inline double Point2::x(void) const { return P[0]; }

inline double Point2::y(void) const { return P[1]; }

inline Point2 &Point2::operator=(const Point2 &p)
{
  P[0] = p.P[0];
  P[1] = p.P[1];
  return *this;
}

inline double &Point2::operator[](int i) { return P[i]; }

inline double Point2::operator[](int i) const { return P[i]; }

inline void Point2::operator+=(const Point2 &p)
{
  P[0] += p.P[0];
  P[1] += p.P[1];
}

inline void Point2::operator-=(const Point2 &p)
{
  P[0] -= p.P[0];
  P[1] -= p.P[1];
}

inline void Point2::operator*=(double mult)
{
  P[0] *= mult;
  P[1] *= mult;
}

inline Point2 Point2::operator*(double mult) const
{
  return Point2(P[0] * mult, P[1] * mult);
}

inline double Point2::distance(const Point2 &p) const
{
  double x = P[0] - p.P[0], y = P[1] - p.P[1];
  return std::sqrt(x * x + y * y);
}

#endif
