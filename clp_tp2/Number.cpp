/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.cpp
 */

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "Number.hpp"

std::istream & operator>>( std::istream & in, Number & n )
{
    // À finir !

    // in est le flux d'entrée
    // ignore les blancs au début
    in >> std::ws;
    while( in.good() ) {
    int c{ in.get() };

    if( std::isdigit( c )) {
        unsigned int d{ static_cast< unsigned int >( c - '0' )};
        // il faut append le chiffre d à n
    }
    else {
        in.putback( c );
        break;
    }
    }

    return in;
}
