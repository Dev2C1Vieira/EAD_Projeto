#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./include/grafos.h"

#pragma region Grafo_Functions

//
int existVertex(Grafo* grafo, char vertex[]) {
    while (grafo != NULL) {
        if (strcmp(grafo->vertex, vertex) == 0) return(1);
        else grafo = grafo->next; 
    }
    return(0);
}

Grafo* createVertex(Grafo* grafo, char newID[]) {
    Grafo* new = malloc(sizeof(struct Grafo_Registo));
    if (new != NULL) {
        if (!existVertex(grafo, newID)) {
            strcpy(new->vertex, newID);
            new->next = NULL;

            if (grafo == NULL) {
                grafo == new;
            } else {
                Grafo* current = grafo;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = new;
            }
        }
    }
}

//
void listGrafo(Grafo* grafo) {
    while (grafo != NULL) {
        printf("\n|     %-20s -> %-20s (%-10.2f);     |", grafo->vertex, grafo->adjacence->vertex, grafo->adjacence->weight);
        grafo = grafo->next;
    }
}

#pragma endregion