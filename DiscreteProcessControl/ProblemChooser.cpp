#include "stdafx.h"
#include "ProblemChooser.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
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

	RPQFileReader reader;
	RpqContainer data;

	reader.readFromFileToContainer(filename, data);

	switch (_problem)
	{
	case 1:
		return solveJackson();
	case 2:
	{
		cout << "Solving Schrage: \n";

		return solveSchrage(data); 
	}
	case 3:
	{
		cout << "Solving Schrage with division: \n";

		return solveSchrageWithDivision(data);
	}
	case 4:
	{
		cout << "Solving Carlier: \n";

		int result_schrage = solveSchrage(data); 
		int result_carlier = solveCalier(data, result_schrage);

		if (result_carlier == -1) return result_schrage;
		return result_carlier;
	}
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
	
	for (auto iterator : data)
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
		
		pi[k] = e;
		t += e.getP();
		//t + qe to termin dostarczenia zadania e (di)
		//Ce to t+pe  (termin zakoñczenia zadania)
		//Se t przed dodaniem pe (termin rozpoczêcia zadania)
		Cmax = max(Cmax, t + e.getQ());
		k++;
	}
	//Temporary workaround:
	data = pi;
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

	for (auto iterator : data)
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

int ProblemChooser::solveCalier(RpqContainer& data, int& UB)
{
	// Lambda for computing block
	auto block = [&](const RpqContainer& permutation, int& CMAX) -> std::tuple<int,int,int>
	{
		int a;
		int b;
		int c = -1;
		int Cmax = 0;
		int time = permutation[0].getR();

		//calculate b
		for (int i = 0; i < permutation.size(); ++i)
		{
			auto node = permutation[i];
			time = max(time, node.getR());

			time += node.getP();

			if ((time + node.getQ()) == CMAX)
			{
				b = i;
			}
			Cmax = max(Cmax, time + node.getQ());
		}
		/*
		Cmax = max(Cmax, time + node.getQ());

		if(Cmax <= time + node.getQ());
		{
		Cmax = time + node.getQ());
		b=t;
		}
		
		//Zapamietywac c oraz identyfikator zadania
		c termin zakonczenia powiekszyc o czas dostarczenia
		blok ab 
		
		*/


		//calculate a
		time = permutation[0].getR();
		Cmax = 0;

		for (int i = 0; i < permutation.size(); ++i)
		{
			auto node = permutation[i];
			time = max(time, node.getR());

			time += node.getP();

			int sum = 0;

			for (int j = i; j <= b; ++j)
			{
				sum += permutation[j].getP();
			}
			sum += permutation[b].getQ();

			if ((node.getR() + sum) == CMAX)
			{
				a = i;
			}
			Cmax = max(Cmax, time + node.getQ());
		}

		//calculate c
		time = permutation[0].getR();
		Cmax = 0;

		for (int i = a; i <= b; ++i)
		{
			if (permutation[i].getQ() < permutation[b].getQ())
			{
				c = i;
			}
		}
		cout << "a " << a << " b " << b << " c " << c << endl;
		return std::make_tuple(a, b, c);
	}; //End of "block" lambda

	// Start of Carlier algorithm:

	int U = solveSchrage(data);
	//I said earlier that this is TEMPORARY workaround- no judging!
	RpqContainer PI = data;
	RpqContainer PI_optimal;
	if (U < UB)
	{
		UB = U;
		PI_optimal = PI;
	}

	auto bl = block(PI, U);
	int b = std::get<1>(bl);
	int c = std::get<2>(bl);

	if (c == -1) return -1;

	int ri = 9999999, qi = 9999999, pi = 0;

	for (int i = c + 1; i <= b; ++i)
	{
		/*if (PI[i].getR() < ri)
			ri = PI[i].getR();*/
		ri = min(ri, PI[i].getR());

		//if (PI[i].getQ() < qi)
		//	qi = PI[i].getQ();
		qi = min(qi, PI[i].getQ());

		pi += PI[i].getP();
	}

	int r_temp = PI[c].getR();
	PI[c].setR(max(PI[c].getR(), ri + pi));
	int LB = solveSchrageWithDivision(PI);

	if (LB < UB)
		solveCalier(PI, UB);

	PI[c].setR(r_temp);

	int q_temp = PI[c].getQ();
	PI[c].setQ(max(PI[c].getQ(), qi + pi));
	LB = solveSchrageWithDivision(PI);

	if (LB < UB)
		solveCalier(PI, UB);

	PI[c].setQ(q_temp);

	int time = PI[0].getR();
	int cMax = 0;

	for (auto node : PI)
	{
		time = max(time, node.getR());
		time += node.getP();
		cMax = max(cMax, time + node.getQ());
	}
	data = PI_optimal;
	return cMax;
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

