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
    int visited;
    struct Adjacencia_Registo* next;
} Adjacent;


typedef struct Grafo_Registo
{
    char vertex[TAM];
    Meio* meio;
    Client* client;
    Adjacent* adjacent;
    int visited;
    struct Grafo_Registo* next;
} Grafo;

#pragma endregion

#pragma region Exist_Records_Functions

//
int existVertex(Grafo* grafo, char vertex[]);

// 
int existEdge(Grafo* grafo, char vOrigin[], char vDestiny[]);

//
int existMeioFromLocation(Meio* meios, char loc[]);

// 
int isMeioInGrafoList(Grafo* grafo, char loc[], int idMeio);

//
int existClientFromLocation(Client* clients, char loc[]);

// 
int isClientInGrafoList(Grafo* grafo, char loc[], int idClient);

#pragma endregion

#pragma region Find_Records_Functions

// 
Grafo* findVertex(Grafo* grafo, char vertex[]);

#pragma endregion

#pragma region Create_Records_Functions

//
Grafo* createVertex(Grafo* grafo, char newID[]);

//
int createEdge(Grafo* grafo, char vOrigin[], char vDestiny[], float weight);

#pragma endregion

#pragma region Add_Records_Functions

//
int addMeiosToVertex(Grafo* grafo, Meio* meios, char loc[], int idMeio);

//
int addClientsToVertex(Grafo* grafo, Client* clients, char loc[], int idClient);

#pragma endregion

#pragma region Count_Records_Functions

//
int countAdjacentsByGeocode(Grafo* grafo, char loc[]);

//
int countMeiosByGeocode(Meio* meios, char loc[]);

//
int countClientsByGeocode(Client* clients, char loc[]);

#pragma endregion

#pragma region List_Records_Functions

//
void listAdjacentsByGeocode(Grafo* grafo, char loc[]);

//
void listMeiosByGeocode(Meio* meios, char loc[]);

//
void listClientsByGeocode(Client* clients, char loc[]);

#pragma endregion

#pragma region Save_Functions

// this function saves the Grafo records into a binary file
int saveGrafo_bin(Grafo* grafo);

// this function saves the Grafo records into a text file
int saveGrafo_txt(Grafo* grafo);

// this function saves the Adjacents records of the Grafo into a binary file
int saveAdjacent_bin(Grafo* grafo);

// this function saves the Adjacents records of the Grafo into a text file
int saveAdjacent_txt(Grafo* grafo);

// this function saves the Meios records of the Grafos into a binary file
int saveGrafoMeios_bin(Grafo* grafo);

// this function saves the Meios records of the Grafo into a text file
int saveGrafoMeios_txt(Grafo* grafo);

// this function saves the Clients records of the Grafos into a binary file
int saveGrafoClients_bin(Grafo* grafo);

// this function saves the Clients records of the Grafo into a text file
int saveGrafoClients_txt(Grafo* grafo);

#pragma endregion

#pragma region Read_Functions

// this function reads the Grafo records from a binary file
Grafo* readGrafo_bin();

// this function reads the Grafo records from a text file
Grafo* readGrafo_txt();

// this function reads the Adjacents records of the Grafo from a binary file
Grafo* readAdjacents_bin(Grafo* grafo);

// this function reads the Adjacents records of the Grafo from a text file
Grafo* readAdjacents_txt(Grafo* grafo);

// this function reads the Meios records of the Grafo from a binary file
Grafo* readGrafoMeios_bin(Grafo* grafo, Meio* meios);

// this function reads the Meios records of the Grafo from a text file
Grafo* readGrafoMeios_txt(Grafo* grafo, Meio* meios);

// this function reads the Clients records of the Grafo from a binary file
Grafo* readGrafoClients_bin(Grafo* grafo, Client* clients);

// this function reads the Clients records of the Grafo from a text file
Grafo* readGrafoClients_txt(Grafo* grafo, Client* clients);

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
