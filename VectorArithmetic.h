#pragma once
#include <vector>
#include "Types.h"

std::vector<double> vector(Node p_A, Node p_B);

double scalarProduct(std::vector<double> p_Vec1, std::vector<double> p_Vec2);

std::vector<double> crossProduct(std::vector<double> p_Vec1, std::vector<double> p_Vec2);

double mixedProduct(std::vector<double> p_Vec1,
	std::vector<double> p_Vec2,
	std::vector<double> p_Vec3);