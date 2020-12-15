//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/test/tstReaction_Hasher.cc
 * \brief  Tests for class Reaction_Hasher.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include "../Definitions.hh"
#include "../Reaction_Hasher.hh"

#include <iostream>

int main()
{
    // Create a few different reactions. Verify that the hashing works, and
    // they all produce different hashes
    Reaction rxn1 = {1001, 293.0, 1};
    Reaction rxn2 = {92235, 273.0, 18};
    Reaction rxn3 = {5010, 300.0, 1};
    Reaction rxn4 = {5010, 300.00001, 1};

    // Save 4 significant digits of temperature
    Reaction_Hasher hasher(4);
    auto hash1 = hasher(rxn1);
    auto hash2 = hasher(rxn2);
    auto hash3 = hasher(rxn3);
    auto hash4 = hasher(rxn4);

    bool test1 = (hash1 != hash2);
    bool test2 = (hash1 != hash3);
    bool test3 = (hash2 != hash3);
    bool test4 = (hash3 == hash4);

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
    if (!test4)
    {
        std::cout << "Test 4 failed." << std::endl;
    }

    if (test1 && test2 && test3 && test4)
    {
        std::cout << "Tests pass" << std::endl;
    }

    return 0;
}

//---------------------------------------------------------------------------//
// End hash_speed_test/test/tstReaction_Hasher.cc
//---------------------------------------------------------------------------//
