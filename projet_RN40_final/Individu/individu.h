//
// Created by Eileen on 10/12/2022.
//

#ifndef PROJET_RN40_FINAL_INDIVIDU_H
#define PROJET_RN40_FINAL_INDIVIDU_H

#include "../structures.h"

float calculate_quality(Individu *people);
void display_people(Individu *Individu);
Individu *initialize_people_ite(int);
Individu *initialize_people_rec(int);
Individu *insert_head_people(Individu *people, Bit value);
Individu *insert_tail_people(Individu *people, Bit value);
Population *insert_tail_pop(Population *pop, Individu *people);
int calculate_value(Individu *people);


#endif //PROJET_RN40_FINAL_INDIVIDU_H
