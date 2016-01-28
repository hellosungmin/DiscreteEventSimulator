



#include <iostream>
#include <iomanip>
#include "EventBasedModel.h"
#include "FutureEventList.h"
using namespace std;


EventBasedModel::EventBasedModel()
: clock(0.00)
{
    futureEventListPtr = new FutureEventList();
    entityManagerPtr = new EntityManager();
    
    double eos;
    cout << "Input EOS " << endl;
    cin >> eos;
    setEOS(eos);
    
}

void EventBasedModel::run()
{
    cout << endl << endl << endl;
    
    static char input;
    
    cout << "Would you like to output simulation process? (y/n) "<< endl;
    
    cin >> input;
    
    if ( input == 'y')
    {
        cout << "Simulation Process : " << endl << endl;
        
    }
    
    while ( getClock() <= getEOS() )
    {
        
        int eventType;
        double eventTime;
        
        // Outputting process
        if ( input == 'y')
        {
            cout << "\nRemaining Events : " ;
            cout << "  Clock : "  << getClock() << "    " << endl;
            cout << *futureEventListPtr;
            cout << endl;
        }
        
        
        
        // Retrieve event and time
        const FutureEvent retreiveEvent = *(futureEventListPtr->retrieveEvent());
        
        eventType = retreiveEvent.getEventType();
        eventTime = retreiveEvent.getEventTime();
        
        
        setClock(eventTime);
        
        if (getClock() <= getEOS())
        {
            eventRoutine(eventType);
        }
    }
    
    finalStatisticalUpdate();
}


void EventBasedModel::statistics() const
{
    
    int finishedSystem = entityManagerPtr->getFinishedSystem();
    double totalTimeInSystem = entityManagerPtr->getTotalSystemTime();
    double maxSystemTime = entityManagerPtr->getMaximumSystemTime();

    
    cout << "\n\n\nStatistics Report : " << endl << endl;
    cout << "       EOS :  " << getEOS() << endl;
    cout << "       System :" << endl;
    cout << setw(45) <<"              Finished in System " << finishedSystem << endl;
    cout << setw(45) <<"              Total Time in System : "<< totalTimeInSystem << endl;
    cout << setw(45) <<"              Maximum System time : " << maxSystemTime <<  endl;
    
}


double EventBasedModel::getClock() const
{
    return clock;
}

void EventBasedModel::setClock(double clock)
{
    if( clock >= 0)
    {
        this->clock = clock;
    }
    else
    {
        invalid_argument("clock value must be greater than 0");
    }
}

double EventBasedModel::getEOS() const
{
    return endOfSimulation;
}

void EventBasedModel::setEOS(double eos)
{
    if( eos >= 0)
    {
        this->endOfSimulation = eos;
    }
    else
    {
        invalid_argument("eos value must be greater than 0");
    }
}

EventBasedModel::~EventBasedModel()
{
    delete futureEventListPtr;
    delete entityManagerPtr;
}