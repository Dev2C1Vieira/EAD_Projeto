#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./include/grafos.h"

#pragma region Grafo_Functions

/**
 * @brief 
 * 
 * @param grafo 
 * @param vertex 
 * @return int 
 */
// 
int existVertex(Grafo* grafo, char vertex[]) {
    while (grafo != NULL) {
        if (strcmp(grafo->vertex, vertex) == 0) return(1);
        grafo = grafo->next; 
    }
    return(0);
}

/**
 * @brief Create a Vertex object
 * 
 * @param grafo 
 * @param newID 
 * @return Grafo* 
 */
// 
Grafo* createVertex(Grafo* grafo, char newID[]) {
    Grafo* new = malloc(sizeof(struct Grafo_Registo));
    if (new != NULL) {
        strcpy(new->vertex, newID);
        new->meio = NULL;
        new->client = NULL;
        new->adjacence = NULL;
        new->next = NULL;
        
        if (grafo == NULL) {
            // the list is empty, so the new record will be the first record
            grafo = new;
        } else {
            Grafo* current = grafo;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new;
        }
        return(grafo);
    }
    //return(0);
}

/**
 * @brief Create a Edge object
 * 
 * @param grafo 
 * @param vOrigin 
 * @param vDestiny 
 * @param weight 
 * @return Grafo* 
 */
//
Grafo* createEdge(Grafo* grafo, char vOrigin[], char vDestiny[], float weight) {
    Adjacence* new;
    if ((existVertex(grafo, vOrigin)) && (existVertex(grafo, vDestiny))) {
        while (strcmp(grafo->vertex, vOrigin) != 0) {
            grafo = grafo->next;
        }
        new = malloc(sizeof(struct Adjacencia_Registo));
        if (new != NULL) {
            strcpy(new, vDestiny);
            new->weight = weight;
            new->next = NULL;  // Novo nó será o último da lista

            if (grafo->adjacence == NULL) {
                // Caso a lista esteja vazia, o novo nó será o primeiro
                grafo->adjacence = new;
            } else {
                // Percorre a lista até o último elemento
                Adjacence* current = grafo->adjacence;
                while (current->next != NULL) {
                    current = current->next;
                }
                // Adiciona o novo nó no final da lista
                current->next = new;
            }
        } 
        return(grafo);
    }
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param vertex 
 */
// 
void listAdjacentes(Grafo* grafo, char vertex[]) {
    if (existVertex(grafo, vertex)) {
        while (strcmp(grafo->vertex, vertex) != 0) {
            grafo = grafo->next;
        }
        if (grafo->adjacence == NULL) printf("\n\tThe vertex of the indicated graph has no adjacent vertices");
        while (grafo->adjacence != NULL) {
            printf("\n|   %-20s %-8.2f    |", grafo->adjacence->vertex, grafo->adjacence->weight);
            grafo->adjacence = grafo->adjacence->next;
        }
    }
}


/*void listPerDistance(Grafo grafo, float distance, char location[]) {
    Meio* meio;
    Adjacence adjacence;
    Grafo aux;

    int found = 0; // control variable to check if at least one Meio was found
    
    if (existVertex(grafo, location)) {
        while (strcmp(grafo->vertex, location) != 0) {
            grafo = grafo->next;
        }
        aux = grafo->vertex;
        meio = aux->meio;
        adjacence = grafo->adjacence;
        while (adjacence != NULL) {
            if (adjacence->weight <= distance) {
                printf("\n|     %-8d %-20s %-12.2f %-14.2f %-11.2f %-14s   |", meio->code, meio->type, 
                meio->battery, meio->autonomy, meio->cost, meio->location); 
                // prints the informations of the record in the console
                found++;
                adjacence = adjacence->next;
            }
            if (adjacence != NULL) {
                aux = adjacence->vertex;
                meio = aux->meio;
            }
        }
        if (found == 0) printf("\n\tThere are no Meios within %.2f radius", distance);
    }
    else printf("\n\tThe indicated vertex does not exist");
}*/

// Error
int saveGrafo(Grafo* grafo) {
    // this C code opens a file called "Grafo.txt" 
    // in write mode ("w") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Text_Files/Grafo.txt", "w");
    // checks if the file is empty or not
    if (fp != NULL)
    {
        Grafo* aux = grafo;
        while (aux != NULL) {
            Adjacence* adj = aux->adjacence;
            
            while (adj != NULL) {
                fprintf(fp, "%s;%s;%.2f\n", aux->vertex, adj->vertex, adj->weight);
                adj = adj->next;
            }
            aux = aux->next;
        }
        fclose(fp); // closes the text file
        return(1);
    }
    return(0);
}

#pragma endregion
