

#include "FutureEvent.h"
#include <iomanip>
using namespace std;


ostream &operator<<( ostream &output, const FutureEvent &object)
{
    output << "Type : " << setw(5) << object.getEventType() << "       Time : " << setw(5) << object.getEventTime();
    
    return output;
}

FutureEvent::FutureEvent
(int eventType, double eventTime, FutureEvent * const nextNode)
{
    setNextNode(nextNode);
    setEventType(eventType);
    setEventTime(eventTime);
}

FutureEvent::FutureEvent(const FutureEvent &other)
{
    eventType = other.getEventType();
    eventTime = other.getEventTime();
    nextNode = NULL;
}

const FutureEvent &FutureEvent::operator=(const FutureEvent &other)
{
    eventType = other.getEventType();
    eventTime = other.getEventTime();
    nextNode = NULL;
    
    return *this;
}


void FutureEvent::printMemory() const
{
    cout << setw(5) << getEventType() << setw(5)  << getEventTime() << "    " << this << "   " <<nextNode;
}

// getters and setters
FutureEvent * FutureEvent::getNextNode() const
{
    return nextNode;
}

void FutureEvent::setNextNode(FutureEvent * const nextNode)
{
    this->nextNode = nextNode;
}

int FutureEvent::getEventType() const
{
    return eventType;
}

void FutureEvent::setEventType(const int eventType)
{
    if ( eventType > 0)
    {
        this->eventType = eventType;
    }
    else
    {
        throw invalid_argument("Event type must be greater than 0");
    }
}

double FutureEvent::getEventTime() const
{
    return eventTime;
}

void FutureEvent::setEventTime(const double eventTime)
{
    if ( eventTime >=0 )
    {
        this->eventTime = eventTime;
    }
    else
    {
        throw invalid_argument("Event time must be greater or equal to 0");
    }
}

