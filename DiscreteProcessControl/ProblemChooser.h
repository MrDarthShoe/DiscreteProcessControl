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
	int solveNEH(vector<vector<int>> list);
	int solveHarmonogram();
	void write_vector(vector<vector<int>> v);
	void copy_vector(vector<vector<int>> old, vector<vector<int>> &n);
	void sort(vector<int> &len, vector<vector<int>> &job);
	int calculate(const vector<vector<int>> &job, vector<vector<int>> &times);
	void insert_elem(vector<vector<int>> &v, unsigned int poz, vector<int> elem);
	int find_best_insert(const vector<vector<int>> list, vector<int> job, vector<vector<int>> &result);


	int _problem;
	int _instance;
};

