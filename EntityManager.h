
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include <vector>
class EntityManager
{
public:
    // called by event type
    EntityManager();
    
    void arrive (double);
    void load (double, int);
    void unload (double, int);
    void unloadNext (double, int);
    
    double getTotalQueueTime();
    double getQueueTime(int);
    double getTotalSystemTime();
    int getFinishedQueue(int);
    int getFinishedSystem();
    double getMaximumWaitingTime(int =0);
    double getMaximumSystemTime();

    void printReferenceModel();


    ~EntityManager();
    
private:
    int entityPtrCounter = 0;
    vector< Entity * > *entities;
    

    
    
    
    
};


#endif