// ===========================================================================
// Program.cpp // Prototype Pattern
// ===========================================================================

#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

// function prototypes
void test_conceptual_example_01();
void test_conceptual_example_02();
void test_conceptual_example_03();

void test_prototype_pattern_chess_01();
void test_prototype_pattern_chess_02();



class Base
{
public:
    virtual ~Base()  // <== add keyword 'virtual' in front of this line !!!
    {
        // do some important cleanup in class Base
        std::cout << "d'tor Base" << std::endl;
    }

    // hat von Derived keine Ahnung
    Base() {}

    Base(const Base& other) {

    }

    // some virtual methods
    virtual void doSomething() {}
};

class Derived : public Base
{
public:
    Derived () {}

    ~Derived()
    {
        // do some important cleanup in class Derived
        std::cout << "d'tor Derived" << std::endl;
    }
};

static void test01() {
    Base* b = new Derived();
    // use b
    delete b; // here's the problem!


    // ===========================================

    // Base* b;

    // Will von b - also dem Objekt, auf das b zeigt !!! - eine Kopie haben !!

    Base* bCopy = new Base(*b);
}



int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    test_conceptual_example_01();
    test_conceptual_example_02();
    test_conceptual_example_03();

    test_prototype_pattern_chess_01();
    test_prototype_pattern_chess_02();
    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
