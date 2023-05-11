#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

#define TAM 50

#pragma region Structs

typedef struct Adjacencia_Registo
{
    char vertex[100];
    float weight;
    struct Adjacencia_Registo* next;
} Adjacence;


typedef struct Grafo_Registo
{
    char vertex[100];
    Meio meio[50];
    Client client[50];
    Adjacence* adjacence;
    struct Grafo_Registo* next;
} Grafo;

#pragma endregion


#pragma region Grafo_Functions

//
int existVertex(Grafo* grafo, char vertex[]);

//
Grafo* createVertex(Grafo* grafo, char newID[]);

//
void listGrafo(Grafo* grafo);

#pragma endregion