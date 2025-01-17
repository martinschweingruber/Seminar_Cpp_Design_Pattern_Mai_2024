// ===========================================================================
// DIP.cpp // Dependency Inversion Principle
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <list>

enum class Relationship { Parent, Child, Sibling };

struct Person
{
    std::string m_name;
};

namespace DependencyInversionPrinciple01
{
    class MyClass{};


    // low-level <<<<<<<<< -------------------
    class Relationships
    {
    public:
        std::vector<std::tuple<Person, Relationship, Person>> m_relations;
        // MyClass m_relations;
        // std::list<std::tuple<Person, Relationship, Person>> m_relations2;
        //MyClass  m_relations2;

        // private
        // getter/setter:   std::vector  // Kopie

        void addParentAndChild(const Person& parent, const Person& child)
        {
            m_relations.push_back(std::tuple<Person, Relationship, Person>( parent, Relationship::Parent, child ));
            
            m_relations.push_back( { child, Relationship::Child, parent } );
        }
    };

    // high-level <<<<<<<<< -------------------
    class FamilyTree
    {
    public:
        FamilyTree(const Relationships& relationships)
        {
            // using structured binding (C++ 17) and range-based for loop (C++ 11)
            for (const auto& [first, relation, second] : relationships.m_relations)
            {
                if (first.m_name == "John" && relation == Relationship::Parent) {
                    std::cout << "John has a child called " << second.m_name << std::endl;
                }
            }
        }
    };
}

namespace DependencyInversionPrinciple02
{
    // abstraction
    struct IRelationshipBrowser
    {
        virtual std::vector<Person> findAllChildrenOf(const std::string& name) const = 0;
    };

    // low-level <<<<<<<<< -------------------
    class Relationships : public IRelationshipBrowser
    {
    private:
        std::vector<std::tuple<Person, Relationship, Person>> m_relations;

    public:
        void addParentAndChild(const Person& parent, const Person& child) {
            m_relations.push_back({ parent, Relationship::Parent, child });
            m_relations.push_back({ child, Relationship::Child, parent });
        }

        std::vector<Person> findAllChildrenOf(const std::string& name) const override {

            std::vector<Person> result;
            for (const auto& [first, rel, second] : m_relations) {
                if (first.m_name == name && rel == Relationship::Parent) {
                    result.push_back(second);
                }
            }
            return result;
        }
    };

    // high-level <<<<<<<<< -------------------
    class FamilyTree
    {
    public:
        FamilyTree(const IRelationshipBrowser& browser) {

            for (const auto& child : browser.findAllChildrenOf("John")) {
                std::cout << "John has a child called " << child.m_name << std::endl;
            }
        }
    };
}

static void test_anti_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple01;

    Person parent{ "John" };
    Person child1{ "Carina" };
    Person child2{ "Mary" };

    Relationships relationships{};

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    FamilyTree tree{ relationships };  // eigentlich sieht diese Zeile anders aus :)
}

static void test_conceptual_example_dip()
{
    using namespace DependencyInversionPrinciple02;

    Person parent{ "John" };
    Person child1{ "Carina" };
    Person child2{ "Mary" };

    Relationships relationships{};

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    const IRelationshipBrowser& browser = relationships;

    FamilyTree tree{ browser };
}

void test_dip()
{
    test_anti_conceptual_example_dip();
    test_conceptual_example_dip();
}

// ===========================================================================
// End-of-File
// ===========================================================================
