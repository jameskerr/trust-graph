#include <iostream>
#include "graph.h"

using std::cout;
using std::endl;

int main() {
	Graph g("web-Google.txt");
	g.show(g.mostConnected());
	return 0;
}