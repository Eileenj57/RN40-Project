//
// Created by Eileen on 10/12/2022.
//

#ifndef PROJET_RN40_FINAL_POPULATION_H
#define PROJET_RN40_FINAL_POPULATION_H

#include "../structures.h"

Population *cross_population(Population *pop, float pCroise);
Individu *getBestPeople(Population *pop);
Individu *getRandomPeople(Population *pop);
Population *initialize_population(int longIndiv, int popSize);
Population *merge_pop(Population *big, Population *small);
Population *quicksort(Population *pop);
Population *tSelect(Population *pop, int selection);

#endif //PROJET_RN40_FINAL_POPULATION_H
