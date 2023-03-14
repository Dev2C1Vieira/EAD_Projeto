#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creation of data structs

struct Date
{
	int day;
	int month;
	int year;
};

// Creating the Meio data struct
typedef struct Mobilidade_Registo
{
	int code; // This is the code that identifies Electric Mobility
	char type[50]; // Idifify the type of Electric Mobility
	float battery;
	float autonomy;
	float cost;
	char location[50];
	struct registo* next;
} Meio;

// Creating the Client data struct
typedef struct Cliente_Registo
{
	int id; // Code that identifies the client
	char nome[100];
	struct Date birthDate;
	int phoneNumber;
	char address[100];
	int nif;
	float saldo;
	char email[50];
	char password[20];
	struct registo* next;
} Client;

// Creating the Manager data struct
typedef struct Gerente_Registo
{
	int id; // Code identifying the manager
	char nome[100];
	struct Date birthDate;
	int phoneNumber;
	char email[50];
	char password[20];
	struct registo* next;
} Manager;

// Creation of functions for manipulating records

// Function that inserts a new record of type Meio
Meio* insertNewRecord_Meio(Meio* start, int cod, char tipo[50], float bat,
	float aut, float custo, char loc[50]);

// Function that inserts a new record of type Client
Client* insertNewRecord_Client(Client* start, int id, char nome[100],
	int birth_day, int birth_month, int birth_year, int phn, 
	char adr[100], int nif, float saldo, char email[50], char pass[50]);

// Function that inserts a new record of type Manager
Manager* insertNewRecord_Manager(Manager* start, int id, char nome[100],
	int birth_day, int birth_month, int birth_year, int phn, char email[50], char pass[50]);


// Function that checks whether or not a certain record of type Meio already exists
int existRecord_Meio(Meio* start, int cod);

// Function that checks whether or not a certain record of type Client already exists
int existRecord_Client(Client* start, int id);

// Function that checks whether or not a certain record of type Manager already exists
int existRecord_Manager(Manager* start, int id);


// Function that lists records of type Meio in the console
void listRecords_Meio(Meio* start);

// Function that lists records of type Client in the console
void listRecords_Client(Client* start);

// Function that lists records of type Manager in the console
void listRecords_Manager(Manager* start);


// Function that removes a record of type Meio from it's code
Meio* removeRecord_Meio(Meio* start, int cod);

// Function that removes a record of type Client from it's id
Client* removeRecord_Client(Client* start, int id);

// Function that removes a record of type Manager from it's id
Manager* removeRecord_Manager(Manager* start, int id);


// 
Meio* editRecord_Meio(Meio* start, int code, char type[50], float bat,
    float aut, float cost, char loc[50]);

//
Client* editRecord_Client(Client* start, int id, char nome[100],
	int birth_day, int birth_month, int birth_year, int phn, 
	char adr[100], int nif, float saldo, char email[50], char pass[50]);

//
Manager* editRecord_Manager(Manager* start, int id, char nome[100],
	int birth_day, int birth_month, int birth_year, int phn, char email[50], char pass[50]);


// Function that saves records of type Meio in a text file
int saveRecords_Meio(Meio* start);

// Function that saves records of type Client in a text file
int saveRecords_Client(Client* start);

// Function that saves records of type Manager in a text file
int saveRecords_Manager(Manager* start);


// Function that reads records of type Meio from a text file
Meio* readRecords_Meio();

// Function that reads records of type Client from a text file
Meio* readRecords_Client();

// Function that reads records of type Manager from a text file
Meio* readRecords_Manager();


// The main menu function, where the user can log itself in in his account
int showMenu(Meio* meios, Client* clients, Manager* managers);

// The sub menu function, where the client can handle records of type Meio
int showSubMenu_Client(Meio* meios, Client* clients, Manager* managers);

// The sub-sub menu function, where the cliente can log itself in in his account
int showSubSubMenu_Client(Meio* meios, Client* clients, Manager* managers);

// The main menu function, where the manager can log itself in in his account
int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers);


// Function that allows to login to Client account
int login_Client(Client* start, char email[50], char pass[50]);

// Function that allows to login to Manager account
int login_Manager(Manager* start, char email[50], char pass[50]);


void red();
void yellow();
void green();
void blue();
void reset();
void clear();

void flushstdin(void);

void pause();