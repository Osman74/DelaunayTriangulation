#pragma once
#include "Triangulation.h"
#include <clocale>
#include <fstream>
int main(int argc, char **argv)
{
	setlocale(0, "RUSSIAN");
	Triangulation T = Triangulation();
	T.inputNodes("inputNodes.msh");
	T.generateMesh("triangulation.msh");
	return 0;
}