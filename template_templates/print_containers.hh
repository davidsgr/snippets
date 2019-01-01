//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   template_templates/print_containers.hh
 * \brief  Prints an arbitrary container using template template parameters
 */
//---------------------------------------------------------------------------//
#ifndef template_templates_print_containers_hh
#define template_templates_print_containers_hh

#include <iostream>

// Print a container using a template-template function
template<template<class, class> class Container, typename V, typename A>
void print_cont(const Container<V, A>& cont)
{
    std::cout << "Container contains: ";
    for (V v : cont)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

// Create a container filled with the given value
template<template<class, class> class Container, typename V, class A>
Container<V, A> build_container()
{
    Container<V, A> c(10, 5);
    return c;
}

//---------------------------------------------------------------------------//
#endif // template_templates_print_containers_hh
//---------------------------------------------------------------------------//
// end of template_templates/print_containers.hh
//---------------------------------------------------------------------------//
