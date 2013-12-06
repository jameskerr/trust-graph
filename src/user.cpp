#include "user.h"
#include <sstream>

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

void User::updateNeighbors(bool ** tc){
    // set true for all neighbors
        // constructs adjacency vector
    for (std::set<int>::iterator i = trust_list.begin(); i != trust_list.end(); ++i){
        tc[matrixID][*i] = true;
    }
}

std::string User::toCSV(){
    int recip = 0;
    
    // Calculate reciprocal trusts
    for (std::set<int>::iterator i = trust_list.begin(); i != trust_list.end(); ++i){
        // If an element it trusts is also trusing it, increment recip
        if (trusted_by_list.find(*i) != trusted_by_list.end()){
            ++recip;
        }
    }
    
    std::stringstream ssID;
    ssID << id;
    std::stringstream ssTrusts;
    ssTrusts << trustCount();
    std::stringstream ssTrustedBy;
    ssTrustedBy << trustedByCount();
    std::stringstream ssRecipTrusts;
    ssRecipTrusts << recip;
    
    return ssID.str() + ',' + ssTrusts.str() + ',' + ssTrustedBy.str() + ',' + ssRecipTrusts.str() + ',';
    
}