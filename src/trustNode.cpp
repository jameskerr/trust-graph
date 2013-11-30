#include <iostream>
#include <sstream>
#include "trustNode.h"

TrustNode::TrustNode():
    ID(0),
    numTrustsOut(0),
    numTrustsIn(0),
    reciprocalTrusts(0),
    active(false)
{
    //
}

TrustNode::~TrustNode(){
    //
}

// Creates string formatted as coma separated value of data in node
std::string TrustNode::toCSV(){
    std::stringstream ssID, ssTO, ssTI, ssTR;
    std::string final = "";
    
    ssID << ID;
    final += ssID.str() + ',';
    ssTO << numTrustsOut;
    final += ssTO.str() + ',';
    ssTI << numTrustsIn;
    final += ssTI.str() + ',';
    ssTR << reciprocalTrusts;
    final += ssTR.str() + ',';
    
    return (final);
}