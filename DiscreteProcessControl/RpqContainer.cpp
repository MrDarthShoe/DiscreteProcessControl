#include "stdafx.h"
#include "RpqContainer.h"

#include <iostream>

RpqContainer::RpqContainer()
{ }

RpqContainer::RpqContainer(size_t size)
	: _data(size)
{ }

RpqContainer::~RpqContainer()
{ }

void RpqContainer::addNode(RpqNode&& node)
{
	_data.push_back(node);
}

void RpqContainer::print()
{
	std::cout << "\nPrinting vector\n";

	for (auto node : _data)
	{
		std::cout << "r: " << node.getR() << " p: " << node.getP() << " q: " << node.getQ() << "\n";
	}
	std::cout << "\n";
}
