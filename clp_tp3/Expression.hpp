/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>
#include <memory>

class Expression {
public:
    static int nb_creees;
    static int nb_detruites;

    Expression() { ++nb_creees; };
    virtual ~Expression() { ++nb_detruites; };

    // Méthode pour l'affichage
    // Argument : le flux de sortie
    // Comportement : ajoute l'expression au flux de sortie
    // Valeur de retour : le flux de sortie (comportant l'expression)
    virtual std::ostream & print(std::ostream& os) const = 0;

    // Méthode pour la dérivation
    // Argument : le nom de la Variable selon laquelle on effectue la dérivation
    // Valeur de retour : un pointeur vers une nouvelle expression (représentant la dérivée)
    virtual Expression *derive(std::string var) const = 0;

    // Méthode pour le clonage
    virtual Expression *clone() const = 0;

    // Méthode pour la simplification des expressions
    virtual Expression *simplifier() const = 0;

private:
};

inline std::ostream & operator<<( std::ostream & os, const Expression *e )
{
    return e->print( os );
}

class Nombre : public Expression {
public:
    Nombre(float valeur) : valeur_(valeur) {}
    ~Nombre() {}

    std::ostream & print(std::ostream& os) const {
        os << valeur_;
        return os;
    }

    Nombre *derive(std::string var) const {
        return new Nombre(0);
    }

    Nombre *clone() const {
        return new Nombre(valeur_);
    }

    Nombre *simplifier() const {
        return this->clone();
    };

    // Pour la simplification
    float getVal() const {
        return valeur_;
    }

private:
    const float valeur_;
};

class Variable : public Expression {
public:
    Variable(std::string nom) : nom_(nom) {}
    ~Variable() {}

    std::ostream & print(std::ostream& os) const {
        os << nom_;
        return os;
    }

     Nombre *derive(std::string var) const {
        if (var == nom_) {
            return new Nombre(1);
        }
        return new Nombre(0);
    }

    Variable *clone() const {
        return new Variable(nom_);
    }

    Variable *simplifier() const {
        return this->clone();
    };

private:
    const std::string nom_;
};

// En C++, les liens entre un opérateur et ses opérandes sont donnés par deux attributs (left et right),
// qui sont des pointeurs vers des objets Expression (Nombre, Variable, Operation).
// Pas besoin de copier les arguments reçus : l'opérateur se les approprie.
class Operation : public Expression {
public:
    Operation(Expression *left, Expression *right) {
        left_ = left;
        right_ = right;
    }

    ~Operation() {
        if (left_ != nullptr) {
            delete left_;
        }
        if (right_ != nullptr) {
            delete right_;
        }
    }

    virtual Operation *clone() const = 0;
    virtual Expression *simplifier() const = 0;

    Expression *left_;
    Expression *right_;

private:
};

class Addition : public Operation {
public:
    Addition(Expression *left, Expression *right) : Operation(left, right) {}
    ~Addition() {}

    std::ostream & print(std::ostream& os) const {
        os << "(";
        this->left_->print(os);
        os << " + ";
        this->right_->print(os);
        os << ")";
        return os;
    }

    Addition *derive(std::string var) const {
        return new Addition(left_->derive(var), right_->derive(var));
    }

    Addition *clone() const {
        return new Addition(left_->clone(), right_->clone());
    };

    Expression *simplifier() const {
        Expression *left_simple = left_->simplifier();
        Expression *right_simple = right_->simplifier();
        Nombre *num_left = dynamic_cast<Nombre *>(left_simple);
        Nombre *num_right = dynamic_cast<Nombre *>(right_simple);

        // On simplifie l'Addition de deux objets Nombre comme la valeur de leur somme
        if (num_left != nullptr && num_right != nullptr) {
            Nombre *res = new Nombre(num_left->getVal() + num_right->getVal());
            delete left_simple;
            delete right_simple;
            return res;
        } else if (num_left != nullptr && num_left->getVal() == 0.0) {
            delete left_simple;
            return right_simple;
        } else if (num_right != nullptr && num_right->getVal() == 0.0) {
            delete right_simple;
            return left_simple;
        }
        return new Addition(left_simple, right_simple);
    }


private:
};

class Multiplication : public Operation {
public:
    Multiplication(Expression *left, Expression *right) : Operation(left, right) {}
    ~Multiplication() {}

    std::ostream & print(std::ostream& os) const {
        os << "(";
        this->left_->print(os);
        os << " * ";
        this->right_->print(os);
        os << ")";
        return os;
    }

    // On utilise la formule de dérivation d'un produit : (uv)' = u'v + uv'.
    Addition *derive(std::string var) const {
        Expression *u = left_->clone();
        Expression *v = right_->clone();
        Expression *u_prime = u->derive(var);
        Expression *v_prime = v->derive(var);
        return new Addition(new Multiplication(u_prime, v), new Multiplication(u, v_prime));
    }

    Multiplication *clone() const {
        return new Multiplication(left_->clone(), right_->clone());
    };

    Expression *simplifier() const {
        Expression *left_simple = left_->simplifier();
        Expression *right_simple = right_->simplifier();
        Nombre *num_left = dynamic_cast<Nombre *>(left_simple);
        Nombre *num_right = dynamic_cast<Nombre *>(right_simple);

        if (num_left != nullptr && num_right != nullptr) {
            Nombre *res = new Nombre(num_left->getVal() * num_right->getVal());
            delete left_simple;
            delete right_simple;
            return res;
        }

        if (num_left != nullptr) {
            if (num_left->getVal() == 0.0) {
                delete left_simple;
                delete right_simple;
                return new Nombre(0.0);
            } else if (num_left->getVal() == 1.0) {
                delete left_simple;
                return right_simple;
            }
        }
        if (num_right != nullptr) {
            if (num_right->getVal() == 0.0) {
                delete right_simple;
                delete left_simple;
                return new Nombre(0.0);
            } else if (num_right->getVal() == 1.0) {
                delete right_simple;
                return left_simple;
            }
        }

        return new Multiplication(left_simple, right_simple);
    }

private:
};

#endif
