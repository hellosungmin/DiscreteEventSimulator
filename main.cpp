

#include <iostream>
#include "FutureEventList.h"
#include "FutureEvent.h"
#include "EventBasedModel.h"
#include "SingleServer.h"
#include "FlexibleMultiserver.h"
#include "LimitedWaitingSpace.h"
#include "BatchedService.h"
#include "TandemLine.h"
#include "Entity.h"
#include <ctime>
using namespace std;


int main()
{
    
    int input;
    cout << "Please select Simulation Type (-1 to end) " << endl;
    cout << "       1 : Single Server System " << endl;
    cout << "       2 : Flexible Multiserver System " << endl;
    cout << "       3 : Limited Waiting Space " << endl;
    cout << "       4 : Batched Service " << endl;
    cout << "       5 : Tandem Line  " << endl;
    cin >> input;
    
    EventBasedModel * simulationModel;

    switch (input) {
        case 1:
            simulationModel = new SingleServer();
            break;
        case 2:
            simulationModel = new FlexibleMultiserver();
            break;
        case 3:
            simulationModel = new LimitedWaitingSpace();
            break;
        case 4:
            simulationModel = new BatchedService();
            break;
        case 5:
            simulationModel = new TandemLine();
            break;
            
        default:
            break;
    }

    simulationModel->run();
	simulationModel->statistics();
    delete simulationModel;

	int a;
	cin >> a;
}







