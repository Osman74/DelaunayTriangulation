#pragma once
#include "VectorArithmetic.h"
#include <cmath>

class Tetrahedron
{
	std::vector<Node> m_Nodes;
	std::vector<Edge> m_Edges;
	std::vector<Tetrahedron*> m_Neighbours;
	std::vector<std::vector<double>> m_Normals;
	Node m_CircumCentre;
	double m_CircumRadius;
public:
	Tetrahedron();
	Tetrahedron(const Node& p_A, const Node& p_B, const Node& p_C, const Node& p_D);
	double volume() const;
	std::vector<Node> getNodes();
	std::vector<Edge> getEdges();
	Node getCircumCentre() const;
	double getCircumRadius() const;
	bool tetrahedronInclusionTest(const Node& p_Point) const;
	~Tetrahedron();
};

