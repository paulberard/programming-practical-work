/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <sstream>
#include <thread>
 
 
#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"
 
/*
 * Test avec 1 producteur et 1 consommateur
 */
void one_producer_one_consumer() {
    // - Créer un générateur de nombres aléatoires
    Random random_generator(1000);
    // - Créer une boîte à lettres
    MessageBox box_;
    // - Créer un producteur et un consommateur
    Producer producer(0, box_, random_generator, 20);
    Consumer consumer(1, box_, random_generator, 20);
    // - Créer les threads correspondants
    std::thread thread_producer(producer);
    std::thread thread_consumer(consumer);
    // - Attendre la fin des threads
    thread_producer.join();
    thread_consumer.join();
}

void several_producers_and_consumers() {
    // TODO :
    // - Créer un générateur de nombres aléatoires
    Random random_generator(1000);
    // - Créer une boîte à lettres
    MessageBox box_;
    // - Créer entre 10 et 20 consommateurs et 2 fois plus de producteurs
    // - Créer les threads correspondants
    int nb_consumers = 10 + rand()%11;
    // int nb_producers = 2 * nb_consumers;

    std::vector< std::thread > group;

    for (int i = 0; i < nb_consumers; i++) {
        group.push_back(std::thread(Consumer(i, box_, random_generator, 20)));
        group.push_back(std::thread(Producer(i, box_, random_generator, 10)));
        group.push_back(std::thread(Producer(nb_consumers + i, box_, random_generator, 10)));
    }

    // - Attendre la fin des threads
    for (auto & thread : group) {
        thread.join();
    }
}

int main() {
    // one_producer_one_consumer();
    several_producers_and_consumers();
    return 0;
}

