#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void red() { printf("\033[1;31m"); }
void yellow() { printf("\033[1;33m"); }
void green() { printf("\033[0;32m"); }
void blue() { printf("\033[0;34m"); }
void reset() { printf("\033[0m"); }
void clear() { system("cls || clear"); }

void flushstdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause() {
    flushstdin();
    fflush(stdin);
    printf("\n\nPress ");
    red();
    printf("any key ");
    reset();
    printf("to continue...");
    getchar();
    reset();
}

//%[^\n] sem s Gets, para permitir valor nulo
//%[^;] sem s, para permitir ler um dado do .txt

// Functions related to records of type Meio

Meio* insertNewRecord_Meio(Meio* start, int cod, char type[50], float bat,
    float aut, float cost, char loc[50]) {
    if (!existRecord_Meio(start, cod)) {
        Meio* meio = malloc(sizeof(struct Mobilidade_Registo));
        if (meio != NULL) {
            meio->code = cod;
            strcpy(meio->type, type);
            meio->battery = bat;
            meio->autonomy = aut;
            meio->cost = cost;
            strcpy(meio->location, loc);
            meio->next = start;
            //meio->next = NULL
            return(meio);
        }
    }
    else return(start);
}

int existRecord_Meio(Meio* start, int cod) {
    while (start != NULL) {
        if (start->code == cod) return(1);
        start = start->next;
    }
    return(0);
}

void listRecords_Meio(Meio* start) {
    while (start != NULL) {
        printf("\n|    %-11d %-30s %.2f %.2f %.2f %s   |\n", start->code, start->type, start->battery,
            start->autonomy, start->cost, start->location);
        start = start->next;
    }
}

int saveRecords_Meio(Meio* start)
{
    FILE* fp = fopen("Data/Records_Meio.txt", "w");

    if (fp != NULL)
    {
        Meio* aux = start;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%f;%f;%f;%s\n", aux->code, aux->type, aux->battery, 
                aux->autonomy, aux->cost, aux->location);
            aux = aux->next;
        }
        fclose(fp);
        return(1);
    }
    
    return(0);
}

// Unfinished
Meio* readRecords_Meio() {
    int code;
    float bat, aut, cost;
    char type[50], loc[50];

    FILE* fp = fopen("../data/Records_Meio.txt","r");

    Meio* aux=NULL;
    
    if (fp!=NULL) {
        while (!feof(fp))
        {
            fscanf(fp,"%d;%[^\n]s;%2.f;%2.f;%2.f;%[^\n]s\n", &code, type, &bat, &aut, &cost, loc);
            aux = insertNewRecord_Meio(aux, code, type, bat, aut, cost, loc);
        }
        fclose(fp);
    }
    return(aux);
}

// Functions related to records of type Client

Client* insertNewRecord_Client(Client* start, int id, char nome[100], int bd, int bm, int by, 
    int phn, char adr[100], int nif, float balance, char email[50], char pass[50]) {
    if (!existRecord_Client(start, id)) {
        Client* client = malloc(sizeof(struct Cliente_Registo));
        if (client != NULL) {
            client->id = id;
            strcpy(client->nome, nome);
            client->birthDate.day = bd;
            client->birthDate.month = bm;
            client->birthDate.year = by;
            client->phoneNumber = phn;
            strcpy(client->address, adr);
            client->nif = nif;
            client->saldo = balance;
            strcpy(client->email, email);
            strcpy(client->password, pass);
            client->next = start;
            return(client);
        }
    }
    else return(start);
}

int existRecord_Client(Client* start, int id) {
    while (start != NULL) {
        if (start->id == id) return(1);
        start = start->next;
    }
    return(0);
}

void listRecords_Client(Client* start) {
    while (start != NULL) {
        printf("%d %s %d-%d-%d %d %d %s %d %f %s %s\n", start->id, start->nome, start->birthDate.day, 
        start->birthDate.month, start->birthDate.year, start->phoneNumber, start->address, 
        start->nif, start->saldo, start->email, start->password);
        start = start->next;
    }
}

int saveRecords_Client(Client* start)
{
    FILE* fp = fopen("Data/Records_Client.txt", "w");

    if (fp != NULL)
    {
        Client* aux = start;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%d-%d-%d;%d;%d;%s;%d;%f;%s;%s\n", aux->id, aux->nome, aux->birthDate.day, 
            aux->birthDate.month, aux->birthDate.year, aux->phoneNumber, aux->address, 
            aux->nif, aux->saldo, aux->email, aux->password);
            aux = aux->next;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}


// Functions related to records of type Manager

Manager* insertNewRecord_Manager(Manager* start, int id, char nome[100],
    int bd, int bm, int by, int phn, char email[50], char pass[50]) {
    if (!existRecord_Manager(start, id)) {
        Manager* manager = malloc(sizeof(struct Gerente_Registo));
        if (manager != NULL) {
            manager->id = id;
            strcpy(manager->nome, nome);
            manager->birthDate.day = bd;
            manager->birthDate.month = bm;
            manager->birthDate.year = by;
            manager->phoneNumber = phn;
            strcpy(manager->email, email);
            strcpy(manager->password, pass);
            manager->next = start;
            return(manager);
        }
    }
    else return(start);
}

int existRecord_Manager(Manager* start, int id) {
    while (start != NULL) {
        if (start->id == id) return(1);
        start = start->next;
    }
    return(0);
}

void listRecords_Manager(Manager* start) {
    while (start != NULL) {
        printf("%d %s %d-%d-%d %d %s %s\n", start->id, start->nome, start->birthDate.day, 
            start->birthDate.month, start->birthDate.year, start->phoneNumber, 
            start->email, start->password);
        start = start->next;
    }
}

int saveRecords_Manager(Manager* start)
{
    FILE* fp = fopen("Data/Records_Manager.txt", "w");

    if (fp != NULL)
    {
        Manager* aux = start;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%d-%d-%d;%d;%s;%s\n", start->id, start->nome, start->birthDate.day, 
                start->birthDate.month, start->birthDate.year, start->phoneNumber,
                start->email, start->password);
            aux = aux->next;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

int login_Client(Client* start, char email[50], char pass[50]) {
    while (start != NULL) {
        if ((strcmp(start->email, email) == 0) && (strcmp(start->password, pass) == 0)) return(1);
        start = start->next;
    }
    return(0);
}

int login_Manager(Manager* start, char email[50], char pass[50]) {
    while (start != NULL) {
        if ((strcmp(start->email, email) == 0) && (strcmp(start->password, pass) == 0)) return(1);
        start = start->next;
    }
    return(0);
}

