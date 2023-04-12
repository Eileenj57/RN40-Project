//
// Created by Eileen on 10/12/2022.
//

#ifndef PROJET_RN40_FINAL_STRUCTURES_H
#define PROJET_RN40_FINAL_STRUCTURES_H

typedef unsigned char Bit;

typedef struct ElemIndiv ElemIndiv;
struct ElemIndiv {
    ElemIndiv *next;
    Bit bit;
};

typedef struct Individu Individu;
struct Individu {
    ElemIndiv *first;
    int longIndiv;
    int value;
    float quality;
};

typedef struct ElemPop ElemPop;
struct ElemPop {
    ElemPop *next;
    Individu *people;
};

typedef struct Population Population;
struct Population {
    ElemPop *first;
    int popSize;
};

#endif //PROJET_RN40_FINAL_STRUCTURES_H
