#include "graph.h"

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::endl;

Graph::Graph(string file_name) {
	fillMap(file_name);
}

Graph::~Graph() {
	//
}



void Graph::fillMap(std::string file_name) {
	string DELIMITER = "\t";

	std::ifstream fin;
	fin.open(file_name.c_str());
	if (!fin.good()) return;

	while (!fin.eof()) {
		string line;
		getline(fin, line);

		if (line.size() == 0) continue;
		
		try {
			int chop_spot = line.find(DELIMITER);
			string str_from = line.substr(0, chop_spot);
			string str_to 	= line.substr(chop_spot, line.size());
			
			int from = atoi(str_from.c_str());
			int to   = atoi(str_to.c_str());
			
			al[from].push_back(to);
			
		} catch(int e) {
			cout << "Could not cast " << line << " into any ints." << endl;
		}
	}
	fin.close();
}

int Graph::mostConnected() {
	int max = 0;
	for (std::map<int, std::vector<int> >::iterator i = al.begin(); i != al.end(); ++i) {
		if (i->second.size() > max) max = i-> first;
	}
	return max;
}

void Graph::show(int key) {
	cout << "Key: " << key << " has " << al[key].size() << " connections:" << endl;
	for (std::vector<int>::const_iterator i = al[key].begin(); i != al[key].end(); ++i)
		cout << *i << endl;
	cout << endl;
}