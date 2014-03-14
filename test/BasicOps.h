#ifndef BASIC_OPS_H
#define BASIC_OPS_H

#include <sstream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Tree.h"

class BasicOpsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BasicOpsTest);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testContains);
    CPPUNIT_TEST(testRemove);
    CPPUNIT_TEST(testClear);
    CPPUNIT_TEST(testIsEmpty);
    CPPUNIT_TEST(testDumpToDot);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    void testAdd();
    void testContains();
    void testRemove();
    void testClear();
    void testIsEmpty();
    void testDumpToDot();

private:
    Tree<std::string> mTree;
    std::vector<std::string> mValues;
};


void
BasicOpsTest::setUp()
{
    mValues.push_back("zipper");
    mValues.push_back("hawked");
    mValues.push_back("hi");
    mValues.push_back("hawk");
    mValues.push_back("wither");
    mValues.push_back("bumbo");

    for (auto& x : mValues) {
        mTree.add(x);
    }
}

void
BasicOpsTest::tearDown()
{
}

void
BasicOpsTest::testAdd()
{
    CPPUNIT_ASSERT(mTree.size() == mValues.size());

    CPPUNIT_ASSERT(!mTree.contains("zygote"));
    CPPUNIT_ASSERT(mTree.add("zygote"));
    CPPUNIT_ASSERT(!mTree.add("zygote"));
    CPPUNIT_ASSERT(mTree.contains("zygote"));
    CPPUNIT_ASSERT(mTree.size() == mValues.size() + 1);
}

void
BasicOpsTest::testContains()
{
    CPPUNIT_ASSERT(mTree.size() == mValues.size());

    for (auto& x : mValues) {
        CPPUNIT_ASSERT(mTree.contains(x));
    }
    CPPUNIT_ASSERT(!mTree.contains("nothing"));
}

void
BasicOpsTest::testRemove()
{
    CPPUNIT_ASSERT(mTree.size() == mValues.size());

    for (auto& x : mValues) {
        size_t count = mTree.size();
        CPPUNIT_ASSERT(mTree.remove(x));
        CPPUNIT_ASSERT(mTree.size() == count - 1);
        CPPUNIT_ASSERT(!mTree.contains(x));
        CPPUNIT_ASSERT(!mTree.remove(x));
        CPPUNIT_ASSERT(mTree.size() == count - 1);
    }
    CPPUNIT_ASSERT(mTree.isEmpty());
}

void
BasicOpsTest::testClear()
{
    CPPUNIT_ASSERT(mTree.size() == mValues.size());

    mTree.clear();
    CPPUNIT_ASSERT(mTree.size() == 0);

    bool looped = false;
    for (auto& x : mTree) {
        looped = x == x;
    }
    CPPUNIT_ASSERT(!looped);
}

void
BasicOpsTest::testIsEmpty()
{
    CPPUNIT_ASSERT(mTree.size() == mValues.size());

    CPPUNIT_ASSERT(!mTree.isEmpty());
    mTree.clear();
    CPPUNIT_ASSERT(mTree.isEmpty());
}

void
BasicOpsTest::testDumpToDot()
{
    std::stringstream stream;
    mTree.dumpToDot(stream);

    std::string expected =
"digraph BST {\n"
"  graph [ordering=\"out\"];\n"
"  zipper -> hawked;\n"
"  hawked -> hawk;\n"
"  hawked -> hi;\n"
"  hawk -> bumbo;\n"
"  bumbo;\n"
"  hi -> wither;\n"
"  wither;\n"
"}\n";
    CPPUNIT_ASSERT(stream.str() == expected);
}

CPPUNIT_TEST_SUITE_REGISTRATION(BasicOpsTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(BasicOpsTest, "BasicOpsTest");

#endif // BASIC_OPS_H
