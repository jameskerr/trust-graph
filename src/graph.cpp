#include "graph.h"


#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using std::string;
using std::cout;
using std::endl;

Graph::Graph(string file_name)
:numNodes(0),
numEdges(0)
{
	cout << "Reading data file..." << endl;
	fillMap(file_name);
	cout << "Computing trust statistics..." << endl;
	computeTrustFrequencies();
}

Graph::~Graph() {
	//
}

void Graph::shortestPath(int a, int b) {
	// Neither of them exist
	if (al.find(a) == al.end()) {
		cout << "User #" << a << "does not exist" << endl;
		return;
	}
	if (al.find(b) == al.end()) {
		cout << "User #" << b << "does not exist" << endl;
		return;
	}

	std::queue<int> pending;
	std::set<int> visited;
	std::map<int, SearchNode> path; // <ids, nodes>

	path[a] = SearchNode(-1,0); // id, parent, cost 
	pending.push(a);

	while (pending.size() != 0) {
		int current = pending.front(); pending.pop();

		for (std::set<int>::iterator i = al[current].trust_list.begin(); i != al[current].trust_list.end(); ++i){
			if (*i == b) {
				cout << "I found the shortest path!" << endl;
				int cursor = current;
				cout << b << endl;
				while (cursor >= 0) {
					cout << cursor << endl;
					cursor = path[cursor].parent;
				}
				return;
			}// all done
			if (visited.find(*i) != visited.end()) continue;
			pending.push(*i);
			if (path[*i].cost > path[current].cost + 1) {
				path[*i].cost = path[current].cost + 1;
				path[*i].parent = current;
			}
		}
		visited.insert(current);
	}
	cout << "There is not a connection between the two." << endl;
}


void Graph::topTrusting(int limit) {
	int count = 0;
	for (std::map<int,int>::reverse_iterator i = most_trusting.rbegin(); i != most_trusting.rend(); ++i) {
		if (count >= limit) return;
		cout << al[i->second] << endl;
		++count;
	}
}

void Graph::topTrusted(int limit) {
	int count = 0;
	for (std::map<int,int>::reverse_iterator i = most_trusted.rbegin(); i != most_trusted.rend(); ++i) {
		if (count >= limit) return;
		cout << al[i->second] << endl;
		++count;
	}
}

void Graph::inspect(int key) {
	cout << "Person #" << key << endl;
	cout << "Trusts: ";
	for (std::set<int>::iterator i = al[key].trust_list.begin(); i != al[key].trust_list.end(); ++i)
		cout << *i << "; ";
	cout << endl;
}

void Graph::summary(int key) {
	cout << al[key];
}

void Graph::fillMap(std::string file_name) {
	string DELIMITER = "\t";

	std::ifstream fin;
	fin.open(file_name.c_str());
	if (!fin.good()) return;	 // Check if the file is good

	string line;
	for (int i = 0; i < 4; getline(fin, line), ++i); // Skip through the header

	while (!fin.eof()) {
		getline(fin, line);
		if (line.size() == 0) continue;  // Continue if it is an empty line
		
		try {
			// PARSE THE LINE
			int chop_spot = line.find(DELIMITER);
			string str_from = line.substr(0, chop_spot);
			string str_to 	= line.substr(chop_spot, line.size());
			// CAST THE STRING INTO INTS
			int from = atoi(str_from.c_str());
			int to   = atoi(str_to.c_str());
			// INSERT THE DATA INTO THE MAP
			al[from].id = from;
			al[from].trusts(to);
			al[to].id = to;
			al[to].isTrustedBy(from);
            
            
            // Update number of nodes (first check to see if 'active', or if node is already in the map)
            if (!al[from].active()){
                al[from].activate();
                ++numNodes;
            }
            if (!al[to].active()){
                al[to].activate();
                ++numNodes;
            }
            // Update number of edges (each line in file is a new edge)
            ++numEdges;

		} catch(int e) {
			cout << "Could not cast " << line << " into any ints." << endl;
		}
	}
	fin.close();
}

void Graph::computeTrustFrequencies() {
	for (std::map<int,User>::iterator i = al.begin(); i != al.end(); ++i) {
		 most_trusting[i->second.trustCount()] = i->first;
		 most_trusted[i->second.trustedByCount()] = i->first;
	}
}

void Graph::toCSV(){
    std::ofstream file;
    file.open("trustData.csv", std::ios::trunc|std::ios::out);
    
    for (std::map<int,User>::iterator i = al.begin(); i != al.end(); ++i) {
        // Make sure user exists in map
        if (!al[i->first].active()) continue;;
        
        // Write out line to file
        file << al[i->first].toCSV() << endl;
    }
    
    file.close();
    
}