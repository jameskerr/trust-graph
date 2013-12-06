#include <iostream>
#include "graph.h"
#include "tools.h"
#include <cstdlib>
#include <stdlib>

using std::cout;
using std::endl;

int main(int argc, char**argv) {
	// ENSURES A FILE NAME ARGUMENT
	if (argc != 2) {
		cout << "Usage: ./graph.exe filename" << endl;
		cout << "File must be downloaded from the SNAP website" << endl;  
		return 0;
	}

	Graph g(argv[1]);
	
	int a, b, user, choice, limit;
	bool keep_going = true;
	
	while (keep_going) {
		g.menu();
		switch (getInt("Choose a choice: ")) {
			case 1:
				user = getInt("User ID: ");
				g.inspect(user);
				pause("Press ENTER to view the menu...");
			break;
			case 2:
				limit = getInt("# of users to show: ");
				g.topTrusted(limit);
				pause("Press ENTER to view the menu...");
			break;
			case 3:
				limit = getInt("# of users to show: ");
				g.topTrusting(limit);
				pause("Press ENTER to view the menu...");
			break;
			case 4:
				a = getInt("1st user ID: ");
				b = getInt("2nd user ID: ");
				g.shortestPath(a,b,1);
				pause("Press ENTER to view the menu...");
			break;
			case 5:
				a = getInt("1st user ID: ");
				b = getInt("2nd user ID: ");
				g.shortestPath(a,b,0);
				pause("Press ENTER to view the menu...");
			break;
			case 6:
				a = getInt("1st user ID: ");
				b = getInt("2nd user ID: ");
				g.transitiveConnection(a,b);
				pause("Press ENTER to view the menu...");
			break;
			case 7:
				g.showStats();
				pause("Press ENTER to view the menu...");
			break;
			case 8:
				g.toCSV();
				pause("Press ENTER to view the menu...");
			break;
			case 9:
				keep_going = false;
				cout << "Goodbye... :)" << endl;
			break;
			default:
			break;
		}
	}
	return 0;
}