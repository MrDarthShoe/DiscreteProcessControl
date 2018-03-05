#include "stdafx.h"
#include "ProblemChooser.h"
#include <iostream>


ProblemChooser::ProblemChooser()
{
}


ProblemChooser::~ProblemChooser()
{
}

void ProblemChooser::solve(int number)
{
	switch (number)
	{
	case 1:
		solveJackson();
		break;

	case 2:
		solveSchrage();
		break;


	case 3:
		solveSchrageWithDivision();
		break;

	case 4:
		solveCalier();
		break;
	case 5:
		solveDynamicWithWiTi();
		break;

	case 6:
		solveNEH();
		break;

	case 7:
		solveHarmonogram();
		break;

	default:
		std::cout << "Problem not found by handler!\n";
		break;
	}
}

void ProblemChooser::solveJackson()
{
}

void ProblemChooser::solveSchrage()
{
}

void ProblemChooser::solveSchrageWithDivision()
{
}

void ProblemChooser::solveCalier()
{
}

void ProblemChooser::solveDynamicWithWiTi()
{
}

void ProblemChooser::solveNEH()
{
}

void ProblemChooser::solveHarmonogram()
{
}

