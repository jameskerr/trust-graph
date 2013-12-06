#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "user.h"
#include "searchNode.h"


class Graph {
public:
	// CONSTRUCTORS
	Graph(std::string file_name);
	virtual ~Graph();

	// PUBLIC FUNCTIONS
	int shortestPath(int a, int b, int trust_type);// trust_type is 0 for trusting, 1 for trusted by
	void topTrusting(int limit);
	void topTrusted(int limit);
	void inspect(int key);
	void summary(int key);
    void getTransClosure();
    void transitiveConnection(int a, int b);
    void toCSV();
    void showStats();
    float average(int trust_type);
    void menu();
    
    // Getters
    int getNumNodes()   { return numNodes; }
    int getNumEdges()   { return numEdges; }

private:
	std::map<int,User> al; 			 // Adjacancy list
	std::map<int,int> most_trusting; // Map sorted on the most trusting
	std::map<int,int> most_trusted;  // Map sorted on the most trusted

    int numNodes;
    int numEdges;
    bool** tc;
    
    bool transClosureCaclulated;
    
	// PRIVATE FUNCTIONS
	void fillMap(std::string file_name);
	void computeTrustFrequencies();
};
#endif