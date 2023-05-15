#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

#pragma region Structs



typedef struct Adjacencia_Registo
{
    char vertex[TAM];
    float weight;
    struct Adjacencia_Registo* next;
} Adjacence;


typedef struct Grafo_Registo
{
    char vertex[TAM];
    Meio* meio;
    Client* client;
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
Grafo* createEdge(Grafo* grafo, char vOrigin[], char vDestiny[], float weight);

// 
void listAdjacentes(Grafo* grafo, char vertex[]);

// 
void listPerDistance(Grafo grafo, float distance, char location[]);

//
//void listGrafo(Grafo* grafo);

// 
int saveGrafo(Grafo* grafo);

#pragma endregion

#pragma region Menu

// 
int showSubMenu_Manager_Grafos(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

#pragma endregion
