
#include <iostream>
#include <iomanip>
#include <random>
#include "SingleServer.h"
#include "EventBasedModel.h"
#include "InterarrivalGenerator.h"
using namespace std;

SingleServer::SingleServer()
: EventBasedModel(), queue(0), machine(1)
{
    interarrivalGenerator = new InterarrivalGenerator;
    serviceGenerator = new ServiceGenerator;
        
    futureEventListPtr->scheduleEvent(1,0.0);
    
    
}

void SingleServer::run()
{
    EventBasedModel::run();
}

void SingleServer::statistics() const
{
    EventBasedModel::statistics();
    
    double totalTimeInQueue = entityManagerPtr->getTotalQueueTime();
    int finishedQueue = entityManagerPtr-> getFinishedQueue(0);
    double maxQueueTime = entityManagerPtr->getMaximumWaitingTime();
    double averageQueueLength = sumQ/getEOS();
    double machineUtilization = sumM/getEOS();
    
    cout << "       Queue :" <<endl;
    cout << setw(45) << left << "              Finished Queue : " << finishedQueue << endl;
    cout << setw(45) << "              Total Time in Queue : " << setprecision(2) << fixed  << totalTimeInQueue << endl;
    cout << setw(45) <<"              Average waiting time in queue: " << totalTimeInQueue/finishedQueue << endl;
    cout << setw(45) <<"              Maximum waiting time : " << maxQueueTime << endl;
    cout << setw(45) <<"              Average Queue Length : " << averageQueueLength << endl;
    cout << "       Machine :" << endl;
    cout << setw(45) <<"              Machine Utilization : " << machineUtilization*100 << "%"<< endl << endl;
    
    
}

void SingleServer::eventRoutine(int eventType)
{
    switch (eventType)
    {
        case 1:
            arriveEventRoutine();
            break;
        case 2:
            loadEventRoutine();
            break;
        case 3:
            unloadEventRoutine();
            break;
        default:
            break;
    }
}

void SingleServer::finalStatisticalUpdate()
{
    sumQ += queue*(getEOS()-before);
    sumM += (machine == 0 ? 1 : 0)*(getEOS()-before);
}

void SingleServer::arriveEventRoutine()
{
    // statistical accumulator
    sumQ += queue*(getClock()-before);
    sumM += (machine == 0 ? 1 : 0)*(getClock()-before);
    before = getClock();
    
    entityManagerPtr->arrive(getClock());
    queue++;
    
    futureEventListPtr->scheduleEvent(1, interarrivalGenerator->generate() + getClock());
    
    if (machine >= 1)
    {
        futureEventListPtr->scheduleEvent(2, getClock());
    }
    
}


void SingleServer::loadEventRoutine()
{
    
    sumQ += queue*(getClock()-before);
    sumM += (machine == 0 ? 1 : 0)*(getClock()-before);
    before = getClock();
    
    static unsigned int loadCounter = 0;
    entityManagerPtr->load(getClock(), loadCounter);
    loadCounter++;
    queue--;
    machine--;
    
    futureEventListPtr->scheduleEvent(3, serviceGenerator->generate() + getClock());
    
    
}

void SingleServer::unloadEventRoutine()
{
    machine++;
    
    static unsigned int unloadCounter = 0;
    entityManagerPtr->unload(getClock(), unloadCounter);
    unloadCounter++;
    
    if ( queue >= 1 )
    {
        futureEventListPtr->scheduleEvent(2, getClock());
    }
    
}


SingleServer::~SingleServer()
{
}
