
#ifndef FutureEvent_h
#define FutureEvent_h

#include <iostream>
using namespace std;

class FutureEvent
{
    friend ostream &operator<<( ostream &, const FutureEvent &);
    
public:
    FutureEvent(const int, const double, FutureEvent * const =0);
    FutureEvent(const FutureEvent &);
    const FutureEvent &operator=(const FutureEvent &);
    
    void printMemory() const; // used for verifying linked-list
    
    // getters and setters of private data members
    FutureEvent * getNextNode() const;
    void setNextNode(FutureEvent * const);
    int getEventType() const;
    void setEventType(const int);
    double getEventTime() const;
    void setEventTime(const double);
    
    
    
    
private:
    // linked list
    FutureEvent * nextNode;
    
    // data members
    int eventType;
    double eventTime;
    
};

#endif
