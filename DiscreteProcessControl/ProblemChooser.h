#pragma once

#include <vector>
#include "RpqNode.h"

typedef std::vector <RpqNode> RpqContainer;

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
    RpqContainer solveSchrage(const RpqContainer& data);
	int solveSchrageWithDivision(const RpqContainer& data);
	void solveCalier(RpqContainer & data, int& UB);
	int solveDynamicWithWiTi();
	int solveNEH();
	int solveHarmonogram();

	int _problem;
	int _instance;
};

