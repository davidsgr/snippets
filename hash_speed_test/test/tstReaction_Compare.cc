//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/test/tstReaction_Compare.cc
 * \brief  Tests for class Reaction_Equality.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include "../Definitions.hh"
#include "../Reaction_Compare.hh"

#include <iostream>

int main()
{
    // Create reactions to test equality
    Reaction rxn1 = {1001, 300.0, 18};
    Reaction rxn2 = {5010, 290.0, 18};
    Reaction rxn3 = {5010, 293.0, 18};
    Reaction rxn4 = {1001, 300.0, 1};

    Reaction_Compare rc;
    bool test1 = rc(rxn1, rxn2);
    bool test2 = rc(rxn2, rxn3);
    bool test3 = rc(rxn4, rxn1);

    if (!test1)
    {
        std::cout << "Test 1 failed." << std::endl;
    }
    if (!test2)
    {
        std::cout << "Test 2 failed." << std::endl;
    }
    if (!test3)
    {
        std::cout << "Test 3 failed." << std::endl;
    }

    if (test1 && test2 && test3)
    {
        std::cout << "Tests passed." << std::endl;
    }

    return 0;
}

//---------------------------------------------------------------------------//
// end of hash_speed_test/test/tstReaction_Compare.cc
//---------------------------------------------------------------------------//
