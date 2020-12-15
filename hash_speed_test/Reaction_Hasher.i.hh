//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/Reaction_Hasher.i.hh
 * \brief  Reaction_Hasher inline method definitions.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef hash_speed_test_Reaction_Hasher_i_hh
#define hash_speed_test_Reaction_Hasher_i_hh

#include <cmath>

//---------------------------------------------------------------------------//
// CONSTRUCTOR
//---------------------------------------------------------------------------//
/*!
 * \brief Constructor
 */
Reaction_Hasher::Reaction_Hasher(unsigned int num_digits)
{
  double basetwo_digits = (10.0 / 3.0) * static_cast<double>(num_digits);
  d_basetwo_digits = std::ceil(basetwo_digits);
}

//---------------------------------------------------------------------------//
// PUBLIC FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Hash operator
 */
auto Reaction_Hasher::operator()(const Reaction& rxn) const -> value_type
{
    value_type hash = INITIAL_BASIS;

    // Add ZAID
    this->hash(hash, rxn.zaid);

    // Add temperature
    this->hash(hash, rxn.temperature);

    // Add MT
    this->hash(hash, rxn.mt);

    return hash;
}

//---------------------------------------------------------------------------//
// PRIVATE FUNTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Hash an integral value
 */
template<typename T>
void Reaction_Hasher::hash(
    value_type& hash,
    T           value,
    typename std::enable_if<std::is_integral<T>::value>::type*) const
{
    this->fnv_hash(hash, reinterpret_cast<const char*>(&value), sizeof(T));
}

//---------------------------------------------------------------------------//
/*!
 * \brief Soft-hash a floating point value
 */
template<typename T>
void Reaction_Hasher::hash(
    value_type& hash,
    T           value,
    typename std::enable_if<std::is_floating_point<T>::value>::type*) const
{
    this->fnv_hash(hash, reinterpret_cast<const char*>(&value), sizeof(T));
}

//---------------------------------------------------------------------------//
/*!
 * \brief Round the given floating-point value
 */
template<typename T>
T Reaction_Hasher::rounded_float(
    T value,
    typename std::enable_if<std::is_floating_point<T>::value>::type*) const
{
    // Decompose into base-2 exponent and floating point value
    // (floating point value is in [.5,1) , i.e. [2**-1, 2**0) )
    int digits = d_basetwo_digits;
    int exp = 0;
    value = std::frexp(value, &exp);
    // Multiply by 2**n (digits to keep)
    value = std::ldexp(value, digits);
    // Round
    value = std::round(value);
    // Combine rounded significand back with the original exponent (divided
    // by 2**n)
    value = std::ldexp(value, exp - digits);
    return value;
}

//---------------------------------------------------------------------------//
/*!
 * \brief Perform FNV hash of the given data
 */
void Reaction_Hasher::fnv_hash(value_type& hash,
                               const char* data,
                               std::size_t count) const
{
    for (const char* end = data + count; data != end; ++data)
    {
        hash ^= *data;
        hash *= MAGIC_PRIME;
    }
}

//---------------------------------------------------------------------------//
#endif // hash_speed_test_Reaction_Hasher_i_hh

//---------------------------------------------------------------------------//
// end of hash_speed_test/Reaction_Hasher.i.hh
//---------------------------------------------------------------------------//
