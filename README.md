
#Discrete Event Simulator
Discrete event systems such as a manufacturing system can be modeled with an event graph.

Key event graph models are implemented through this project. 


## Usage
Users can:
     1 : Select an event graph model
     2 : Input statistical conditions
     3 : Output statistical report
     
     
## Class diagram
Classes can grouped into 4 parts :
  
        1 : Individual Event-based Model 
        :(After "Fetch" cycle retrieves next event from FutureEventList, the  "Execution" cycle begins.) 
             - EventBasedModel // base class for individual models
             - SingleServer
             - FlexibleMultiserver
             - LimitedWaitingSpace
             - BatchedService 
             - TandemLine
   
         2 : FutureEventList
            - FutureEvetList
            - FutureEvent
  
         3 : Interarrival time/Service time generator
         :(Generates random numbers needed in "Execution" cycle.)
             - InterarrivalGenerator 
             - ServiceGenerator

         4 : Statistical Accumulators
         :(Event type is passed by individual model during "Execution" cycle. When the simulation is terminated,
         EntityManager returns statistical informations.)
             - EntityManager
             - Entity

