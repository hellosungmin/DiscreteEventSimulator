
#include "FutureEventList.h"
#include "EntityManager.h"
#include "EventBasedModel.h"
#include "InterarrivalGenerator.h"
#include "ServiceGenerator.h"
using namespace std;


#ifndef BATCHEDSERVICE_H
#define BATCHEDSERVICE_H


class BatchedService : public EventBasedModel
{
    
public:
    BatchedService();
    virtual void run();
    virtual void statistics() const;
    virtual ~BatchedService();
    
private:

    // State Variable
    int queue;
    int machine;
    int batch;
    
    
private: // utitlity functions
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

