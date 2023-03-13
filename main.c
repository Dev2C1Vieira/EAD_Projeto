#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void getstring(char str[]) {
    do {
        gets(str);
    } while (strlen(str) == 0);
}

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
                else showSubMenu_Manager(meios, clients, managers);
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

int showSubMenu_Client(Meio* meios, Client* clients, Manager* managers) {
    int op = 1;

    while (1)
    {
        do
        {
            clear();
            reset();
            red();
            printf("  --------- Wellcome to the Client Menu ---------\n");
            reset();
            if (op < 1 || op > 6)
            {
                printf("\n  Invalid Option! [1-3]\n");
            }
            printf("\n  Here you need to choose the option you want to run\n");
            printf("\n  1. Insert a new record of type Meio!");
            printf("\n  2. List the records of type Meio!");
            printf("\n  3. Insert a new record of type Meio!");
            printf("\n  4. Insert a new record of type Meio!");
            printf("\n  5. Insert a new client!");
            printf("\n  6. Return to Main Menu.");
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
            //showSubMenu_Client();
            break;
        case 2:
            //showSubMenu_Manager();
            break;
        case 3:
            clear();
            showMenu(meios, clients, managers);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            clear();
            showMenu(meios, clients, managers);
            break;
        }
    }
}

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
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter your email: ");
            getstring(email);
            printf("Enter your password: ");
            getstring(pass);
            if (!login_Client(clients, email, pass)) {
                printf("Your information is incorrect");
            }
            else showSubMenu_Client(meios, clients, managers);
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

int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers) {
    int op = 1, cod;
    char tipo[50], loc[50];
    float bat, aut, custo;

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
                printf("\nInvalid Option! [1-3]\n");
            }
            yellow();
            printf("\n  Here you need to choose the option you want to run\n");
            reset();
            printf("\n  1. Insert a new record of type Meio!");
            printf("\n  2. List the records of type Meio!");
            printf("\n  3. Remove a record of type Meio!");
            printf("\n  4. Save the records of type Meio!");
            printf("\n  5. Read the records of type Meio!");
            printf("\n  6. Return to Main Menu.");
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
            // Insert a new record of type Meio
            yellow();
            printf("Enter the needed information!\n\n");
            reset();
            printf("Enter the code of the new record: ");
            scanf("%d", &cod);
            printf("Enter the type of the new record: ");
            getstring(tipo);
            printf("Enter the battery of the new record: ");
            scanf("%f", &bat);
            flushstdin();
            printf("Enter the autonomy of the new record: ");
            scanf("%f", &aut);
            flushstdin();
            printf("Enter the cost of the new record: ");
            scanf("%f", &custo);
            flushstdin();
            printf("Enter the location of the new record: ");
            getstring(loc);
            if (!existRecord_Meio(meios, cod)) {
                meios = insertNewRecord_Meio(meios, cod, tipo, bat, aut, custo, loc);
                red();
                printf("\n\nNew registered record!");
                reset();
            }
            else {
                red();
                printf("\n\nCan't insert the new record");
                reset();
            }
            pause();
            break;
        case 2:
            // List the records of type Meio
            red();
            printf("\nTable containing the information of the records of type Meio.\n");
            // Table Construction
            yellow();
            printf("\n+--------------------------------------------------------------------------------------------+");
            printf("\n|    CODE      TYPE               BATTERY      AUTONOMY       COST      LOCATION             |");
            printf("\n+--------------------------------------------------------------------------------------------+");
            reset();
            listRecords_Meio(meios);
            pause();
            break;
        case 3:
            // Remove a record of type Meio
            break;
        case 4:
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
        case 5:
            // Read the records of type Meio
            break;
        case 6:
            clear();
            showMenu(meios, clients, managers);
            break;
        }
    }
}

int main()
{
    Meio* meios = NULL; // Empty Linked List of type Meio
    Client* clients = NULL; // Empty Linked List of type Client
    Manager* managers = NULL; // Empty Linked List of type Manager

    meios = insertNewRecord_Meio(meios, 0001, "Bicicleta", 27.30, 180, 36.45, "Amorim");
    meios = insertNewRecord_Meio(meios, 0002, "Trotinete", 16.30, 120, 24.45, "Estela");
    meios = insertNewRecord_Meio(meios, 0003, "Mota", 21.80, 201, 57.45, "Beiriz");

    clients = insertNewRecord_Client(clients, 0001, "Pedro Carvalho", 10, 01, 2002, 911678261, "Rua das Flores, 76 Amorim", 
        729164537, 753.56, "pedro@gmail.com", "pc123456789");

    managers = insertNewRecord_Manager(managers, 1, "Tiago Silva", 05, 11, 1989, 827625413, "ola", "123");

    showMenu(meios, clients, managers);

    return(0);
}