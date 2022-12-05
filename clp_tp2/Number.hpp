/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.hpp
 */

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>

class Number {
public:
    // constructeur
    Number( unsigned long l ) { 
        this->first_ = new Digit(l);
     }

    // destructeur
    ~Number() { 
        delete this->first_;
     }

    // construction par copie
    Number(const Number & n) {
        first_ = new Digit(*n.first_);
    }

    // affectation par copie
    Number& operator= (const Number & n) {
        first_ = new Digit(*n.first_);
        return (*this);
    }

    // addition
    void add( unsigned int i ) {
        this->first_->add(i);
    }

    // multiplication
    void multiply( unsigned int i ){
        this->first_->multiply(i);
    }

    Number( std::string s ) {
        // gestion des erreurs
        if (s == "") {
            throw std::invalid_argument("Chaîne vide.");
        }
        for (char c : s) {
            if (!std::isdigit(c)) {
                throw std::invalid_argument("La chaîne contient au moins un caractère qui n'est pas un chiffre décimal.");
            }
        }
        // À finir !
    }
 
    // méthode affichant le nombre sur le flux de sortie
    void print( std::ostream & out ) const { 
        this->first_->print(out);
     }

private:
    using DigitType = unsigned int;
    // Un chiffre décimal par maillon : l'objectif ici n'est pas la performance
    // mais votre code doit être écrit en tenant compte de cet aspect
    static const DigitType number_base{ 10u };
    struct Digit {
        DigitType digit_;
        Digit * next_;

        // constructeur
        Digit(unsigned long l) {
            if (l >= number_base) {
                digit_ = l % number_base;
                next_ = new Digit(l / number_base);
            } else {
                digit_ = l;
                next_ = nullptr;
            }
        }

        // destructeur
        ~Digit() {
            if (next_ != nullptr) {
                delete next_;
            }
        }

        // contruction par copie
        Digit( const Digit & d ) {
            if (d.next_ == nullptr) {
                digit_ = d.digit_;
                next_ = nullptr;
            } else {
                digit_ = d.digit_;
                next_ = new Digit(*d.next_);
            }
        }

        // addition
        void add(unsigned int i) {
            unsigned int sum = digit_ + i;
            if (sum >= number_base) {
                digit_ = sum % number_base;
                if (next_ != nullptr) {
                    next_->add(sum/number_base);
                }
                else {
                    next_ = new Digit(sum/number_base);
                }
            } 
            else {
                digit_ = sum;
            }
        }

        // multiplication
        void multiply(unsigned int i) {
            unsigned int product = digit_ * i;
            if (next_ != nullptr) {
                next_->multiply(i);
            }
            if (product >= number_base) {
                digit_ = product % number_base;
                if (next_ != nullptr) {
                    next_->add(product/number_base);
                }
                else {
                    next_ = new Digit(product/number_base);
                }
            }
            else {
                digit_ = product;
            }
        }

        // méthode affichant les chiffres sur le flux
        void print(std::ostream & out ) {
            if (next_ == nullptr) {
                out << digit_;
                return;
            }
            next_->print(out);
            out << digit_;
        }
    };
    Digit * first_;
};

inline std::ostream & operator<<( std::ostream & out, const Number & n )
{
    n.print( out );
    return out;
}

std::istream & operator>>( std::istream & in, Number & n );

#endif
