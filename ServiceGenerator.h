

#ifndef ServiceGenerator_h
#define ServiceGenerator_h
#include "Array.h"

class ServiceGenerator
{
    
public:
    ServiceGenerator();
    double generate();
    void setType(int);
    
private:
    int type;
    double lowerBound;
    double upperBound;
    double mean;
    double stddev;
    Array<double> specifiedValues;
    int specifiedCounter;
    
    void prompt() const;
    void initialize();
    
};


#endif