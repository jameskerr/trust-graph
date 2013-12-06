#include <iostream>
#include "graph.h"

using std::cout;
using std::endl;

int main() {
	Graph g("data.txt");
	//g.inspect(4);
	//g.inspect(109);
	//g.topTrusted(2);
	//g.topTrusting(2);
	//g.shortestPath(31, 888);
	
    //g.toCSV();
    g.getTransClosure();
    
    cout<< "NumNodes: " << g.getNumNodes() << endl;
    cout << "Edges: " << g.getNumEdges() << endl;
    
	return 0;
}