#include "user.h"

User::User(const User& source) {
	id = source.id;
	trust_list = source.trust_list;
	trusted_by_list = source.trusted_by_list;

}

std::ostream& operator << (std::ostream& out, User& user) {
	// User
	out << "/--- User #" << user.id << std::endl;

	// Graph
	for (int i = 10; i >= 0; --i) {
	out << "|   ";																			// Padding
	out << (((((double)user.trustCount() / 3035.0) * 10.0) >= (double)i) ? "##" : "  ");	// Trusts Bar
	out << "         ";																		// Padding
	out << (((((double)user.trustedByCount() / 3035.0) * 10.0) >= (double)i) ? "##" : "  ");// Trusted By Bar
	out << "    "; 																			// Padding
	out << std::endl;
	}
	out << "|  ----       ----   " << std::endl;
	out << "| Trusts   Trusted By" << std::endl;

	// Stats
	out << "| Trust Index: " << ((double)user.trustedByCount() / (double)user.trustCount() )* 100  << std::endl;
	out << "| Trusts " << user.trustCount() << " other users" << std::endl;
	out << "| Trusted by " << user.trustedByCount() << " other users" << std::endl;
	
	return out;
}

bool operator < (const User& source, const User& other) { 
	return (source.id < other.id); 
}