
#include <iostream>
#include <iomanip>
#include <random>
#include "TandemLine.h"

using namespace std;

TandemLine::TandemLine()
: EventBasedModel(), queue1(0), queue2(0), machine1(1), machine2(1)
{

    interarrivalGenerator = new InterarrivalGenerator;
    cout << "\nMachine 1 : " << endl;
    serviceGenerator1 = new ServiceGenerator;
    cout << "\nMachine 2 : " << endl;
    serviceGenerator2 = new ServiceGenerator;
    
    futureEventListPtr->scheduleEvent(7,0.0);
    
    
}

void TandemLine::run()
{
    EventBasedModel::run();
    
}

void TandemLine::statistics() const
{
    EventBasedModel::statistics();
    
    double totalTimeInQueue = entityManagerPtr->getTotalQueueTime();
    double totalTimeInQueue1 = entityManagerPtr->getQueueTime(0);
    double totalTimeInQueue2 = entityManagerPtr->getQueueTime(1);
    int finishedQueue1 = entityManagerPtr-> getFinishedQueue(0);
    int finishedQueue2 = entityManagerPtr-> getFinishedQueue(1);
    double maxQueue1Time = entityManagerPtr->getMaximumWaitingTime(0);
    double maxQueue2Time = entityManagerPtr->getMaximumWaitingTime(1);
    double averageQueue1Length = sumQ1/getEOS();
    double machine1Utilization = sumM1/getEOS();
    double averageQueue2Length = sumQ2/getEOS();
    double machine2Utilization = sumM2/getEOS();
    
    

    cout << "       Queue:" <<endl;
    cout << setw(45) << "              Total Time in Queue : " << setprecision(2) << fixed  << totalTimeInQueue << endl;
    cout << "       Queue 1:" <<endl;
    cout << setw(45) << left << "              Finished Queue : " << finishedQueue1 << endl;
    cout << setw(45) <<"              Average waiting time in queue: " << totalTimeInQueue1/finishedQueue1 << endl;
    cout << setw(45) <<"              Maximum waiting time : " << maxQueue1Time << endl;
    cout << setw(45) <<"              Average Queue Length : " << averageQueue1Length << endl;
    
    cout << "       Queue 2:" <<endl;
    cout << setw(45) << left << "              Finished Queue : " << finishedQueue2 << endl;
    cout << setw(45) <<"              Average waiting time in queue: " << totalTimeInQueue2/finishedQueue2 << endl;
    cout << setw(45) <<"              Maximum waiting time : " << maxQueue2Time << endl;
    cout << setw(45) <<"              Average Queue Length : " << averageQueue2Length << endl;
    cout << "       Machine :" << endl;
    cout << setw(45) <<"              Machine 1 Utilization : " << machine1Utilization*100 << "%"<< endl;
    cout << setw(45) <<"              Machine 2 Utilization : " << machine2Utilization*100 << "%"<< endl << endl;
    
    
}

void TandemLine::eventRoutine(int eventType)
{
    // 1 : Arrival, 2 : Load, 3 : Unload
    switch (eventType)
    {
        case 7:
            arriveEventRoutine();
            break;
        case 8:
            load1EventRoutine();
            break;
        case 9:
            unload1EventRoutine();
            break;
        case 10:
            load2EventRoutine();
            break;
        case 11:
            unload2EventRoutine();
            break;
        default:
            break;
    }
}


void TandemLine::finalStatisticalUpdate()
{
    sumQ1 += queue1*(getEOS()-before1);
    sumM1 += (machine1 == 0 ? 1 : 0)*(getEOS()-before1);
    
    sumQ2 += queue2*(getEOS()-before2);
    sumM2 += (machine2 == 0 ? 1 : 0)*(getEOS()-before2);
    
}

void TandemLine::arriveEventRoutine()
{
    // statistical accumulator
    sumQ1 += queue1*(getClock()-before1);
    sumM1 += (machine1 == 0 ? 1 : 0)*(getClock()-before1);
    before1 = getClock();
    
    entityManagerPtr->arrive(getClock());
    queue1++;
    
    
    futureEventListPtr->scheduleEvent(7, interarrivalGenerator->generate()+ getClock());
    
    
    if (machine1 >= 1)
    {
        futureEventListPtr->scheduleEvent(8, getClock());
    }
    
}


void TandemLine::load1EventRoutine()
{
    
    sumQ1 += queue1*(getClock()-before1);
    sumM1 += (machine1 == 0 ? 1 : 0)*(getClock()-before1);
    before1 = getClock();
    
    
    static unsigned int loadCounter1 = 0;
    entityManagerPtr->load(getClock(), loadCounter1);
    loadCounter1++;
    queue1--;
    machine1 = 0;
    
    
    futureEventListPtr->scheduleEvent(9, (serviceGenerator1->generate() + getClock()));
    
    
}
void TandemLine::unload1EventRoutine()
{
    sumQ2 += queue2*(getClock()-before2);
    sumM2 += (machine2 == 0 ? 1 : 0)*(getClock()-before2);
    before2 = getClock();
    
    static unsigned int unloadCounter1 = 0;
    entityManagerPtr->unloadNext(getClock(),unloadCounter1);
    unloadCounter1++;
    machine1 = 1;
    queue2++;
    
    
    
    if ( machine2 > 0)
    {
        futureEventListPtr->scheduleEvent(10, getClock());
    }
    
    if ( queue1 >= 1 )
    {
        futureEventListPtr->scheduleEvent(8, getClock());
    }

    
}



void TandemLine::load2EventRoutine()
{
    sumQ2 += queue2*(getClock()-before2);
    sumM2 += (machine2 == 0 ? 1 : 0)*(getClock()-before2);
    before2 = getClock();
    
    static unsigned int loadCounter2 = 0;
    entityManagerPtr->load(getClock(), loadCounter2);
    loadCounter2++;
    machine2 = 0;
    queue2--;
    
    futureEventListPtr->scheduleEvent(11, serviceGenerator2->generate()+ getClock());
    
    
    
    
}

void TandemLine::unload2EventRoutine()
{
    
    static unsigned int unloadCounter2 = 0;
    entityManagerPtr->unload(getClock(), unloadCounter2);
    unloadCounter2++;
    machine2 = 1;
    
    if ( queue2 > 0 )
    {
        futureEventListPtr->scheduleEvent(10, getClock());
    }
    
    
}

TandemLine::~TandemLine()
{
}
