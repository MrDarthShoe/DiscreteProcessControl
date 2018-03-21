#pragma once

#include "ProblemChooser.h"

class RPQFileReader
{
public:
	RPQFileReader();
	~RPQFileReader();
	
	void readFromFileToContainer(std::string& filename, RpqContainer& container);

	bool checkResult(std::string& filename, int to_check);

};

