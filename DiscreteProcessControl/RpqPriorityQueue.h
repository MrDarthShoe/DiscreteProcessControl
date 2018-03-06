#pragma once

#include <queue>

#include "RpqNode.h"

template <class Compare>
class RpqPriorityQueue
{
public:
	RpqPriorityQueue();
	~RpqPriorityQueue();

	std::priority_queue<RpqNode, std::vector<RpqNode>, Compare>& getData();
	void push(const RpqNode& node);
	size_t size();
	void pop();
	const RpqNode& top();

private:
	std::priority_queue<RpqNode, std::vector<RpqNode>, Compare>  _data;
};

template <class Compare>
RpqPriorityQueue<Compare>::RpqPriorityQueue(): _data() { }

template <class Compare>
RpqPriorityQueue<Compare>::~RpqPriorityQueue() { }

template <class Compare>
std::priority_queue<RpqNode, std::vector<RpqNode>, Compare>& RpqPriorityQueue<Compare>::getData() { return _data; }

template <class Compare>
void RpqPriorityQueue<Compare>::push(const RpqNode& node) { _data.push(node); }

template <class Compare>
size_t RpqPriorityQueue<Compare>::size() { return _data.size(); }

template <class Compare>
void RpqPriorityQueue<Compare>::pop() { _data.pop(); }

template <class Compare>
const RpqNode& RpqPriorityQueue<Compare>::top() { return _data.top(); }


//Compare functors:
struct compare_r {
	bool operator() (const RpqNode& left, const RpqNode& right)
	{
		return (left.getR()) > (right.getR());
	}
}; 

struct compare_q {
	bool operator() (const RpqNode& left, const RpqNode& right)
	{
		return (left.getQ()) < (right.getQ());
	}
};
