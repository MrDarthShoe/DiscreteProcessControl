#pragma once

#include <vector>
#include "RpqNode.h"

class RpqContainer
{
public:
	RpqContainer();
	~RpqContainer();

	std::vector<RpqNode>& getData() { return _data; }
	void sort();
	RpqNode& getMin() const;
	RpqNode& getMax() const;

private:
	std::vector<RpqNode> _data;
};

