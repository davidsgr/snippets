//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/test/tstReaction_Equality.cc
 * \brief  Tests for class Reaction_Equality.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include "../Definitions.hh"
#include "../Reaction_Equality.hh"

#include <iostream>

int main()
{
    // Create reactions to test equality
    Reaction rxn1 = {1001, 293.0, 1};
    Reaction rxn2 = {1001, 293.000000000000001, 1};
    Reaction rxn3 = {5010, 300.0, 1};

    Reaction_Equality req;

    bool test1 = req(rxn1, rxn2);
    bool test2 = !req(rxn1, rxn3);

    if (!test1)
    {
        std::cout << "Test 1 failed." << std::endl;
    }
    if (!test2)
    {
        std::cout << "Test 2 failed." << std::endl;
    }

    if (test1 && test2)
    {
        std::cout << "Tests passed." << std::endl;
    }

    return 0;
}

//---------------------------------------------------------------------------//
// end of hash_speed_test/test/tstReaction_Equality.cc
//---------------------------------------------------------------------------//
