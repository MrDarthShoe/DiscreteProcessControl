#pragma once

#include <vector>
#include "RpqNode.h"

class RpqContainer
{
public:
	RpqContainer();
	RpqContainer(size_t size);
	~RpqContainer();

	std::vector<RpqNode>& getData() { return _data; }

	size_t size() { return _data.size(); }
	
	void addNode(RpqNode&& node);

	void print();

private:
	std::vector<RpqNode> _data;
};

