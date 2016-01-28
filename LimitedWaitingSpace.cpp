#include <iostream>
#include <iomanip>
#include <random>
#include "LimitedWaitingSpace.h"

using namespace std;

LimitedWaitingSpace::LimitedWaitingSpace()
: EventBasedModel(), queue(0), machine(1)
{
    cout << "Input capacity " << endl;
    cin >> capacity;
    
    
    interarrivalGenerator = new InterarrivalGenerator;
    serviceGenerator = new ServiceGenerator;
    
    futureEventListPtr->scheduleEvent(1,0.0);
    
    
}

void LimitedWaitingSpace::run()
{
    EventBasedModel::run();
}

void LimitedWaitingSpace::statistics() const
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

void LimitedWaitingSpace::eventRoutine(int eventType)
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
        case 4:
            enterEventRoutine();
            break;
        default:
            break;
    }
}

void LimitedWaitingSpace::finalStatisticalUpdate()
{
    // statistical accumulator
    sumQ += queue*(getEOS()-before);
    sumM += (machine == 0 ? 1 : 0)*(getEOS()-before);
}

void LimitedWaitingSpace::arriveEventRoutine()
{
    
    futureEventListPtr->scheduleEvent(1, interarrivalGenerator->generate()+ getClock());
    
    
    if (queue < capacity)
    {
        futureEventListPtr->scheduleEvent(4, getClock());
    }
    
}

void LimitedWaitingSpace::enterEventRoutine()
{
    // statistical accumulator
    sumQ += queue*(getClock()-before);
    sumM += (machine == 0 ? 1 : 0)*(getClock()-before);
    before = getClock();
    
    entityManagerPtr->arrive(getClock());
    queue++;
    
    if (machine >= 1)
    {
        futureEventListPtr->scheduleEvent(2, getClock());
    }
    
}


void LimitedWaitingSpace::loadEventRoutine()
{
    
    sumQ += queue*(getClock()-before);
    sumM += (machine == 0 ? 1 : 0)*(getClock()-before);
    before = getClock();
    
    static unsigned int loadCounter = 0;
    entityManagerPtr->load(getClock(), loadCounter);
    loadCounter++;
    queue--;
    machine--;
    
    futureEventListPtr->scheduleEvent(3, serviceGenerator->generate()+ getClock());
    
    
}
void LimitedWaitingSpace::unloadEventRoutine()
{
    
    static unsigned int unloadCounter = 0;
    entityManagerPtr->unload(getClock(), unloadCounter);
    unloadCounter++;
    machine++;
    
    if ( queue >= 1 )
    {
        futureEventListPtr->scheduleEvent(2, getClock());
    }
    
}





LimitedWaitingSpace::~LimitedWaitingSpace()
{
}
