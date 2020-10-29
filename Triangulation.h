#pragma once
#include "Tetrahedron.h"
#include <set>
class Triangulation
{
	std::vector<Node> m_InputNodes;

public:
	Triangulation(std::vector<Node> p_Nodes);
	double metric(Node& p_A, Node& p_B) const;
	bool sphereInclusionTest(Node& p_Centre, double& p_Radius, Node& p_Point) const;
	std::set<Tetrahedron> generateMesh(std::set<Node> p_Nodes);
	~Triangulation();
};

