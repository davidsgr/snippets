//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/Reaction_Equality.hh
 * \brief  Reaction_Equality class declaration.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef hash_speed_test_Reaction_Equality_hh
#define hash_speed_test_Reaction_Equality_hh

#include "Definitions.hh"

//===========================================================================//
/*!
 * \class Reaction_Equality
 * \brief Tests that two reactions are equal.
 */
//===========================================================================//

class Reaction_Equality
{
  private:
    static constexpr tfloat_type s_rel_prec = 1.0e-6f;
    static constexpr tfloat_type s_abs_prec = 1.0e-8f;

  public:
    //! Perform equality operator on two reactions
    inline bool operator()(const Reaction& rxn1, const Reaction& rxn2) const;
    
  private:
    // Soft equal comparator for temperatures
    inline bool soft_equal(tfloat_type temp1, tfloat_type temp2) const;  
};

//---------------------------------------------------------------------------//
// INLINE DEFINITIONS
//---------------------------------------------------------------------------//
#include "Reaction_Equality.i.hh"
//---------------------------------------------------------------------------//
#endif // hash_speed_test_Reaction_Equality_hh
//---------------------------------------------------------------------------//
// end of hash_speed_test/Reaction_Equality.hh
//---------------------------------------------------------------------------//
