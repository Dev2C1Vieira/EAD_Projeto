#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


#pragma region Global_Variables

/**
 * @brief 
 * 
 */
// This global variable allows the logged in client ID to be retained for booking purposes
int globalID_Client = 0;

/**
 * @brief 
 * 
 */
// This global variable allows the logged in manager ID to be retained for managing purposes
int globalID_Manager = 0;

/**
 * @brief 
 * 
 */
// This global variable allows the logged in client Name to be retained for booking purposes
const char* globalName_Client;

/**
 * @brief 
 * 
 */
// This global variable allows the logged in manager Name to be retained for booking purposes
const char* globalName_Manager;

#pragma endregion

/**
 * @brief 
 * 
 * @param str 
 */
// this functions is needed to read a string in case it is not empty
void getstring(char str[]) {
    do {
        gets(str);
    } while (strlen(str) == 0);
}

#pragma region Menu_Functions

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
int showMenu(Meio* meios, Client* clients, Manager* managers) {
    int op = 1;
    char email[50], pass[50];

    while (1)
    {
        do
        {
            clear();
            reset(); 
            red();
            printf("  -------- Welcome to the Menu ---------\n");
            reset();
            if (op < 1 || op > 3)
            {
                printf("\nInvalid Option! [1-3]\n");
            }
            yellow();
            printf("\n  Here you need to login to your account!\n");
            reset();
            printf("\n  1. I am a client.");
            printf("\n  2. I am a manager.");
            printf("\n  3. Exit.");
            red();
            printf("\n\n  Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 3);
        clear();
        switch (op)
        {
        case 1:
            showSubSubMenu_Client(meios, clients, managers);
            break;
        case 2:
            while (1)
            {
                clear();
                yellow();
                printf("Enter the needed information!\n\n");
                reset();
                printf("Enter your email: ");
                getstring(email);
                printf("Enter your password: ");
                getstring(pass);
                if (!login_Manager(managers, email, pass)) {
                    red();
                    printf("\nYour information is incorrect!");
                    printf("\n\nPlease try again...");
                    reset();
                }
                else {
                    // keeping the manager id in a global variable to use it later
                    globalID_Manager = searchID_Manager(managers, email, pass);
                    showSubMenu_Manager(meios, clients, managers);
                }
                pause();
            }
            break;
        case 3:
            exit(0); // stdlib archive
            printf("Program execution has ended");
            break;
        }
    }
}

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
int showSubMenu_Client(Meio* meios, Client* clients, Manager* managers) {
    int op = 1, cod;

    globalName_Client = searchName_Client(clients, globalID_Client);

    while (1)
    {
        do
        {
            clear();
            reset();
            red();
            printf("  --------- Wellcome to the Booking Menu ---------\n");
            reset();
            if (op < 1 || op > 6) {
                red(); 
                printf("\n  Invalid Option! [1-7]\n");
            }
            reset();
            printf("\n  Hello, %s\n", globalName_Client);
            yellow();
            printf("\n  Here you need to choose the option you want to run\n");
            reset();
            printf("\n  +-------------------------------------------+");
            printf("\n  |  1. List the means of transport!          |");
            printf("\n  |  2. Book a means of transport!            |");
            printf("\n  |  3. Stop booking a means of transport!    |");
            printf("\n  |  4. list my booked means of transport!    |");
            printf("\n  |  5. Save reservations!                    |");
            printf("\n  |  6. Read reservations!                    |");
            printf("\n  |  7. Return to Client Login Menu.          |");
            printf("\n  +-------------------------------------------+");
            red();
            printf("\n\n  Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 7);
        clear();
        switch (op)
        {
        case 1:
            red();
            printf("\nTable containing the information of the records of type Meio.\n");
            // Table Construction
            yellow();
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            printf("\n|    CODE      TYPE                 BATTERY      AUTONOMY       COST      STATUS          LOCATION           |");
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            reset();
            listRecords_Meio(meios);
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            printf("\n\nTotal sum of records of type Meios:");
            red();
            // this function return the amount of records in the Linked List Meios
            printf(" %d", countRecords_Meio(meios));
            reset();
            pause();
            break;
        case 2:
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter the code of the mean you want to Book: ");
            scanf("%d", &cod);
            if (!existRecord_Meio(meios, cod)) {
                red();
                printf("\n\nThe mean with code");
                yellow();
                printf(" %d ", cod);
                reset();
                red();
                printf("doesn't exist!");
                printf("\n\nUnable to book the mean!");
                reset();
            }
            else {
                if (!isMeioBooked(meios, cod)) {
                    meios = bookMeio(meios, cod, globalID_Client);
                    red();
                    printf("\n\nReservation made successfully");
                    reset();
                }
                else {
                    red();
                    printf("\n\nThe mean with code");
                    yellow();
                    printf(" %d ", cod);
                    reset();
                    red();
                    printf("is already booked");
                    printf("\n\nUnable to book the mean!");
                    reset();
                }
            }
            pause();
            break;
        case 3:
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter the code the mean you want to remove: ");
            scanf("%d", &cod);
            if (!existRecord_Meio(meios, cod)) {
                red();
                printf("\n\nThe mean with code");
                yellow();
                printf(" %d ", cod);
                reset();
                red();
                printf("doesn't exist!");
                printf("\n\nUnable to remove the mean!");
                reset();
            }
            else {
                meios = cancelbookMeio(meios, cod);
                red();
                printf("\n\nA mean containing the code");
                yellow();
                printf(" %d ", cod);
                reset();
                red();
                printf("was successfully unbooked!");
                reset();
            }
            pause();
            break;
        case 4:
            red();
            printf("\nTable containing the information of the records of type Meio.\n");
            // Table Construction
            yellow();
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            printf("\n|    CODE      TYPE                 BATTERY      AUTONOMY       COST      STATUS          LOCATION           |");
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            reset();
            listBookingRecords(meios, globalID_Client);
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            printf("\n\nTotal sum of records of type Meios:");
            red();
            // this function return the amount of records in the Linked List Meios
            printf(" %d", countRecords_Book(meios, globalID_Client));
            reset();
            pause();
            break;
        case 5:
            // Save the reservations of type Meio
            if (!saveRecords_Meio(meios)) {
                red();
                printf("Unable to save reservations!");
                reset();
            }
            else {
                saveRecords_Meio(meios);
                yellow();
                printf("Reservations have been saved successfully!");
                reset();
            }
            pause();
            break;
        case 6:
            // Read the records of type Meio
            meios = readrecords_Meio();
            yellow();
            printf("The reservations were successfully read!");
            reset();
            pause();
            break;
        case 7:
            clear();
            showSubSubMenu_Client(meios, clients, managers);
            break;
        }
    }
}

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
int showSubSubMenu_Client(Meio* meios, Client* clients, Manager* managers) {
    int op = 1, id, phn, nif, bd, bm, by;
    char name[50], addr[50], email[50], pass[50];
    float balance;

    while (1)
    {
        do
        {
            clear();
            reset();
            red();
            printf("  --------- Welcome to the Client Login Menu ---------\n");
            reset();
            if (op < 1 || op > 3)
            {
                printf("\nInvalid Option! [1-3]\n");
            }
            yellow();
            printf("\n  Here you can login to your existing account or create one if you don't already have one.\n");
            reset();
            printf("\n  1. I've already have one account.");
            printf("\n  2. I want to create one.");
            printf("\n  3. Return to Main Menu");
            red();
            printf("\n\n  Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 3);
        clear();
        switch (op)
        {
        case 1:
            while (1)
            {
                clear();
                yellow();
                printf("Enter the needed information!\n\n");
                reset();
                printf("Enter your email: ");
                getstring(email);
                printf("Enter your password: ");
                getstring(pass);
                if (!login_Client(clients, email, pass)) {
                    red();
                    printf("\nYour information is incorrect!");
                    printf("\n\nPlease try again...");
                    reset();
                }
                else {
                    // keeping the client id in a global variable to use it later
                    globalID_Client = searchID_Client(clients, email, pass);
                    showSubMenu_Client(meios, clients, managers);
                    
                }
                pause();
            }
            
            break;
        case 2:
            // Insert a new record of type Client
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter your id number: ");
            scanf("%d", &id);
            flushstdin();
            printf("Enter the name you want to be displayed: ");
            getstring(name);
            printf("Enter your birthdate (dd-mm-yyyy): ");
            scanf("%d-%d-%d", &bd, &bm, &by);
            flushstdin();
            printf("Enter your phone number: ");
            scanf("%d", &phn);
            flushstdin();
            printf("Enter your address: ");
            getstring(addr);
            printf("Enter your nif: ");
            scanf("%d", &nif);
            flushstdin();
            printf("Enter your balance: ");
            scanf("%.2f", &balance);
            flushstdin();
            printf("Enter your email: ");
            getstring(email);
            printf("Enter your password: ");
            getstring(pass);
            if (!existRecord_Client(clients, id)) {
                clients = insertNewRecord_Client(clients, id, name, bd, bm, by, phn, addr, nif, balance, email, pass);
                red();
                printf("\n\nYour registration was successful!");
                reset();
            }
            else {
                red();
                printf("\n\nYour registration was unsuccessful.");
                reset();
            }
            pause();
            break;
        case 3:
            clear();
            showMenu(meios, clients, managers);
            break;
        }
        
    }
}

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers) {
    int op = 1;

    while (1)
    {
        do
        {
            clear();
            reset(); 
            red();
            printf("  -------- Welcome to the Manager Menu ---------\n");
            reset();
            if (op < 1 || op > 3)
            {
                printf("\nInvalid Option! [1-3]\n");
            }
            yellow();
            printf("\n  Here you choose whether you want to manage records of type Meios or Clients!\n");
            reset();
            printf("\n  1. Manage Meios.");
            printf("\n  2. Manage Clients.");
            printf("\n  3. Return to Main Menu.");
            red();
            printf("\n\n  Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 6);
        clear();
        switch (op)
        {
        case 1:
            showSubMenu_Manager_Meios(meios, clients, managers);
            break;
        case 2:
            showSubMenu_Manager_Clients(meios, clients, managers);
            break;
        case 3:
            clear();
            showMenu(meios, clients, managers);
            break;
        }
    }
}

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
int showSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers) {
    int op = 1, cod;
    char type[50], loc[50], bat_s[20], aut_s[20], cost_s[20];
    float bat, aut, cost;

    while (1)
    {
        do
        {
            clear();
            reset();
            red();
            printf("  -------- Welcome to the Manager Sub-Menu ---------\n");
            reset();
            if (op < 1 || op > 7)
            {
                printf("\nInvalid Option! [1-7]\n");
            }
            yellow();
            printf("\n  Here you need to choose the option you want to run\n");
            reset();
            printf("\n  +-----------------------------------------+");
            printf("\n  |  1. Insert a new record of type Meio!   |");
            printf("\n  |  2. List the records of type Meio!      |");
            printf("\n  |  3. Remove a record of type Meio!       |");
            printf("\n  |  4. Edit a record of type Meio!         |");
            printf("\n  |  5. Save the records of type Meio!      |");
            printf("\n  |  6. Read the records of type Meio       |");
            printf("\n  |  7. Return to Main Menu.                |");
            printf("\n  +-----------------------------------------+");
            red();
            printf("\n\n    Choose an Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 7);
        clear();
        switch (op)
        {
        case 1:
            // Insert a new record of type Meio
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter the code of the new record: ");
            scanf("%d", &cod);
            printf("Enter the type of the new record: ");
            getstring(type);
            printf("Enter the battery of the new record: ");
            scanf("%f", &bat);
            flushstdin();
            printf("Enter the autonomy of the new record: ");
            scanf("%f", &aut);
            flushstdin();
            printf("Enter the cost of the new record: ");
            scanf("%f", &cost);
            flushstdin();
            printf("Enter the location of the new record: ");
            getstring(loc);
            if (!existRecord_Meio(meios, cod)) {
                meios = insertNewRecord_Meio(meios, cod, type, bat, aut, cost, 0, 0, loc);
                saveRecords_Meio(meios);
                red();
                printf("\n\nNew registered record!");
                reset();
            }
            else {
                red();
                printf("\n\nA record with code");
                yellow();
                printf(" %d ", cod);
                reset();
                red();
                printf("already exists!");
                printf("\n\nUnable to insert new record!");
                reset();
            }
            pause();
            break;
        case 2:
            // List the records of type Meio
            //meios = readrecords_Meio(meios);
            red();
            printf("\nTable containing the information of the records of type Meio.\n");
            // Table Construction
            yellow();
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            printf("\n|    CODE      TYPE                 BATTERY      AUTONOMY       COST      STATUS          LOCATION           |");
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            reset();
            listRecords_Meio(meios);
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            pause();
            break;
        case 3:
            // Remove a record of type Meio
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter the code of record you want to remove: ");
            scanf("%d", &cod);
            if (!existRecord_Meio(meios, cod)) {
                red();
                printf("\n\nThe record with code");
                yellow();
                printf(" %d ", cod);
                reset();
                red();
                printf("doesn't exist!");
                printf("\n\nUnable to remove the record!");
                reset();
            }
            else {
                meios = removeRecord_Meio(meios, cod);
                red();
                printf("\n\nA record containing the code");
                yellow();
                printf(" %d ", cod);
                reset();
                red();
                printf("was successfully removed!");
                reset();
            }
            pause();
            break;
        case 4:
            yellow();
            printf("What record id you want to edit?\n\n");
            reset();
            printf("Enter the code: ");
            scanf("%d", &cod);
            if (existRecord_Meio(meios, cod)) {
                clear();
                yellow();
                printf("Edit only the fields you want to change!\n\n");
                reset();
                
                flushstdin();
                /*printf("Enter the type of the record: ");
                fgets(type, sizeof type, stdin);
                printf("Enter the battery of the record: ");
                //scanf("%[^\n]", &bat_s);
                fgets(bat_s, sizeof bat_s, stdin);
                printf("Enter the autonomy of the record: ");
                //scanf("%[^\n]", &aut_s);
                fgets(aut_s, sizeof aut_s, stdin);
                printf("Enter the cost of the record: ");
                //scanf("%[^\n]", &cost_s);
                fgets(cost_s, sizeof cost_s, stdin);
                printf("Enter the location of the record: ");
                fgets(loc, sizeof loc, stdin);*/
                
                printf("Enter the type of the record: ");
                getstring(type);
                printf("Enter the battery of the new record: ");
                scanf("%f", &bat);
                flushstdin();
                printf("Enter the autonomy of the record: ");
                scanf("%f", &aut);
                flushstdin();
                printf("Enter the cost of the record: ");
                scanf("%f", &cost);
                flushstdin();
                printf("Enter the location of the record: ");
                getstring(loc);
                
                //meios = consultarDados(meios, id);
                //if (aut = null) aut = meios->aut;
                //Create consulting function

                /*//https://stackoverflow.com/questions/30220691/how-to-get-empty-input-or-only-enter-in-c - LINK for stackoverflow

                if (bat_s[0] == '\n') {
                    bat = -1;
                }
                if (aut_s[0] == '\n') {
                    aut = -1;
                }
                if (cost_s[0] == '\n') {
                    cost = -1;
                }
                else {
                    bat = atof(bat_s);
                    aut = atof(aut_s);
                    cost = atof(cost_s);
                }*/
                
                meios = editRecord_Meio(meios, cod, type, bat, aut, cost, loc);
                red();
                printf("\n\nRegistration data has been successfully edited!");
                reset();
            }
            else {
                red();
                printf("\n\nRecord with id");
                yellow();
                printf(" %d ", cod);
                red();
                printf("does not exist");
                printf("\n\nUnable to edit registry data");
                reset();
            }
            pause();
            break;
        case 5:
            // Save the records of type Meio
            if (!saveRecords_Meio(meios)) {
                red();
                printf("Unable to save records!");
                reset();
            }
            else {
                saveRecords_Meio(meios);
                yellow();
                printf("Records have been saved successfully!");
                reset();
            }
            pause();
            break;
        case 6:
            // Read the records of type Meio
            meios = readrecords_Meio();
            yellow();
            printf("The records were successfully read!");
            reset();
            pause();
            break;
        case 7:
            clear();
            showSubMenu_Manager(meios, clients, managers);
            break;
        }
    }
}

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
int showSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers) {
    int op = 1, id, phn, nif, bd, bm, by;
    char name[50], addr[50], email[50], pass[50];
    float balance;

    while (1)
    {
        do
        {
            clear();
            reset();
            red();
            printf("  -------- Welcome to the Manager Sub-Menu ---------\n");
            reset();
            if (op < 1 || op > 7)
            {
                printf("\nInvalid Option! [1-7]\n");
            }
            yellow();
            printf("\n  Here you need to choose the option you want to run\n");
            reset();
            printf("\n  +-------------------------------------------+");
            printf("\n  |  1. Insert a new record of type Client!   |");
            printf("\n  |  2. List the records of type Client!      |");
            printf("\n  |  3. Remove a record of type Client!       |");
            printf("\n  |  4. Edit a record of type Client!         |");
            printf("\n  |  5. Save the records of type Client!      |");
            printf("\n  |  6. Read the records of type Client       |");
            printf("\n  |  7. Return to Main Menu.                  |");
            printf("\n  +-------------------------------------------+");
            red();
            printf("\n\n    Choose an Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 7);
        clear();
        switch (op)
        {
        case 1:
            // Insert a new record of type Client
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter your id number: ");
            scanf("%d", &id);
            flushstdin();
            printf("Enter the name you want to be displayed: ");
            getstring(name);
            printf("Enter your birthdate (dd-mm-yyyy): ");
            scanf("%d-%d-%d", &bd, &bm, &by);
            flushstdin();
            printf("Enter your phone number: ");
            scanf("%d", &phn);
            flushstdin();
            printf("Enter your address: ");
            getstring(addr);
            printf("Enter your nif: ");
            scanf("%d", &nif);
            flushstdin();
            printf("Enter your balance: ");
            scanf("%f", &balance);
            flushstdin();
            printf("Enter your email: ");
            getstring(email);
            printf("Enter your password: ");
            getstring(pass);
            if (!existRecord_Client(clients, id)) {
                clients = insertNewRecord_Client(clients, id, name, bd, bm, by, phn, addr, nif, balance, email, pass);
                saveRecords_Client(clients);
                red();
                printf("\n\nNew client registred!!");
                reset();
            }
            else {
                red();
                printf("\n\nA client with id");
                yellow();
                printf(" %d ", id);
                reset();
                red();
                printf("already exists!");
                printf("\n\nUnable to insert new client!");
                reset();
            }
            pause();
            break;
        case 2:
            // List the records of type Client
            red();
            printf("\nTable containing the information of the records of type Client.\n");
            // Table Construction
            yellow();
            printf("\n+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            printf("\n|    ID      NAME                 BIRTHDATE      PHONE NUMBER       ADDRESS                                  NIF             BALANCE       EMAIL                        |");
            printf("\n+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            reset();
            listRecords_Client(clients);
            printf("\n+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            pause();
            break;
        case 3:
            // Remove a record of type Client
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter the id of the client you want to remove: ");
            scanf("%d", &id);
            if (!existRecord_Client(clients, id)) {
                red();
                printf("\n\nThe client with id");
                yellow();
                printf(" %d ", id);
                reset();
                red();
                printf("doesn't exist!");
                printf("\n\nUnable to remove the client!");
                reset();
            }
            else {
                clients = removeRecord_Client(clients, id);
                red();
                printf("\n\nA client containing the code");
                yellow();
                printf(" %d ", id);
                reset();
                red();
                printf("was successfully removed!");
                reset();
            }
            pause();
            break;
        case 4:
            // Edit a record of type Client
            yellow();
            printf("What record id you want to edit?\n\n");
            reset();
            printf("Enter the id: ");
            scanf("%d", &id);
            if (existRecord_Client(clients, id)) {
                clear();
                yellow();
                printf("Edit only the fields you want to change!\n\n");
                reset();
                flushstdin();
                printf("Enter the new name of the client: ");
                getstring(name);
                printf("Enter the new birthdate (dd-mm-yyyy) of the client: ");
                scanf("%d-%d-%d", &bd, &bm, &by);
                flushstdin();
                printf("Enter the new phone number of the client: ");
                scanf("%d", &phn);
                flushstdin();
                printf("Enter the new address of the client: ");
                getstring(addr);
                printf("Enter the new nif of the client: ");
                scanf("%d", &nif);
                flushstdin();
                printf("Enter the new balance of the client: ");
                scanf("%.2f", &balance);
                flushstdin();
                printf("Enter the new email of the client: ");
                getstring(email);
                printf("Enter the new password of the client: ");
                getstring(pass);
                
                //meios = consultarDados(meios, id);
                //if (aut = null) aut = meios->aut;
                //Create consulting function
                
                /*//https://stackoverflow.com/questions/30220691/how-to-get-empty-input-or-only-enter-in-c - LINK for stackoverflow

                if (bat_s[0] == '\n') {
                    bat = -1;
                }
                if (aut_s[0] == '\n') {
                    aut = -1;
                }
                if (cost_s[0] == '\n') {
                    cost = -1;
                }
                else {
                    bat = atof(bat_s);
                    aut = atof(aut_s);
                    cost = atof(cost_s);
                }*/
                
                clients = editRecord_Client(clients, id, name, bd, bm, by, phn, addr, nif, balance, email, pass);
                red();
                printf("\n\nRegistration data has been successfully edited!");
                reset();
            }
            else {
                red();
                printf("\n\nRecord with id");
                yellow();
                printf(" %d ", id);
                red();
                printf("does not exist");
                printf("\n\nUnable to edit registry data");
                reset();
            }
            pause();
            break;
        case 5:
            // Save the records of type Client
            if (!saveRecords_Client(clients)) {
                red();
                printf("Unable to save records!");
                reset();
            }
            else {
                saveRecords_Client(clients);
                yellow();
                printf("Records have been saved successfully!");
                reset();
            }
            pause();
            break;
        case 6:
            // Read the records of type Client
            clients = readrecords_Client();
            yellow();
            printf("The records were successfully read!");
            reset();
            pause();
            break;
        case 7:
            clear();
            showSubMenu_Manager(meios, clients, managers);
            break;
        }
    }
}

#pragma endregion

int main()
{
    /**
     * @brief 
     * 
     */
    Meio* meios = NULL; // Empty Linked List of type Meio
    /**
     * @brief 
     * 
     */
    Client* clients = NULL; // Empty Linked List of type Client
    /**
     * @brief 
     * 
     */
    Manager* managers = NULL; // Empty Linked List of type Manager
    //resMeios resmeios = NULL; // Empty Linked List of type Reservations
    
    managers = insertNewRecord_Manager(managers, 1, "Tiago Silva", 05, 11, 1989, 827625413, "ola", "123");

    meios = readrecords_Meio();

    clients = readrecords_Client();

    /**
     * @brief Construct a new show Menu object
     * 
     */
    showMenu(meios, clients, managers);

    return(0);
}