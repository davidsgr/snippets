//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/Reaction_Hasher.hh
 * \brief  Reaction_Hasher class declaration.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef hash_speed_test_Reaction_Hasher_hh
#define hash_speed_test_Reaction_Hasher_hh

#include "Definitions.hh"

//===========================================================================//
/*!
 * \class Reaction_Hasher
 * \brief Performs a hash of a reaction.
 */
//===========================================================================//

class Reaction_Hasher
{
    using value_type = std::uint64_t;

  private:
    static constexpr value_type INITIAL_BASIS = 0xcbf29ce484222325ull;
    static constexpr value_type MAGIC_PRIME   = 0x00000100000001b3ull;

    int d_basetwo_digits;

  public:
    // Constructor
    inline explicit Reaction_Hasher(unsigned int num_digits = 4);

    // Hashing operator
    inline value_type operator()(const Reaction& rxn) const;

  private:
    // Hash the given integral value
    template<typename T>
    void hash(
        value_type& hash,
        T           value,
        typename std::enable_if<std::is_integral<T>::value>::type* = 0) const;

    // Soft-hash the given floating-point value
    template<typename T>
    void hash(
        value_type& hash,
        T           value,
        typename std::enable_if<
            std::is_floating_point<T>::value>::type* = 0) const;

    // Round the given floating-point value
    template<typename T>
    inline T rounded_float(
        T value,
        typename std::enable_if<
        std::is_floating_point<T>::value>::type* = 0) const;

    // Add raw data to the hash using the FNV algorithm
    inline void fnv_hash(value_type& hash,
                         const char* data,
                         std::size_t count) const;
};

//---------------------------------------------------------------------------//
// INLINE DEFINITIONS
//---------------------------------------------------------------------------//
#include "Reaction_Hasher.i.hh"
//---------------------------------------------------------------------------//
#endif // hash_speed_test_Reaction_Hasher_hh
//---------------------------------------------------------------------------//
// end of hash_speed_test/Reaction_Hasher.hh
//---------------------------------------------------------------------------//
