# DiscreteEventSimulator

Description :

  DiscreteEventSimulator allow users to :
      1 : Select an event graph model
      2 : Input statistical conditions
      3 : Output statistical report
      
Class Description :

  Classes can grouped into 4 parts :
  
      1 : Interarrival time/Service time generator
             - InterarrivalGenerator 
             - ServiceGenerator
             
      2 : FutureEventList
            - FutureEvetList
            - FutureEvent
            
      3 : Individual Event-based Model 
            - EventBasedModel // base class for individual models
            - SingleServer
            - FlexibleMultiserver
            - LimitedWaitingSpace
            - BatchedService 
            - TandemLine
            
      4 : Statistical Accumulators
            - EntityManager
            - Entity
