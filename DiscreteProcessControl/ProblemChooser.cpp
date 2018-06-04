#include "stdafx.h"
#include "ProblemChooser.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include "RPQFileReader.h"
#include "RpqNode.h"
#include "RpqPriorityQueue.h"

using namespace std;



int eval(const RpqContainer& permutation)
{
    int time = permutation[0].getR();
    int cMax = 0;
    RpqNode pi(0, 0, 0);

    size_t n = permutation.size();
    for (int i = 0; i < n; i++)
    {
        RpqNode temp = permutation[i];

        time = max(time, temp.getR());

        //pi = temp;
        time += temp.getP();
        cMax = max(cMax, time + temp.getQ());
    }
    return cMax;
};

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

		return eval(solveSchrage(data)); 
	}
	case 3:
	{
		cout << "Solving Schrage with division: \n";

		return solveSchrageWithDivision(data);
	}
	case 4:
	{
		cout << "Solving Carlier: \n";

        int Cmax = numeric_limits<int>::max();
        solveCalier(data, Cmax);
        return Cmax;
	}
	case 5:
		return solveDynamicWithWiTi();
	case 6:

		cout << "Solving NEH: \n";
		vector<vector<int>> input;
		vector<int> process;
		
		cin >> N;
		cin >> M;
		for (int i = 0; i < N; i++)
		{
			std::vector<int> a;
			input.push_back(a);
			int summ = 0;
			for (int j = 0; j < M; j++)
			{
				int temp;
				cin >> temp;
				summ += temp;
				input[i].push_back(temp);
			}
			process.push_back(summ);
		}

		
		sort(process, input);

		// NEH
		int c = NEH(input);
		cout << "Cmax: " << c << std::endl;
		//return solveNEH();
	case 7:
		return solveHarmonogram();
	default:
		cout << "Problem not found by handler!\n";
		return 0;
	}
}


void ProblemChooser::write_vector(vector<vector<int>> v)
{
	for (unsigned int i = 0; i < v.size(); i++)
	{
		for (unsigned int j = 0; j < v[0].size(); j++)
		{
			cout << v[i][j] << " \t";
		}
		cout << "\n";
	}
}


void ProblemChooser::copy_vector(vector<vector<int>> old, vector<vector<int>> &n)
{
	for (unsigned int i = 0; i < n.size(); i++)
		n[i].clear();
	n.clear();

	for (unsigned int i = 0; i < old.size(); i++)
	{
		vector<int> l;
		for (unsigned int j = 0; j < old[0].size(); j++)
		{
			l.push_back(old[i][j]);
		}
		n.push_back(l);
	}
}




int ProblemChooser::solveJackson()
{
	cout << "No jackson yet!\n";
	return 0;
}

RpqContainer ProblemChooser::solveSchrage(const RpqContainer& data)
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
	//data = pi;
	//return Cmax;
    return pi;
}

int ProblemChooser::solveSchrageWithDivision(const RpqContainer& data)
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
	l.setQ(numeric_limits<int>::max());

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



void ProblemChooser::solveCalier(RpqContainer& data, int& UB)
{
    // Lambda for computing block
    auto block = [&](const RpqContainer& permutation) -> tuple<int, int, int>
    {
        int a = -1;
        int b = -1;
        int c = -1;
        int Cmax = 0;
        int CMAX = eval(permutation);
        int time = permutation[0].getR();
        RpqNode pi(0, 0, 0);

        size_t n = permutation.size();

        for (int i = 0; i < n; i++)
        {
            RpqNode temp = permutation[i];

            time = max(time, temp.getR());

            time += temp.getP();

            if ((time + permutation[i].getQ()) == CMAX)
            {
                b = i;                                // ostatni zwiêksza CMAX
            }
            Cmax = max(Cmax, time + temp.getQ());
        }

        time = permutation[0].getR();
        Cmax = 0;

        for (int i = 0; i < n; i++)
        {
            RpqNode temp = permutation[i];
            time = max(time, temp.getR());
            time += temp.getP();

            if (a == -1)
            {
                int summ = 0;
                for (int j = i; j <= b; j++)
                {
                    summ += (permutation[j].getP());
                }
                summ += permutation[b].getQ();
                if (CMAX == permutation[i].getR() + summ)
                    a = i;
            }
            Cmax = max(Cmax, time + temp.getQ());
        }

        time = permutation[0].getR();
        Cmax = 0;

        for (int i = a; i <= b; i++)
        {
            if (permutation[i].getQ() < permutation[b].getQ())
                c = i;
        }

        //cout << "a " << a << " b " << b << " c " << c << "\n";
        return make_tuple(a, b, c);
    };

        /*
        Cmax = max(Cmax, time + node.getQ());

        if(Cmax <= time + node.getQ());
        {
        Cmax = time + node.getQ());
        b=t;
        }
        /*
        //Zapamietywac c oraz identyfikator zadania
        c termin zakonczenia powiekszyc o czas dostarczenia
        blok ab


        a,b,c pozycje w permutacji schrage
        b pozycja zadania dla kórego termin zakoñæzenia o powiêkszony o czqs dostarczenia jest równy cmax. Bierzemy ten co na prawo!

        r(a) + suma czasów zadañ na pozycjach od (a do b) + q daje cmax najbardziej na lewo albo o najmniejszym momencie rozpoczecia

        c zadanie pomiêdzy a i b o czasie dostarczenia mniejszym od zadania b je¿eli jest kilka to zadanie które najbli¿ej b lub na prawo najbardziej

        referencyjne q ma mniejsze od b
        przesuwanie referencyjnego w lewo lub w prawo daje szansê na polepszenie fcji celu
        */

    RpqContainer PI = solveSchrage(data);
    int U = eval(PI);

    if (U < UB)
        UB = U;

    auto tup = block(PI);
    int b = get<1>(tup);
    int c = get<2>(tup);

    if (c == -1)
        return;

    int rprim = numeric_limits<int>::max();
    int qprim = numeric_limits<int>::max();
    int pprim = 0;

    for (int i = c + 1; i <= b; i++)
    {
        if (PI[i].getR() < rprim)
            rprim = PI[i].getR();

        if (PI[i].getQ() < qprim)
            qprim = PI[i].getQ();

        pprim += PI[i].getP();
    }

    int r_temp = PI[c].getR();
    PI[c].setR(max(PI[c].getR(), rprim + pprim));
    int LB = solveSchrageWithDivision(PI);

    if (LB < UB)
        solveCalier(PI, UB);

    PI[c].setR(r_temp);

    int q_temp = PI[c].getQ();
    PI[c].setQ(max(PI[c].getQ(), qprim + pprim));
    LB = solveSchrageWithDivision(PI);

    if (LB < UB)
        solveCalier(PI, UB);

    PI[c].setQ(q_temp);
}

int ProblemChooser::solveDynamicWithWiTi()
{
	return 0;
}

void ProblemChooser::sort(vector<int> &len, vector<vector<int>> &job)
{
	for (unsigned int i = 0; i < len.size(); i++)
	{
		for (unsigned int j = 0; j < len.size(); j++)
		{
			if (i != j)
			{
				if (len[i] < len[j])
				{
					vector<int> t;
					int temp;
					temp = len[j];
					t = job[j];
					len[j] = len[i];
					job[j] = job[i];
					len[i] = temp;
					job[i] = t;
				}
			}
		}
	}
}

int ProblemChooser::calculate(const vector<vector<int>> &job, vector<vector<int>> &times)
{
	
	for (unsigned int i = 0; i < times.size(); i++)
		times[i].clear();
	times.clear();

	
	int n = job.size();
	int m = job[0].size();

	
	for (int i = 0; i < n; i++)
	{
		vector<int> a;
		times.push_back(a);
		for (int j = 0; j < m; j++)
		{
			int temp = 0;
			times[i].push_back(temp);
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (j == 0 && i == 0)
				times[i][j] = job[i][j];
			else if (j == 0)
				times[i][j] = job[i][j] + times[i - 1][j];
			else if (i == 0) 
			{
				times[i][j] = job[i][j] + times[i][j - 1];
			}
			else
			{
				if (times[i][j - 1] > times[i - 1][j])
					times[i][j] = job[i][j] + times[i][j - 1];
				else
					times[i][j] = job[i][j] + times[i - 1][j];
			}
		}
	}
	return times[n - 1][m - 1];
}


void ProblemChooser::insert_elem(vector<vector<int>> &v, unsigned int poz, vector<int> elem)
{
	vector<vector<int>>::iterator it = v.begin();
	while (poz--)
		it++;

	v.insert(it, elem);
}


int ProblemChooser::find_best_insert(const vector<vector<int>> list, vector<int> job, vector<vector<int>> &result)
{
	int cmax = 99999;
	int n = list.size();
	
	for (int i = 0; i <= n; i++)
	{
		vector<vector<int>> data; 
		vector<vector<int>> calculated_data; 
		copy_vector(list, data);

		
		insert_elem(data, i, job);
		
		int c = calculate(data, calculated_data);
		if (c < cmax)
		{
			cmax = c;
			copy_vector(data, result);
		}
	}
	return cmax; 
}



int ProblemChooser::solveNEH(vector<vector<int>> list)
{

	/*
	
	b³ad 1-4% wzgledem rozw optymalnego
	faza wstepna: lista zadan posortowane po prio
	priorytet suma operacji wykonywania na kazdej z maszyn
	faza iteracyjna zasadnicza: n-iteracji
	generowanie k permutacji czesciowych w kazdej iteracji 
	wybieramy permutacje ktora generuje najmniejszy cmax z kazdej iteracji


	
	
	*/


	int c = 0;
	vector<vector<int>> best_permutation;
	
	int size1 = list.size();
	vector<int> job;
	for (unsigned int l = 0; l < list[size1 - 1].size(); l++)
		job.push_back(list[size1 - 1][l]);
	list.pop_back();
	
	best_permutation.push_back(job);
	job.clear();
	int n = list.size(); 

	while (n--)
	{
		
		for (unsigned int l = 0; l < list[n].size(); l++)
			job.push_back(list[n][l]);
		list.pop_back();

		vector<vector<int>> result;
		c = find_best_insert(best_permutation, job, result);
		copy_vector(result, best_permutation);
		job.clear();
	}

	return c;



	//return 0;
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
