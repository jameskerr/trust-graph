#include <iostream>
#include "graph.h"

using std::cout;
using std::endl;

int main() {
	Graph g("epinions.txt");
	g.show(g.mostConnectedOutward(), true);
    g.show(g.mostConnectedOutward(), false);
    g.analyze();
    g.show(g.mostConnectedOutward(), false);
	return 0;
}