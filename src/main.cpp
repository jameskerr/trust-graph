#include <iostream>
#include "graph.h"

using std::cout;
using std::endl;

int main() {
	Graph g("data.txt");
	
	cout << "TOP TRUSTED" << endl;
	g.topTrusted(5);
	
	cout << "TOP TRUSTING" << endl;
	g.topTrusting(5);
	
	return 0;
}