#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


#pragma region Auxiliar_Functions

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

#pragma endregion

#pragma region Meios_Related_Functions

// Functions related to records of type Meio

Meio* insertNewRecord_Meio(Meio* start, int code, char type[50], float bat, 
    float aut, float cost, int idclient, int status, char loc[50]) {
    if (!existRecord_Meio(start, code)) {
        Meio* meio = malloc(sizeof(struct Mobilidade_Registo));
        if (meio != NULL) {
            meio->code = code;
            strcpy(meio->type, type);
            meio->battery = bat;
            meio->autonomy = aut;
            meio->cost = cost;
            meio->idClient = idclient;
            meio->status = status;
            strcpy(meio->location, loc);
            meio->next = start;
            return(meio);
        }
    }
    else return(start);
}

int countRecords_Meio(Meio* start) {
    int counter = 0;
    while (start != NULL) {
        start = start->next;
        counter++;
    }
    return(counter);
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
        if (start->status == 0) {
            printf("\n|     %-8d %-20s %-12.2f %-14.2f %-9.2f %-17s %-14s   |", start->code, start->type, 
                start->battery, start->autonomy, start->cost, "Por Reservar", start->location);
        }
        else if (start->status == 1){
            printf("\n|     %-8d %-20s %-12.2f %-14.2f %-9.2f %-17s %-14s   |", start->code, start->type, 
                start->battery, start->autonomy, start->cost, "Reservado", start->location);
        }
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
        while ((now != NULL) && (now->code != code)) {
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

Meio* editRecord_Meio(Meio* start, int code, char type[50], 
	float bat, float aut, float cost, char loc[50]) {
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
            aux = aux->next;
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
            fprintf(fp, "%d;%s;%f;%f;%f;%d;%d;%s\n", aux->code, aux->type, aux->battery, 
                aux->autonomy, aux->cost, aux->idClient, aux->status, aux->location);
            aux = aux->next;
        }
        fclose(fp);
        return(1);
    }
    
    return(0);
}

// Unfinished
Meio* readrecords_Meio() {
    int code, idclient, status;
    float bat, aut, cost;
    char type[50], loc[50];

    FILE* fp = fopen("../data/Records_Meio.txt","r");

    Meio* meios = NULL;
    
    if (fp != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), fp))
        {
            sscanf(line, "%d;%[^;];%f;%f;%f;%d;%d;%[^\n]\n", &code, type, &bat, &aut, &cost, &idclient, &status, loc);
            meios = insertNewRecord_Meio(meios, code, type, bat, aut, cost, idclient, status, loc);
        }
        fclose(fp);
    }
    return(meios);
}

#pragma endregion

#pragma region Clients_Related_Functions

// Functions related to records of type Client

Client* insertNewRecord_Client(Client* start, int id, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]) {
    if (!existRecord_Client(start, id)) {
        Client* client = malloc(sizeof(struct Cliente_Registo));
        if (client != NULL) {
            client->id = id;
            strcpy(client->name, name);
            client->birthDate.day = bd;
            client->birthDate.month = bm;
            client->birthDate.year = by;
            client->phoneNumber = phn;
            strcpy(client->address, addr);
            client->nif = nif;
            client->balance = balance;
            strcpy(client->email, email);
            strcpy(client->password, pass);
            client->next = start;
            return(client);
        }
    }
    else return(start);
}

int countRecords_Client(Client* start) {
    int counter = 0;
    while (start != NULL) {
        start = start->next;
        counter++;
    }
    return(counter);
}

const int searchID_Client(Client* start, char email[50], char pass[50]) {
    while (start != NULL)
    {
        if ((strcmp(start->email, email) == 0) && (strcmp(start->password, pass) == 0)) {
            return(start->id);
        }
        start = start->next;
    }
    return(0);
}

const char* searchName_Client(Client* start, int id) {
    while (start != NULL) {
        if (start->id == id) {
            return(start->name);
        }
        start = start->next;
    }
    return("NULL");
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
        printf("\n|    %-7d %-20s %-0d-%-0d-%-9d %-18d %-40s %-15d %-13.2f %-22s     |", start->id, start->name,
            start->birthDate.day, start->birthDate.month, start->birthDate.year, 
            start->phoneNumber, start->address, start->nif, start->balance, start->email);
            start = start->next;
    }
    
}

Client* removeRecord_Client(Client* start, int id) {
    Client *prev = start, *now = start, *aux;

    if (now == NULL) return(NULL);
    else if (now->id == id) {
        aux = now->next;
        free(now);
        return(aux);
    }
    else {
        while ((now != NULL) && (now->id != id)) {
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

Client* editRecord_Client(Client* start, int id, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]) {
        Client* aux = start;

        if (existRecord_Client(aux, id)) {
        while (aux != NULL) {
            if (aux->id == id) {
                strcpy(aux->name, name);
                aux->birthDate.day = bd;
                aux->birthDate.month = bm;
                aux->birthDate.year = by;
                aux->phoneNumber = phn;
                strcpy(aux->address, addr);
                aux->nif = nif;
                aux->balance = balance;
                strcpy(aux->email, email);
                strcpy(aux->password, pass);
                return(aux);
            }
            aux = aux->next;
        }
    }
    else return(start);
}

int saveRecords_Client(Client* start)
{
    FILE* fp = fopen("../data/Records_Client.txt", "w");

    if (fp != NULL)
    {
        Client* aux = start;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%d-%d-%d;%d;%s;%d;%f;%s;%s\n", aux->id, aux->name, aux->birthDate.day, 
            aux->birthDate.month, aux->birthDate.year, aux->phoneNumber, aux->address, 
            aux->nif, aux->balance, aux->email, aux->password);
            aux = aux->next;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

Meio* readrecords_Client() {
    int id, phn, nif, bd, bm, by;
    float balance;
    char name[50], addr[50], email[50], pass[20];

    FILE* fp = fopen("../data/Records_Client.txt","r");

    Client* client = NULL;
    
    if (fp != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), fp))
        {
            sscanf(line, "%d;%[^;];%d-%d-%d;%d;%[^;];%d;%f;%[^;];%[^\n]\n", &id, 
            name, &bd, &bm, &by, &phn, addr, &nif, &balance, email, pass);
            client = insertNewRecord_Client(client, id, name, bd, bm, by, phn, addr, nif, balance, email, pass);
        }
        fclose(fp);
    }
    return(client);
}

int login_Client(Client* start, char email[50], char pass[50]) {
    while (start != NULL) {
        if ((strcmp(start->email, email) == 0) && (strcmp(start->password, pass) == 0)) return(1);
        start = start->next;
    }
    return(0);
}


#pragma endregion

#pragma region Managers_Related_Functions

// Functions related to records of type Manager

Manager* insertNewRecord_Manager(Manager* start, int id, char name[100],
    int bd, int bm, int by, int phn, char email[50], char pass[50]) {
    if (!existRecord_Manager(start, id)) {
        Manager* manager = malloc(sizeof(struct Gerente_Registo));
        if (manager != NULL) {
            manager->id = id;
            strcpy(manager->name, name);
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

int countRecords_Manager(Manager* start) {
    int counter = 0;
    while (start != NULL) {
        start = start->next;
        counter++;
    }
    return(counter);
}

const int searchID_Manager(Manager* start, char email[50], char pass[50]) {
    while (start != NULL)
    {
        if ((strcpy(start->email, email) == 0) && (strcpy(start->password, pass) == 0)) {
            return(start->id);
        }
        start = start->next;
    }
    return(0);
}

const char* searchName_Manager(Manager* start, int id) {
    while (start != NULL) {
        if (start->id == id) {
            return(start->name);
        }
        start = start->next;
    }
    return("There is no name, which matches the given id");
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
        printf("%d %s %d-%d-%d %d %s %s\n", start->id, start->name, start->birthDate.day, 
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
            fprintf(fp, "%d;%s;%d-%d-%d;%d;%s;%s\n", start->id, start->name, start->birthDate.day, 
                start->birthDate.month, start->birthDate.year, start->phoneNumber,
                start->email, start->password);
            aux = aux->next;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

int login_Manager(Manager* start, char email[50], char pass[50]) {
    while (start != NULL) {
        if ((strcmp(start->email, email) == 0) && (strcmp(start->password, pass) == 0)) return(1);
        start = start->next;
    }
    return(0);
}

#pragma endregion

#pragma region Booking_Related_Functions

int isMeioBooked(Meio* start, int code) {
    while (start != NULL) {
        if (start->code == code) {
            if (start->status == 1) return(1);
        }
        start = start->next;
    }
    return(0);
}

Meio* bookMeio(Meio* start, int code, int idclient) {
    Meio* aux = start;
    if (existRecord_Meio(aux, code)) {
        while (aux != NULL) {
            if (aux->code == code) {       
                aux->status = 1;
                aux->idClient = idclient;
                return(aux);
            }
            aux = aux->next;
        }
    }
    else return(start);
}

Meio* cancelbookMeio(Meio* start, int code) {
    Meio* aux = start;
    if (existRecord_Meio(aux, code)) {
        while (aux != NULL) {
            if (aux->code == code) {       
                aux->status = 0;
                aux->idClient = 0;
                return(aux);
            }
            aux = aux->next;
        }
    }
    else return(start);
}

#pragma endregion