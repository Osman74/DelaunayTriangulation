#pragma once
#include <vector>
#include <iostream>
#include <iterator>
struct Node {
	unsigned m_ID;
	double m_X;
	double m_Y;
	double m_Z;
	bool is_Apex;
	Node() = default;
	Node(int ID, double x, double y, double z) :
		m_ID(ID), m_X(x), m_Y(y), m_Z(z) {}

	bool operator<(const Node& p_node) const {
		return m_ID < p_node.m_ID;
	}
	friend std::ostream& operator<<(std::ostream& p_Out, const Node& p_Node) {
		p_Out << "ID узла - " << p_Node.m_ID << std::endl;
		p_Out << "X - " << p_Node.m_X << std::endl;
		p_Out << "Y - " << p_Node.m_Y << std::endl;
		p_Out << "Z - " << p_Node.m_Z << std::endl;
		return p_Out;
	}
};

struct Edge {
	unsigned FirstNode_ID;
	unsigned LastNode_ID;
	unsigned Center_ID;

	Edge(unsigned p_ID1, unsigned p_ID2, unsigned p_ID3) : FirstNode_ID(p_ID1), LastNode_ID(p_ID2), Center_ID(p_ID3) {}

	bool operator==(const Edge& right_edge) const {
		if (right_edge.FirstNode_ID == FirstNode_ID && right_edge.LastNode_ID == LastNode_ID)
			return true;
		else if (right_edge.FirstNode_ID == LastNode_ID && right_edge.LastNode_ID == FirstNode_ID)
			return true;
		else return false;
	}
	bool operator<(const Edge& Right_Edge) const {
		return Center_ID < Right_Edge.Center_ID;
	}
	void UpdateCenter(unsigned p_NodeID) {
		Center_ID = p_NodeID;
	}
};

struct FiniteElement {
	unsigned m_ID;
	unsigned m_IDType;
	std::vector<unsigned> m_NodeIDs;
	friend std::ostream& operator<<(std::ostream& p_Out, const FiniteElement& p_FE) {
		p_Out << "ID КЭ - " << p_FE.m_ID << std::endl;
		p_Out << "ID материала - " << p_FE.m_IDType << std::endl;
		p_Out << "ID узлов КЭ : ";
		std::copy(p_FE.m_NodeIDs.begin(), p_FE.m_NodeIDs.end(), std::ostream_iterator<int>(p_Out, " "));
		p_Out << std::endl;
		return p_Out;
	}
};

struct SurfaceFiniteElement {
	unsigned m_ID;
	unsigned m_IDSurface;
	std::vector<unsigned> m_NodeIDs;
	friend std::ostream& operator<<(std::ostream& p_Out, const SurfaceFiniteElement& p_SFE) {
		p_Out << "ID поверхностного КЭ - " << p_SFE.m_ID << std::endl;
		p_Out << "ID поверхности - " << p_SFE.m_IDSurface << std::endl;
		p_Out << "ID узлов поверхностного КЭ : ";
		std::copy(p_SFE.m_NodeIDs.begin(), p_SFE.m_NodeIDs.end(), std::ostream_iterator<int>(p_Out, " "));
		p_Out << std::endl;
		return p_Out;
	}
};


