#ifndef TRUSTNODE_H
#define TRUSTNODE_H

#include <iostream>
#include <map>
#include <vector>

class TrustNode {
private:
    int ID;
    int numTrustsOut;
    int numTrustsIn;
    int reciprocalTrusts;
    
    std::vector<int> adj;
    bool active;
    
public:
	TrustNode();
	virtual ~TrustNode();

    std::string toCSV();
    
    // Getters and Setters
    int getID() {return ID;}
    void setID(int x) {ID = x;}
    
    unsigned long getTrustsOut() {return getSize();}
    void setTrustsOut(int x) {numTrustsOut = x;}
    void incTrustsOut() {++numTrustsOut;}
    
    int getTrustsIn() {return numTrustsIn;}
    void setTrustsIn(int x) {numTrustsIn = x;}
    void incTrustsIn() {++numTrustsIn;}
    
    int getRecTrusts() {return reciprocalTrusts;}
    void setRecTrusts(int x) {reciprocalTrusts = x;}
    void incRecTrusts() {++reciprocalTrusts;}
    
    std::vector<int>* getAdj(){return &adj;}
    unsigned long getSize() {return adj.size();}
    
    void activate(){active = true;};
    bool isActive(){return active;}
};
#endif