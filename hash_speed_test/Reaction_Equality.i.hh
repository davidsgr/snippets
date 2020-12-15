//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/Reaction_Equality.i.hh
 * \brief  Reaction_Equality inline method definitions.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef hash_speed_test_Reaction_Equality_i_hh
#define hash_speed_test_Reaction_Equality_i_hh

#include <cmath>

//---------------------------------------------------------------------------//
// PUBLIC FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Perform equality operator on two reactions
 */
bool Reaction_Equality::operator()(const Reaction& rxn1,
                                   const Reaction& rxn2) const
{
    return (rxn1.zaid == rxn2.zaid
            && rxn1.mt == rxn2.mt
            && this->soft_equal(rxn1.temperature, rxn2.temperature));
}

//---------------------------------------------------------------------------//
// PRIVATE FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Soft equal comparator for temperatures
 */
bool Reaction_Equality::soft_equal(tfloat_type temp1,
                                   tfloat_type temp2) const
{
    tfloat_type eps_rel = s_rel_prec;
    tfloat_type abs_e   = std::fabs(temp1);

    // Typical case: relative error comparison to reference
    if (std::fabs(temp1 - temp2) < eps_rel * abs_e)
    {
        return true;
    }

    tfloat_type eps_abs = s_abs_prec;
    tfloat_type abs_a = std::fabs(temp2);
    // If one is within the absolute threshold of zero, and the other within
    // relative of zero, they're equal
    if ((abs_e < eps_abs) && (abs_a < eps_rel))
    {
        return true;
    }
    if ((abs_a < eps_abs) && (abs_e < eps_rel))
    {
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------//
#endif // hash_speed_test_Reaction_Equality_i_hh

//---------------------------------------------------------------------------//
// end of hash_speed_test/Reaction_Equality.i.hh
//---------------------------------------------------------------------------//
