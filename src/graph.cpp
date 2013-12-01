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
        else if (line[0] == '#') continue;
		
		try {
			int chop_spot = line.find(DELIMITER);
			string str_from = line.substr(0, chop_spot);
			string str_to 	= line.substr(chop_spot, line.size());
			int from = atoi(str_from.c_str());
			int to   = atoi(str_to.c_str());
			
            al[from].getAdj()->push_back(to);
            al[from].activate();
			
		} catch(int e) {
			cout << "Could not cast " << line << " into any ints." << endl;
		}
	}
	fin.close();
}

int Graph::mostConnectedOutward(){
	int max = 0;
	for (std::map<int, TrustNode >::iterator i = al.begin(); i != al.end(); ++i) {
		if (al[i->first].getSize() > al[max].getSize()) max = i->first;
	}
	return max;
}

int Graph::mostConnectedInward(){
    if (!analyzed){
        cout << "Graph must be analyzed first." << endl;
        return -1;
    }
    
    int max = 0;
	for (std::map<int, TrustNode >::iterator i = al.begin(); i != al.end(); ++i) {
		if (al[i->first].getTrustsIn() > al[max].getTrustsIn()) max = i-> first;
	}
	return max;
}

void Graph::show(int key, bool outward) {
    if (key == -1){
        cout << "Node could not be shown" << endl;
        return;
    }
    if (outward){
        // If you want to show a node's outward connections
        cout << "Key: " << key << " has " << al[key].getSize() << " outward connections:" << endl;
        for (std::vector<int>::const_iterator i = al[key].getAdj()->begin(); i != al[key].getAdj()->end(); ++i)
            cout << *i << endl;
    }
    else{
        // Showing inward connections (after analysis)
        if (!analyzed) {
            cout<<"Graph must be analyzed first." << endl;
            return;
        }
        cout << "Key: " << key << " has " << al[key].getTrustsIn() << " inward connections:" << endl;
    }
	cout << endl;
}




// Primary analysis functions

void Graph::analyze(){
    // Initialize data array to the size of the graph
    // This array will hold values to be saved in CSV file
    
    // Iterates over nodes to collect data
    analyzed = true;
    examineNodes();
    saveCSV();
}

void Graph::examineNodes(){
    // Iterate through nodes
    for (std::map<int, TrustNode >::iterator i = al.begin(); i != al.end(); ++i) {
        
        // Makes sure node key is used
        if (!al[i->first].isActive()) continue;
        
        // Set trustNode ID value so it can be saved to file
        al[i->first].setID(i->first);
        
        // Iterate through node's neighbors
        for (std::vector<int>::const_iterator j = al[i->first].getAdj()->begin(); j != al[i->first].getAdj()->end(); ++j){
            // Each neighbor is an outward trust from the node
            al[i->first].incTrustsOut();
            
            // Increment trusts in to adjacent node from old node
            al[*j].incTrustsIn();
            
            // Check neighbors for original nodes key
            if(std::find(al[*j].getAdj()->begin(), al[*j].getAdj()->end(), i->first) != al[*j].getAdj()->end()) {
                // If adj node points back to original node, increment reciprocity value in original
                al[i->first].incRecTrusts();
            }
        }
	}
}

void Graph::saveCSV(){
    // open file
    std::ofstream file;
    file.open("trustData.csv", std::ios::out | std::ios::trunc);
    
    // Print headers to CSV file
    file << "ID,Outward Trusts,Inward Trusts,Reciprocal Trusts,";
    
    // Print all nodes to CSV
    for (std::map<int, TrustNode >::iterator i = al.begin(); i != al.end(); ++i) {
        if (!al[i->first].isActive()) continue;
        file << al[i->first].toCSV() << endl;
    }
    
    file.close();
}