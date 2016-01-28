#include "EventBasedModel.h"
#include "InterarrivalGenerator.h"
#include "ServiceGenerator.h"
using namespace std;


#ifndef LIMITEDWAITINGSPACE_H
#define LIMITEDWAITINGSPACE_H


class LimitedWaitingSpace : public EventBasedModel
{
    
public:
    LimitedWaitingSpace();
    virtual void run();
    virtual void statistics() const;
    virtual ~LimitedWaitingSpace();
    
private:

    // State Variable
    int queue;
    int machine;
    int capacity;
    
    
    // utitlity functions
    virtual void eventRoutine(int);
    virtual void finalStatisticalUpdate();
    void arriveEventRoutine();
    void loadEventRoutine();
    void unloadEventRoutine();
    void enterEventRoutine();
    
    // statistical accumulator
    double sumQ = 0;
    double before = 0;
    double sumM = 0;
    
    InterarrivalGenerator *interarrivalGenerator;
    ServiceGenerator *serviceGenerator;

    
};


#endif