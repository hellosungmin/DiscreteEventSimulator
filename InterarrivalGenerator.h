

#ifndef InterarrivalGenerator_h
#define InterarrivalGenerator_h

#include "Array.h"

class InterarrivalGenerator
{
    
public:
    InterarrivalGenerator();
    double generate();
    void setType(int);
    
private:
    int type;
    double lambda;
    Array<double> specifiedValues;
    int specifiedCounter;
    
    void prompt() const;
    void initialize();
    
};


#endif