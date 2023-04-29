#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"


#pragma region Auxiliar_Functions

/**
 * @brief 
 * 
 */
void red() { printf("\033[1;31m"); }
/**
 * @brief 
 * 
 */
void yellow() { printf("\033[1;33m"); }
/**
 * @brief 
 * 
 */
void green() { printf("\033[0;32m"); }
/**
 * @brief 
 * 
 */
void blue() { printf("\033[0;34m"); }
/**
 * @brief 
 * 
 */
void reset() { printf("\033[0m"); }
/**
 * @brief 
 * 
 */
void clear() { system("cls || clear"); }

/**
 * @brief 
 * 
 */
void flushstdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief 
 * 
 */
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

#pragma region System_Date_Time

/**
 * @brief Get the Current Date object
 * 
 * @return struct date 
 */
// 
struct date getCurrentDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct date d = {tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900};
    return(d);
}

/**
 * @brief Get the Current Time object
 * 
 * @return struct time 
 */
// 
struct time getCurrentTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct time time = {tm.tm_hour, tm.tm_min};
    return(time);
}

#pragma endregion

#pragma region Meios_Related_Functions

// Functions related to records of type Meio

/**
 * @brief Get the Last Meio Code object
 * 
 * @param start 
 * @return int 
 */
// this function returns the code of the last record, present in the linked list.
int getLastMeioCode(Meio* start) {
    if (start == NULL) {
        // the list is empty, so there is no id to increment, so return 0.
        return(0);
    }
    else {
        // scrolls through the list to the last record
        Meio* last = start;
        while (last->next != NULL) {
            last = last->next;
        }
        // returns the code of the last record, so it can be incremented
        return(last->code);
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @param type 
 * @param bat 
 * @param aut 
 * @param cost 
 * @param idclient 
 * @param status 
 * @param loc 
 * @return Meio* 
 */
// inserts a new records in the Meio linked list
Meio* insertNewRecord_Meio(Meio* start, char type[50], float bat, 
    float aut, float cost, int status, char loc[50]) { // here is included the needed parameters
    
    int lastCode = getLastMeioCode(start);
    Meio* meio = malloc(sizeof(struct Mobilidade_Registo));
    // this line of code dynamically allocates memory for a new struct object Mobilidade_Registro 
    // and stores the address of the allocated memory in the middle variable.
    if (meio != NULL) {
        meio->code = (lastCode)+1; // here the value of the parameter code is assigned in the respective field of the new record.
        strcpy(meio->type, type); // here the value of the parameter type is assigned in the respective field of the new record.
        meio->battery = bat; // here the value of the parameter bat is assigned in the respective field of the new record.
        meio->autonomy = aut; // here the value of the parameter aut is assigned in the respective field of the new record.
        meio->cost = cost; // here the value of the parameter cost is assigned in the respective field of the new record.
        //meio->idClient = idclient; // here the value of the parameter idclient is assigned in the respective field of the new record.
        meio->status = status; // here the value of the parameter status is assigned in the respective field of the new record.
        strcpy(meio->location, loc); // here the value of the parameter loc is assigned in the respective field of the new record.
        meio->next = NULL; // here the 'next' field of the new record is pointing to the record that used to be the last one
    
        if (start == NULL) {
            // the list is empty, so the new record will be the first record
            start = meio;
        }
        else {
            // scrolls through the list to the last record
            Meio* current = start;
            while (current->next != NULL) {
                current = current->next;
            }
            // adds the new record to the end of the list
            current->next = meio;
        }
        return(start); 
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// count the number of records in the Meio linked list
int countRecords_Meio(Meio* start) {
    int counter = 0;
    while (start != NULL) { // goes through the linked list until it finds the last record
        start = start->next; // the record being read by the loop and passed to the next record
        counter++; // the incrementing variable is incremented
    }
    return(counter); // return the incrementing variable
}

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @return int 
 */
// verifies if the Meio record exists or not
int existRecord_Meio(Meio* start, int code) {
    while (start != NULL) { /// goes through the linked list until it finds the last record
        // checks if the record that is being checked is the same as the record represented by the given id
        if (start->code == code) return(1); // return 1 if a record of the linked list is the same as the one being requested
        start = start->next; // the record being read by the loop and passed to the next record
    }
    return(0); // return 0 if any record of the linked list is the same as the one being requested
}

/**
 * @brief 
 * 
 * @param start 
 */
// lists the informations of the records in the console
void listRecords_Meio(Meio* start) {
    while (start != NULL) { // goes through the linked list until it finds the last record
        if (start->status == 0) { // verifies if the record status is 1 then it is booked, but if 0 then it is yet to be booked
            printf("\n|     %-8d %-20s %-12.2f %-14.2f %-11.2f %-17s %-14s   |", start->code, start->type, 
                start->battery, start->autonomy, start->cost, "Por Reservar", start->location); 
                // prints the informations of the record in the console
        }
        else if (start->status == 1){ // verifies if the record status is 0 then it is yet to be booked
            printf("\n|     %-8d %-20s %-12.2f %-14.2f %-11.2f %-17s %-14s   |", start->code, start->type, 
                start->battery, start->autonomy, start->cost, "Reservado", start->location);
                // prints the informations of the record in the console
        }
        start = start->next; // the record being read by the loop and passed to the next record
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @return Meio* 
 */
// removes the Meio record from the linked list
Meio* removeRecord_Meio(Meio* start, int code) {
    Meio *prev = start, *now = start, *aux;

    if (now == NULL) return(NULL);
    else if (now->code == code) { // checks if the record code, is the same as the given code if so ...
        aux = now->next;  // moves on to the next record and ...
        free(now); // this is where the memory allocated by the record to be removed is freed.
        return(aux); // return the records of the linked list but now without the removed record
    }
    else {
        // here as the indicated record was removed now it's needed that the previous record and the next record
        // become now connected, by assigning to variable next of the previous record the information of the next record
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

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @param type 
 * @param bat 
 * @param aut 
 * @param cost 
 * @param loc 
 * @return Meio* 
 */
// edits the information of the Meio record on the linked list
Meio* editRecord_Meio(Meio* start, int code, char type[50], 
	float bat, float aut, float cost, char loc[50]) {
    /*int code_v;
    char type_v[50], loc_v[50];
    float bat_v, aut_v, cost_v;

    // Saving the old data
    code_v = start->code;
    strcpy(type_v, start->type);
    bat_v = start->battery;
    aut_v = start->autonomy;
    cost_v = start->cost;
    strcpy(loc_v, start->location);
    
    if (type[0] == '\n') {
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

    Meio* aux = start; // creates a new linked list and initializes it with the first Client linked list record
    // Setting the new data to the record
    if (existRecord_Meio(aux, code)) { // verifies if the indicated record exist
        while (aux != NULL) { // goes through the linked list until it finds the last record
            if (aux->code == code) { // finds the record containing the given record
                // the fields receive the new data given by parameter
                strcpy(aux->type, type);
                aux->battery = bat;
                aux->autonomy = aut;
                aux->cost = cost;
                strcpy(aux->location, loc);
            }
            aux = aux->next;
        }
    }
    return(start);
}

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// saves the content of the Meio linked list in the "Records_Meio" text file
int saveRecords_Meio(Meio* start)
{
    // this C code opens a file called "Records_Meio.txt" 
    // in write mode ("w") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Text_Files/Records_Meio.txt", "w");
    // checks if the file is empty or not
    if (fp != NULL)
    {
        Meio* aux = start;
        while (aux != NULL)
        {
            // saves in the text file each field of a respective record separated by ';'
            fprintf(fp, "%d;%s;%f;%f;%f;%d;%s\n", aux->code, aux->type, aux->battery, 
                aux->autonomy, aux->cost, aux->status, aux->location);
            aux = aux->next; // moves to the next record
        }
        fclose(fp); // closes the text file
        return(1);
    }
    
    return(0);
}

/**
 * @brief 
 * 
 * @return Meio* 
 */
// reads the content of the "Records_Meio" and gives it to the Meio linked list
Meio* readrecords_Meio() {
    int code, idclient, status;
    float bat, aut, cost;
    char type[50], loc[50];
    // creating variables to keep the information of the records in the text file

    FILE* fp = fopen("../data/Text_Files/Records_Meio.txt","r"); // opens the "Records_Meio" text file

    Meio* meios = NULL; // creates a new NULL linked list
    
    if (fp != NULL) { // checks if the text file is empty
        char line[1024];
        // the fgets function is used to read a line of text from a file and store it in a character buffer. 
        // the first argument is a pointer to the buffer that will store the line read.
        // the second argument is the buffer size. In this case, sizeof(line) returns the size of the line buffer in bytes.
        // the third argument is a pointer to the file from which the line is to be read.
        while (fgets(line, sizeof(line), fp))
        {
            // returns the information of each record and gives them to the linked list
            sscanf(line, "%d;%[^;];%f;%f;%f;%d;%[^\n]\n", &code, type, &bat, &aut, &cost, &status, loc);
            meios = insertNewRecord_Meio(meios, type, bat, aut, cost, status, loc);
            // insert the records in the linked list
        }
        fclose(fp);
    }
    return(meios);
}

#pragma endregion

#pragma region Clients_Related_Functions

// Functions related to records of type Client

/**
 * @brief Get the Last Client I D object
 * 
 * @param start 
 * @return int 
 */
// this function returns the id of the last record, present in the linked list.
int getLastClientID(Client* start) {
    if (start == NULL) {
        // the list is empty, so there is no id to increment, so return 0.
        return(0);
    }
    else {
        // scrolls through the list to the last record
        Client* last = start;
        while (last->next != NULL) {
            last = last->next;
        }
        // returns the code of the last record, so it can be incremented
        return(last->id);
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @param name 
 * @param bd 
 * @param bm 
 * @param by 
 * @param phn 
 * @param addr 
 * @param nif 
 * @param balance 
 * @param email 
 * @param pass 
 * @return Client* 
 */
// inserts a new records in the Client linked list
Client* insertNewRecord_Client(Client* start, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]) { // here is included the needed parameters
    
    int lastID = getLastClientID(start);
    Client* client = malloc(sizeof(struct Cliente_Registo));
    if (client != NULL) {
        client->id = (lastID)+1;
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
        client->next = NULL;
        
        if (start == NULL) {
            // the list is empty, so the new record will be the first record
            start = client;
        }
        else {
            // scrolls through the list to the last record
            Client* current = start;
            while (current->next != NULL) {
                current = current->next;
            }
            // adds the new record to the end of the list
            current->next = client;
        }
        return(start);
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// count the number of records in the Client linked list
int countRecords_Client(Client* start) {
    int counter = 0;
    while (start != NULL) {
        start = start->next;
        counter++;
    }
    return(counter);
}

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return const int 
 */
// return the id of the client by searching the record containing the email and pass given
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

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return const char* 
 */
// return the name of the client by searching the record containing the given id
const char* searchName_Client(Client* start, int id) {
    while (start != NULL) {
        if (start->id == id) {
            return(start->name);
        }
        start = start->next;
    }
    return("NULL");
}

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return int 
 */
// verifies if the client record exists or not
int existRecord_Client(Client* start, int id) {
    while (start != NULL) {
        if (start->id == id) return(1);
        start = start->next;
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param start 
 */
// lists the informations of the records in the console
void listRecords_Client(Client* start) {
    while (start != NULL) {
        printf("\n|    %-6d %-21s %-0.02d-%-0.02d-%-8.04d %-18.09d %-40s %-15.09d %-13.2f %-34s %-15s     |", 
            start->id, start->name, start->birthDate.day, start->birthDate.month, 
            start->birthDate.year, start->phoneNumber, start->address, start->nif, 
            start->balance, start->email, start->password);
            start = start->next;
    }
    
}

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return Client* 
 */
// removes the client record from the linked list
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

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @param name 
 * @param bd 
 * @param bm 
 * @param by 
 * @param phn 
 * @param addr 
 * @param nif 
 * @param balance 
 * @param email 
 * @param pass 
 * @return Client* 
 */
// edits the information of the client record on the linked list
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
            }
            aux = aux->next;
        }
    }
    return(start);
}

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// saves the content of the Client linked list in the "Records_Client" text file
int saveRecords_Client(Client* start)
{
    FILE* fp = fopen("../data/Text_Files/Records_Client.txt", "w");

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

/**
 * @brief 
 * 
 * @return Meio* 
 */
// reads the content of the "Records_Client" and gives it to the Client linked list
Client* readrecords_Client() {
    int id, phn, nif, bd, bm, by;
    float balance;
    char name[50], addr[50], email[50], pass[20];

    FILE* fp = fopen("../data/Text_Files/Records_Client.txt","r");

    Client* client = NULL;
    
    if (fp != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), fp))
        {
            sscanf(line, "%d;%[^;];%d-%d-%d;%d;%[^;];%d;%f;%[^;];%[^\n]\n", &id, 
            name, &bd, &bm, &by, &phn, addr, &nif, &balance, email, pass);
            client = insertNewRecord_Client(client, name, bd, bm, by, phn, addr, nif, balance, email, pass);
        }
        fclose(fp);
    }
    return(client);
}

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return int 
 */
// log in to the account whose registration corresponds to the indicated email and pass
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

/**
 * @brief Get the Last Manager I D object
 * 
 * @param start 
 * @return int 
 */
// this function returns the id of the last record, present in the linked list.
int getLastManagerID(Manager* start) {
    if (start == NULL) {
        // the list is empty, so there is no id to increment, so return 0.
        return(0);
    }
    else {
        // scrolls through the list to the last record
        Manager* last = start;
        while (last->next != NULL) {
            last = last->next;
        }
        // returns the code of the last record, so it can be incremented
        return(last->id);
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @param name 
 * @param bd 
 * @param bm 
 * @param by 
 * @param phn 
 * @param email 
 * @param pass 
 * @return Manager* 
 */
// inserts a new records in the Manager linked list
Manager* insertNewRecord_Manager(Manager* start, char name[100],
    int bd, int bm, int by, int phn, char email[50], char pass[50]) {
    
    int lastID = getLastManagerID(start);
    Manager* manager = malloc(sizeof(struct Gerente_Registo));
    if (manager != NULL) {
        manager->id = (lastID)+1;
        strcpy(manager->name, name);
        manager->birthDate.day = bd;
        manager->birthDate.month = bm;
        manager->birthDate.year = by;
        manager->phoneNumber = phn;
        strcpy(manager->email, email);
        strcpy(manager->password, pass);
        manager->next = NULL;
        if (start == NULL) {
            // 
            start = manager;
        }
        else {
            // 
            Manager* current = start;
            while (current->next != NULL)
            {
                current->next = manager;
            }
            // 
            current->next = manager;
        }
        return(start);
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// count the number of records in the Manager linked list
int countRecords_Manager(Manager* start) {
    int counter = 0;
    while (start != NULL) {
        start = start->next;
        counter++;
    }
    return(counter);
}

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return const int 
 */
// return the id of the manager by searching the record containing the email and pass given
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

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return const char* 
 */
// return the name of the manager by searching the record containing the given id
const char* searchName_Manager(Manager* start, int id) {
    while (start != NULL) {
        if (start->id == id) {
            return(start->name);
        }
        start = start->next;
    }
    return("There is no name, which matches the given id");
}

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return int 
 */
// verifies if the manager record exists or not
int existRecord_Manager(Manager* start, int id) {
    while (start != NULL) {
        if (start->id == id) return(1);
        start = start->next;
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param start 
 */
// lists the informations of the records in the console
void listRecords_Manager(Manager* start) {
    while (start != NULL) {
        printf("%d %s %d-%d-%d %d %s %s\n", start->id, start->name, start->birthDate.day, 
            start->birthDate.month, start->birthDate.year, start->phoneNumber, 
            start->email, start->password);
        start = start->next;
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// saves the content of the Manager linked list in the "Records_Manager" text file
int saveRecords_Manager(Manager* start)
{
    FILE* fp = fopen("Data/Text_Files/Records_Manager.txt", "w");

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

/**
 * @brief 
 * 
 * @return Meio* 
 */
// reads the content of the "Records_Client" and gives it to the Client linked list
Manager* readrecords_Manager() {
    int id, phn, bd, bm, by;
    char name[50], email[50], pass[20];

    FILE* fp = fopen("../data/Text_Files/Records_Manager.txt","r");

    Manager* manager = NULL;
    
    if (fp != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), fp))
        {
            sscanf(line, "%d;%[^;];%d-%d-%d;%d;%[^;];%[^\n]\n", 
            &id, name, &bd, &bm, &by, &phn, email, pass);
            manager = insertNewRecord_Manager(manager, name, bd, bm, by, phn, email, pass);
        }
        fclose(fp);
    }
    return(manager);
}

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return int 
 */
// log in to the account whose registration corresponds to the indicated email and pass
int login_Manager(Manager* start, char email[50], char pass[50]) {
    while (start != NULL) {
        if ((strcmp(start->email, email) == 0) && (strcmp(start->password, pass) == 0)) return(1);
        start = start->next;
    }
    return(0);
}

#pragma endregion

#pragma region Booking_Related_Functions

/**
 * @brief Get the Last Res I D object
 * 
 * @param start 
 * @return int 
 */
// 
int getLastResID(resMeios* head) {
    if (head == NULL) {
        // the list is empty, so there is no id to increment, so return 0.
        return(0);
    }
    else {
        // scrolls through the list to the last record
        resMeios* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        // returns the code of the last record, so it can be incremented
        return(last->id);
    }
}

/**
 * @brief 
 * 
 * @return int 
 */
// 
int isMeioMineToUnbook(resMeios* head, int id, int idclient) {
    while (head != NULL) {
        if (head->id == id) {
            if (head->clients->id == idclient) return(1);
        }
        head = head->next;
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @return int 
 */
// checks if a record is booked or not
int isMeioBooked(Meio* head, int code) {
    while (head != NULL) { // goes through the linked list until it finds the last record
        if (head->code == code) { // finds the record containing the given record
            if (head->status == 1) return(1); // checks if the records status is 1
            // if so it return 1 so that the program knows that this record is now booked
            // and can't be booked no more, until it's reservation is canceled by it's clients
        }
        head = head->next; // moves to the next record
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return int 
 */
//
int existRecord_Booked(resMeios* head, int id) {
    while (head != NULL) { /// goes through the linked list until it finds the last record
        // checks if the record that is being checked is the same as the record represented by the given id
        if (head->id == id) return(1); // return 1 if a record of the linked list is the same as the one being requested
        head = head->next; // the record being read by the loop and passed to the next record
    }
    return(0); // return 0 if any record of the linked list is the same as the one being requested
}

/**
 * @brief Get the Meio By Index object
 * 
 * @param head 
 * @param index 
 * @return Meio* 
 */
// 
Meio* getMeioByIndex(Meio* head, int index) {
    Meio* current = head;
    while (current != NULL) {
        if (current->code == index) {
            return current;
        }
        current = current->next;
    }
    return NULL; // returns NULL if no record is found with the given code
}

/**
 * @brief Get the Client By Index object
 * 
 * @param head 
 * @param index 
 * @return Client* 
 */
// 
Client* getClientByIndex(Client* head, int index) {
    Client* current = head;
    while (current != NULL) {
        if (current->id == index) {
            return current;
        }
        current = current->next;
    }
    return NULL; // returns NULL if no record is found with the given code
}

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @param idclient 
 * @return Meio* 
 */
// creates a new reservation type record, storing your Meio, your Client 
// and the period in which the reservation took place
resMeios* bookMeio(resMeios* head, int idMeio, int idClient, Meio* meios, Client* clients, struct periodDateTime perTime) {

    // Procura pelo registro desejado na lista ligada Meio
    Meio* meio = getMeioByIndex(meios, idMeio);
    // 
    Client* client = getClientByIndex(clients, idClient);
    // 
    int lastID = getLastResID(head);

    if (meio == NULL) {
        red();
        printf("\n\tMeio not found.\n");
        reset();
        return(head);
    }
    if (client == NULL) return(head);

    // Criar a nova reserva
    resMeios* newRes = (resMeios*)malloc(sizeof(resMeios));
    newRes->id = (lastID)+1;
    newRes->meios = meio;
    newRes->clients = client;
    newRes->bookDate = perTime;
    /*newRes->bookDate.date.day = perTime.date.day;
    newRes->bookDate.date.month = perTime.date.month;
    newRes->bookDate.date.year = perTime.date.year;
    newRes->bookDate.time.hour = perTime.time.hour;
    newRes->bookDate.time.min = perTime.time.min;*/
    newRes->next = NULL;

    // updates the 'status' field of Meio to 1, so now it becomes booked
    meio->status = 1;

    // Add the new reservation to the ResMeios linked list
    if (head == NULL) {
        head = newRes;
    } else {
        resMeios* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newRes;
    }

    return(head);
}

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @return Meio* 
 */
// cancels the reservation of the record, by changing the record status to 0
resMeios* cancelbookMeio(resMeios* head, int id) {
    
    if (head == NULL) {
        printf("The reservation list is empty.\n");
        return head;
    }
    
    resMeios* current = head;
    resMeios* prev = NULL;
    //resMeios* after = current->next;
    while (current != NULL) {
        if (current->id == id) { // find the reservation you want to cancel
            if (prev == NULL) { // if the reservation to be canceled is at the beginning of the list
                head = current->next;
            } 
            else {
                prev->next = current->next;
            }
            // updates the 'status' field of Meio to 0, so it is now available for booking
            current->meios->status = 0;
            free(current); // frees the memory allocated by the canceled reservation
            //after->id = current->id;
            return head;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

/**
 * @brief 
 * 
 * @param start 
 */
//
void listNonBookingRecords(Meio* head) {
    while (head != NULL) { // goes through the linked list until it finds the last record
        if (head->status != 1) {
            if (head->status == 0) { // verifies if the record status is 1 then it is booked, but if 0 then it is yet to be booked
            printf("\n|     %-8d %-20s %-12.2f %-14.2f %-9.2f %-17s %-14s   |", head->code, head->type, 
                head->battery, head->autonomy, head->cost, "Por Reservar", head->location); 
                // prints the informations of the record in the console
            }
            else if (head->status == 1){ // verifies if the record status is 0 then it is yet to be booked
                printf("\n|     %-8d %-20s %-12.2f %-14.2f %-9.2f %-17s %-14s   |", head->code, head->type, 
                    head->battery, head->autonomy, head->cost, "Reservado", head->location);
                    // prints the informations of the record in the console
            }
        }
        head = head->next; // the record being read by the loop and passed to the next record
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @param idclient 
 */
// lists all the records from the Meio linked list but only those booked by the logged in client
void listClientBookingRecords(resMeios* head, int idclient) {
    while (head != NULL) { // goes through the linked list until it finds the last record
        if ((head->meios->status == 1) && (head->clients->id == idclient)) { // finds the record containing the given id 
            // but only if it's was booked by the logged in client
            printf("\n|     %-10d %-0.2d-%-0.02d-%-9d %-0.02d:%-9.02d %-15d %-20s %8d %-20s   |", head->id, 
                head->bookDate.date.day, head->bookDate.date.month, head->bookDate.date.year,
                head->bookDate.time.hour, head->bookDate.time.min,
                head->meios->code, head->meios->type,
                head->clients->id, head->clients->name);
            // lists the information of the records in the console
        }
        head = head->next;
    }
}

/**
 * @brief 
 * 
 * @param start 
 * @param idclient 
 * @return int 
 */
// counts the ammount of records that the logged in client booked
int countRecords_Book(resMeios* head, int idclient) {
    int counter = 0; // creation of an incrementation variable
    while (head != NULL) { // goes through the linked list until it finds the last record
        if (head->clients->id == idclient) { // finds the record containing the given client id
            if (head->meios->status == 1) { // checks if the record status is indeed booked
                counter++; // increments the incrementation variable
            }
        }
        head = head->next; // moves to the next record
    }
    return(counter); // returns the incrementation variable
}

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// 
int saveRecords_Book(resMeios* head) {
    // this C code opens a file called "Records_Reservations.txt" 
    // in write mode ("w") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Text_Files/Records_Reservations.txt", "w");
    // checks if the file is empty or not
    if (fp != NULL)
    {
        resMeios* aux = head;
        while (aux != NULL)
        {
            // saves in the text file each field of a respective record separated by ';'
            fprintf(fp, "%d;%d-%d-%d;%d:%d;%d;%s;%d;%s\n", aux->id, 
                aux->bookDate.date.day, aux->bookDate.date.month, aux->bookDate.date.year,
                aux->bookDate.time.hour, aux->bookDate.time.min,
                aux->meios->code, aux->meios->type, 
                aux->clients->id, aux->clients->name);
            aux = aux->next; // moves to the next record
        }
        fclose(fp); // closes the text file
        return(1);
    }
    
    return(0);
}

/**
 * @brief 
 * 
 * @return resMeios* 
 */
//
resMeios* readrecords_Book(Meio* meio, Client* client) {
    int id, dd, dm, dy, th, tm, idMeio, idClient;
    char typeMeio[50], nameClient[50];
    // creating variables to keep the information of the records in the text file

    struct periodDateTime pdt;

    FILE* fp = fopen("../data/Text_Files/Records_Reservations.txt","r"); // opens the "Records_Meio" text file

    resMeios* res = NULL; // creates a new NULL linked list
    
    if (fp != NULL) { // checks if the text file is empty
        char line[1024];
        // the fgets function is used to read a line of text from a file and store it in a character buffer. 
        // the first argument is a pointer to the buffer that will store the line read.
        // the second argument is the buffer size. In this case, sizeof(line) returns the size of the line buffer in bytes.
        // the third argument is a pointer to the file from which the line is to be read.
        while (fgets(line, sizeof(line), fp))
        {
            // returns the information of each record and gives them to the linked list
            sscanf(line, "%d;%d-%d-%d;%d:%d;%d;%[^;];%d;%[^\n]\n", &id, 
                &dd, &dm, &dy, &th, &tm, &idMeio, typeMeio, &idClient, nameClient);
            pdt.date.day = dd;
            pdt.date.month = dm;
            pdt.date.year = dy;
            pdt.time.hour = th;
            pdt.time.min = tm;
            res = bookMeio(res, idMeio, idClient, meio, client, pdt);
            // insert the records in the linked list
        }
        fclose(fp);
    }
    return(res);
}

#pragma endregion