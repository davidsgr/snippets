//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   hash_speed_test/hash_speed_test.cc
 * \brief  hash_speed_test class definitions.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include <vector>
#include <unordered_map>
#include <map>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>

#include "Reaction_Hasher.hh"
#include "Reaction_Equality.hh"
#include "Reaction_Compare.hh"

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


//---------------------------------------------------------------------------//

tfloat_type find_closest_temp(const std::vector<tfloat_type>& temps,
                              tfloat_type                     temperature)
{
    tfloat_type diff = std::fabs(temperature - temps.front());
    for (auto iter = temps.begin() + 1; iter != temps.end(); ++iter)
    {
        tfloat_type new_diff = std::fabs(temperature - *iter);
        if (new_diff < diff)
        {
            diff = new_diff;
        }
        else
        {
            // We found the closest temperature
            return *iter;
        }
    }

    // If we get down here, return highest temp
    return temps.back();
}

//---------------------------------------------------------------------------//

int main()
{
    // Load a bunch of nuclides
    std::vector<ZAID> zaids = {
        1001, 1002, 1003, 2003, 2004, 3006, 3007, 4007, 4009, 5010, 5011, 6000,
        7014, 7015, 8016, 8017, 9019, 11022, 11023, 12024, 12025, 12026, 13027,
        14028, 14029, 14030, 15031, 16032, 16033, 16034, 16036, 17035, 17037,
        18036, 18038, 18040, 19039, 19040, 19041, 20040, 20042, 20043, 20044,
        20046, 20048, 21045, 22046, 22047, 22048, 22049, 22050, 23050, 23051,
        24050, 24052, 24053, 24054, 25055, 26054, 26056, 26057, 26058, 27058,
        27059, 28058, 28059, 28060, 28061, 28062, 28064, 29063, 29065, 30064,
        30065, 30066, 30067, 30068, 30070, 31069, 31071, 32070, 32072, 32073,
        32074, 32076, 33074, 33075, 34074, 34076, 34077, 34078, 34079, 34080,
        34082, 35079, 35081, 36078, 36080, 36082, 36083, 36084, 36085, 36086,
        37085, 37086, 37087, 38084, 38086, 38087, 38088, 38089, 38090, 39089,
        39090, 39091, 40090, 40091, 40092, 40093, 40094, 40095, 40096, 41093,
        41094, 41095, 42092, 42094, 42095, 42096, 42097, 42098, 42099, 42100,
        43099, 44096, 44098, 44099, 44100, 44101, 44102, 44103, 44104, 44105,
        44106, 45103, 45105, 46102, 46104, 46105, 46106, 46107, 46108, 46110,
        47107, 47109, 47111, 48106, 48108, 48110, 48111, 48112, 48113, 48114,
        48116, 49113, 49115, 50112, 50113, 50114, 50115, 50116, 50117, 50118,
        50119, 50120, 50122, 50123, 50124, 50125, 50126, 51121, 51123, 51124,
        51125, 51126, 52120, 52122, 52123, 52124, 52125, 52126, 52128, 52130,
        52132, 53127, 53129, 53130, 53131, 53135, 54123, 54124, 54126, 54128,
        54129, 54130, 54131, 54132, 54133, 54134, 54135, 54136, 55133, 55134,
        55135, 55136, 55137, 56130, 56132, 56133, 56134, 56135, 56136, 56137,
        56138, 56140, 57138, 57139, 57140, 58136, 58138, 58139, 58140, 58141,
        58142, 58143, 58144, 59141, 59142, 59143, 60142, 60143, 60144, 60145,
        60146, 60147, 60148, 60150, 61147, 61148, 61149, 61151, 62144, 62147,
        62148, 62149, 62150, 62151, 62152, 62153, 62154, 63151, 63152, 63153,
        63154, 63155, 63156, 63157, 64152, 64153, 64154, 64155, 64156, 64157,
        64158, 64160, 65159, 65160, 66156, 66158, 66160, 66161, 66162, 66163,
        66164, 67165, 68162, 68164, 68166, 68167, 68168, 68170, 69168, 69169,
        69170, 71175, 71176, 72174, 72176, 72177, 72178, 72179, 72180, 73180,
        73181, 73182, 74180, 74182, 74183, 74184, 74186, 75185, 75187, 77191,
        77193, 79197, 80196, 80198, 80199, 80200, 80201, 80202, 80204, 81203,
        81205, 82204, 82206, 82207, 82208, 83209, 88223, 88224, 88225, 88226,
        89225, 89226, 89227, 90227, 90228, 90229, 90230, 90231, 90232, 90233,
        90234, 91229, 91230, 91231, 91232, 91233, 92230, 92231, 92232, 92233,
        92234, 92235, 92236, 92237, 92238, 92239, 92240, 92241, 93234, 93235,
        93236, 93237, 93238, 93239, 94236, 94237, 94238, 94239, 94240, 94241,
        94242, 94243, 94244, 94246, 95240, 95241, 95242, 95243, 95244, 96240,
        96241, 96242, 96243, 96244, 96245, 96246, 96247, 96248, 96249, 96250,
        97245, 97246, 97247, 97248, 97249, 97250, 98246, 98248, 98249, 98250,
        98251, 98252, 98253, 98254, 99251, 99252, 99253, 99254, 99255, 100255,
        1001001, 1008016, 1013027, 1014028, 1014029, 1014030, 1026000, 1027058,
        1040090, 1040091, 1040092, 1040093, 1040094, 1040095, 1040096, 1047110,
        1048115, 1052127, 1052129, 1061148, 1067166, 1092235, 1095242, 1095244,
        1099254, 2001001, 3004009, 3006000, 4001001, 4001002, 5001001, 5001002,
        5004009, 5006000, 5008016, 6001001, 7001001, 8001001, 8001002, 9001001};
    std::vector<MT> mts = {1, 2, 3, 4, 16, 17, 18, 27, 37, 51, 52, 53, 54, 55,
                           56, 57, 3001, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
                           68, 452, 69, 70, 71, 455, 72, 456, 73, 74, 75, 459,
                           76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
                           89, 90, 91, 101, 102};
    std::vector<tfloat_type> temps = {300.0, 600.0, 900.0, 1200.0};

    // Fill nuclide temp hashtable
    Nuclide_Temp_Hashtable nth;
    for (ZAID zaid : zaids)
    {
        nth[zaid] = temps;
    }

    // Fill reaction index hashtable
    Reaction_Index_Hashtable rih;
    index_type idx = 0;
    for (ZAID zaid : zaids)
    {
        for (tfloat_type temp : temps)
        {
            for (MT mt : mts)
            {
                rih[Reaction{zaid, temp, mt}] = idx++;
            }
        }
    }

    // Fill reaction index map
    Reaction_Index_Map rim;
    idx = 0;
    for (ZAID zaid : zaids)
    {
        for (tfloat_type temp : temps)
        {
            for (MT mt : mts)
            {
                rim[Reaction{zaid, temp, mt}] = idx++;
            }
        }
    }

    // Setup random seed
    srand((unsigned) time(0));

    // >>> LOOKUP METHOD 1: Given a reaction at some temperature between 300
    // >>> and 900, lookup the reaction index using method 1:
    // 1) Lookup the temperature vector using the nuclide temp hashtable
    // 2) Perform linear search for closest temperature
    // 3) Lookup index from Reaction_Index_Map using closest temperature

    // Loop and sample. Time the method
    using Clock = std::chrono::high_resolution_clock;
    auto t1 = Clock::now();
    unsigned int num_samples = 100000000;
    for (unsigned int sample = 0; sample < num_samples; ++sample)
    {
        // Sample ZAID and MT
        int zaid_index = rand() % (zaids.size());
        int mt_index = rand() % (mts.size());
        // Sample random temperature between 1200 and 300
        tfloat_type temperature
            = (static_cast<double>(rand()) / RAND_MAX) * (1200 - 300) + 300;

        // Get the ZAID
        ZAID zaid = zaids[zaid_index];
        MT mt = mts[mt_index];

        // Step 1: Lookup the temperature vector for this nuclide
        const std::vector<tfloat_type>& available_temps
            = nth.find(zaid)->second;

        // Step 2: Get the closest temperature
        tfloat_type closest_temp
            = find_closest_temp(available_temps, temperature);

        // Step 3: Lookup the index for this reaction
        index_type idx = rih[Reaction{zaid, closest_temp, mt}];
    }
    auto t2 = Clock::now();
    std::cout << "Method 1: "
              << std::chrono::duration_cast<
                  std::chrono::milliseconds>(t2 - t1).count()
              << " ms" << std::endl;

    return 0;
}


//---------------------------------------------------------------------------//
// end of hash_speed_test/hash_speed_test.cc
//---------------------------------------------------------------------------//
