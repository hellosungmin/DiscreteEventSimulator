
#include <iostream>
#include "FutureEventList.h"


ostream &operator<<(ostream &output, const FutureEventList &list)
{
    FutureEvent *currentPrint = list.firstNode;
    
    while(currentPrint != list.lastNode)
    {
        output << (*currentPrint) << endl;
        currentPrint = currentPrint->getNextNode();
    }
    
    output << (*currentPrint) << endl; // last node
    
    return output;
}



FutureEventList::FutureEventList()
{
    firstNode = NULL;
    lastNode = NULL;
}

FutureEventList::FutureEventList(const FutureEventList &other)
{
    copyFromOther(other);
}


const FutureEventList &FutureEventList::operator=(const FutureEventList &other)
{
    if (&other != this)
    {
        // deleting previous allocations
        deleteList();
        
        // assigning to list
        copyFromOther(other);
    }
    
    return *this;
}

bool FutureEventList::printMemory()
{
    if ( isEmpty() )
    {
        cout << "firstNode : " << firstNode << endl;
        cout << "EmptyList"<< endl;
        cout << "lastNode : " << lastNode << endl;
        return true;
    }
    
    
    FutureEvent *currentPrint = firstNode;
    
    cout << "firstNode : " << firstNode << endl;

    while(currentPrint != lastNode)
    {
        currentPrint->printMemory();
        cout << endl;
        currentPrint = currentPrint->getNextNode();
    }
    
    currentPrint->printMemory(); //last node
    cout << endl;
    
    cout << "lastNode : " << lastNode << endl;


    return true;
}


bool FutureEventList::scheduleEvent(const int eventType, const double eventTime)
{
    // scheduling on empty list
    if ( isEmpty() )
    {
        insertFront(eventType, eventTime);
        return true;
    }
    
    // front and back of list
    if (firstNode->getEventTime() > eventTime)
    {
        insertFront(eventType, eventTime);
        return true;
    }
    else if (lastNode->getEventTime() < eventTime)
    {
        insertBack(eventType, eventTime);
        return true;
    }
    
    // searching for inbetween nodes
    FutureEvent *currentNode = firstNode->getNextNode();
    FutureEvent *previousNode = firstNode;
    
    bool breakOut = false;
    while(!breakOut)
    {
        if ( currentNode->getEventTime() > eventTime )
        {
            FutureEvent *newNode = new FutureEvent(eventType, eventTime, currentNode);
            previousNode->setNextNode(newNode);
            breakOut = true;
        }
        
        previousNode = currentNode;
        currentNode = currentNode->getNextNode();
    }
    
    return (breakOut ? true : false );
}

bool FutureEventList::scheduleEvent(const FutureEvent &other)
{
    return scheduleEvent(other.getEventType(), other.getEventTime());
}

const FutureEvent *FutureEventList::retrieveEvent()
{
    if ( isEmpty() )
    {
        throw logic_error("There is no event to retrieve");
    }
    else
    {
        FutureEvent *returnEvent = new FutureEvent(firstNode->getEventType(), firstNode->getEventTime());
        FutureEvent *toDelete = firstNode;
        
        if( firstNode == lastNode) // single element
        {
            firstNode = NULL;
            lastNode = NULL;
        }
        else // more than one
        {
            firstNode = firstNode->getNextNode();
        }
        
        delete toDelete;
        return returnEvent;
    }
}


bool FutureEventList::cancelEvent(const int eventType)
{
    if(isEmpty())
    {
        throw logic_error("There is no event to cancel.");
    }
    
    // front
    if(firstNode->getEventType() == eventType)
    {
        cancelFront(eventType);
        return true;
    }
    
    // back
    if(lastNode->getEventType() == eventType) // back
    {
        cancelBack(eventType);
        return true;
    }
    
    // between
    FutureEvent *currentNode = firstNode->getNextNode();
    FutureEvent *previousNode = firstNode;
    
    FutureEvent *toDelete = NULL;
    bool breakOut = false;
    while(!breakOut)
    {
        if (currentNode->getEventType() == eventType)
        {
            previousNode->setNextNode(currentNode->getNextNode());
            toDelete = currentNode;
            breakOut = true;
        }
        
        previousNode = currentNode;
        currentNode = currentNode->getNextNode();
    }

    delete toDelete;
    return true;
    
}



// getters and setters
FutureEvent * FutureEventList::getFirstNode() const
{
    return firstNode;
}

void FutureEventList::setFirstNode(FutureEvent * const firstNode)
{
    this->firstNode = firstNode;
}

FutureEvent * FutureEventList::getLastNode() const
{
    return lastNode;
}

void FutureEventList::setLastNode (FutureEvent * const lastNode)
{
    this->lastNode = lastNode;
}


bool FutureEventList::isEmpty() const
{
    
    return (firstNode == NULL);
}

// used in copy constructor and assignment operator overloading
void FutureEventList::copyFromOther(const FutureEventList &other)
{
    // assign from
    FutureEvent *otherObject = other.getFirstNode();
    
    // assign to
    FutureEvent *currentCopy = new FutureEvent( otherObject->getEventType(), otherObject->getEventTime());
    FutureEvent *previousCopy = currentCopy; // used to assign previous node
    
    firstNode = currentCopy;
    
    // copying dynamically allocated objects
    while(otherObject != other.getLastNode())
    {
        otherObject = otherObject->getNextNode(); // next object
        
        // assigning object's members and previousNode
        currentCopy = new FutureEvent( otherObject->getEventType(), otherObject->getEventTime());
        
        // assigning previousNode's nextNode to currentCopy
        previousCopy->setNextNode(currentCopy);
        
        // updating previousCopy
        previousCopy = currentCopy;
    }
    
    lastNode = currentCopy;
}

void FutureEventList::deleteList()
{
    if ( !isEmpty() )
    {
        FutureEvent * currentDelete = firstNode;
        FutureEvent * temp;

        while(currentDelete != lastNode)
        {
            temp = currentDelete;
            currentDelete = currentDelete->getNextNode();
            delete temp;
        }
        
        delete currentDelete; // last node
    }
}


void FutureEventList::insertFront(const int eventType, const double eventTime)
{
    FutureEvent * newNode = new FutureEvent(eventType, eventTime);
    FutureEvent * nextNode = firstNode;
    
    if(isEmpty())
    {
        firstNode = newNode;
        lastNode = newNode;
    }
    else
    {
        firstNode = newNode;
        newNode->setNextNode(nextNode);
    }
}

void FutureEventList::insertBack(const int eventType, const double eventTime)
{
    FutureEvent * newNode = new FutureEvent(eventType, eventTime);
    FutureEvent * previousNode = lastNode;
    
    if(isEmpty())
    {
        firstNode = newNode;
        lastNode = newNode;
    }
    else
    {
        lastNode = newNode;
        previousNode->setNextNode(newNode);
    }
}

void FutureEventList::cancelFront(const int eventType)
{
    if (isEmpty())
    {
        throw logic_error("There is no event to cancel.");
    }
    else
    {
        FutureEvent *toCancel = firstNode;
        
        if(firstNode == lastNode) // single element
        {
            firstNode = NULL;
            lastNode = NULL;
        }
        else
        {
            firstNode = firstNode->getNextNode();
        }
        
        delete toCancel;
    }
}

void FutureEventList::cancelBack(const int eventType)
{
    if( isEmpty())
    {
        throw logic_error("There is no event to cancel.");
    }
    else
    {
        FutureEvent *toCancel = lastNode;
        
        if (firstNode == lastNode) // single element
        {
            firstNode = NULL;
            lastNode = NULL;
        }
        else
        {
            FutureEvent *secondToLast = firstNode;
            
            // finding second to last
            while (secondToLast->getNextNode()!=lastNode)
            {
                secondToLast = secondToLast->getNextNode();
            }
            
            secondToLast->setNextNode(NULL);
            lastNode = secondToLast;
        }
        
        delete toCancel;
    }
}



FutureEventList::~FutureEventList()
{
    deleteList();
}

