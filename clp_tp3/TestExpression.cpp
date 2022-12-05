/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Expression.hpp"

 
int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

// Affichage

// Nombre

TEST( TestExpressionNombre, TestAffichage )
{
    // Construction d'un Nombre
    Nombre *num = new Nombre(4.89);
    std::ostringstream os;
    os << num;
    // Test sur l'affichage de la valeur du Nombre
    EXPECT_EQ( os.str(), "4.89" );

    delete num;
}

// Variable

TEST( TestExpressionVariable, TestAffichage )
{
    // Construction d'une Variable
    Variable *var = new Variable("var");
    std::ostringstream os;
    os << var;
    // Test sur l'affichage du nom de la Variable
    EXPECT_EQ( os.str(), "var" );

    delete var;
}


// Dérivation

// Nombre

TEST( TestExpressionNombre, TestDeriveNombre )
{
    // Construction d'un Nombre
    Nombre *num = new Nombre(6);
    // On dérive par rapport à une variable x
    Expression *derivee = num->derive("x");
    std::ostringstream os;
    os << derivee;
    // Test sur l'obtention de "0" pour la dérivation d'un Nombre
    EXPECT_EQ( os.str(), "0" );
    
    // On vérifie que le Nombre est non-modifié
    std::ostringstream os_2;
    os_2 << num;
    EXPECT_EQ( os_2.str(), "6" );

    delete num;
    delete derivee;
}

// Variable

TEST( TestExpressionVariable, TestDeriveVar )
{
    // Construction d'une Variable
    Variable *x = new Variable("x");
    // On dérive la Variable par rapport à elle-même
    Expression *derivee = x->derive("x");
    std::ostringstream os;
    os << derivee;
    // Test sur l'obtention de "1" pour la dérivation d'une Variable par rapport à elle-même
    EXPECT_EQ( os.str(), "1" );

    // On vérifie que la Variable est non-modifiée
    std::ostringstream os_2;
    os_2 << x;
    EXPECT_EQ( os_2.str(), "x" );

    delete x;
    delete derivee;
}

TEST( TestExpressionVariable, TestDeriveAutreVar )
// On vérifie que la variable initiale est inchangée
{
    // Construction d'une Variable
    Variable *x1 = new Variable("x1");
    // On dérive la Variable "x1" par rapport à une autre Variable "x2"
    Expression *derivee = x1->derive("x2");
    std::ostringstream os;
    os << derivee;
    // Test sur l'obtention de "0" pour la dérivation d'une Variable par rapport une autre Variable
    EXPECT_EQ( os.str(), "0" );

    // On vérifie que la Variable est non-modifiée
    std::ostringstream os_2;
    os_2 << x1;
    EXPECT_EQ( os_2.str(), "x1" );

    delete x1;
    delete derivee;
}

// Opérations

// Addition

// Affichage

TEST( TestExpressionOperations, TestAdditionNombresAffichage )
{ 
    // Construction de deux objets Nombre et un objet Addition
    Nombre *num1 = new Nombre(0.1);
    Nombre *num2 = new Nombre(2.2);
    Addition *addition_ = new Addition( num1, num2 );
    std::ostringstream os;
    os << addition_;
    // Test sur l'obtention de "(0.1 + 2.2)" pour l'affichage de l'Addition de deux objets Nombre
    EXPECT_EQ( os.str(), "(0.1 + 2.2)" );

    delete addition_;
}

TEST( TestExpressionOperations, TestAdditionVariablesAffichage )
{ 
    // Construction de deux objets Variable et un objet Addition
    Variable *x = new Variable("x");
    Variable *y = new Variable("y");
    Addition *addition_ = new Addition( x, y );
    std::ostringstream os;
    os << addition_;
    // Test sur l'obtention de "(x + y)" pour l'affichage de l'Addition de deux objets Variable
    EXPECT_EQ( os.str(), "(x + y)" );

    delete addition_;
}

TEST( TestExpressionOperations, TestAdditionComposeAffichage )
{ 
    // Construction de deux objets Nombre, un objet Variable et 
    Nombre *num1 = new Nombre(8.6);
    Variable *x = new Variable("x");
    Nombre *num2 = new Nombre(1.9);
    Addition *addition1 = new Addition( num1, x );
    Addition *addition2 = new Addition( num2, addition1 );
    std::ostringstream os;
    os << addition2;
    // Test sur l'obtention de "(1.9 + (8.6 + x))" pour l'affichage d'une composition de deux Additions
    EXPECT_EQ( os.str(), "(1.9 + (8.6 + x))" );

    delete addition2;
}

// Dérivation

TEST( TestExpressionOperations, TestAdditionDerivation )
{ 
    Variable *x = new Variable("x");
    Nombre *num = new Nombre(0.7);
    Addition *addition_ = new Addition( x, num );
    Expression *derivee = addition_->derive("x");
    std::ostringstream os_1;
    os_1 << derivee;
    EXPECT_EQ( os_1.str(), "(1 + 0)" );

    std::ostringstream os_2;
    os_2 << addition_;
    EXPECT_EQ( os_2.str(), "(x + 0.7)" );

    delete addition_;
    delete derivee;
}

TEST( TestExpressionOperations, TestAdditionDerivationCompose )
{ 
    Nombre *num = new Nombre(7.5);
    Variable *x = new Variable("x");
    Variable *y = new Variable("y");
    Addition *addition1 = new Addition( num, x );
    Addition *addition2 = new Addition( y, addition1 );
    Expression *derivee = addition2->derive("x");
    std::ostringstream os_1;
    os_1 << derivee;
    EXPECT_EQ( os_1.str(), "(0 + (0 + 1))" );
    
    std::ostringstream os_2;
    os_2 << addition2;
    EXPECT_EQ( os_2.str(), "(y + (7.5 + x))" );

    delete addition2;
    delete derivee;
}

// Multiplication 

TEST( TestExpressionOperations, TestMultiplicationNombresAffichage )
{
    Nombre *num1 = new Nombre(3.5);
    Nombre *num2 = new Nombre(5.8);
    Multiplication *mult = new Multiplication{ num1, num2 };
    std::ostringstream os;
    os << mult;
    EXPECT_EQ( os.str(), "(3.5 * 5.8)" );

    delete mult;
}

TEST( TestExpressionOperations, TestMultiplicationVariablesAffichage )
{
    Variable *x = new Variable("x");
    Variable *y = new Variable("y");
    Multiplication *mult = new Multiplication{ x, y };
    std::ostringstream os;
    os << mult;
    EXPECT_EQ( os.str(), "(x * y)" );

    delete mult;
}

TEST( TestExpressionOperations, TestMultiplicationComposeAffichage )
{
    Variable *x = new Variable("x");
    Nombre *num1 = new Nombre(1.4);
    Nombre *num2 = new Nombre(2.7);
    Multiplication *mult1 = new Multiplication{ x, num1 };
    Multiplication *mult2 = new Multiplication{ num2, mult1 };
    std::ostringstream os;
    os << mult2;
    EXPECT_EQ( os.str(), "(2.7 * (x * 1.4))" );

    delete mult2;
}

TEST( TestExpressionOperations, TestMultiplicationDerivation )
{ 
    Nombre *num = new Nombre(7.1);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication( num, x );
    Expression *derivee = mult->derive("x");
    std::ostringstream os_1;
    os_1 << derivee;
    EXPECT_EQ( os_1.str(), "((0 * x) + (7.1 * 1))" );

    std::ostringstream os_2;
    os_2 << mult;
    EXPECT_EQ( os_2.str(), "(7.1 * x)" );

    delete mult;
    delete derivee;
}

TEST( TestExpressionOperations, TestMultiplicationDerivationCompose )
{ 
    Nombre *num = new Nombre(2.6);
    Variable *x = new Variable("x");
    Variable *y = new Variable("y");
    Multiplication *mult1 = new Multiplication( num, x );
    Multiplication *mult2 = new Multiplication( mult1, y );
    Expression *derivee = mult2->derive("x");
    std::ostringstream os_1;
    os_1 << derivee;
    EXPECT_EQ( os_1.str(), "((((0 * x) + (2.6 * 1)) * y) + ((2.6 * x) * 0))" );
    
    std::ostringstream os_2;
    os_2 << mult2;
    EXPECT_EQ( os_2.str(), "((2.6 * x) * y)" );

    delete mult2;
    delete derivee;
}

// Clonage

TEST( TestExpressionClonage, TestClonageNombre )
{
    Nombre *num = new Nombre(6.2);
    Nombre *clone = num->clone();
    delete num;

    // On vérifie que le clone n'a pas été effacé
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "6.2" );

    delete clone;
}

TEST( TestExpressionClonage, TestClonageVariable )
{
    Variable *var = new Variable("x");
    Variable *clone = var->clone();
    delete var;

    // On vérifie que le clone n'a pas été effacé
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "x" );

    delete clone;
}

TEST( TestExpressionClonage, TestClonageAddition )
{
    Nombre *num = new Nombre(6.2);
    Variable *x = new Variable("x");
    Addition *addition_ = new Addition{ x, num };
    Addition *clone = addition_->clone();
    delete addition_;

    // On vérifie que le clone n'a pas été effacé
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "(x + 6.2)" );

    delete clone;
}

TEST( TestExpressionClonage, TestClonageMultiplication )
{
    Nombre *num = new Nombre(0.2);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication{ num, x };
    Multiplication *clone = mult->clone();
    delete mult;

    // On vérifie que le clone n'a pas été effacé
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "(0.2 * x)" );

    delete clone;
}

// Simplification

// Addition

TEST( TestExpressionSimplification, TestSimplificationAdditionGauche )
{
    Nombre *num = new Nombre(0.0);
    Variable *x = new Variable("x");
    Addition *addition_ = new Addition{ num, x };
    Expression *addition_simpl = addition_->simplifier();
    std::ostringstream os;
    os << addition_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete addition_;
    delete addition_simpl;
}

TEST( TestExpressionSimplification, TestSimplificationAdditionDroite )
{
    Variable *x = new Variable("x");
    Nombre *num = new Nombre(0.0);
    Addition *addition_ = new Addition{ x, num };
    Expression *addition_simpl = addition_->simplifier();
    std::ostringstream os;
    os << addition_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete addition_;
    delete addition_simpl;
}

TEST( TestExpressionSimplification, TestSimplificationAdditionNombres )
{
    Nombre *num1 = new Nombre(1.9);
    Nombre *num2 = new Nombre(3.1);
    Addition *addition_ = new Addition{ num1, num2 };
    Expression *addition_simpl = addition_->simplifier();
    std::ostringstream os;
    os << addition_simpl;
    EXPECT_EQ( os.str(), "5" );

    delete addition_;
    delete addition_simpl;
}

// Multiplication

TEST( TestExpressionSimplification, TestSimplificationMultiplication1Gauche )
{
    Nombre *num = new Nombre(1.0);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication{ num, x };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpressionSimplification, TestSimplificationMultiplication1Droite )
{
    Variable *x = new Variable("x");
    Nombre *num = new Nombre(1.0);
    Multiplication *mult = new Multiplication{ x, num };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpressionSimplification, TestSimplificationMultiplication0Gauche )
{
    Nombre *num = new Nombre(0.0);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication{ num, x };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "0" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpressionSimplification, TestSimplificationMultiplication0Droite )
{
    Variable *x = new Variable("x");
    Nombre *num = new Nombre(0.0);
    Multiplication *mult = new Multiplication{ x, num };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "0" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpressionSimplification, TestSimplificationMultiplicationNombres)
{
    Nombre *num1 = new Nombre(7.0);
    Nombre *num2 = new Nombre(2.0);
    Multiplication *mult = new Multiplication{ num1, num2 };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "14" );

    delete mult;
    delete mult_simpl;
}

// Nombre d'instances créées et détruites

TEST( TestExpression, TestInstancesCreeesDetruites )
{
    EXPECT_EQ( Expression::nb_creees, Expression::nb_detruites );
}
