
#include "FutureEventList.h"
#include "EntityManager.h"
#include "EventBasedModel.h"
#include "InterarrivalGenerator.h"
#include "ServiceGenerator.h"
using namespace std;


#ifndef FLEXIBLEMULTISERVER_H
#define FLEXIBLEMULTISERVER_H


class FlexibleMultiserver : public EventBasedModel
{
    
public:
    FlexibleMultiserver();
    virtual void run();
    virtual void statistics() const;
    virtual ~FlexibleMultiserver();
    
private:
    
    // State Variable
    int queue;
    int machine;
    double numberOfMachine;
    
    
    // utitlity functions
    virtual void eventRoutine(int);
    virtual void finalStatisticalUpdate();
    void arriveEventRoutine();
    void loadEventRoutine();
    void unloadEventRoutine();
    
private: // statistical accumulator
    double sumQ = 0;
    double before = 0;
    double sumM = 0;
    
    InterarrivalGenerator *interarrivalGenerator;
    ServiceGenerator *serviceGenerator;
    
    
};


#endif