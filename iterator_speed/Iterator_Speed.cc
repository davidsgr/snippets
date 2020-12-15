//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   iterator_speed/Iterator_Speed.cc
 * \brief  Iterator_Speed class definitions.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <cstdlib>

// Test the speed of iterating over a container vs using []
int main(void)
{
    // Fill a vector
    std::vector<double> values(1000000000);
    for (double& d : values)
    {
        d = std::rand() / RAND_MAX;
    }

    // Iterate over the vector with operator[]
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < values.size() - 1; ++i)
    {
        if (values[i-1] < values[i] && values[i+1] > values[i])
        {
            ++count;
        }
        else
        {
            --count;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    // Iterate over the vector with iterators
    count = 0;
    start = std::chrono::high_resolution_clock::now();
    auto iter_m1 = values.begin();
    auto iter = iter_m1 + 1;
    auto iter_p1 = iter + 1;
    while (iter_p1 != values.end())
    {
        if (*iter_m1 < *iter && *iter_p1 > *iter)
        {
            ++count;
        }
        else
        {
            --count;
        }
        ++iter_m1, ++iter, ++iter_p1;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    // Better brackets
    start = std::chrono::high_resolution_clock::now();
    auto prev = values[0];
    auto current = values[1];
    for (unsigned int i = 2, i_end = values.size(); i < i_end; ++i)
    {
        auto next = values[i];
        if (prev < current && next > current)
        {
            ++count;
        }
        else
        {
            --count;
        }
        prev = current;
        current = next;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

//---------------------------------------------------------------------------//
// end of iterator_speed/Iterator_Speed.cc
//---------------------------------------------------------------------------//
