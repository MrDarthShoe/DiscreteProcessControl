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
	string filename(to_string(_problem) + "\\" + "SCHRAGE" + to_string(_instance) + ".DAT");

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
	{
		cout << "Solving Schrage with division: \n";

		RPQFileReader reader;
		RpqContainer data;

		reader.readFromFileToContainer(filename, data);
		return solveSchrageWithDivision(data);
	}
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

	auto removeReadyTasks = [&](RpqPriorityQueue<compare_r>& N, RpqPriorityQueue<compare_q>& G, int& t, RpqNode& e)
	{
		while (N.size() && (N.top().getR() <= t))
		{
			e = N.top();
			G.push(N.top());
			N.pop();
		}
	};
	
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
		//t + qe to termin dostarczenia zadania e (di)
		//Ce to t+pe  (termin zakoñczenia zadania)
		//Se t przed dodaniem pe (termin rozpoczêcia zadania)
		Cmax = max(Cmax, t + e.getQ());
		k++;
	}
	return Cmax;
}

int ProblemChooser::solveSchrageWithDivision(RpqContainer& data)
{
	//Proper Schrage Alrorithm help variables:
	int t = 0, Cmax = 0;
	RpqNode e;
	RpqNode l;
	RpqPriorityQueue<compare_r> N;
	RpqPriorityQueue<compare_q> G;

	auto removeReadyTasks = [&](RpqPriorityQueue<compare_r>& N, RpqPriorityQueue<compare_q>& G, int& t, RpqNode& e, RpqNode& l)
	{
		while (N.size() && (N.top().getR() <= t))
		{
			e = N.top();
			G.push(N.top());
			N.pop();

			if (e.getQ() > l.getQ())
			{
				l.setP(t - e.getR());
				t = e.getR();
				if (l.getP() > 0) G.push(l);
			}
		}
	};

	for (auto iterator : data.getData())
	{
		N.push(iterator);
	}

	l.setR(0);
	l.setP(0);
	l.setQ(99999);

	while (G.size() || N.size())
	{
		removeReadyTasks(N, G, t, e, l);
		if (!G.size())
		{
			t = N.top().getR();
			removeReadyTasks(N, G, t, e, l);
		}
		e = G.top();
		G.pop();

		t += e.getP();
		//t + qe to termin dostarczenia zadania e (di)
		//Ce to t+pe  (termin zakoñczenia zadania)
		//Se t przed dodaniem pe (termin rozpoczêcia zadania)
		Cmax = max(Cmax, t + e.getQ());
		l = e;
	}
	return Cmax;
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

