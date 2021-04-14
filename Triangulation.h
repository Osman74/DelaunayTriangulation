#pragma once
#include "Tetrahedron.h"
#include <vector>
#include <string>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <stack>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include "Context.h"
#include "Point3.h"
#include "Point2.h"
#include "BoundingBox3d.h"
#ifndef MAX_NUM_THREADS_
#define MAX_NUM_THREADS_ 8
#endif

typedef unsigned char CHECKTYPE;
struct Tet;

struct Vert {
private:
    double _x[3];
    double _lc;
    std::size_t _num;
    Tet* _t;

public:
    inline void setT(Tet* t) { _t = t; }
    inline Tet* getT() const { return _t; }
    inline std::size_t getNum() const { return _num; }
    inline void setNum(std::size_t n) { _num = n; }
    unsigned char _thread;
    inline double x() const { return _x[0]; }
    inline double y() const { return _x[1]; }
    inline double z() const { return _x[2]; }
    inline double lc() const { return _lc; }
    inline double& x() { return _x[0]; }
    inline double& y() { return _x[1]; }
    inline double& z() { return _x[2]; }
    inline double& lc() { return _lc; }
    inline operator double* () { return _x; }
    Vert(double X = 0, double Y = 0, double Z = 0, double lc = 0, int num = 0)
        : _num(num), _t(nullptr), _thread(0)
    {
        _x[0] = X;
        _x[1] = Y;
        _x[2] = Z;
        _lc = lc;
    }
    Vert operator+(const Vert& other)
    {
        return Vert(x() + other.x(), y() + other.y(), z() + other.z(),
            other.lc() + _lc);
    }
    Vert operator*(const double& other)
    {
        return Vert(x() * other, y() * other, z() * other, _lc * other);
    }
    Point3 point() const { return Point3(x(), y(), z()); }
};

class tetContainer;

class Triangulation
{
    std::vector<Node> m_InputNodes;
    std::vector<Node*> m_Nodes;
    std::vector<Tetrahedron*> m_Tetrahedrons;
    double metric(Node& p_A, Node& p_B) const;
    bool sphereInclusionTest(Node p_Centre, double p_Radius, Node p_Point) const;
    bool visibilityTest(Node p_Node, FiniteElement p_FE);
    friend std::ostream& operator<<(std::ostream& p_Out, Triangulation& p_Triangulation);
    void delaunayTriangulation(const int numThreads, const int nptsatonce, bool removeBox);

public:
    Triangulation()
    {}
    void inputNodes(std::string fileName);
    void generateMesh(std::string fileName);

	~Triangulation();
};
