// ===========================================================================
// Program.cpp // Adapter Pattern
// ===========================================================================


#include <iostream>

// function prototypes
void test_conceptual_example();
void test_media_player_01();
void test_media_player_02();
void test_pluggable_adapter_design();

class Base
{
public:
    virtual ~Base()  // <== add keyword 'virtual' in front of this line !!!
    {
        // do some important cleanup in class Base
        std::cout << "d'tor Base" << std::endl;
    }

    // some virtual methods
    virtual void doSomething() {}
};

class Derived : public Base
{
public:
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
}


int main() 
{
    //test01();
    //return 1;

    test_conceptual_example();
    test_media_player_01();
    test_media_player_02();
    test_pluggable_adapter_design();

    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
