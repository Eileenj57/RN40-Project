//
// Created by Eileen on 10/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "individu.h"

#define valueA (-1)
#define valueB 1

//#define valueA 0.1
//#define valueB 5


float calculate_quality(Individu *people) {
    // Pour éviter tout problème, on vérifie que people n'est pas NULL
    if(people != NULL) {
        // Calcul de la qualité en fonction de valueA et valueB
        float X = (float)(people->value / pow(2,people->longIndiv)) * (float)(valueB - valueA) + valueA;
        float quality = -(X * X); //f1
        //float quality = -log(X); //f2

        return quality;
    } else {
        return 0;
    }
}

void display_people(Individu *individu) {
    ElemIndiv *elem;
    elem = individu->first;
    while(elem != NULL) {
        // On affiche chaque bit de l'individu
        printf("%u",elem->bit);
        elem = elem->next;
    }
}

// Fonction itérative
Individu *initialize_people_ite(int longindiv) {
    Individu *l = malloc(sizeof(Individu));
    Individu *p = malloc(sizeof(Individu));
    l->first = NULL;
    p->first = NULL;
    while (longindiv>0) {
        l->first = malloc(sizeof(ElemIndiv));
        l->longIndiv = longindiv;
        l->first->bit = rand()%2;
        l->first->next = p->first;
        p->first = l->first;
        longindiv--;

    }
    return p;
}

// Fonction récursive
Individu *initialize_people_rec(int longindiv) {
    if(longindiv == 0) {
        // Condition d'arrêt, on retourne une population vierge
        return insert_head_people(NULL,rand() % 2);
    }
    // On ajoute à chaque fois en récurrence à la suite de la liste chainée population
    return insert_tail_people(initialize_people_rec(longindiv - 1),rand() % 2);
}

Individu *insert_head_people(Individu *people, Bit value) {
    if(people == NULL) {
        // Cas où people n'est pas défini, on retourne un people vierge
        people = malloc(sizeof(Individu));
        people->first = NULL;
        people->longIndiv = 0;
    }
    else if(people->first == NULL) {
        // Cas où le premier élément n'est pas défini, on le rajoute
        ElemIndiv *element = malloc(sizeof(ElemIndiv));
        element->bit = value;
        element->next = NULL;
        people->first = element;
        people->longIndiv = 1;
    } else {
        // Tous les autres cas, on ajoute au début de la liste
        ElemIndiv *element = malloc(sizeof(ElemIndiv));
        element->bit = value;
        element->next = people->first;
        people->first = element;
        people->longIndiv = people->longIndiv + 1;
    }
    return people;
}

Individu *insert_tail_people(Individu *people, Bit value) {
    if(people == NULL) {
        // Cas où people n'est pas défini, on retourne un people vierge
        people = malloc(sizeof(Individu));
        people->first = NULL;
        people->longIndiv = 0;
    }
    else if(people->first == NULL) {
        // Cas où le premier élément n'est pas défini, on le rajoute
        ElemIndiv *element = malloc(sizeof(ElemIndiv));
        element->bit = value;
        element->next = NULL;
        people->first = element;
        people->longIndiv = 1;
    } else {
        // Tous les autres cas, on ajoute à la fin de la liste
        ElemIndiv *check = people->first;
        while(check->next != NULL) {
            check = check->next;
        }
        ElemIndiv *element = malloc(sizeof(ElemIndiv));
        element->bit = value;
        element->next = NULL;
        check->next = element;
        people->longIndiv = people->longIndiv + 1;
    }

    return people;
}

Population *insert_tail_pop(Population *pop, Individu *people) {
    if(pop == NULL) {
        // Cas où pop n'est pas défini, on retourne une population vierge
        pop = malloc(sizeof(Population));
        pop->first = NULL;
        pop->popSize = 0;
    }
    else if(pop->first == NULL){
        // Cas où le premier élément n'est pas défini, on le rajoute
        ElemPop *element = malloc(sizeof(ElemPop));
        element->people = people;
        element->next = NULL;
        pop->first = element;
        pop->popSize = 1;
    } else {
        // Tous les autres cas, on ajoute à la fin de la liste
        ElemPop *check = pop->first;
        while(check->next != NULL) {
            check = check->next;
        }
        ElemPop *element = malloc(sizeof(ElemPop));
        element->people = people;
        element->next = NULL;
        check->next = element;
        pop->popSize = pop->popSize + 1;
    }
    return pop;
}

int calculate_value(Individu *people) {
    int value = 0;
    ElemIndiv *actuel;
    actuel = people->first;
    for(int i = people->longIndiv; i > 0 ; i--) {
        // On calcule la valeur
        value = (actuel->bit) * (int)pow(2,i-1) + value;
        actuel = actuel->next;
    }

    return value;
}
