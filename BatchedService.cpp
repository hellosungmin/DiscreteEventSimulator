
#include <iostream>
#include <iomanip>
#include <random>
#include "BatchedService.h"

using namespace std;

BatchedService::BatchedService()
: EventBasedModel(), queue(0), machine(1)
{


    cout << "Input Batch Size " << endl;
    cin >> batch;
    
    interarrivalGenerator = new InterarrivalGenerator;
    serviceGenerator = new ServiceGenerator;
    
    futureEventListPtr->scheduleEvent(1,0.0);
    
    
}

void BatchedService::run()
{
    EventBasedModel::run();
}

void BatchedService::statistics() const
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

void BatchedService::eventRoutine(int eventType)
{
    // 1 : Arrival, 2 : Load, 3 : Unload
    switch (eventType)
    {
        case 1:
            arriveEventRoutine();
            break;
        case 5:
            loadEventRoutine();
            break;
        case 6:
            unloadEventRoutine();
            break;
            
        default:
            break;
    }
}

void BatchedService::finalStatisticalUpdate()
{
    // statistical accumulator
    sumQ += queue*(getEOS()-before);
    sumM += (machine == 0 ? 1 : 0)*(getEOS()-before);
}

void BatchedService::arriveEventRoutine()
{
    // statistical accumulator
    sumQ += queue*(getClock()-before);
    sumM += (machine == 0 ? 1 : 0)*(getClock()-before);
    before = getClock();
    
    entityManagerPtr->arrive(getClock());
    queue++;
    
    
    futureEventListPtr->scheduleEvent(1, interarrivalGenerator->generate()+ getClock());
    
    
    if ((machine >= 1)&(queue>=batch))
    {
        futureEventListPtr->scheduleEvent(5, getClock());
    }
    
}


void BatchedService::loadEventRoutine()
{
    
    sumQ += queue*(getClock()-before);
    sumM += (machine == 0 ? 1 : 0)*(getClock()-before);
    before = getClock();
    
    static unsigned int loadCounter = 0;
    for ( int i = 0; i < batch; i++)
    {
        entityManagerPtr->load(getClock(), loadCounter);
        loadCounter++;
    }
    queue = (queue - batch);
    machine--;
    
    futureEventListPtr->scheduleEvent(6, serviceGenerator->generate()+ getClock());
    
    
    
}
void BatchedService::unloadEventRoutine()
{
    
    static unsigned int unloadCounter = 0;
    for ( int i = 0 ; i < batch; i++)
    {
        entityManagerPtr->unload(getClock(), unloadCounter);
        unloadCounter++;
    }
    machine++;
    
    if ( queue >= batch )
    {
        futureEventListPtr->scheduleEvent(5, getClock());
    }
    
}


BatchedService::~BatchedService()
{

}