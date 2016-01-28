

#ifndef EventBasedModel_h
#define EventBasedModel_h

#include "FutureEventList.h"
#include "EntityManager.h"


// abstract base class
class EventBasedModel
{
public:
    EventBasedModel();
    
    virtual void run();
    virtual void statistics() const;
    virtual ~EventBasedModel();
    virtual void eventRoutine(int) =0;
    virtual void finalStatisticalUpdate() =0;
    
    
    // getters and setters
    double getClock() const;
    void setClock(double);
    double getEOS() const;
    void setEOS(double);

protected:
    FutureEventList *futureEventListPtr;
    EntityManager *entityManagerPtr;
    

private:
    // State Variable
    double clock = 0.00;
    double endOfSimulation;

};


#endif
