
#include <iostream>
#include "Entity.h"
#include "Array.h"
using namespace std;



ostream &operator<<(ostream &output, Entity &right)
{
    output << "No. : " << right.entityNumber;
    
    return output;
}



Entity::Entity(double arrivalTime, int entityNumber)
: queueTimePtr(new Array<double>(2,-1))
{
    this->arrivalTime = arrivalTime;
    this->entityNumber = entityNumber;
}

void Entity::queueStart(double clock)
{
    
    if ( queueStartTime == -1 )
    {
        this->queueStartTime = clock;
    }
    else
    {
        throw invalid_argument ( "Error in time ordering of queue start and end " );
    }
}


void Entity::queueEnd(double clock)
{
    
    if ( queueStartTime != -1)
    {
        (*queueTimePtr)[queueTimeCounter] = ( clock - queueStartTime );
        queueTimeCounter++;
        
        queueStartTime = -1;
    }
    else
    {
        throw invalid_argument( "Error because queue start time is not set ");
    }
    
}

void Entity::unload(double clock)
{
    unloadTime = clock;
}


int Entity::getEntityNumber()
{
    if ( entityNumber != -1)
    {
        return entityNumber;
    }
    else
    {
        throw invalid_argument( "Entity Number is not set! ");
    }
}

// 0~99
double Entity::getQueueTime(int queueNumber)
{
    return (*queueTimePtr)[queueNumber];
    
}


double Entity::getQueueTime()
{
    double sum = 0;
    bool breakOut = false;
    
    for ( int i = 0 ; (i<queueTimePtr->getSize())&&(!breakOut); i++)
    {
        if ( (*queueTimePtr)[i] != -1 )
        {
            sum += (*queueTimePtr)[i];
        }
        else
        {
            breakOut = true;
        }
    }
    
    return sum;
}

double Entity::getTotalTime()
{
    if ((arrivalTime == -1)||(unloadTime == -1))
    {
        return -1;
    }
    else
    {
        return (unloadTime - arrivalTime);
    }
}







