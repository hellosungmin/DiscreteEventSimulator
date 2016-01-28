


#include <iostream>
#include <random> 
#include "ServiceGenerator.h"
using namespace std;



ServiceGenerator::ServiceGenerator()
{
    int serviceType;
    prompt();
    cin >> serviceType;
    setType(serviceType);
    initialize();
    
    
}

double ServiceGenerator::generate()
{
    double returnValue;
    
    if ( this->type == 1)
    {
        static default_random_engine generator;
        uniform_real_distribution<double> distribution(lowerBound,upperBound);
        returnValue = distribution(generator);
    }
    else if ( this->type == 2)
    {
        static default_random_engine generator;
        normal_distribution<double> distribution(mean,stddev);
        returnValue = abs(distribution(generator));
    }
    else if ( this->type == 3)
    {
        returnValue = specifiedValues[specifiedCounter];
        specifiedCounter++;
        
    }
    else if ( this-> type == 4)
    {
        returnValue = specifiedValues[specifiedCounter];
        specifiedCounter++;
    }
    
    return returnValue;
}


void ServiceGenerator::setType(int type)
{
    if(type > 0 && type <= 4)
    {
        this->type = type;
    }
    else
    {
        throw invalid_argument("Type must be between 1-4");
    }
}


void ServiceGenerator::prompt() const
{
    cout << "Select distribution type for service time : " << endl;
    cout << "       1 : uniform distribution "<< endl;
    cout << "       2 : normal distribution "<< endl;
    cout << "       3 : input your own" << endl;
    cout << "       4 : value in example " << endl;
}

void ServiceGenerator::initialize()
{
    if ( this->type == 1)
    {
        cout << "Input lowerbound : "<< endl;
        cin >> lowerBound;
        cout << "Input upperbound : "<< endl;
        cin >> upperBound;
    }
    else if ( this->type == 2)
    {
        cout << "Input mean : " << endl;
        cin >> mean;
        cout << "Input standard deviation : " << endl;
        cin >> stddev;
    }
    else if ( this->type == 3)
    {
        specifiedCounter = 0;
        int count = 0;
        int input;
        
        cout << "Input service time (-1 to end)" << endl;
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
    else if ( this-> type == 4)
    {
        specifiedCounter = 0;
        const int serviceTimeSize = 10;
        const double serviceTime[serviceTimeSize] = {2.90, 1.76, 3.39, 4.52, 4.46, 4.36, 2.07, 3.36, 2.37, 5.38};
        
        for ( int i = 0 ; i < serviceTimeSize; i++)
        {
            specifiedValues[i] = serviceTime[i];
        }
    }
    
}
