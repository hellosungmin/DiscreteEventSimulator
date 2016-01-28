
#include <iostream>
#include "EntityManager.h"
#include "Entity.h"
using namespace std;

EntityManager::EntityManager()
: entityPtrCounter(0)
{
    entities = new vector<Entity *>(100000);

}

void EntityManager::arrive (double clock)
{
    (*entities)[entityPtrCounter] = new Entity(clock, entityPtrCounter + 1);
    (*entities)[entityPtrCounter]->queueStart(clock);
    entityPtrCounter++;
}

void EntityManager::load (double clock, int entityNumber)
{
    (*entities)[entityNumber]->queueEnd(clock);
}

void EntityManager::unload (double clock, int entityNumber)
{
    (*entities)[entityNumber]->unload(clock);
}

// used when passing an entity to a next machine
void EntityManager::unloadNext(double clock, int entityNumber)
{
    (*entities)[entityNumber]->queueStart(clock);
}


double EntityManager::getTotalQueueTime()
{
    double sum = 0;
    
    for ( int i = 0; (i < entities->size()); i++)
    {
        if ( ((*entities)[i] != NULL)&&((*entities)[i]->getQueueTime() != -1))
        {
            sum += (*entities)[i]->getQueueTime();
        }
        
    }
    return sum;
}

double EntityManager::getQueueTime(int queueNumber)
{
    
    double sum = 0;
    
    for ( int i = 0 ; (i < entities->size()); i++)
    {
        if ( ((*entities)[i] != NULL)&&((*entities)[i]->getQueueTime(queueNumber) != -1))
        {
            sum += (*entities)[i]->getQueueTime(queueNumber);
        }
    }
    return sum;
}

double EntityManager::getTotalSystemTime()
{
    double sum = 0;
    
    for ( int i = 0 ; i < entities->size(); i++)
    {
        if ( ((*entities)[i] != NULL)&&((*entities)[i]->getTotalTime() != -1))
        {
            sum += (*entities)[i]->getTotalTime();
        }
    }
    return sum;
}

int EntityManager::getFinishedQueue(int queue )
{
    
    int finished = 0;
    
    for ( int i = 0 ; i < entityPtrCounter; i++)
    {
        if ((*entities)[i]->getQueueTime(queue) != -1)
        {
            finished++; //// Change for Dispatching rule
        }
        else
        {
            return finished;
        }
    }
    
    return finished;
}

int EntityManager::getFinishedSystem()
{
    
    int finished = 0 ;
    
    for ( int i = 0 ; i < entityPtrCounter; i++)
    {
        if ((*entities)[i]->getTotalTime() != -1)
        {
            finished++; //// Change for Dispatching rule
        }
        else
        {
            return finished;
        }
    }
    
    return finished;
    
}


double EntityManager::getMaximumWaitingTime(int queue)
{
    double max = -1;
    
    for ( int i = 0 ; (i < entities->size()); i++)
    {
        if ( ((*entities)[i] != NULL)&&((*entities)[i]->getQueueTime(queue) != -1))
        {
            if ( (*entities)[i]->getQueueTime(queue) > max )
            {
                max = (*entities)[i]->getQueueTime(queue);
            }
        }
    }
    
    if ( max == -1)
    {
        throw invalid_argument ( "maximum shouldn't be -1 ") ;
    }
    
    return max;
}

double EntityManager::getMaximumSystemTime()
{
    double max = -1;
    
    for ( int i = 0 ; i < entities->size(); i++)
    {
        if ( ((*entities)[i] != NULL)&&((*entities)[i]->getTotalTime() != -1))
        {
            if ( (*entities)[i]->getTotalTime() > max )
            {
                max = (*entities)[i]->getTotalTime();
            }
        }
    }
    
    if ( max == -1)
    {
        throw invalid_argument ( "maximum shouldn't be -1 ") ;
    }
    
    return max;
    
}


EntityManager::~EntityManager()
{
    for (int i = 0; i < entities->size(); i++)
    {
        if ((*entities)[i] != NULL)
        {
            delete (*entities)[i];
        }
    }
}




