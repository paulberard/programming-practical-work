/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include <chrono>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"

#include "../Random.hpp"

// Définition de l'unité de temps : un nombre entier de microsecondes
using microseconds = std::chrono::duration< int, std::micro >;
 
/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        for (unsigned int i = 0; i < nb_messages_; i++) {
            // - Retirer de box_ nb_messages_ entiers avec attente aléatoire avant
            //   chaque retrait.
            std::this_thread::sleep_for( microseconds( random_engine_() ));
            // - Afficher des messages entre chaque étape pour suivre l'avancement.
            osyncstream(std::cout) << "Consumer " << name_ << " en attente... ";
            int received_int = box_.get();
            // - Afficher un message d'erreur si un nombre négatif est extrait.
            if (received_int < 0) {
                osyncstream(std::cerr) << "Consumer " << name_ << " a reçu un nombre négatif : " << received_int << "\n";
            }
            else {
                osyncstream(std::cout) << "Consumer " << name_ << " lit : " << received_int << "\n";
            }
        }
    };
};
