

#ifndef Array_h
#define Array_h

#include <iostream>
#include <iomanip>
using namespace std;



template < typename T >
class Array
{
    
public:
    Array(int = 1, int = 0); // initialize value = 999 if it is an object
     ~Array();
    Array( const Array &);
    
    const Array< T > &operator=(const Array &);
    T &operator[](int);
    T operator[](int) const;
    
    // getters and setters
    int getSize() const;
    void setSize(int);
    
    
private:
    int size;
    T *ptr;
    int initialize;
    
    
    bool checkRange(int) const;
};



template< typename T >
Array< T >::Array(int size, int initialize)
: initialize(initialize)
{
    setSize(size);
    ptr = new T[size];
    
    for( int i = 0 ; i < size; i++)
    {
        ptr[i] = this->initialize;
    }

}

template< typename T >
Array< T >::Array( const Array &other)
{
    setSize(other.getSize());
    ptr = new T[size];
    
    for (int i = 0; i < size; i++)
    {
        ptr[i] = other[i];
    }
}


template< typename T >
const Array< T > &Array< T >::operator=(const Array &other)
{
    if( &other != this)
    {
        if( other.getSize() != this->size)
        {
            delete [] ptr;
            size = other.getSize();
            ptr = new T[size];
        }
        
        for ( int i = 0; i < size; i++)
        {
            ptr[i] = other[i];
        }
    }
    return *this;
}


template< typename T >
T &Array< T >::operator[](int subscript)
{
    
    try
    {
        checkRange(subscript);
    }
    catch (invalid_argument &e)
    {
        for ( int i = size; i <= subscript; i++)
        {
            ptr[i] = *(new T);
            ptr[i] = initialize;
        }
        setSize(subscript+1);
    }
    
    return ptr[subscript];
}

template< typename T >
T Array< T >::operator[](int subscript) const
{
    checkRange(subscript);
    
    return ptr[subscript];
    
    
}





template< typename T >
int Array< T >::getSize() const
{
    return size;
}

template< typename T >
void Array< T >::setSize(int size)
{
    if( size > 0)
    {
        this->size = size;
    }
    else
    {
        throw invalid_argument("Size must be greater than 0");
    }
}

template< typename T >
bool Array< T >::checkRange(int subscript) const
{
    if( subscript < 0 || subscript >= size)
    {
        throw invalid_argument("Subscript is out of range.");
    }
    else
    {
        return true;
    }
}

template< typename T >
Array< T >::~Array()
{
    delete [] ptr;
}


#endif