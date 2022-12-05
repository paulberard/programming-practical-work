/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {
        // TODO :
        // - Ajouter les instructions de synchronisation
        // - Ne pas faire d'affichage dans cette méthode

        std::unique_lock lk(m);
        // On attend qu'un consommateur extraie un message dans le FIFO 
        while (box_size > 0) {
            cv1.wait(lk);
        }
        // On dépose un message dans le FIFO
        basic_put( message );

        // On ajoute 1 à la taille du FIFO après dépôt du message
        box_size++;

        cv2.notify_one();
    }
 
    int get() {
        // TODO :
        // - Ajouter les instructions de synchronisation
        // - Ne pas faire d'affichage dans cette méthode

        std::unique_lock lk2(m);
        // Tant que le FIFO est vide, on attend qu'un producteur dépose un message dans le FIFO
        while (box_size == 0) {
            cv2.wait(lk2);
        }
        // On extrait le message du FIFO
        int message{ basic_get() };

        // On réinitialise la taille du FIFO à 0
        box_size = 0;

        cv1.notify_one();

        return message;
    }
private:
    // TODO : 
    // - Ajouter les objets de synchronisation
    std::mutex m;
    std::condition_variable cv1;
    std::condition_variable cv2;
    int box_size = 0;
};
