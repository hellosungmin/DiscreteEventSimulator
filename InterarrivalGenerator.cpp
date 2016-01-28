
#include <iostream>
#include <random> 
#include "InterarrivalGenerator.h"
using namespace std;



InterarrivalGenerator::InterarrivalGenerator()
{
    int interarrivalType;
    prompt();
    cin >> interarrivalType;
    setType(interarrivalType);
    initialize();
    
}

double InterarrivalGenerator::generate()
{
    double returnValue;
    if ( type == 1)
    {
        static default_random_engine generator;
        exponential_distribution<double> distribution(lambda);
        returnValue = distribution(generator);
    }
    else if ( type == 2)
    {
        returnValue = specifiedValues[specifiedCounter];
        specifiedCounter++;
    }
    else if ( type == 3)
    {
        returnValue = specifiedValues[specifiedCounter];
        specifiedCounter++;
    }
    
    return returnValue;
}


void InterarrivalGenerator::setType(int type)
{
    if( type > 0 && type <= 3)
    {
        this->type = type;
    }
    else
    {
        throw invalid_argument("Type must be between 1~3");
    }
}

void InterarrivalGenerator::prompt() const
{
    cout << "Select distribution type for interarrial time : " << endl;
    cout << "       1 : exponential distribution " << endl;
    cout << "       2 : input your own" << endl;
    cout << "       3 : value in example " << endl;
}

void InterarrivalGenerator::initialize()
{
    if (this->type == 1)
    {
        cout << "Input lambda :  " << endl;
        cin >> lambda;
    }
    else if(this->type == 2)
    {
        specifiedCounter = 0;
        int count = 0;
        int input;
        
        cout << "Input interarrival time (-1 to end)" << endl;
        cout << "element # " << count + 1 << " : " ;
        cin >> input;
        
        while( input != -1)
        {
            specifiedValues[count] = input;
            count++;
            
            cout << "element # " << count + 1 << " : " ;
            cin >> input;
        }
    }
    else if(this->type == 3)
    {
        specifiedCounter = 0;
        const int interarrivalTimeSize = 10;
        const double interarrivalTime[interarrivalTimeSize] = {1.73, 1.35, 0.71, 0.62, 14.28, 0.70, 15.52, 3.15, 1.76, 1.00};
        
        for ( int i = 0 ; i < interarrivalTimeSize; i++)
        {
            specifiedValues[i] = interarrivalTime[i];
        }
    }
}
