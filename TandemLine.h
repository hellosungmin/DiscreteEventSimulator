
#include "FutureEventList.h"
#include "EntityManager.h"
#include "EventBasedModel.h"
#include "InterarrivalGenerator.h"
#include "ServiceGenerator.h"
using namespace std;


#ifndef TANDEMLINE_H
#define TANDEMLINE_H


class TandemLine : public EventBasedModel
{
    
public:
    TandemLine();
    virtual void run();
    virtual void statistics() const;
    virtual ~TandemLine();
    
private:

    // State Variable
    int queue1 =0;
    int queue2 =0;
    int machine1 =1;
    int machine2 =1;

    
    
    // utitlity functions
    virtual void eventRoutine(int);
    virtual void finalStatisticalUpdate();
    void arriveEventRoutine();
    void load1EventRoutine();
    void unload1EventRoutine();
    void load2EventRoutine();
    void unload2EventRoutine();
    
private: // statistical accumulator
    double sumQ1 = 0;
    double sumQ2 = 0;
    double sumM1 = 1;
    double sumM2 = 1;
    double before1 = 0;
    double before2 = 0;
    
    InterarrivalGenerator *interarrivalGenerator;
    ServiceGenerator *serviceGenerator1;
    ServiceGenerator *serviceGenerator2;

    
    
    
};

#endif
