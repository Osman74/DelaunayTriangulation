#pragma once
#include "VectorArithmetic.h"
#include <cmath>
#include <iostream>

class Tetrahedron
{
	std::vector<Node> m_Nodes;
	std::vector<Edge> m_Edges;
	std::vector<FiniteElement> m_FiniteElements;
	std::vector<Tetrahedron*> m_Neighbours;
	std::vector<std::vector<double>> m_Normals;
	Node m_CircumCentre;
	double m_CircumRadius;
public:
	Tetrahedron();
	Tetrahedron(Node p_A, Node p_B, Node p_C, Node p_D);
	double volume() const;
	std::vector<Node> getNodes();
	std::vector<Edge> getEdges();
	std::vector<FiniteElement> getFiniteElements();
	Node getCircumCentre() const;
	double getCircumRadius() const;
	bool tetrahedronInclusionTest(Node& p_Point) const;
	friend std::ostream& operator<<(std::ostream& p_Out, Tetrahedron& p_Tetrahedron);
	~Tetrahedron();
};

