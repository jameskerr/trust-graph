#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

class Graph {
public:
	Graph(std::string file_name);
	virtual ~Graph();

	void fillMap(std::string file_name);
	int mostConnected();
	void show(int key);

private:
	std::map< int, std::vector<int> > al;
};
#endif