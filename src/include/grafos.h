#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

#pragma region Structs

// Creation of data structs

typedef struct Adjacencia_Registo
{
    char vertex[TAM];
    float weight;
    struct Adjacencia_Registo* next;
} Adjacent;


typedef struct Grafo_Registo
{
    char vertex[TAM];
    Meio* meio;
    Client* client;
    Adjacent* adjacent;
    struct Grafo_Registo* next;
} Grafo;

#pragma endregion

#pragma region Grafo_Functions

//
int existVertex(Grafo* grafo, char vertex[]);

//
Grafo* createVertex(Grafo* grafo, char newID[]);

//
Grafo* createEdge(Grafo* grafo, char vOrigin[], char vDestiny[], float weight);

//
int countAdjacentsByGeocode(Grafo* grafo, char vertex[]);

//
void listAdjacentsByGeocode(Grafo* grafo, char vertex[]);

// 
void listPerDistance(Grafo grafo, float distance, char location[]);

//
//void listGrafo(Grafo* grafo);

// 
int saveGrafo(Grafo* grafo);

// 
int saveAdjacent(Grafo* grafo);

// 
Grafo* readGrafo();

// 
Grafo* readAdjacents(Grafo* grafo);

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
int loop_Client_Login(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
//
int loop_Manager_Login(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

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
int Manager_Meios_Loop(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

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
int showSubSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

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
int Manager_Clients_Loop(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

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
int showSubSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

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
int showMenu(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param manager 
 * @return int 
 */
// this client menu that allows the client to manipulate the records of reservations of Means
int showSubMenu_Client(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

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
int showSubOthersMenu_Client(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this client sub menu that allows the client to log in if he already has one, or to create one otherwise
int showSubSubMenu_Client(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this manager menu that allows the manager to choose if he wants to manipulate Meio records or Clients records
int showSubMenu_Manager(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this client menu that allows the manager to manipulate the records of reservations of Means
int showSubMenu_Manager_Meios(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @return int 
 */
// this client menu that allows the manager to manipulate the records of Clients
int showSubMenu_Manager_Clients(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);

/**
 * @brief 
 * 
 * @param meios 
 * @param clients 
 * @param managers 
 * @param resmeios 
 * @param grafo 
 * @return int 
 */
// 
int showSubMenu_Manager_Grafos(Meio* meios, Client* clients, Manager* managers, resMeios* resmeios, Grafo* grafo);


#pragma endregion
