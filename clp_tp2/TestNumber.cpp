/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp -lgtest -lpthread
 */

#include <exception>
#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Number.hpp"


TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}
 
TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}
 
TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

// tests unitaires pour la construction par copie
TEST( TestNumber, TestNumberCopyConstructor0 )
{
    Number *number1;
    number1 = new Number{ 0 };
    Number number2{ *number1 };
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumberCopyConstructor12345678 )
{
    Number *number1;
    number1 = new Number{ 12345678 };
    Number number2{ *number1 };
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "12345678" );
}

TEST( TestNumber, TestNumberCopyConstructorBig )
{
    Number *number1;
    number1 = new Number{ 12345123451234512345UL };
    Number number2{ *number1 };
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

// tests unitaires pour l'affectation par copie
TEST( TestNumber, TestNumberCopyAssign0 )
{
    Number *number1;
    number1 = new Number{ 0 };
    Number number2 = *number1;
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumberCopyAssign12345678 )
{
    Number *number1;
    number1 = new Number{ 12345678 };
    Number number2 = *number1;
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "12345678" );
}

TEST( TestNumber, TestNumberCopyAssignBig )
{
    Number *number1;
    number1 = new Number{ 12345123451234512345UL };
    Number number2 = *number1;
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

// tests unitaires pour l'addition
TEST( TestNumber, TestNumberAdd0 )
{
    Number number1{ 123 };
    unsigned int number2{ 0 };
    number1.add( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "123" );
}

TEST( TestNumber, TestNumberAdd150 )
{
    Number number1{ 123 };
    unsigned int number2{ 150 };
    number1.add( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "273" );
}

TEST( TestNumber, TestNumberAddBig )
{
    Number number1{ 12345123451234512345UL };
    unsigned int number2{ 3210 };
    number1.add( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "12345123451234515555" );
}

// tests unitaires pour la multiplication
TEST(TestNumber, TestNumberMultiply0) {
    Number number1{ 5 };
    unsigned int number2{ 0 };
    number1.multiply( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumberMultiply150 )
{
    Number number1{ 5 };
    unsigned int number2{ 150 };
    number1.multiply( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "750" );
}

TEST( TestNumber, TestNumberMultiplyBig )
{
    Number number1{ 12345123451234512345UL };
    unsigned int number2{ 5 };
    number1.multiply( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "61725617256172561725" );
}

// définition fonction factorielle d'un entier
Number factorial( unsigned int i ) {
    Number number{ 1 };
    for (unsigned int j = 1; j <= i; ++j) {
        number.multiply( j );
    }
    return number;
}

// test unitaire pour la factorielle
TEST( TestNumber, TestFactorial123 )
{
    std::ostringstream os;
    os << factorial( 123 );;
    EXPECT_EQ( os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                         "358923621676688311569606126402021707358352212940477825910915704116514"
                         "72186029519906261646730733907419814952960000000000000000000000000000" );
}

// Ajouter les tests unitaires pour la partie 5 (Lecture).

int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
