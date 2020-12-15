//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/Definitions.hh
 * \brief  Definitions class declaration.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef hash_speed_test_Definitions_hh
#define hash_speed_test_Definitions_hh

#include <vector>

// Define some basic types
using ZAID        = unsigned int;
using MT          = int;
using tfloat_type = float;
using index_type  = unsigned int;
using Vec_Temp    = std::vector<tfloat_type>;

struct Reaction
{
    ZAID        zaid;
    tfloat_type temperature;
    MT          mt;
};

//---------------------------------------------------------------------------//
#endif // hash_speed_test_Definitions_hh
//---------------------------------------------------------------------------//
// end of hash_speed_test/Definitions.hh
//---------------------------------------------------------------------------//
