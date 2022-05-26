#include <iostream>
#include <vector>
using namespace std;

// vvvvvvvvvvv example-1 vvvvvvvvvvv
// vector example
template< typename C >
void print2nd( const C& container )
{
    if( container.size() >= 2 ) {
        // C::const_iterator iter( container.begin() ); //  error: dependent-name 'C::const_iterator' is parsed as a non-type, but instantiation yields a type
        typename C::const_iterator iter( container.begin() );
        iter++;
        int value = *iter;
        cout << value;
    }
}

// vector example
template< class C >
void print3nd( const C& container )
{
    if( container.size() >= 2 ) {
        // C::const_iterator iter( container.begin() );
        typename C::const_iterator iter( container.begin() );
        iter+=2;
        int value = *iter;
        cout << value;
    }
}

// user defined class example
class CUserContainer {
public:
    static int AAA;

    // nested class
    class BBB {
    private:
        int m_nData;
    };
};

int CUserContainer::AAA = 2;

template< class D >
void Test( const D& container )
{
    cout << D::AAA; // AAA is static variable in CUserContainer
    // cout << D::BBB; // error: dependent-name 'D::BBB' is parsed as a non-type, but instantiation yields a type

    // D::BBB is considered as a type
    typename D::BBB bbb;
    cout << &bbb;
}
// ^^^^^^^^^^^ example-1 ^^^^^^^^^^^

// vvvvvvvvvvv this part is for typename special rule example vvvvvvvvvvvvvvvvvvvvvvvv
//===============class template==========
template < typename A >
class MyClass {
public:
    MyClass( A a );
private:
    A m_a;
};

template < typename A >
MyClass< A >::MyClass( A a )
{
    m_a = a;
}

template< typename A >
class DerivedMyClass:
public MyClass< A >
{
public:
    DerivedMyClass( A a, int nB );
    
private:
    int m_nB;
};

template < typename A >
DerivedMyClass< A >::DerivedMyClass( A a, int nB ):
MyClass< A >( a ),
m_nB( nB )
{
}

//===============class template2==========
template < typename A >
class MyClassNested {
public:
    MyClassNested( A a, int c ):m_a( a ), m_c( c ){};

    class Nest {
    public:
        Nest( int n ):m_n( n ){};
    private:
        int m_n; 
    };

private:
    A m_a;
    Nest m_c;
};

template< class A >
class DerivedMyClassNested:
// public typename MyClassNested< A >::Nest // error: keyword 'typename' not allowed in this context (the base class is implicitly a type)
public MyClassNested< A >::Nest
{
public:
    DerivedMyClassNested( int a, int c ):
    // typename MyClassNested< A >::Nest( c ), // error: keyword 'typename' not allowed in this context (a qualified member initializer is implicitly a type)
    MyClassNested< A >::Nest( c ),
    m_a( a ) {};

private:
    int m_a;
};
// ^^^^^^^^^^^^^^^^^^ this part is for typename special rule example ^^^^^^^^^^^^^^^^^^^^^^^^^

int main( void )
{
    // example-1
    // use "typename" to specify nested dependent name
    // correct example
    vector< int > MyVector;
    MyVector.push_back( 1 );
    MyVector.push_back( 2 );
    print2nd( MyVector );

    // incorrect example
    CUserContainer MyContainer;
    Test( MyContainer ); // try to uncomment this line

    // example-2
    // typename special rule
    MyClass< int >Test1( 1 );
    DerivedMyClass< int >D1( 1, 2 ); // derived from MyClass< int >

    MyClassNested< int >Test2( 1, 2 );
    DerivedMyClassNested< int >Test3( 1, 3 ); // derived from MyClassNested< int >::Nest

    return 0;
}