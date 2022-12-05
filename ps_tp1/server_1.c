/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>

int main()
{

    printf("Go ! \n");

    while (1){
        int id = getpid();
        int father_id = getppid();
        printf("id %d father_id %d \n", id, father_id);

        int random_nb = rand()%100;
        printf("%d \n", random_nb);

        sleep(1);
    }

    printf("After the loop. \n");
    
    return EXIT_SUCCESS;
}
