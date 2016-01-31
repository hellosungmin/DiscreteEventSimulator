
#Discrete Event Simulator

Discrete event systems (e.g. manufacturing system) can be modeled with an event graph.

Key event graph models are implemented through this project. 


## Usage

Users can:

     1 : Select an event graph model
     
     2 : Input statistical conditions
     
     3 : Output statistical report
     
     
## Class diagram
Classes can grouped into 4 parts :
  
        1 : Individual Event-based Model
              description : 
                 - After "Fetch" cycle retrieves next event from FutureEventList, 
                   the  "Execution" cycle begins.
               
              classes : 
                 - EventBasedModel            // Base class for individual models below
                 - SingleServer                 
                 - FlexibleMultiserver          
                 - LimitedWaitingSpace         
                 - BatchedService               
                 - TandemLine
   
         2 : FutureEventList
              classes : 
                 - FutureEvetList
                 - FutureEvent
  
         3 : Interarrival time/Service time generator
              description : 
                 - Generates random numbers needed in "Execution" cycle.
            
              classes :
                 - InterarrivalGenerator 
                 - ServiceGenerator

         4 : Statistical Accumulators
              description :
                 - Event type is passed by individual model during "Execution" cycle. 
                   When the simulation is terminated, EntityManager returns statistical informations.
                   
              classes :
                 - EntityManager
                 - Entity

