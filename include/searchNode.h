#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

class SearchNode {
public:
	SearchNode(int _parent=-1, int _cost=INT_MAX) :parent(_parent), cost(_cost) {}
	int parent;
	int cost;
};
#endif