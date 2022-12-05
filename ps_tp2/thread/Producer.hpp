/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
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
 * Producteur de messages
 */
class Producer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        for (unsigned int i = 0; i < nb_messages_; i++) {
            // - Déposer dans box_ nb_messages_ entiers positifs avec attente
            //   aléatoire avant chaque dépôt.
            std::this_thread::sleep_for( microseconds( random_engine_() ));
            // Envoi du message.
            box_.put(i);
            // - Afficher des messages entre chaque étape pour suivre l'avancement.
            osyncstream(std::cout) << "Producer " << name_ << " écrit : " << i << "\n";
        }
    }
};
 
