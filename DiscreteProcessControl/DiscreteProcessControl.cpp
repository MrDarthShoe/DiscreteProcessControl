#include "stdafx.h"

#include <iostream>
#include "ProblemChooser.h"

int main()
{
	ProblemChooser chooser;

	for (;;)
	{
		chooser.selectProblem();
		chooser.printResult();

		std::cin.ignore();
	}
    return 0;
}

