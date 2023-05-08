#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
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

#pragma region Auxiliar_Functions

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
int loop_Client_Login(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    int id, phn, nif, bd, bm, by;
    char op, name[50], addr[50], email[50], pass[50];
    float balance;

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
            
            // Keep trying loop or exit login loop
            do
            {
                yellow();
                printf("\n\n  Try Again (y/n): ");
                scanf("%s", &op);
                if ((!(op == 'y')) && (!(op == 'n'))) {
                    clear();
                    printf("\nInvalid Option! [y/n]\n");
                }
                else {
                    if (op == 'y') { // Compare first character of op with 'y'
                        loop_Client_Login(meios, clients, managers, resmeios);
                    }
                    else {
                        showSubSubMenu_Client(meios, clients, managers, resmeios);
                    }
                }
            } while (((!(op == 'y')) && (!(op == 'n'))));
        }
        else {
            // keeping the client id in a global variable to use it later
            globalID_Client = searchID_Client(clients, email, pass);
            showSubMenu_Client(meios, clients, managers, resmeios);        
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
// 
int loop_Manager_Login(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    char op[0], email[50], pass[50];

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
            
            // Keep trying loop or exit login loop
            do
            {
                yellow();
                printf("\n\n  Try Again (y/n): ");
                getstring(op);
                if ((!(op[0] == 'y')) && (!(op[0] == 'n'))) {
                    clear();
                    printf("\nInvalid Option! [y/n]\n");
                }
                else {
                    if (op[0] == 'y') { // Compare first character of op with 'y'
                        loop_Manager_Login(meios, clients, managers, resmeios);
                    }
                    else {
                        showMenu(meios, clients, managers, resmeios);
                    }
                }
            } while (((!(op[0] == 'y')) && (!(op[0] == 'n'))));
        }
        else {
            // keeping the manager id in a global variable to use it later
            globalID_Manager = searchID_Manager(managers, email, pass);
            showSubMenu_Manager(meios, clients, managers, resmeios);
        }
    }
}

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
int Manager_Meios_Loop(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    // List the available records of type Meio
    red();
    printf("\nTable containing the information of the records of type Meio.\n");
    reset();
    printf("\n\nTotal sum of records of type Meios:");
    red();
    // this function return the amount of records in the Linked List Meios
    printf(" %d\n", countUnavailableRecords_Meio(meios));
    reset();
    // Table Construction
    yellow();
    printf("\n+--------------------------------------------------------------------------------------------------------------+");
    printf("\n|    CODE      TYPE                 BATTERY      AUTONOMY       COST        STATUS            LOCATION         |");
    printf("\n+--------------------------------------------------------------------------------------------------------------+");
    reset();
    listUnavailableRecords_Meio(meios);
    printf("\n+--------------------------------------------------------------------------------------------------------------+");
    printf("\n|            1. Delete a Record!           2. Recover a Record!            3. Return to Main Menu.             |");
    printf("\n+--------------------------------------------------------------------------------------------------------------+");
    return(1);
}

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
int showSubSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {

    int cod;
    char op;
    while (1) {
        clear();
        Manager_Meios_Loop(meios, clients, managers, resmeios);
        do
        {
            red();
            printf("\n\n    Choose an Option: ");
            reset();
            scanf("%s", &op);
            if (op == '3') {
                showSubMenu_Manager_Meios(meios, clients, managers, resmeios);
            }

            if ((!(op == '1')) && (!(op == '2')) && (!(op == '3'))) {
                clear();
                Manager_Meios_Loop(meios, clients, managers, resmeios);
                printf("\n\n\tInvalid Option! [1/3]\n");
            }
            else {
                if (op == '1') {
                    printf("\n\tEnter the code of record you want to delete: ");
                    scanf("%d", &cod);
                    if (!existRecord_Meio(meios, cod)) {
                        red();
                        printf("\n\n\tThe record with code");
                        yellow();
                        printf(" %d ", cod);
                        reset();
                        red();
                        printf("doesn't exist!");
                        printf("\n\n\tUnable to remove the record!");
                        reset();
                    }
                    else {
                        if (!isRecordAvailable_Meio(meios, cod)) {
                            deleteRecord_Meio(meios, cod);
                            saveRecords_Meio(meios);
                            red();
                            printf("\n\n\tA record containing the code");
                            yellow();
                            printf(" %d ", cod);
                            reset();
                            red();
                            printf("was successfully deleted!");
                            reset();
                        }
                        else {
                            red();
                            printf("\n\n\tThe record with code");
                            yellow();
                            printf(" %d ", cod);
                            reset();
                            red();
                            printf("isnt's a removed record!");
                            printf("\n\n\tUnable to delete the record!");
                            reset();
                        }
                    }
                    pause();
                }
                else {
                    printf("\n\tEnter the code of record you want to recover: ");
                    scanf("%d", &cod);
                    if (!existRecord_Meio(meios, cod)) {
                        red();
                        printf("\n\n\tThe record with code");
                        yellow();
                        printf(" %d ", cod);
                        reset();
                        red();
                        printf("doesn't exist!");
                        printf("\n\n\tUnable to recover the record!");
                        reset();
                    }
                    else {
                        if (!isRecordAvailable_Meio(meios, cod)) {
                            recoverRecord_Meio(meios, cod);
                            saveRecords_Meio(meios);
                            red();
                            printf("\n\n\tA record containing the code");
                            yellow();
                            printf(" %d ", cod);
                            reset();
                            red();
                            printf("was successfully recovered!");
                            reset();
                        }
                        else {
                            red();
                            printf("\n\n\tThe record with code");
                            yellow();
                            printf(" %d ", cod);
                            reset();
                            red();
                            printf("isnt's a removed record!");
                            printf("\n\n\tUnable to recover the record!");
                            reset();
                        }
                    }
                    pause();
                }
            }
        } while (((!(op == '1')) && (!(op == '2'))));
        
    }
}

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
int Manager_Clients_Loop(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    // List the records of type Client
    red();
    printf("\nTable containing the information of the records of type Client.\n");
    reset();
    printf("\n\nTotal sum of records of type Client:");
    red();
    // this function return the amount of records in the Linked List Meios
    printf(" %d\n", countUnavailableRecords_Client(clients));
    reset();
    // Table Construction
    yellow();
    printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
    printf("\n|    ID      NAME                 BIRTHDATE      PHONE NUMBER       ADDRESS                                  NIF             BALANCE       EMAIL                              PASSWORD            |");
    printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
    reset();
    listUnavailableRecords_Client(clients);
    printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
    printf("\n|                                1. Delete a Record!                                 2. Recover a Record!                                  3. Return to Main Menu.                                |");
    printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
    return(1);
}

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
int showSubSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    
    int id;
    char op;
    while (1) {
        clear();
        Manager_Clients_Loop(meios, clients, managers, resmeios);
        do
        {
            red();
            printf("\n\n    Choose an Option: ");
            reset();
            scanf("%s", &op);
            if (op == '3') {
                showSubMenu_Manager_Clients(meios, clients, managers, resmeios);
            }

            if ((!(op == '1')) && (!(op == '2')) && (!(op == '3'))) {
                clear();
                Manager_Clients_Loop(meios, clients, managers, resmeios);
                printf("\n\n\tInvalid Option! [1/3]\n");
            }
            else {
                if (op == '1') {
                    printf("\n\tEnter the id of record you want to delete: ");
                    scanf("%d", &id);
                    if (!existRecord_Client(clients, id)) {
                        red();
                        printf("\n\n\tThe record with code");
                        yellow();
                        printf(" %d ", id);
                        reset();
                        red();
                        printf("doesn't exist!");
                        printf("\n\n\tUnable to remove the record!");
                        reset();
                    }
                    else {
                        if (!isRecordAvailable_Client(clients, id)) {
                            deleteRecord_Client(clients, id);
                            saveRecords_Client(clients);
                            red();
                            printf("\n\n\tA record containing the id");
                            yellow();
                            printf(" %d ", id);
                            reset();
                            red();
                            printf("was successfully deleted!");
                            reset();
                        }
                        else {
                            red();
                            printf("\n\n\tThe record with id");
                            yellow();
                            printf(" %d ", id);
                            reset();
                            red();
                            printf("isnt's a removed record!");
                            printf("\n\n\tUnable to delete the record!");
                            reset();
                        }
                    }
                    pause();
                }
                else {
                    printf("\n\tEnter the id of record you want to recover: ");
                    scanf("%d", &id);
                    if (!existRecord_Client(clients, id)) {
                        red();
                        printf("\n\n\tThe record with id");
                        yellow();
                        printf(" %d ", id);
                        reset();
                        red();
                        printf("doesn't exist!");
                        printf("\n\n\tUnable to recover the record!");
                        reset();
                    }
                    else {
                        if (!isRecordAvailable_Client(clients, id)) {
                            recoverRecord_Client(clients, id);
                            saveRecords_Client(clients);
                            red();
                            printf("\n\n\tA record containing the id");
                            yellow();
                            printf(" %d ", id);
                            reset();
                            red();
                            printf("was successfully recovered!");
                            reset();
                        }
                        else {
                            red();
                            printf("\n\n\tThe record with id");
                            yellow();
                            printf(" %d ", id);
                            reset();
                            red();
                            printf("isnt's a removed record!");
                            printf("\n\n\tUnable to recover the record!");
                            reset();
                        }
                    }
                    pause();
                }
            }
        } while (((!(op == '1')) && (!(op == '2'))));
        
    }
}

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
// 
int showMenu(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    int op = 1;
    
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
            showSubSubMenu_Client(meios, clients, managers, resmeios);
            break;
        case 2:
            loop_Manager_Login(meios, clients, managers, resmeios);
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
// 
int showSubMenu_Client(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    int op = 1, cod, id;

    struct periodDateTime spdt;
    spdt.date = getCurrentDate();

    struct time t = getCurrentTime();
    spdt.time.hour = t.hour;
    spdt.time.min = t.min;
    
    struct periodDateTime fpdt;

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
            if (op < 1 || op > 7) {
                red(); 
                printf("\n  Invalid Option! [1-7]\n");
            }
            reset();
            printf("\n  Hello, %s.\n", globalName_Client);
            yellow();
            printf("\n  Here you need to choose the option you want to run\n");
            reset();
            printf("\n  +-------------------------------------------+");
            printf("\n  |  1. List the means of transport!          |");
            printf("\n  |  2. Book a means of transport!            |");
            printf("\n  |  3. Cancel a reservation!                 |");
            printf("\n  |  4. List my available reservations!       |");
            printf("\n  |  5. List my unavailable reservations!     |");
            printf("\n  |  6. Other options!                        |");
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
            printf("\nTable containing the information of the accessible records.\n");
            // Table Construction
            yellow();
            printf("\n+-----------------------------------------------------------------------------------------------+");
            printf("\n|    CODE      TYPE                 BATTERY      AUTONOMY       COST        LOCATION            |");
            printf("\n+-----------------------------------------------------------------------------------------------+");
            reset();
            listNonBookingRecords(meios);
            printf("\n+-----------------------------------------------------------------------------------------------+");
            printf("\n\nTotal sum of accessible records:");
            red();
            // this function return the amount of records in the Linked List Meios
            printf(" %d\n", countNonBookingRecords(meios));
            reset();
            pause();
            break;
        case 2:
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter the code of the mean you want to Book: ");
            scanf("%d", &cod);

            fpdt.date.day = 0; // 
            fpdt.date.month = 0; // 
            fpdt.date.year = 0; // 
            fpdt.time.hour = 0; // 
            fpdt.time.min = 0; // 

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
                    if (isRecordAvailable_Meio(meios, cod)) {
                        resmeios = bookMeio(resmeios, spdt, fpdt, cod, globalID_Client, meios, clients, 0.0, 1);
                        saveRecords_Meio(meios);
                        saveRecords_Book(resmeios);
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
                        printf("is not available!");
                        printf("\n\nUnable to book the mean!");
                        reset();
                    }
                }
                else {
                    red();
                    printf("\n\nThe mean with code");
                    yellow();
                    printf(" %d ", cod);
                    reset();
                    red();
                    printf("is already booked!");
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
            printf("Enter the id of the reservation you want to unbook: ");
            scanf("%d", &id);
            //flushstdin();
            if (!existRecord_Booked(resmeios, id)) {
                red();
                printf("\n\nThe reservation with the id");
                yellow();
                printf(" %d ", id);
                reset();
                red();
                printf("doesn't exist!");
                printf("\n\nUnable to unbook the mean!");
                reset();
            }
            else {
                if (!isMeioMineToUnbook(resmeios, id, globalID_Client)) {
                    yellow();
                    printf("\n\nYou can't unbook this Mean because it is booked under some other client name.");
                    printf("\n\nSorry for the inconvenience!");
                    red();
                    printf("\n\nUnable to unbook the mean!");
                    reset();
                }
                else {
                    fpdt.date = getCurrentDate();
                    fpdt.time.hour = t.hour;
                    fpdt.time.min = t.min;

                    resmeios = cancelbookMeio(resmeios, id, fpdt);
                    saveRecords_Meio(meios);
                    saveRecords_Client(clients);
                    saveRecords_Book(resmeios);
                    red();
                    printf("\n\nA mean containing the code");
                    yellow();
                    printf(" %d ", cod);
                    reset();
                    red();
                    printf("was successfully unbooked!");
                    reset();
                }
            }
            pause();
            break;
        case 4:
            red();
            printf("\nTable containing the information of my available reservations.\n");
            // Table Construction
            yellow();
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            printf("\n|     RESID       STARTDATE        STARTTIME      MEIOTYPE        CLIENTNAME                COST/HOUR        |");
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            reset();
            listClientBookingRecords(resmeios, globalID_Client);
            printf("\n+------------------------------------------------------------------------------------------------------------+");
            printf("\n\nTotal sum of available reservations:");
            red();
            // this function return the amount of records in the Linked List Meios
            printf(" %d", countAvailableRecords_Book(resmeios, globalID_Client));
            reset();
            pause();
            break;
        case 5:
            red();
            printf("\nTable containing the information of my unavailable reservations.\n");
            // Table Construction
            yellow();
            printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            printf("\n|     RESID       STARTDATE        STARTTIME      ENDDATE          ENDTIME      MEIOTYPE             CLIENTNAME                COST/HOUR        TOTALCOST     |");
            printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            reset();
            listCancelledBookingRecords(resmeios, globalID_Client);
            printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            printf("\n\nTotal sum of unavailable reservations:");
            red();
            // this function return the amount of records in the Linked List Meios
            printf(" %d", countUnavailableRecords_Book(resmeios, globalID_Client));
            reset();
            pause();
            break;
        case 6:
            // 
            clear();
            showSubOthersMenu_Client(meios, clients, managers, resmeios);
            break;
        case 7:
            //
            clear();
            showSubSubMenu_Client(meios, clients, managers, resmeios);
            break;
        }
    }
}

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param manager 
 * @param resmeios 
 * @return int 
 */
// 
int showSubOthersMenu_Client(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    int op = 1, id, phn, nif, bd, bm, by;
    char name[50], addr[50], email[50], pass[50];
    float balance = 0.0;

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
            if (op < 1 || op > 3) {
                red(); 
                printf("\n  Invalid Option! [1-3]\n");
            }
            reset();
            printf("\n  Hello, %s.\n", globalName_Client);
            yellow();
            printf("\n  Here you can choose other types of options.\n");
            reset();
            printf("\n  +-------------------------------------------+");
            printf("\n  |  1. Update my informations!               |");
            printf("\n  |  2. Add balance to my wallet!             |");
            printf("\n  |  3. Return to Client Menu.                |");
            printf("\n  +-------------------------------------------+");
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
                // 
                clear();
                yellow();
                printf("Edit only the fields you want to change!\n\n");
                reset();
                printf("Enter your new name: ");
                getstring(name);
                printf("Enter your new birthdate (dd-mm-yyyy): ");
                scanf("%d-%d-%d", &bd, &bm, &by);
                flushstdin();
                printf("Enter your new phone number: ");
                scanf("%d", &phn);
                flushstdin();
                printf("Enter your new address: ");
                getstring(addr);
                printf("Enter your new nif: ");
                scanf("%d", &nif);
                flushstdin();
                printf("Enter your new email: ");
                getstring(email);
                printf("Enter your new password: ");
                getstring(pass);
                clients = editRecord_Client(clients, globalID_Client, name, bd, bm, by, phn, addr, nif, email, pass);
                saveRecords_Client(clients);
                red();
                printf("\n\nRegistration data has been successfully edited!");
                reset();
                pause();
                break;
            case 2:
                // 
                clear();
                yellow();
                printf("Enter the amount you want to add!\n\n");
                reset();
                printf("Enter your new balance: ");
                scanf("%f", &balance);
                clients = addBalance(clients, globalID_Client, balance);
                saveRecords_Client(clients);
                red();
                printf("\n\nBalance has been successfully added!");
                reset();
                pause();
                break;
            case 3:
                // 
                clear();
                showSubMenu_Client(meios, clients, managers, resmeios);
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
// 
int showSubSubMenu_Client(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
    int op = 1;
    int id, phn, nif, bd, bm, by;
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
            loop_Client_Login(meios, clients, managers, resmeios);
            break;
        case 2:
            // Insert a new record of type Client
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
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
            printf("Enter your email: ");
            getstring(email);
            printf("Enter your password: ");
            getstring(pass);
            clients = insertNewRecord_Client(clients, name, bd, bm, by, phn, addr, nif, 0.0, email, pass, 1);
            saveRecords_Client(clients);
            red();
            printf("\n\nNew client registred!!");
            reset();
            pause();
            break;
        case 3:
            clear();
            showMenu(meios, clients, managers, resmeios);
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
// 
int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
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
            showSubMenu_Manager_Meios(meios, clients, managers, resmeios);
            break;
        case 2:
            showSubMenu_Manager_Clients(meios, clients, managers, resmeios);
            break;
        case 3:
            clear();
            showMenu(meios, clients, managers, resmeios);
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
// 
int showSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
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
            if (op < 1 || op > 6)
            {
                printf("\nInvalid Option! [1-6]\n");
            }
            yellow();
            printf("\n  Here you need to choose the option you want to run\n");
            reset();
            printf("\n  +-------------------------------------------+");
            printf("\n  |  1. Insert a new record of type Meio!     |");
            printf("\n  |  2. List the records of type Meio!        |");
            printf("\n  |  3. Remove a record of type Meio!         |");
            printf("\n  |  4. Edit a record of type Meio!           |");
            printf("\n  |  5. List Meios history!                   |");
            printf("\n  |  6. Return to Main Menu.                  |");
            printf("\n  +-------------------------------------------+");
            red();
            printf("\n\n    Choose an Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 6);
        clear();
        switch (op)
        {
        case 1:
            // Insert a new record of type Meio
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
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

            meios = insertNewRecord_Meio(meios, type, bat, aut, cost, loc, 0, 1);
            saveRecords_Meio(meios);

            red();
            printf("\n\nNew registered record!");
            reset();
            pause();
            break;
        case 2:
            // List the available records of type Meio
            red();
            printf("\nTable containing the information of the records of type Meio.\n");
            // Table Construction
            yellow();
            printf("\n+--------------------------------------------------------------------------------------------------------------+");
            printf("\n|    CODE      TYPE                 BATTERY      AUTONOMY       COST        STATUS            LOCATION         |");
            printf("\n+--------------------------------------------------------------------------------------------------------------+");
            reset();
            listAvailableRecords_Meio(meios);
            printf("\n+--------------------------------------------------------------------------------------------------------------+");
            printf("\n\nTotal sum of records of type Meios:");
            red();
            // this function return the amount of records in the Linked List Meios
            printf(" %d\n", countAvailableRecords_Meio(meios));
            reset();
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
                if (isRecordAvailable_Meio(meios, cod)) {
                    meios = removeRecord_Meio(meios, cod);
                    saveRecords_Meio(meios);
                    red();
                    printf("\n\nA record containing the code");
                    yellow();
                    printf(" %d ", cod);
                    reset();
                    red();
                    printf("was successfully removed!");
                    reset();
                }
                else {
                    red();
                    printf("\n\nThe record with code");
                    yellow();
                    printf(" %d ", cod);
                    reset();
                    red();
                    printf("is already unavailable!");
                    printf("\n\nUnable to remove the record!");
                    reset();
                }
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
                saveRecords_Meio(meios);
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
            showSubSubMenu_Manager_Meios(meios, clients, managers, resmeios);
            pause();
            break;
        case 6:
            clear();
            showSubMenu_Manager(meios, clients, managers, resmeios);
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
// 
int showSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios) {
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
            if (op < 1 || op > 6)
            {
                printf("\nInvalid Option! [1-6]\n");
            }
            yellow();
            printf("\n  Here you need to choose the option you want to run\n");
            reset();
            printf("\n  +-------------------------------------------+");
            printf("\n  |  1. Insert a new record of type Client!   |");
            printf("\n  |  2. List the records of type Client!      |");
            printf("\n  |  3. Remove a record of type Client!       |");
            printf("\n  |  4. Edit a record of type Client!         |");
            printf("\n  |  5. List Client history!                  |");
            printf("\n  |  6. Return to Main Menu.                  |");
            printf("\n  +-------------------------------------------+");
            red();
            printf("\n\n    Choose an Option: ");
            reset();
            scanf("%d", &op);
            flushstdin();
            reset();
        } while (op < 1 || op > 6);
        clear();
        switch (op)
        {
        case 1:
            // Insert a new record of type Client
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
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
            printf("Enter your email: ");
            getstring(email);
            printf("Enter your password: ");
            getstring(pass);
            clients = insertNewRecord_Client(clients, name, bd, bm, by, phn, addr, nif, 0.0, email, pass, 1);
            saveRecords_Client(clients);
            red();
            printf("\n\nNew client registred!!");
            reset();
            pause();
            break;
        case 2:
            // List the records of type Client
            red();
            printf("\nTable containing the information of the records of type Client.\n");
            // Table Construction
            yellow();
            printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            printf("\n|    ID      NAME                 BIRTHDATE      PHONE NUMBER       ADDRESS                                  NIF             BALANCE       EMAIL                              PASSWORD            |");
            printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            reset();
            listAvailableRecords_Client(clients);
            printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            printf("\n\nTotal sum of records of type Client:");
            red();
            // this function return the amount of records in the Linked List Meios
            printf(" %d\n", countAvailableRecords_Client(clients));
            reset();
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
                saveRecords_Client(clients);
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
                
                clients = editRecord_Client(clients, id, name, bd, bm, by, phn, addr, nif, email, pass);
                saveRecords_Client(clients);
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
            showSubSubMenu_Manager_Clients(meios, clients, managers, resmeios);
            pause();
            break;
        case 6:
            clear();
            showSubMenu_Manager(meios, clients, managers, resmeios);
            break;
        }
    }
}

#pragma endregion

#pragma region Main_Function

int main()
{
    /**
     * @brief 
     * 
     */
    // Empty Linked List of type Meio
    Meio* meios = NULL;
    
    /**
     * @brief 
     * 
     */
    // Empty Linked List of type Client
    Client* clients = NULL;

    /**
     * @brief 
     * 
     */
    // Empty Linked List of type Manager
    Manager* managers = NULL;

    /**
     * @brief 
     * 
     */
    //
    resMeios* resmeios = NULL;
    
    /**
     * @brief 
     * 
     */
    //
    meios = readrecords_Meio();

    /**
     * @brief 
     * 
     */
    //
    clients = readrecords_Client();

    /**
     * @brief 
     * 
     */
    //
    managers = readrecords_Manager();

    /**
     * @brief 
     * 
     */
    // 
    resmeios = readrecords_Book(meios, clients);

    /**
     * @brief Construct a new show Menu object
     * 
     */
    //
    showMenu(meios, clients, managers, resmeios);

    /*float timediff = 0.0;

    struct periodDateTime fd;
    struct periodDateTime sd;

    printf("Enter a first date and time (dd-mm-yyyy hh:mm): ");
    scanf("%d-%d-%d %d:%d", &fd.date.day, &fd.date.month, &fd.date.year, &fd.time.hour, &fd.time.min);
    flushstdin();
    printf("Enter a second date and time (dd-mm-yyyy hh:mm): ");
    scanf("%d-%d-%d %d:%d", &sd.date.day, &sd.date.month, &sd.date.year, &sd.time.hour, &sd.time.min);
    flushstdin();

    timediff = returnTimeDiff(fd, sd);

    printf("\n\tTime Difference in hours: %.2f\n", timediff);*/

    return(0);
}

#pragma endregion