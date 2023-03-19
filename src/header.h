#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma region Structs

// Creation of data structs

// this struct serves to store a record in date format
struct Date
{
	int day; // This is the day field 
	int month; // This is the month field
	int year; // This is the year field
};

// Creating the Meio data struct
typedef struct Mobilidade_Registo
{
	int code; // This is the code that identifies Electric Mobility
	char type[50]; // Idifify the type of Electric Mobility
	float battery; // Idifify the battery of the Electric Mobility
	float autonomy; // Idifify the autonomy of the Electric Mobility
	float cost; // Idifify the cost of the Electric Mobility
	char location[50]; // Idifify the location of the Electric Mobility
	int idClient; // auxiliar way to identify who booked the mean of transport
	int status; // if status = 0, then it's not booked, but if status = 1, then it has already been booked 
	struct registo* next; // Points to the next record in the Meio linked list
} Meio;

// Creating the Client data struct
typedef struct Cliente_Registo
{
	int id; // This is the id field that identifies the client
	char name[100]; // This is the name field that identifies the client
	struct Date birthDate; // This is the birth date field that identifies the client
	int phoneNumber; // This is the phone number field that identifies the client
	char address[100]; // This is the address field that identifies the client
	int nif; // This is the nif field that identifies the client
	float balance; // This is the balance field that identifies the client
	char email[50]; // This is the email field that identifies the client
	char password[20]; // This is the password field that identifies the client
	struct registo* next; // Points to the next record in the Client linked list
} Client;

// Creating the Manager data struct
typedef struct Gerente_Registo
{
	int id; // This is the id field that identifies the manager
	char name[100]; // This is the name field that identifies the manager
	struct Date birthDate; // This is the birth date field that identifies the manager
	int phoneNumber; // This is the phone number field that identifies the manager
	char email[50]; // This is the email field that identifies the manager
	char password[20]; // This is the password field that identifies the manager
	struct registo* next; // Points to the next record in the Manager linked list
} Manager;

#pragma endregion

// Creation of the functions that manipulate records

#pragma region Insert_Functions

// Function that inserts a new record of type Meio
Meio* insertNewRecord_Meio(Meio* start, int code, char type[50], 
	float bat, float aut, float cost, int idclient, int status, char loc[50]); // here is included the need parameters

// Function that inserts a new record of type Client
Client* insertNewRecord_Client(Client* start, int id, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]); // here is included the need parameters

// Function that inserts a new record of type Manager
Manager* insertNewRecord_Manager(Manager* start, int id, char name[100],
	int bd, int bm, int by, int phn, char email[50], char pass[50]); // here is included the need parameters

#pragma endregion

#pragma region Count_Records_Functions

// this function return the amount of records present in the Meio linked list 
int countRecords_Meio(Meio* start);

// this function return the amount of records present in the Client linked list 
int countRecords_Client(Client* start);

// this function return the amount of records present in the Manager linked list 
int countRecords_Manager(Manager* start);

// this function return the amount of records present in the Meio linked list, but only about a specific client
int countRecords_Book(Meio* start, int idclient);

#pragma endregion

#pragma region Booking_Functions

//resMeios bookReservationsLast(resMeios start, void *meio, void *client);

// this function goes through the linked list and checks if a certain record indicated by the user is already reserved
int isMeioBooked(Meio* start, int code);

// this function scrolls through the linked list and reserves the record indicated by the user
Meio* bookMeio(Meio* start, int code, int idclient);

// this function scrolls through the linked list and cancels the reservation of the record indicated by the user
Meio* cancelbookMeio(Meio* start, int code);

// this function goes through the linked list, and lists the records that were reserved by the client that is logged in
void listBookingRecords(Meio* start, int idclient);

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

// this function traverses the Meio linked list and lists the records present in it
void listRecords_Meio(Meio* start);

// this function traverses the Client linked list and lists the records present in it
void listRecords_Client(Client* start);

// this function traverses the Manager linked list and lists the records present in it
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

// this function goes through the Meio linked list and edits the record data that contains the code indicated by the user
Meio* editRecord_Meio(Meio* start, int code, char type[50], 
	float bat, float aut, float cost, char loc[50]); // here is included the need parameters

// this function goes through the Client linked list and edits the record data that contains the code indicated by the user
Client* editRecord_Client(Client* start, int id, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]); // here is included the need parameters

// this function goes through the Manager linked list and edits the record data that contains the code indicated by the user
Manager* editRecord_Manager(Manager* start, int id, char name[100], int bd, 
	int bm, int by, int phn, char email[50], char pass[50]); // here is included the need parameters

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

// this main menu that allows the user to indicate their status in order to be able to login to their respective account
int showMenu(Meio* meios, Client* clients, Manager* managers);

// this client menu that allows the client to manipulate the records of reservations of Means
int showSubMenu_Client(Meio* meios, Client* clients, Manager* manager);

// this client sub menu that allows the client to log in if he already has one, or to create one otherwise
int showSubSubMenu_Client(Meio* meios, Client* clients, Manager* managers);

// this manager menu that allows the manager to choose if he wants to manipulate Meio records or Clients records
int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers);

// this client menu that allows the manager to manipulate the records of reservations of Means
int showSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers);

// this client menu that allows the manager to manipulate the records of Clients
int showSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers);

#pragma endregion

#pragma region search_ID_Functions

// this function goes through the Client linked list and return the client id which is represented by the email and password used to login
const int searchID_Client(Client* start, char email[50], char pass[50]);

// this function goes through the Manager linked list and return the manager id which is represented by the email and password used to login
const int searchID_Manager(Manager* start, char email[50], char pass[50]);

#pragma endregion

#pragma region search_Name_Functions

// this function goes through the Client linked list and return the client name which is represented by id of the client logged in
const char* searchName_Client(Client* start, int id);

// this function goes through the Manager linked list and return the client name which is represented by id of the manager logged in
const char* searchName_Manager(Manager* start, int id);

#pragma endregion

#pragma region Login_Functions

// Function that allows to login to Client account
int login_Client(Client* start, char email[50], char pass[50]);

// Function that allows to login to Manager account
int login_Manager(Manager* start, char email[50], char pass[50]);

#pragma endregion

#pragma region Auxiliar_Functions

void red(); // a function that changes the font color to red
void yellow(); // a function that changes the font color to yellow
void green(); // a function that changes the font color to green
void blue(); // a function that changes the font color to blue
void reset(); // a function that return the font color to it's original font
void clear(); // a function that clears all the information present in the console

void flushstdin(void); // a function that clears the keyboard buffer

void pause(); // a function that interrupts the program until a random key is pressed by the user

#pragma endregion