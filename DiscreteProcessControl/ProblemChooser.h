#pragma once

#include "RpqContainer.h"

class ProblemChooser
{
public:
	ProblemChooser();
	~ProblemChooser();
	void selectProblem();
	void printResult();
private:
	int solve();
	int solveJackson();
	int solveSchrage(RpqContainer& data);
	int solveSchrageWithDivision(RpqContainer& data);
	int solveCalier();
	int solveDynamicWithWiTi();
	int solveNEH();
	int solveHarmonogram();

	int _problem;
	int _instance;
};

