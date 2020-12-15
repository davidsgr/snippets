//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/hash_speed_test.cc
 * \brief  hash_speed_test class definitions.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include <tuple>
#include <vector>
#include <unordered_map>

#include "Reaction_Hasher.hh"

/*
 * The purpose of this test is to figure out the fastest way to retrieve a
 * reaction's index into a flattened index vector.  This is for implementing
 * double indexed lookups of cross sections.
 *
 * Each reaction (ZAID, temperature, MT combination) has an associated index
 * vector, which in turn provides an index into the cross sections and energy
 * grid. However, the reaction data sits at various temperature points, and we
 * often wish to lookup the the cross sections at in-between temperatures. In
 * this case, we will snap to the nearest temperature.  However, we could
 * theoretically obviate most of the temperature search cost by having every
 * requested temperature in the problem map to the correct snapped-to index. 
 *
 * Therefore, we wish to answer two questions:
 * 1) Is the search for the correct temperature expensive enough that it is
 * worth mapping every requested temperature to the actual reaction index.
 * 2) Should we store the reaction->index mapping as a single std::map, and
 * use the std::map::lower_bound() method to search, or should we use a
 * ZAID->temperatures hash table, do a fast linear search for the nearest
 * temperature, and then use a (ZAID,temp,MT)->index hash table lookup.
 */

// Define a nuclide->temperature map using a hash table
using Nuclide_Temp_Hashtable = std::unordered_map<ZAID, Vec_Temp>;

// Define a Reaction->index map using a hash table
using Reaction_Index_Hashtable
     = std::unordered_map<Reaction, index_type,
                          Reaction_Hasher,
                          Reaction_Equality>;

// Define a Reaction->index map using a std::map
using Reaction_Index_Map = std::map<Reaction, index_type, Reaction_Compare>;












namespace hash_speed_test
{
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
} // namespace hash_speed_test

//---------------------------------------------------------------------------//
// end of hash_speed_test/hash_speed_test.cc
//---------------------------------------------------------------------------//
