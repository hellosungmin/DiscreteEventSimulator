
#ifndef FutureEventList_h
#define FutureEventList_h

#include "FutureEvent.h"
#include <iostream>
using namespace std;

class FutureEventList
{
    friend ostream &operator<<(ostream &, const FutureEventList &);

public:
    FutureEventList();
    FutureEventList(const FutureEventList &);
    const FutureEventList &operator=(const FutureEventList &);

    bool printMemory(); // used for verifying linked list
    bool scheduleEvent(const int, const double);
    bool scheduleEvent(const FutureEvent &);
    const FutureEvent *retrieveEvent();
    bool cancelEvent(const int);

    
    // getters and setters
    FutureEvent * getFirstNode() const;
    void setFirstNode(FutureEvent * const);
    FutureEvent * getLastNode() const;
    void setLastNode (FutureEvent * const);
    
    
    
    ~FutureEventList();

    
private:
    FutureEvent *firstNode;
    FutureEvent *lastNode;
    bool isEmpty() const;
    void copyFromOther(const FutureEventList &);
    void deleteList();
    void insertFront(const int, const double);
    void insertBack(const int, const double);
    void cancelFront(const int);
    void cancelBack(const int);

    
};


#endif

