#pragma once

#include <QDebug>

#define DEBUG_LOCATION() qDebug("* %s", __PRETTY_FUNCTION__)

#define DEBUG_VALUE(value) qDebug() << "  "#value << value;

#define TEST(function) static bool function##Run = true; if (function##Run) { qDebug("* Run test '%s'", #function); function##Run = false; function(); qDebug("Test '%s' PASSED", #function); }

template <typename Type>
bool testCompare(const Type& actual, const Type& expected)
{
    return actual == expected;
}

template <typename Type>
void testAssert(const Type& actual, const Type& expected, const char* file, const int line)
{
    if (actual != expected)
    {
        qCritical() << "! Assert actual" << actual << ", expected" << expected << ", at" << file << ":" << line;
        abort();
    }
}

#define TEST_ASSERT(a, e) testAssert(a, e, __FILE__, __LINE__)
