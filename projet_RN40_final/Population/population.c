//
// Created by Eileen on 10/12/2022.
//
#include <stdio.h>
#include <stdlib.h>

#include "population.h"
#include "../Individu/individu.h"


Population *cross_population(Population *pop, float pCroise){

    // On initialise les deux individus qui seront croisés
    Individu *P1, *P2;

    // On crée la nouvelle population qui va être initialisée
    Population *newPop = malloc(sizeof(Population));
    newPop->popSize = 0;
    newPop->first = NULL;

    // Tant que la nouvelle population ne fait pas la taille de l'actuelle, on continue
    while(newPop->popSize < pop->popSize){
        // On initialise l'individu qui sera le résultat du croisement de P1 et P2
        Individu *P3 = malloc(sizeof(Individu));
        P3->first = NULL;
        P3->longIndiv = 0;

        // On sélectionne 2 individus aléatoirement
        P1 = getRandomPeople(pop);
        do {
            // On fait en sorte de ne pas sélectionner deux fois le même individu
            P2 = getRandomPeople(pop);
        } while(P1 == P2);


        ElemIndiv *bitP1, *bitP2;

        // On récupère le premier element de la liste chainée de P1 et P2
        bitP1 = P1->first;
        bitP2 = P2->first;

        // On croise les deux individus pour former un nouvel individu tant que l'on n'a pas parcouru tous les bits de l'individu
        while(bitP1 != NULL && bitP2 != NULL) {
            if(rand()%2 < pCroise) {
                // On prend bit de P1
                insert_tail_people(P3,bitP1->bit);
            } else {
                // On prend bit de P2
                insert_tail_people(P3,bitP2->bit);

            }

            // On passe aux bits suivants
            bitP1 = bitP1->next;
            bitP2 = bitP2->next;
        }

        // On complète les paramètres de P3
        P3->value = calculate_value(P3);
        P3->quality = calculate_quality(P3);
        // On a créé le nouvel individu, on le rajoute à la nouvelle population
        insert_tail_pop(newPop,P3);

    }
    return newPop;
}

Individu *getBestPeople(Population *pop) {
    ElemPop *best, *elem;

    best = pop->first;
    elem = pop->first;

    // Tant qu'on n'a pas parcouru toute la population
    while(elem != NULL) {
        // Si on trouve un individu meilleur que celui d'avant (donc avec une qualité plus petite) on le stocke dans Best
        if(elem->people->quality < best->people->quality) {
            best = elem;
        }

        elem = elem->next;
    }

    return best->people;
}

Individu *getRandomPeople(Population *pop) {

    ElemPop *elem;
    elem = pop->first;

    // génère un nombre aléatoire entre 0 et la taille de la population
    int random = rand()%pop->popSize;
    for(int i = 0; i < random; i++) {
        // récupère l'individu correspondant à ce nombre aléatoire
        elem = elem->next;
    }

    return elem->people;
}

Population *initialize_population(int longIndiv, int popSize) {
    // On génère le premier élément
    Population *pop = malloc(sizeof(Population));
    pop->popSize = popSize;
    pop->first = malloc(sizeof(ElemPop));
    ElemPop *elem = pop->first;
    elem->people = initialize_people_rec(longIndiv);

    // On définit ses caractéristiques
    elem->people->value = calculate_value(elem->people);
    elem->people->quality = calculate_quality(elem->people);


    for(int i = 1; i < popSize; i++) {
        // On génère le reste de la population jusqu'à la taille souhaitée
        elem->next = malloc(sizeof(ElemPop));
        elem = elem->next;
        elem->people = initialize_people_rec(longIndiv);

        // On définit ses caractéristiques
        elem->people->value = calculate_value(elem->people);
        elem->people->quality = calculate_quality(elem->people);
    }

    return pop;
}

Population *merge_pop(Population *big, Population *small) {
    ElemPop *smallElem = small->first;


    // big = meilleure qualité, small = moins bonne qualité
    if (big == NULL) {
        //Si big est NULL, on le crée
        big = malloc(sizeof(Population));
        big->first = NULL;
        big->popSize = 0;
    }

    while (smallElem != NULL) {
        // On parcourt la population de moins bonne qualité
        // On ajoute chaque individu dans l'ordre à la suite de la population big
        // On conserve ainsi l'ordre du plus grand au plus petit
        big = insert_tail_pop(big, smallElem->people);

        smallElem = smallElem->next;
    }
    return big;
}

Population *quicksort(Population *pop) {
    // Les conditions d'arrêts
    if(pop->popSize == 1 || pop == NULL || pop->first == NULL) {
        return pop;
    }

    // Dans un premier temps, il faut diviser pop en deux, et mettre les plus grands dans l'une, les plus petits dans l'autre
    int popSize = pop->popSize;
    ElemPop *elem = pop->first;

    // On initialise les populations : best = meilleure qualité, worst = moins bonne qualité
    Population *best = malloc(sizeof(Population));
    Population *worst = malloc(sizeof(Population));

    // On définit leurs paramètres
    best->popSize = 0;
    best->first = NULL;
    worst->popSize = 0;
    worst->first = NULL;


    while(elem != NULL) {
        // Pour chaque element de la population, on compare avec tous les autres elements
        int supp = 0;
        ElemPop *compare = pop->first;
        while(compare != NULL) {
            float quality1 = elem->people->quality;
            float quality2 = compare->people->quality;

            if(quality1 >= quality2) {
                // On compare les qualités afin de compter combien d'individus ont une qualité inférieure ou égale à l'individu traité
                supp++;
            }
            compare = compare->next;
        }

        // En fonction de supp, on place l'individu soit dans les meilleurs, soit dans les moins bons
        // Si meilleur est déjà plein (ça taille fait la moitié de la taille de la population initiale) on le place dans les moins bon
        if(supp >= popSize / 2 && best->popSize <= popSize / 2) {

            // Cet individu a une meilleure qualité que la moitié des individus
            best = insert_tail_pop(best,elem->people);
        }
        else {
            // Cet individu a une moins bonne qualité que la moitié des individus
            worst = insert_tail_pop(worst,elem->people);
        }

        elem = elem->next;
    }

    if(best->popSize == 0) {
        // Si on a la pop best qui est vide, alors on ne retourne que la population worst
        return worst;
    }
    else if(worst->popSize == 0) {
        // Sinon si on a la pop worst qui est vide, alors on ne retourne que la population best
        return best;
    }
    else {
        // Sinon on retourne la fusion des populations best et worst triées par récurrence
        return merge_pop(quicksort(best),quicksort(worst));
    }

}

Population *tSelect(Population *pop, int selection) {

    // On définit une Population Selected qui correspond aux individus qui vont être sélectionnés
    // pour compléter le reste de la population initiale
    Population *selected = malloc(sizeof(Population));
    selected->first = NULL;
    selected->popSize = 0;

    ElemPop *elem = pop->first;

    for(int i = 0; i < selection; i++) {
        // On récupère les individus sélectionnés
        insert_tail_pop(selected,elem->people);

        elem = elem->next;
    }

    ElemPop *forReplace = selected->first;

    // elem correspond au premier element qui doit être remplacé, puis on continue tant qu'il n'est pas NULL
    while(elem != NULL) {
        if(forReplace == NULL) {
            // Si on arrive à la fin de la liste chainée de la population sélectionnée, on recommence au début
            forReplace = selected->first;
        }

        // On tronque au fur et à mesure
        elem->people = forReplace->people;

        elem = elem->next;
        forReplace = forReplace->next;
    }

    return pop;
}