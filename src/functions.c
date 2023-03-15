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

// %[^\n] sem s Gets, para permitir valor nulo
// %[^;] sem s, para permitir ler um dado do .txt

// Functions related to records of type Meio

Meio* insertNewRecord_Meio(Meio* start, int code, char type[50], float bat,
    float aut, float cost, char loc[50]) {
    if (!existRecord_Meio(start, code)) {
        Meio* meio = malloc(sizeof(struct Mobilidade_Registo));
        if (meio != NULL) {
            meio->code = code;
            strcpy(meio->type, type);
            meio->battery = bat;
            meio->autonomy = aut;
            meio->cost = cost;
            strcpy(meio->location, loc);
            meio->next = start;
            return(meio);
        }
    }
    else return(start);
    //saveRecords_Meio(start);
}

int existRecord_Meio(Meio* start, int code) {
    while (start != NULL) {
        if (start->code == code) return(1);
        start = start->next;
    }
    return(0);
}

void listRecords_Meio(Meio* start) {
    while (start != NULL) {
        printf("\n|     %-8d %-20s %-12.2f %-14.2f %-10.2f %-15s   |", start->code, start->type, start->battery,
            start->autonomy, start->cost, start->location);
        start = start->next;
    }
}

Meio* removeRecord_Meio(Meio* start, int code) {
    Meio *prev = start, *now = start, *aux;

    if (now == NULL) return(NULL);
        else if (now->code == code) {
            aux = now->next;
            free(now);
            return(aux);
        }
        else {
            while ((now != NULL) && (now->code != code))
            {
                prev = now;
                now = now->next;
            }
            if (now == NULL) return(start);
            else {
                prev->next = now->next;
                free(now);
                return(start);
            }
        }
}

Meio* editRecord_Meio(Meio* start, int code, char type[50], float bat,
    float aut, float cost, char loc[50]) {
        int code_v;
    char type_v[50], loc_v[50];
    float bat_v, aut_v, cost_v;

    Meio* aux = start;

    // Saving the old data
    /*    code_v = start->code;
    strcpy(type_v, start->type);
    bat_v = start->battery;
    aut_v = start->autonomy;
    cost_v = start->cost;
    strcpy(loc_v, start->location);*/

    // Setting the new data to the record
    if (existRecord_Meio(aux, code)) {
        while (aux != NULL) {
            if (aux->code == code) {
                
                /*if (type[0] == '\n') {
                    strcpy(aux->type, type_v);
                    aux->battery = bat_v;
                    aux->autonomy = aut;
                    aux->cost = cost;
                    strcpy(aux->location, loc);
                }
                if (bat == -1.00) {
                    strcpy(aux->type, type);
                    aux->battery = bat_v;
                    aux->autonomy = aut;
                    aux->cost = cost;
                    strcpy(aux->location, loc);
                }
                if (aut == -1.00) {
                    strcpy(aux->type, type);
                    aux->battery = bat;
                    aux->autonomy = aut_v;
                    aux->cost = cost;
                    strcpy(aux->location, loc);
                }
                if (cost == -1.00) {
                    strcpy(aux->type, type);
                    aux->battery = bat;
                    aux->autonomy = aut;
                    aux->cost = cost_v;
                    strcpy(aux->location, loc);
                    
                }
                if (loc[0] == '\n') {
                    strcpy(aux->type, type);
                    aux->battery = bat_v;
                    aux->autonomy = aut;
                    aux->cost = cost;
                    strcpy(aux->location, loc_v);
                }
                return(aux);*/
                
                strcpy(aux->type, type);
                aux->battery = bat;
                aux->autonomy = aut;
                aux->cost = cost;
                strcpy(aux->location, loc);
                return(aux);
            }
        }
    }
    else return(start);
    }

int saveRecords_Meio(Meio* start)
{
    FILE* fp = fopen("../data/Records_Meio.txt", "w");

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

    Meio* meios = NULL;
    
    if (fp != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), fp))
        {
            sscanf(line, "%d;%[^;];%f;%f;%f;%[^\n]\n", &code, type, &bat, &aut, &cost, loc);
            meios = insertNewRecord_Meio(meios, code, type, bat, aut, cost, loc);
        }
        fclose(fp);
    }
    return(meios);
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
        printf("\n|     %d %s %d-%d-%d %d %d %s %d %f %s %s   |", start->id, start->nome, start->birthDate.day, 
        start->birthDate.month, start->birthDate.year, start->phoneNumber, start->address, 
        start->nif, start->saldo, start->email, start->password);
        start = start->next;
    }
}

int saveRecords_Client(Client* start)
{
    FILE* fp = fopen("../data/Records_Client.txt", "w");

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

Meio* readRecords_Client() {
    int id, phn, nif, bd, bm, by;
    float saldo;
    char nome[50], addr[50], email[50], pass[20];

    FILE* fp = fopen("../data/Records_Client.txt","r");

    Meio* meios = NULL;
    
    if (fp != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), fp))
        {
            sscanf(line, "%d;%[^;];%d-%d-%d;%d;%d;%[^;];%d;%f;%[^;];%[^\n]\n", 
            &code, type, &bat, &aut, &cost, loc);
            meios = insertNewRecord_Meio(meios, code, type, bat, aut, cost, loc);
        }
        fclose(fp);
    }
    return(meios);
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

