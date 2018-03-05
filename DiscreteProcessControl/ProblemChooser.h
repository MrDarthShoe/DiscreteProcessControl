#pragma once
class ProblemChooser
{
public:
	ProblemChooser();
	~ProblemChooser();
	void solve(int number);
private:
	void solveJackson();
	void solveSchrage();
	void solveSchrageWithDivision();
	void solveCalier();
	void solveDynamicWithWiTi();
	void solveNEH();
	void solveHarmonogram();
};

