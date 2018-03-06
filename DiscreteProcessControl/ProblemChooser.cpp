#include "stdafx.h"
#include "ProblemChooser.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "RPQFileReader.h"
#include "RpqNode.h"
#include "RpqPriorityQueue.h"

using namespace std;

void removeReadyTasks(RpqPriorityQueue<compare_r>& N, RpqPriorityQueue<compare_q>& G, int& t, RpqNode& e)
{
	while (N.size() && (N.top().getR() <= t))
	{
		e = N.top();
		G.push(N.top());
		N.pop();
	}
}


ProblemChooser::ProblemChooser()
	: _problem(0), _instance(1)
{ }


ProblemChooser::~ProblemChooser()
{ }

void ProblemChooser::printResult()
{
	cout << "Result is: " << solve() << "\n";
}

int ProblemChooser::solve()
{
	string filename("SCHRAGE" + to_string(_instance) + ".DAT");

	switch (_problem)
	{
	case 1:
		return solveJackson();
	case 2:
	{
		cout << "Solving Schrage: \n";

		RPQFileReader reader;
		RpqContainer data;

		reader.readFromFileToContainer(filename, data);
		return solveSchrage(data); 
	}
	case 3:
		return solveSchrageWithDivision();
	case 4:
		return solveCalier();
	case 5:
		return solveDynamicWithWiTi();
	case 6:
		return solveNEH();
	case 7:
		return solveHarmonogram();
	default:
		cout << "Problem not found by handler!\n";
		return 0;
	}
}

int ProblemChooser::solveJackson()
{
	cout << "No jackson yet!\n";
	return 0;
}

int ProblemChooser::solveSchrage(RpqContainer& data)
{

	//Proper Schrage Alrorithm help variables:
	int t=0, k=0, Cmax=0;
	RpqNode e;
	RpqContainer pi(data.size());
	RpqPriorityQueue<compare_r> N;
	RpqPriorityQueue<compare_q> G;
	
	for (auto iterator : data.getData())
	{
		N.push(iterator);
	}

	while (G.size() || N.size())
	{
		removeReadyTasks(N, G, t, e);
		if (!G.size())
		{
			t = N.top().getR();
			removeReadyTasks(N, G, t, e);
		}
		e = G.top();
		G.pop();

		pi.getData()[k] = e;
		t += e.getP();
		Cmax = max(Cmax, t + e.getQ());
		k++;
	}
	return Cmax;
}

int ProblemChooser::solveSchrageWithDivision()
{
	return 0;
}

int ProblemChooser::solveCalier()
{
	return 0;
}

int ProblemChooser::solveDynamicWithWiTi()
{
	return 0;
}

int ProblemChooser::solveNEH()
{
	return 0;
}

int ProblemChooser::solveHarmonogram()
{
	return 0;
}

void ProblemChooser::selectProblem()
{
	cout << "Enter problem number:\n";
	cin >> _problem;
	cout << "Enter instance number:\n";
	cin >> _instance;
}

