#pragma once
#include "Tetrahedron.h"

Tetrahedron::Tetrahedron() 
{
	m_Nodes.resize(4);
	m_Nodes[0] = Node();
	m_Nodes[1] = Node();
	m_Nodes[2] = Node();
	m_Nodes[3] = Node();
}

Tetrahedron::Tetrahedron(Node p_A, Node p_B, Node p_C, Node p_D)
{
	m_Nodes.resize(4);
	m_Nodes[0] = p_A;
	m_Nodes[1] = p_B;
	m_Nodes[2] = p_C;
	m_Nodes[3] = p_D;
	m_Edges.push_back(Edge(p_A.m_ID, p_B.m_ID));
	m_Edges.push_back(Edge(p_B.m_ID, p_C.m_ID));
	m_Edges.push_back(Edge(p_C.m_ID, p_D.m_ID));
	m_Edges.push_back(Edge(p_A.m_ID, p_D.m_ID));
	m_FiniteElements.push_back(FiniteElement(std::vector<unsigned>{p_A.m_ID, p_B.m_ID, p_C.m_ID}));
	m_FiniteElements.push_back(FiniteElement(std::vector<unsigned>{p_A.m_ID, p_B.m_ID, p_D.m_ID}));
	m_FiniteElements.push_back(FiniteElement(std::vector<unsigned>{p_B.m_ID, p_C.m_ID, p_D.m_ID}));
	m_FiniteElements.push_back(FiniteElement(std::vector<unsigned>{p_A.m_ID, p_C.m_ID, p_D.m_ID}));
}

double det3(double a11, double a12, double a13,
	double a21, double a22, double a23,
	double a31, double a32, double a33) {
	return a11 * a22*a33 + a12 * a23*a31 + a13 * a21*a32 - a11 * a23*a32 - a12 * a21*a33 - a13 * a22*a31;
}

double Tetrahedron::volume() const
{
	Node A = m_Nodes[0];
	Node B = m_Nodes[1];
	Node C = m_Nodes[2];
	Node D = m_Nodes[3];
	return abs(mixedProduct(vector(A, B), vector(A, C), vector(A, D))) / 6;
}

std::vector<Node> Tetrahedron::getNodes()
{
	return m_Nodes;
}

std::vector<Edge> Tetrahedron::getEdges() 
{
	return m_Edges;
}

std::vector<FiniteElement> Tetrahedron::getFiniteElements()
{
	return m_FiniteElements;
}

//b1-a1	  b2-a2	  b3-a3 | b^2 - a^2
//c1-a1   c2-a2   c3-a3 | c^2 - a^2
//d1-a1   d2-a2   d3-a3 | d^2 - a^2
//A(a1,a2,a3), B(b1,b2,b3), C(c1,c2,c3), D(d1,d2,d3)
//O(x,y,z)
//a^2=a1a1 + a2a2 + a3a3, b^2=b1b1 + b2b2 + b3b3, c^2=c1c1 + c2c2 + c3c3, d^2=d1d1 + d2d2 + d3d3

Node Tetrahedron::getCircumCentre() const 
{
	Node A = m_Nodes[0];
	double a1 = A.m_X;
	double a2 = A.m_Y;
	double a3 = A.m_Z;
	Node B = m_Nodes[1];
	double b1 = B.m_X;
	double b2 = B.m_Y;
	double b3 = B.m_Z;
	Node C = m_Nodes[2];
	double c1 = C.m_X;
	double c2 = C.m_Y;
	double c3 = C.m_Z;
	Node D = m_Nodes[3];
	double d1 = D.m_X;
	double d2 = D.m_Y;
	double d3 = D.m_Z;
	
	double a = a1 * a1 + a2 * a2 + a3 * a3;
	double b = b1 * b1 + b2 * b2 + b3 * b3;
	double c = c1 * c1 + c2 * c2 + c3 * c3;
	double d = d1 * d1 + d2 * d2 + d3 * d3;

	//Метод Крамера
	double delta = det3(b1 - a1, b2 - a2, b3 - a3, c1 - a1, c2 - a2, c3 - a3, d1 - a1, d2 - a2, d3 - a3);
	double delta1 = det3(b*b - a*a, b2 - a2, b3 - a3, c*c - a*a, c2 - a2, c3 - a3, d*d - a*a, d2 - a2, d3 - a3);
	double delta2 = det3(b1 - a1, b*b - a * a, b3 - a3, c1 - a1, c*c - a * a, c3 - a3, d1 - a1, d*d - a * a, d3 - a3);
	double delta3 = det3(b1 - a1, b2 - a2, b*b - a * a, c1 - a1, c2 - a2, c*c - a * a, d1 - a1, d2 - a2, d*d - a * a);

	double x = delta1 / delta;
	double y = delta2 / delta;
	double z = delta3 / delta;

	return Node(0, x, y, z);
}



double Tetrahedron::getCircumRadius() const 
{
	Node O = getCircumCentre();
	return (O.m_X - m_Nodes[0].m_X)*(O.m_X - m_Nodes[0].m_X)
		+ (O.m_Y - m_Nodes[0].m_Y)*(O.m_Y - m_Nodes[0].m_Y)
		+ (O.m_Z - m_Nodes[0].m_Z)*(O.m_Z - m_Nodes[0].m_Z);
}

bool Tetrahedron::tetrahedronInclusionTest(Node& p_Point) const
{
	double V = volume();
	Tetrahedron T1(p_Point, m_Nodes[1], m_Nodes[2], m_Nodes[3]);
	Tetrahedron T2(m_Nodes[0], p_Point, m_Nodes[2], m_Nodes[3]);
	Tetrahedron T3(m_Nodes[0], m_Nodes[1], p_Point, m_Nodes[3]);
	Tetrahedron T4(m_Nodes[0], m_Nodes[1], m_Nodes[2], p_Point);
	double L1 = T1.volume() / V;
	double L2 = T2.volume() / V;
	double L3 = T3.volume() / V;
	double L4 = T4.volume() / V;
	if ((L1 >= 0) && (L2 >= 0) && (L3 >= 0) && (L4 >= 0))
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& p_Out, Tetrahedron& p_Tetrahedron)
{
	p_Out << p_Tetrahedron.m_Nodes[0].m_ID << " " << p_Tetrahedron.m_Nodes[1].m_ID << " " << p_Tetrahedron.m_Nodes[2].m_ID << " " << p_Tetrahedron.m_Nodes[3].m_ID;
	return p_Out;
}

Tetrahedron::~Tetrahedron()
{
}
