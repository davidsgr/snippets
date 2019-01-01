//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   template_templates/main.cc
 * \brief  main class definitions.
 * \note   Copyright (c) 2018 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include "print_containers.hh"

#include <vector>
#include <list>

int main(void)
{
    // Create a vector of integers and print using the template-template
    // function
    std::vector<int> vi = {1, 2, 3, 4, 5};
    print_cont(vi);

    // Create a list of doubles and print using the template-template function
    std::list<double> ld = {5.0, 6.0, 7.0, 8.0, 9.0};
    print_cont(ld);

    // Explicit template specialization with template templates doesn't appear
    // to work with gcc 8
    // Create a vector filled with 5
    //using vec_t = std::vector<int>;
    //vec_t vi2 = build_container<vec_t, int, std::allocator<int>>();
    //print_cont(vi2);
}

//---------------------------------------------------------------------------//
// end of template_templates/main.cc
//---------------------------------------------------------------------------//
