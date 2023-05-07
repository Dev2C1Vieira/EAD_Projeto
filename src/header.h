#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#pragma region Structs

// Creation of data structs

/**
 * @brief 
 * 
 */
// this struct serves to store a record in birth date format
struct BirthDate
{
	int day; // This is the day field 
	int month; // This is the month field
	int year; // This is the year field
};

// this struct serves to store a record in date format
struct date
{
  int day, month, year;
};

// this struct serves to store a record in time format
struct time
{
  int hour, min;
};

// this struct serves to store the date and time when the reservation took place
struct periodDateTime
{
	struct date date;
	struct time time;
};

/**
 * @brief 
 * 
 */
// Creating the Meio data struct
typedef struct Mobilidade_Registo
{
	int code; // This is the code that identifies Electric Mobility
	char type[50]; // Idifify the type of Electric Mobility
	float battery; // Idifify the battery of the Electric Mobility
	float autonomy; // Idifify the autonomy of the Electric Mobility
	float cost; // Idifify the cost of the Electric Mobility
	char location[50]; // Idifify the location of the Electric Mobility 
	int status; // if status = 0, then it's not booked, but if status = 1, then it has already been booked
	int available; // 
	struct Mobilidade_Registo* next; // Points to the next record in the Meio linked list
} Meio;

/**
 * @brief 
 * 
 */
// Creating the Client data struct
typedef struct Cliente_Registo
{
	int id; // This is the id field that identifies the client
	char name[100]; // This is the name field that identifies the client
	struct BirthDate birthDate; // This is the birth date field that identifies the client
	int phoneNumber; // This is the phone number field that identifies the client
	char address[100]; // This is the address field that identifies the client
	int nif; // This is the nif field that identifies the client
	float balance; // This is the balance field that identifies the client
	char email[50]; // This is the email field that identifies the client
	char password[20]; // This is the password field that identifies the client
	int available; // 
	struct Cliente_Registo* next; // Points to the next record in the Client linked list
} Client;

/**
 * @brief 
 * 
 */
// Creating the Manager data struct
typedef struct Gerente_Registo
{
	int id; // This is the id field that identifies the manager
	char name[100]; // This is the name field that identifies the manager
	struct BirthDate birthDate; // This is the birth date field that identifies the manager
	int phoneNumber; // This is the phone number field that identifies the manager
	char email[50]; // This is the email field that identifies the manager
	char password[20]; // This is the password field that identifies the manager
	int available; // 
	struct Gerente_Registo* next; // Points to the next record in the Manager linked list
} Manager;

typedef struct ResMeios
{
	int id; // 
	struct periodDateTime bookDate; // 
	struct periodDateTime unbookDate; // 
    Meio *meios; // 
    Client *clients; // 
	float totalCost; // 
	int available; // 
    struct Reserva *next; // 
} resMeios;

#pragma endregion

#pragma region System_Date_Time

/**
 * @brief Get the Current Date object
 * 
 * @return struct date 
 */
// 
struct date getCurrentDate();

/**
 * @brief Get the Current Time object
 * 
 * @return struct time 
 */
// 
struct time getCurrentTime();

#pragma endregion

#pragma region Get_Last_ID

/**
 * @brief Get the Last Meio Code object
 * 
 * @param start 
 * @return int 
 */
// 
int getLastMeioCode(Meio* start);

/**
 * @brief Get the Last Client ID object
 * 
 * @param start 
 * @return int 
 */
// 
int getLastClientID(Client* start);

/**
 * @brief Get the Last Manager ID object
 * 
 * @param start 
 * @return int 
 */
// 
int getLastManagerID(Manager* start);

#pragma endregion

#pragma region Insert_Functions

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
// Function that inserts a new record of type Meio
Meio* insertNewRecord_Meio(Meio* start, char type[50], 
	float bat, float aut, float cost, char loc[50], int status, int available); // here is included the need parameters

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
// Function that inserts a new record of type Client
Client* insertNewRecord_Client(Client* start, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50], int available); // here is included the need parameters

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
// Function that inserts a new record of type Manager
Manager* insertNewRecord_Manager(Manager* start, char name[100],
	int bd, int bm, int by, int phn, char email[50], char pass[50]); // here is included the need parameters

/**
 * @brief 
 * 
 * @param head 
 * @param idMeio 
 * @param idClient 
 * @param meios 
 * @param clients 
 * @param startDateTime 
 * @return resMeios* 
 */
// this function scrolls through the linked list and reserves the record indicated by the user
resMeios* bookMeio(resMeios* head, struct periodDateTime startDateTime, struct periodDateTime finishDateTime, 
	int idMeio, int idClient, Meio* meios, Client* clients, float totalcost, int available);

#pragma endregion

#pragma region Count_Records_Functions

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// this function return the amount of records present in the Meio linked list 
int countAvailableRecords_Meio(Meio* start);

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// 
int countUnavailableRecords_Meio(Meio* start);

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// this function return the amount of records present in the Client linked list 
int countAvailableRecords_Client(Client* start);

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// 
int countUnavailableRecords_Client(Client* start);

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// this function return the amount of records present in the Manager linked list 
int countAvailableRecords_Manager(Manager* start);

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// 
int countUnavailableRecords_Manager(Manager* start);

/**
 * @brief 
 * 
 * @param head 
 * @return int 
 */
//
int countNonBookingRecords(Meio* head);

/**
 * @brief 
 * 
 * @param start 
 * @param idclient 
 * @return int 
 */
// this function return the amount of records present in the Meio linked list, but only about a specific client
int countAvailableRecords_Book(resMeios* head, int idclient);

/**
 * @brief 
 * 
 * @param head 
 * @param idclient 
 * @return int 
 */
// 
int countUnavailableRecords_Book(resMeios* head, int idclient);

#pragma endregion

#pragma region Query_Records

/**
 * @brief Get the Meio By Index object
 * 
 * @param head 
 * @param index 
 * @return Meio* 
 */
// 
Meio* getMeioByIndex(Meio* head, int index);

/**
 * @brief Get the Client By Index object
 * 
 * @param head 
 * @param index 
 * @return Client* 
 */
// 
Client* getClientByIndex(Client* head, int index);

#pragma endregion

#pragma region Booking_Functions

/**
 * @brief Get the Last Res I D object
 * 
 * @param start 
 * @return int 
 */
// 
int getLastResID(resMeios* head);

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @param idclient 
 * @return int 
 */
// this function is used to check if the Meio belongs to the client who is trying to cancel the reservation.
int isMeioMineToUnbook(resMeios* head, int id, int idclient);

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @return int 
 */
// this function goes through the linked list and checks if a certain record indicated by the user is already reserved
int isMeioBooked(Meio* head, int code);

/**
 * @brief 
 * 
 * @param startDateTime 
 * @param endDateTime 
 * @return float 
 */
// 
float returnTimeDiff(struct periodDateTime startDateTime, struct periodDateTime endDateTime);

/**
 * @brief 
 * 
 * @param head 
 * @param id 
 * @return float 
 */
// 
float calculateTotalCost(resMeios* head, int id, float timediff);

/**
 * @brief 
 * 
 * @param head 
 * @param id 
 * @return int 
 */
// 
int canItBeUnbooked(resMeios* head, int id);

#pragma endregion

#pragma region Exist_Functions

/**
 * @brief 
 * 
 * @param start 
 * @param cod 
 * @return int 
 */
// Function that checks whether or not a certain record of type Meio already exists
int existRecord_Meio(Meio* start, int cod);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return int 
 */
// Function that checks whether or not a certain record of type Client already exists
int existRecord_Client(Client* start, int id);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return int 
 */
// Function that checks whether or not a certain record of type Manager already exists
int existRecord_Manager(Manager* start, int id);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return int 
 */
// Function that checks whether or not a certain record of type Reservation already exists
int existRecord_Booked(resMeios* head, int id);

#pragma endregion

#pragma region Check_Available_Functions

// Function that checks whether or not a certain record of type Meio is available
int isRecordAvailable_Meio(Meio* start, int code);

// Function that checks whether or not a certain record of type Client is available
int isRecordAvailable_Client(Client* start, int id);

// Function that checks whether or not a certain record of type Manager is available
int isRecordAvailable_Manager(Manager* start, int id);

#pragma endregion

#pragma region List_Functions

/**
 * @brief 
 * 
 * @param start 
 */
// this function traverses the Meio linked list and lists the records present in it
void listAvailableRecords_Meio(Meio* start);

/**
 * @brief 
 * 
 * @param start 
 */
// 
void listUnavailableRecords_Meio(Meio* start);

/**
 * @brief 
 * 
 * @param start 
 */
// this function traverses the Client linked list and lists the records present in it
void listAvailableRecords_Client(Client* start);

/**
 * @brief 
 * 
 * @param start 
 */
//
void listUnavailableRecords_Client(Client* start);

/**
 * @brief 
 * 
 * @param start 
 */
// this function traverses the Manager linked list and lists the records present in it
void listAvailableRecords_Manager(Manager* start);

/**
 * @brief 
 * 
 * @param start 
 */
// 
void listUnavailableRecords_Manager(Manager* start);

/**
 * @brief 
 * 
 * @param head 
 */
// this function traverses the Meio linked list and lists the non booked records present in it
void listNonBookingRecords(Meio* head);

/**
 * @brief 
 * 
 * @param head 
 * @param idClient 
 */
// this function goes through the linked list, and lists the records that were reserved by the client that is logged in
void listClientBookingRecords(resMeios* head, int idClient);

/**
 * @brief 
 * 
 * @param head 
 * @param idClient 
 */
//
void listCancelledBookingRecords(resMeios* head, int idClient);

#pragma endregion

#pragma region Remove_Functions

/**
 * @brief 
 * 
 * @param start 
 * @param cod 
 * @return Meio* 
 */
// Updates the 'available' field to 0, so it is now not available for booking.
Meio* removeRecord_Meio(Meio* start, int code);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return Client* 
 */
// Function that removes a record of type Client from it's id
Client* removeRecord_Client(Client* start, int id);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return Manager* 
 */
// Function that removes a record of type Manager from it's id
Manager* removeRecord_Manager(Manager* start, int id);

/**
 * @brief 
 * 
 * @param head 
 * @param id 
 * @param endDateTime 
 * @return resMeios* 
 */
// this function scrolls through the linked list and cancels the reservation of the record indicated by the user
resMeios* cancelbookMeio(resMeios* head, int id, struct periodDateTime endDateTime);

#pragma endregion

#pragma region Recover_Functions

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @return Meio* 
 */
// Updates the 'available' field to 1, so it is now available for booking.
Meio* recoverRecord_Meio(Meio* start, int code);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return Client* 
 */
// Function that removes a record of type Client from it's id
Client* recoverRecord_Client(Client* start, int id);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return Manager* 
 */
// Function that removes a record of type Manager from it's id
Manager* recoverRecord_Manager(Manager* start, int id);

#pragma endregion

#pragma region Delete_Functions

/**
 * @brief 
 * 
 * @param start 
 * @param code 
 * @return Meio* 
 */
// removes the Meio record from the linked list
Meio* deleteRecord_Meio(Meio* start, int code);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return Client* 
 */
// 
Client* deleteRecord_Client(Client* start, int id);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return Manager* 
 */
// 
Manager* deleteRecord_Manager(Manager* start, int id);

/**
 * @brief 
 * 
 * @param head 
 * @param id 
 * @param endDateTime 
 * @return resMeios* 
 */
// 
resMeios* deletebookMeio(resMeios* head, int id, struct periodDateTime endDateTime);

#pragma endregion

#pragma region Edit_Functions

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
// this function goes through the Meio linked list and edits the record data that contains the code indicated by the user
Meio* editRecord_Meio(Meio* start, int code, char type[50], 
	float bat, float aut, float cost, char loc[50]); // here is included the need parameters

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
// this function goes through the Client linked list and edits the record data that contains the code indicated by the user
Client* editRecord_Client(Client* start, int id, char name[100],
	int bd, int bm, int by, int phn, char addr[100], int nif, 
	float balance, char email[50], char pass[50]); // here is included the need parameters

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
// this function goes through the Manager linked list and edits the record data that contains the code indicated by the user
Manager* editRecord_Manager(Manager* start, int id, char name[100], int bd, 
	int bm, int by, int phn, char email[50], char pass[50]); // here is included the need parameters

#pragma endregion

#pragma region Save_Functions

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// Function that saves records of type Meio in a text file
int saveRecords_Meio(Meio* start);

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// Function that saves records of type Client in a text file
int saveRecords_Client(Client* start);

/**
 * @brief 
 * 
 * @param start 
 * @return int 
 */
// Function that saves records of type Manager in a text file
int saveRecords_Manager(Manager* start);

/**
 * @brief 
 * 
 * @param head 
 * @return int 
 */
// 
int saveRecords_Book(resMeios* head);

#pragma endregion

#pragma region Read_Functions

/**
 * @brief 
 * 
 * @return Meio* 
 */
// Function that reads records of type Meio from a text file
Meio* readrecords_Meio();

/**
 * @brief 
 * 
 * @return Meio* 
 */
// Function that reads records of type Client from a text file
Client* readrecords_Client();

/**
 * @brief 
 * 
 * @return Meio* 
 */
// Function that reads records of type Manager from a text file
Manager* readrecords_Manager();

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @return resMeios* 
 */
// 
resMeios* readrecords_Book(Meio* meios, Client* clients);

#pragma endregion

#pragma region Menu_Functions

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this main menu that allows the user to indicate their status in order to be able to login to their respective account
int showMenu(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param manager 
 * @return int 
 */
// this client menu that allows the client to manipulate the records of reservations of Means
int showSubMenu_Client(Meio* meios, Client* clients, Manager* manager, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this client sub menu that allows the client to log in if he already has one, or to create one otherwise
int showSubSubMenu_Client(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this manager menu that allows the manager to choose if he wants to manipulate Meio records or Clients records
int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this client menu that allows the manager to manipulate the records of reservations of Means
int showSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this client menu that allows the manager to manipulate the records of Clients
int showSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

#pragma endregion

#pragma region search_ID_Functions

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return const int 
 */
// this function goes through the Client linked list and return the client id which is represented by the email and password used to login
const int searchID_Client(Client* start, char email[50], char pass[50]);

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return const int 
 */
// this function goes through the Manager linked list and return the manager id which is represented by the email and password used to login
const int searchID_Manager(Manager* start, char email[50], char pass[50]);

#pragma endregion

#pragma region search_Name_Functions

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return const char* 
 */
// this function goes through the Client linked list and return the client name which is represented by id of the client logged in
const char* searchName_Client(Client* start, int id);

/**
 * @brief 
 * 
 * @param start 
 * @param id 
 * @return const char* 
 */
// this function goes through the Manager linked list and return the client name which is represented by id of the manager logged in
const char* searchName_Manager(Manager* start, int id);

#pragma endregion

#pragma region Loop_Login_Functions

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// 
int loop_Client_Login(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
//
int loop_Manager_Login(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

#pragma endregion

#pragma region Recover_Delete_Records_Menus

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @param resmeios 
 * @return int 
 */
// 
int Manager_Meios_Loop(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @param resmeios 
 * @return int 
 */
// 
int showSubSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @param resmeios 
 * @return int 
 */
//
int Manager_Clients_Loop(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @param resmeios 
 * @return int 
 */
// 
int showSubSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios);

#pragma endregion

#pragma region Login_Functions

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return int 
 */
// Function that allows to login to Client account
int login_Client(Client* start, char email[50], char pass[50]);

/**
 * @brief 
 * 
 * @param start 
 * @param email 
 * @param pass 
 * @return int 
 */
// Function that allows to login to Manager account
int login_Manager(Manager* start, char email[50], char pass[50]);

#pragma endregion

#pragma region Auxiliar_Functions

/**
 * @brief 
 * 
 */
void red(); // a function that changes the font color to red
/**
 * @brief 
 * 
 */
void yellow(); // a function that changes the font color to yellow
/**
 * @brief 
 * 
 */
void green(); // a function that changes the font color to green
/**
 * @brief 
 * 
 */
void blue(); // a function that changes the font color to blue
/**
 * @brief 
 * 
 */
void reset(); // a function that return the font color to it's original font
/**
 * @brief 
 * 
 */
void clear(); // a function that clears all the information present in the console

/**
 * @brief 
 * 
 */
void flushstdin(void); // a function that clears the keyboard buffer

/**
 * @brief 
 * 
 */
void pause(); // a function that interrupts the program until a random key is pressed by the user

#pragma endregion