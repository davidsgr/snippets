//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/Reaction_Compare.hh
 * \brief  Reaction_Compare class declaration.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef hash_speed_test_Reaction_Compare_hh
#define hash_speed_test_Reaction_Compare_hh

//===========================================================================//
/*!
 * \class Reaction_Compare
 * \brief Implements operator less-than for two reactions
 */
//===========================================================================//

class Reaction_Compare
{
  public:
    //! Implements operator < for two reactions
    bool operator()(const Reaction& rxn1, const Reaction& rxn2) const
    {
        // Lexicographical compare, with ZAID and MT first, temperature last
        if (rxn1.zaid < rxn2.zaid)
            return true;
        else if (rxn1.zaid == rxn2.zaid)
        {
            if (rxn1.mt < rxn2.mt)
                return true;
            else if (rxn1.mt == rxn2.mt)
            {
                if (rxn1.temperature < rxn2.temperature)
                    return true;
            }
        }

        return false;
    }
};

//---------------------------------------------------------------------------//
#endif // hash_speed_test_Reaction_Compare_hh
//---------------------------------------------------------------------------//
// end of hash_speed_test/Reaction_Compare.hh
//---------------------------------------------------------------------------//
