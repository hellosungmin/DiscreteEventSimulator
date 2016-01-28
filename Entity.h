
#ifndef ENTITY_H
#define ENTITY_H

#include "Array.h"
#include <iostream>

class Entity
{
    friend ostream &operator<<(ostream &, Entity &);
    
public:
    
    Entity(double, int);
    
    // Setters
    void queueStart(double);
    void queueEnd(double);
    void unload(double);
    
    // Getters
    int getEntityNumber();
    double getQueueTime(int);
    double getQueueTime();
    double getTotalTime();
    
private:
    int entityNumber = -1;
    double arrivalTime = -1;
    double unloadTime = -1;
    double queueStartTime = -1;
    Array<double> *queueTimePtr;
    int queueTimeCounter = 0;
    

};
#endif