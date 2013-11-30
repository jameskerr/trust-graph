#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "trustNode.h"

class Graph {
public:
	Graph(std::string file_name);
	virtual ~Graph();

	void fillMap(std::string file_name);
	int mostConnectedOutward();
    int mostConnectedInward();
	void show(int key, bool outward);
    unsigned long getSize() {return al.size();}
    void analyze();
    
private:
	std::map< int, TrustNode > al;
    bool analyzed;
    
    void examineNodes();
    void saveCSV();
    
};
#endif