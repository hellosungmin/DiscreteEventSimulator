
#include "FutureEvent.h"
#include "FutureEventList.h"
#include "EntityManager.h"
#include "EventBasedModel.h"
#include "InterarrivalGenerator.h"
#include "ServiceGenerator.h"
using namespace std;


#ifndef SINGLESERVER_H
#define SINGLESERVER_H


class SingleServer : public EventBasedModel
{
    
public:
    SingleServer();
    virtual void run();
    virtual void statistics() const;
    virtual ~SingleServer();
    
private:
    
    // State Variable
    int queue;
    int machine;
    
    // utitlity functions
    virtual void eventRoutine(int);
    virtual void finalStatisticalUpdate();
    void arriveEventRoutine();
    void loadEventRoutine();
    void unloadEventRoutine();
    
    // statistical accumulator
    double sumQ = 0;
    double before = 0;
    double sumM = 0;
    
    InterarrivalGenerator *interarrivalGenerator;
    ServiceGenerator *serviceGenerator;

};


#endif

