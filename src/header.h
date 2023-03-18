#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Structs

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
	int status;
	struct registo* next;
} Meio;

// Creating the Client data struct
typedef struct Cliente_Registo
{
	int id; // Code that identifies the client
	char name[100];
	struct Date birthDate;
	int phoneNumber;
	char address[100];
	int nif;
	float balance;
	char email[50];
	char password[20];
	struct registo* next;
} Client;

// Creating the Manager data struct
typedef struct Gerente_Registo
{
	int id; // Code identifying the manager
	char name[100];
	struct Date birthDate;
	int phoneNumber;
	char email[50];
	char password[20];
	struct registo* next;
} Manager;


typedef struct Reservations_Meios
{
	void *meio; // pointer to the meios struct
	void *client; // pointer to the clients struct
	int book; // if 0, then it is unbooked. If 1 then it is reserved.
	struct registo *next;
} *resMeios, SResMeios;

#pragma endregion

// Creation of functions for manipulating records

#pragma region Insert_Functions

// Function that inserts a new record of type Meio
Meio* insertNewRecord_Meio(Meio* start, int code, char type[50], 
	float bat, float aut, float cost, int status, char loc[50]);

// Function that inserts a new record of type Client
Client* insertNewRecord_Client(Client* start, int id, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]);

// Function that inserts a new record of type Manager
Manager* insertNewRecord_Manager(Manager* start, int id, char name[100],
	int bd, int bm, int by, int phn, char email[50], char pass[50]);

#pragma endregion

#pragma region Count_Records_Functions

int countRecords_Meio(Meio* start);

int countRecords_Client(Client* start);

int countRecords_Manager(Manager* start);

#pragma endregion

#pragma region Booking_Functions

resMeios bookReservationsLast(resMeios start, void *meio, void *client);

#pragma endregion

#pragma region Exist_Functions

// Function that checks whether or not a certain record of type Meio already exists
int existRecord_Meio(Meio* start, int cod);

// Function that checks whether or not a certain record of type Client already exists
int existRecord_Client(Client* start, int id);

// Function that checks whether or not a certain record of type Manager already exists
int existRecord_Manager(Manager* start, int id);

#pragma endregion

#pragma region List_Functions

// Function that lists records of type Meio in the console
void listRecords_Meio(Meio* start);

// Function that lists records of type Client in the console
void listRecords_Client(Client* start);

// Function that lists records of type Manager in the console
void listRecords_Manager(Manager* start);

#pragma endregion

#pragma region Remove_Functions

// Function that removes a record of type Meio from it's code
Meio* removeRecord_Meio(Meio* start, int cod);

// Function that removes a record of type Client from it's id
Client* removeRecord_Client(Client* start, int id);

// Function that removes a record of type Manager from it's id
Manager* removeRecord_Manager(Manager* start, int id);

#pragma endregion

#pragma region Edit_Functions

// 
Meio* editRecord_Meio(Meio* start, int code, char type[50], 
	float bat, float aut, float cost, char loc[50]);

//
Client* editRecord_Client(Client* start, int id, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]);

//
Manager* editRecord_Manager(Manager* start, int id, char name[100], int bd, 
	int bm, int by, int phn, char email[50], char pass[50]);

#pragma endregion

#pragma region Save_Functions

// Function that saves records of type Meio in a text file
int saveRecords_Meio(Meio* start);

// Function that saves records of type Client in a text file
int saveRecords_Client(Client* start);

// Function that saves records of type Manager in a text file
int saveRecords_Manager(Manager* start);

#pragma endregion

#pragma region Read_Functions

// Function that reads records of type Meio from a text file
Meio* readrecords_Meio();

// Function that reads records of type Client from a text file
Meio* readrecords_Client();

// Function that reads records of type Manager from a text file
Meio* readrecords_Manager();

#pragma endregion

#pragma region Menu_Functions

// The main menu function, where the user can log itself in in his account
int showMenu(Meio* meios, Client* clients, Manager* managers);

// The sub menu function, where the client can handle records of type Meio
int showSubMenu_Client(Meio* meios, Client* clients, Manager* managers);

// The sub-sub menu function, where the cliente can log itself in in his account
int showSubSubMenu_Client(Meio* meios, Client* clients, Manager* managers);

// The main menu function, where the manager can log itself in in his account
int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers);

#pragma endregion

#pragma region search_ID_Functions

int searchID_Client(Client* start, char email[50], char pass[50]);

int searchID_Manager(Manager* start, char email[50], char pass[50]);

#pragma endregion

#pragma region Login_Functions

// Function that allows to login to Client account
int login_Client(Client* start, char email[50], char pass[50]);

// Function that allows to login to Manager account
int login_Manager(Manager* start, char email[50], char pass[50]);

#pragma endregion

#pragma region Auxiliar_Functions

void red();
void yellow();
void green();
void blue();
void reset();
void clear();

void flushstdin(void);

void pause();

#pragma endregion