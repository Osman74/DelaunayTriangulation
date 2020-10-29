#include "Triangulation.h"



Triangulation::Triangulation(std::vector<Node> p_Nodes) : m_InputNodes(p_Nodes)
{}

double Triangulation::metric(Node& p_A, Node& p_B) const
{
	return (p_B.m_X - p_A.m_X)*(p_B.m_X - p_A.m_X)
		+ (p_B.m_Y - p_A.m_Y)*(p_B.m_Y - p_A.m_Y)
		+ (p_B.m_Z - p_A.m_Z)*(p_B.m_Z - p_A.m_Z);
}

bool Triangulation::sphereInclusionTest(Node& p_Centre, double& p_Radius, Node& p_Point) const
{
	return metric(p_Centre, p_Point) <= p_Radius;
}

std::set<Tetrahedron> Triangulation::generateMesh(std::set<Node> p_Nodes)
{
	std::set<Tetrahedron> tetrahedrons;
	Tetrahedron BASE;
	std::set<Tetrahedron> CORE;
	for (auto iter = p_Nodes.begin(); iter != p_Nodes.end(); iter++)
	{
		//..........................
		for (auto tetrahedron = tetrahedrons.begin(); tetrahedron != tetrahedrons.end(); tetrahedron++)
		{
			if(tetrahedron->tetrahedronInclusionTest(*iter))
				BASE = *tetrahedron;
		}
		for (auto tetrahedron = tetrahedrons.begin(); tetrahedron != tetrahedrons.end(); tetrahedron++)
		{
			if (sphereInclusionTest(tetrahedron->getCircumCentre, tetrahedron->getCircumRadius, *iter))
				CORE.insert(*tetrahedron);
		}
		//..........................
	}
	return tetrahedrons;
}

Triangulation::~Triangulation()
{
}
