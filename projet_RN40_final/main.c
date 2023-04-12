#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "individu/individu.h"
#include "population/population.h"

int main() {
    // On initialise une seule fois srand(time(NULL))
    srand(time(NULL));

    int restart;
    do {
        // On vide la console
        system("cls");

        printf("\nBienvenue dans une simplification d'algorithmes genetiques !\n\n");

        // F1
        int longIndiv = 8;
        // F2 :
        //int longIndiv = 16;
        float pCroise = 0.5;
        int taillePop;
        int select;
        int nGen;

        taillePop = rand() %(200 - 20) + 20;
        select = ((rand()%(90 - 10) + 10) * taillePop) / 100;
        nGen = rand() %(200 - 20) + 20;

        // On affiche les informations
        printf("Nombre de bit.s par individu : %i", longIndiv);
        printf("\nProbabilite de croisement : %.3f", pCroise);
        printf("\nTaille population : %i", taillePop);
        printf("\nNombre de selection.s : %i", select);
        printf("\nNombre de generation.s : %i", nGen);

        // On initialise la population
        Population *pop = initialize_population(longIndiv,taillePop);

        // Nombre de générations
        for(int i = 0; i < nGen; i++) {
            pop = cross_population(pop,pCroise);
            pop = quicksort(pop);
            pop = tSelect(pop,select);
        }

        // On recherche et affiche le meilleur individu
        Individu *best = getBestPeople(pop);
        printf("\n\nLe meilleur individu a pour liste de bits : ");
        display_people(best);
        printf("\nSoit %i en decimal", best->value);
        printf("\nEt pour qualite %.8f\n", best->quality);

        do {
            printf("\n\nTapez 1 pour recommencer ou 0 pour arreter\n");
            scanf("%i", &restart);
        } while(restart != 0 && restart != 1);

    } while(restart == 1);
    return 0;
}
