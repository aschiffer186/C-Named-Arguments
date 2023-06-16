#include <gtest/gtest.h>

#include "NamedArguments.hpp"

int numDefaultCtorCalls = 0;
int numCopyCtorCalls = 0;
int numMoveCtorCalls = 0;
int numCopyAssgnCalls = 0;
int numMoveAssgnCalls = 0;
int numDtorCalls = 0;

struct Tattle 
{
    Tattle()
    {
        ++numDefaultCtorCalls;
    }

    Tattle(const Tattle&)
    {
        ++numCopyCtorCalls;
    }

    Tattle(Tattle&&) noexcept 
    {
        ++numMoveCtorCalls;
    }

    Tattle& operator=(const Tattle&)
    {
        ++numCopyAssgnCalls;
        return *this;
    }

    Tattle& operator=(Tattle&&) noexcept 
    {
        ++numMoveAssgnCalls;
        return *this;
    }

    ~Tattle()
    {
        ++numDtorCalls;
    }
};

TEST(TestNamedArguments, Test)
{
 
}