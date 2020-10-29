#include <vector>

double scalarProduct(std::vector<double> p_Vec1, std::vector<double> p_Vec2)
{
	return p_Vec1[0] * p_Vec2[0]
		+ p_Vec1[1] * p_Vec2[1]
		+ p_Vec1[2] * p_Vec2[2];
}

std::vector<double> crossProduct(std::vector<double> p_Vec1, std::vector<double> p_Vec2)
{
	return std::vector<double>({ p_Vec1[1] * p_Vec2[2] - p_Vec1[2] * p_Vec2[1],
								p_Vec1[2] * p_Vec2[0] - p_Vec1[0] * p_Vec2[2],
								p_Vec1[0] * p_Vec2[1] - p_Vec1[1] * p_Vec2[0] });
}

double mixedProduct(std::vector<double> p_Vec1,
	std::vector<double> p_Vec2,
	std::vector<double> p_Vec3)
{
	return scalarProduct(crossProduct(p_Vec1, p_Vec2), p_Vec3);
}