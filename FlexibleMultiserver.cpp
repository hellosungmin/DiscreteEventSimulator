


#include <iostream>
#include <iomanip>
#include <random>
#include "FlexibleMultiserver.h"

using namespace std;

FlexibleMultiserver::FlexibleMultiserver()
: EventBasedModel(), queue(0)
{
    cout << "Input number of Machine : " << endl;
    cin >> numberOfMachine;
    machine = numberOfMachine;
    
    interarrivalGenerator = new InterarrivalGenerator;
    serviceGenerator = new ServiceGenerator;
    
    futureEventListPtr->scheduleEvent(1,0.0);
    
}

void FlexibleMultiserver::run()
{
    EventBasedModel::run();
}

void FlexibleMultiserver::statistics() const
{
    EventBasedModel::statistics();
    
    double totalTimeInQueue = entityManagerPtr->getTotalQueueTime();
    int finishedQueue = entityManagerPtr-> getFinishedQueue(0);
    double maxQueueTime = entityManagerPtr->getMaximumWaitingTime();
    double averageQueueLength = sumQ/getEOS();
    double machineUtilization = sumM/(getEOS()*numberOfMachine);
    
    cout << "       Queue :" <<endl;
    cout << setw(45) << left << "              Finished Queue : " << finishedQueue << endl;
    cout << setw(45) << "              Total Time in Queue : " << setprecision(2) << fixed  << totalTimeInQueue << endl;
    cout << setw(45) <<"              Average waiting time in queue: " << totalTimeInQueue/finishedQueue << endl;
    cout << setw(45) <<"              Maximum waiting time : " << maxQueueTime << endl;
    cout << setw(45) <<"              Average Queue Length : " << averageQueueLength << endl;
    cout << "       Machine :" << endl;
    cout << setw(45) <<"              Average Machine Utilization : " << machineUtilization*100 << "%"<< endl << endl;
    
    
}

void FlexibleMultiserver::eventRoutine(int eventType)
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

void FlexibleMultiserver::finalStatisticalUpdate()
{
    // statistical accumulator
    sumQ += queue*(getEOS()-before);
    sumM += (numberOfMachine - machine)*(getEOS()-before);
}

void FlexibleMultiserver::arriveEventRoutine()
{
    // statistical accumulator
    sumQ += queue*(getClock()-before);
    sumM += (numberOfMachine - machine)*(getClock()-before);
    before = getClock();
    
    entityManagerPtr->arrive(getClock());
    queue++;
    
    
    futureEventListPtr->scheduleEvent(1, interarrivalGenerator->generate()+ getClock());
    
    if (machine >= 1)
    {
        futureEventListPtr->scheduleEvent(2, getClock());
    }
    
}


void FlexibleMultiserver::loadEventRoutine()
{
    
    sumQ += queue*(getClock()-before);
    sumM += (numberOfMachine - machine)*(getClock()-before);
    before = getClock();
    
    static unsigned int loadCounter = 0;
    entityManagerPtr->load(getClock(), loadCounter);
    loadCounter++;
    queue--;
    machine--;
    
    futureEventListPtr->scheduleEvent(3, serviceGenerator->generate() + getClock());
    
    if ((queue > 0) && (machine > 0))
    {
        futureEventListPtr->scheduleEvent(2, getClock());
    }
    
}

void FlexibleMultiserver::unloadEventRoutine()
{
    
    static unsigned int unloadCounter = 0;
    entityManagerPtr->unload(getClock(), unloadCounter);
    unloadCounter++;
    machine++;
    
    if ( (queue >= 1)&&(machine > 0 ))
    {
        futureEventListPtr->scheduleEvent(2, getClock());
    }
    
}

FlexibleMultiserver::~FlexibleMultiserver()
{
}