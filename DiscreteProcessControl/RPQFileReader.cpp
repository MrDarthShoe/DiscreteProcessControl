#include "stdafx.h"
#include "RPQFileReader.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

RPQFileReader::RPQFileReader()
{ }


RPQFileReader::~RPQFileReader()
{ }

void RPQFileReader::readFromFileToContainer(string& filename, RpqContainer& container)
{
	ifstream input_file(filename);

	if (input_file.is_open())
	{
		int cases;
		int r, p, q;
		input_file >> cases;

		for (int i = 0; i < cases; ++i)
		{
			input_file >> r >> p >> q;
			container.push_back( RpqNode(r, p, q) );
		}
		input_file.close();
	} 
	else
	{
		cerr << "Unable to open a file: " << filename << endl;
	}
}

bool RPQFileReader::checkResult(string& filename, int to_check)
{
	ifstream input_file(filename);

	if (input_file.is_open())
	{
		int result;

		input_file >> result;
		
		input_file.close();

		return to_check == result;
	}
	else
	{
		cerr << "Unable to open a file: " << filename << endl;
	}
}
