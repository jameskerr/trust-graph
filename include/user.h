#ifndef USER_H
#define USER_H

#include <set>
#include <iostream>



class User {
public:
	// CONSTRUCTORS
	User() {}
	User(int _id) :id(_id) {}
	User(const User& source);
	
	// FRIEND CLASS
	friend class Graph;

	// OPERATORS
	friend std::ostream& operator << (std::ostream& out, User& user); 
	friend bool operator < (const User& source, const User& other);

	// PUBLIC FUNCTIONS
	inline int 	ID()				{ return id; }
	inline int 	trustCount() 		{ return trust_list.size(); }
	inline void trusts(int u) 		{ trust_list.insert(u); }
	inline int 	trustedByCount() 	{ return trusted_by_list.size(); }
	inline void isTrustedBy(int u)  { trusted_by_list.insert(u); }
    std::string toCSV();

    void activate()                 { isActive = true; }
    bool active()                   { return isActive; }
    
private:
	int id;
	bool isActive;
    
	std::set<int> trust_list;
	std::set<int> trusted_by_list;
};
#endif
