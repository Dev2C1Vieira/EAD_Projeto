#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./include/grafos.h"


#pragma region Exist_Records_Functions

/**
 * @brief 
 * 
 * @param grafo 
 * @param vertex 
 * @return int 
 */
int existVertex(Grafo* grafo, char vertex[]) {
    while (grafo != NULL) {
        if (strcmp(grafo->vertex, fromLocationToGeocode(vertex)) == 0) return(1);
        grafo = grafo->next; 
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param vOrigin 
 * @param vDestiny 
 * @return int 
 */
int existEdge(Grafo* grafo, char vOrigin[], char vDestiny[]) {
    while (grafo != NULL) {
        if (strcmp(grafo->vertex, vOrigin) == 0) {
            Adjacent* current = grafo->adjacent;

            while (current != NULL) {
                if (strcmp(current->vertex, vDestiny) == 0) return(1);
                current = current->next;
            }
        }
        grafo = grafo->next;
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param meios 
 * @param loc 
 * @return int 
 */
int existMeioFromLocation(Meio* meios, char loc[]) {
    while (meios != NULL) {
        if ((strcmp(fromGeocodeToLocation(meios->location), loc) == 0)) return(1); // Location found in Meios list
        meios = meios->next;
    }
    return(0); // Location not found in Meios list
}

 /**
  * @brief 
  * 
  * @param grafo 
  * @param loc 
  * @param idMeio 
  * @return int 
  */
int isMeioInGrafoList(Grafo* grafo, char loc[], int idMeio) {
    Grafo* current = grafo;

    while (current != NULL) {
        if (strcmp(current->vertex, fromLocationToGeocode(loc)) == 0) {
            Meio* meiosList = grafo->meio;
            
            while (meiosList != NULL) {
                if (meiosList->code == idMeio) {
                    return(1); // this meio is already part of this vertex meios list
                }
                meiosList = meiosList->next;
            }
        }
        current = current->next;
    }
    return(0); // this meio is not yet part of this vertex meios list
}

/**
 * @brief 
 * 
 * @param clients 
 * @param loc 
 * @return int 
 */
int existClientFromLocation(Client* clients, char loc[]) {
    while (clients != NULL) {
        if ((strcmp(fromGeocodeToLocation(clients->address), loc) == 0)) return(1); // location found in Clients list
        clients = clients->next;
    }
    return(0); // location not found in Clients list
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param loc 
 * @param idClient 
 * @return int 
 */
int isClientInGrafoList(Grafo* grafo, char loc[], int idClient) {
    Grafo* current = grafo;

    while (current != NULL) {
        if (strcmp(current->vertex, fromLocationToGeocode(loc)) == 0) {
            Client* clientsList = grafo->client;
            
            while (clientsList != NULL) {
                if (clientsList->id == idClient) {
                    return(1); // this client is already part of this vertex clients list
                }
                clientsList = clientsList->next;
            }
        }
        current = current->next;
    }
    return(0); // this client is not yet part of this vertex clients list
}

#pragma endregion

#pragma region Find_Records_Functions

// 
Grafo* findVertex(Grafo* grafo, char vertex[]) {
    Grafo* currentVertex = grafo;

    while (currentVertex != NULL) {
        if (strcmp(currentVertex->vertex, vertex) == 0) {
            return(currentVertex); // vertex found
        }
        currentVertex = currentVertex->next;
    }
    return(NULL);  // vertex not found
}

#pragma endregion

#pragma region Create_Records_Functions

/**
 * @brief Create a Vertex object
 * 
 * @param grafo 
 * @param newID 
 * @param meios 
 * @return Grafo* 
 */
// 
Grafo* createVertex(Grafo* grafo, char newID[]) {
    Grafo* new = malloc(sizeof(struct Grafo_Registo));
    if (new != NULL) {
        strcpy(new->vertex, fromLocationToGeocode(newID));
        // Connects the Meio linked list to the meio field of the new vertex
        new->meio = NULL;
        //new->client = NULL;
        new->adjacent = NULL;
        new->visited = 0;
        new->next = NULL;
        
        if (grafo == NULL) {
            // the list is empty, so the new record will be the first record
            grafo = new;
        } else {
            Grafo* current = grafo;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new;
        }
        return(grafo);
    }
}

/**
 * @brief Create a Edge object
 * 
 * @param grafo 
 * @param vOrigin 
 * @param vDestiny 
 * @param weight 
 * @return int 
 */
//
int createEdge(Grafo* grafo, char vOrigin[], char vDestiny[], float weight) {
    Adjacent* new;
    while (grafo != NULL) {
        if (strcmp(grafo->vertex, fromLocationToGeocode(vOrigin)) == 0) {
            new = malloc(sizeof(struct Adjacencia_Registo));
            if (new != NULL) {
                strcpy(new, fromLocationToGeocode(vDestiny));
                new->weight = weight;
                new->visited = 0;
                new->next = NULL;

                // Encontra o último nó da lista de adjacentes
                Adjacent* last = grafo->adjacent;
                if (last == NULL) {
                    // Se a lista está vazia, o novo nó será o primeiro
                    grafo->adjacent = new;
                } else {
                    // Percorre até o último nó da lista
                    while (last->next != NULL) {
                        last = last->next;
                    }
                    // Adiciona o novo nó no final da lista
                    last->next = new;
                }
                return 1;
            } else return 0;
        } 
        grafo = grafo->next;
    }
}

#pragma endregion

#pragma region Add_Records_Functions

/**
 * @brief 
 * 
 * @param grafo 
 * @param meios 
 * @param loc 
 * @param idMeio 
 * @return int 
 */
int addMeiosToVertex(Grafo* grafo, Meio* meios, char loc[], int idMeio) {
    Meio* meio = meios;

    while (grafo != NULL) {
        if (strcmp(grafo->vertex, fromLocationToGeocode(loc)) == 0) {
            while (meio != NULL) {
                if (meio->code == idMeio) {
                    if (strcmp(grafo->vertex, meio->location) == 0) {
                        Meio* newMeio = (Meio*)malloc(sizeof(Meio));

                        newMeio->code = meio->code;   
                        strcpy(newMeio->type, meio->type);
                        newMeio->battery = meio->battery;
                        newMeio->autonomy = meio->autonomy;
                        newMeio->cost = meio->cost;
                        strcpy(newMeio->location, meio->location);
                        newMeio->status = meio->status;
                        newMeio->available = meio->available;
                        newMeio->next = NULL;

                        // Checks if the 'Meio' field of the graph is empty
                        if (grafo->meio == NULL) {
                            grafo->meio = newMeio;
                        } else {
                            // Finds the last record of the 'Meio' linked list of the graph
                            Meio* lasMeio = grafo->meio;
                            while (lasMeio->next != NULL) {
                                lasMeio = lasMeio->next;
                            }
                            // Adds the new record to the end of the linked list
                            lasMeio->next = newMeio;
                            
                        }
                        return(1);
                    } 
                    else return(-1);
                }
                meio = meio->next;
            }
        }
        grafo = grafo->next;
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param clients 
 * @param loc 
 * @param idClient 
 * @return int 
 */
int addClientsToVertex(Grafo* grafo, Client* clients, char loc[], int idClient) {
    Client* client = clients;

    while (grafo != NULL) {
        if (strcmp(grafo->vertex, fromLocationToGeocode(loc)) == 0) {
            while (client != NULL) {
                if (client->id == idClient) {
                    if (strcmp(grafo->vertex, client->address) == 0) {
                        Client* newClient = (Client*)malloc(sizeof(Client));

                        newClient->id = client->id;
                        strcpy(newClient->name, client->name);
                        newClient->birthDate = client->birthDate;
                        newClient->phoneNumber = client->phoneNumber;
                        strcpy(newClient->address, client->address);
                        newClient->nif = client->nif;
                        newClient->balance = client->balance;
                        strcpy(newClient->email, client->email);
                        strcpy(newClient->password, client->password);
                        newClient->available = client->available;
                        newClient->next = NULL;

                        // Checks if the 'Client' field of the graph is empty
                        if (grafo->client == NULL) {
                            grafo->client = newClient;
                        } else {
                            // Finds the last record of the 'Client' linked list of the graph
                            Client* lastClient = grafo->client;
                            while (lastClient->next != NULL) {
                                lastClient = lastClient->next;
                            }
                            // Adds the new record to the end of the linked list
                            lastClient->next = newClient;
                            
                        }
                        return(1); // Indicate successful addition of the client
                    } 
                    else return(-1); // Indicate that the client's address does not match the vertex
                }
                client = client->next;
            }
        }
        grafo = grafo->next;
    }
    return(0); // Indicate that the specified loc or idClient was not found in the grafo or clients
}

#pragma endregion

#pragma region Count_Records_Functions

/**
 * @brief 
 * 
 * @param grafo 
 * @return int 
 */
int countGrafoVertices(Grafo* grafo) {
    int counter = 0;

    while (grafo != NULL) {
        counter++;
        grafo = grafo->next;
    }
    return(counter);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param vertex 
 * @return int 
 */
int countAdjacentsInAVertex(Grafo* grafo, char loc[]) {
    int counter = 0;

    while (grafo != NULL) {
        if (strcmp(grafo->vertex, fromLocationToGeocode(loc)) == 0) {
            Adjacent* current = grafo->adjacent;

            while (current != NULL) {
                counter++; // 
                current = current->next;
            }
            return(counter);
        }
        grafo = grafo->next;
    }
    return(counter);
}


int countMeiosInAVertex(Grafo* grafo, char loc[]) {
    int counter = 0;

    while (grafo != NULL) {
        if (strcmp(grafo->vertex, fromLocationToGeocode(loc)) == 0) {
            Meio* current = grafo->meio;

            while (current != NULL) {
                counter++; // 
                current = current->next;
            }
            return(counter);
        }
        grafo = grafo->next;
    }
    return(counter);
}


int countClientsInAVertex(Grafo* grafo, char loc[]) {
    int counter = 0;

    while (grafo != NULL) {
        if (strcmp(grafo->vertex, fromLocationToGeocode(loc)) == 0) {
            Client* current = grafo->client;

            while (current != NULL) {
                counter++; // 
                current = current->next;
            }
            return(counter);
        }
        grafo = grafo->next;
    }
    return(counter);
}


int countMeiosByGeocode(Meio* meios, char loc[]) {
    int counter = 0;

    while (meios != NULL) {
        if (strcmp(meios->location, fromLocationToGeocode(loc)) == 0) counter++;
        meios = meios->next;
    }
    return(counter);
}


int countClientsByGeocode(Client* clients, char loc[]) {
    int counter = 0;

    while (clients != NULL) {
        if (strcmp(clients->address, fromLocationToGeocode(loc)) == 0) counter++;
        clients = clients->next;
    }
    return(counter);
}

#pragma endregion

#pragma region List_Records_Functions

/**
 * @brief 
 * 
 * @param grafo 
 */
void listGrafoVertices(Grafo* grafo) {
    Grafo* grafoList = grafo;

    if (grafoList == NULL) {
        printf("\n|                               |");
        printf("\n|     There are no vertices!    |");
        printf("\n|                               |");
    }  

    while (grafoList != NULL) {
        // prints the informations of the record in the console
        printf("\n|     %-22s    |", fromGeocodeToLocation(grafoList->vertex));
        grafoList = grafoList->next;
    }
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param vertex 
 */
void listAdjacentsInAVertex(Grafo* grafo, char loc[]) {
    Grafo* current = grafo;
    
    while (current != NULL) {
        if (strcmp(current->vertex, fromLocationToGeocode(loc)) == 0) {
            Adjacent* currentAdj = current->adjacent;
    
            if (currentAdj == NULL) {
                printf("\n|                                                       |");
                printf("\n| There are no adjacents vertices added to this vertex! |");
                printf("\n|                                                       |");
            }  

            while (currentAdj != NULL) {
                // prints the informations of the record in the console
                printf("\n|     %-33s %-12.2f    |", fromGeocodeToLocation(currentAdj->vertex), currentAdj->weight);
                currentAdj = currentAdj->next;
            }
        }
        current = current->next;
    }
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param loc 
 */
void listMeiosInAVertex(Grafo* grafo, char loc[]) {
    Grafo* current = grafo;

    while (current != NULL) {
        if (strcmp(current->vertex, fromLocationToGeocode(loc)) == 0) {
            Meio* currentMeio = current->meio;
    
            if (currentMeio == NULL) {
                printf("\n|                                                                                               |");
                printf("\n|                           There are no Meios added to this vertex!                            |");
                printf("\n|                                                                                               |");
            } 
            
            while (currentMeio != NULL) {
                // 
                printf("\n|     %-8d %-20s %-12.2f %-14.2f %-11.2f %-17s   |", currentMeio->code, currentMeio->type, 
                    currentMeio->battery, currentMeio->autonomy, currentMeio->cost, fromGeocodeToLocation(currentMeio->location));

                currentMeio = currentMeio->next;
            }
        }
        current = current->next;
    }
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param loc 
 */
void listClientsInAVertex(Grafo* grafo, char loc[]) {
    Grafo* current = grafo;

    while (current != NULL) {
        if (strcmp(current->vertex, fromLocationToGeocode(loc)) == 0) {
            Client* currentClient = current->client;
                                        
            if (currentClient == NULL) {
                printf("\n|                                                                                                                                                                   |");
                printf("\n|                                                            There are no Clients added to this vertex!                                                             |"); 
                printf("\n|                                                                                                                                                                   |");
            }
            
            while (currentClient != NULL) {
                // 
                printf("\n|    %-7d %-20s %-0.2d-%-0.02d-%-8.4d %-18.09d %-20s %-15.09d %-13.2f %-29s %-11s    |", 
                    currentClient->id, currentClient->name, currentClient->birthDate.day, currentClient->birthDate.month, 
                    currentClient->birthDate.year, currentClient->phoneNumber, fromGeocodeToLocation(currentClient->address), currentClient->nif, 
                    currentClient->balance, currentClient->email, currentClient->password);

                currentClient = currentClient->next;
            }
        }
        current = current->next;
    }
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param vertex 
 */
void listMeiosByGeocode(Meio* meios, char loc[]) {
    int count = 0;
    
    while (meios != NULL) {
        if (strcmp(meios->location, fromLocationToGeocode(loc)) == 0) {
            count++;
            // 
            printf("\n|     %-8d %-20s %-12.2f %-14.2f %-11.2f %-17s   |", meios->code, meios->type, 
                    meios->battery, meios->autonomy, meios->cost, fromGeocodeToLocation(meios->location));
        }
        meios = meios->next;
    }

    if (count == 0) {
        printf("\n|                                                                                               |");
        printf("\n|                          There are no Meios listed in this location!                          |");
        printf("\n|                                                                                               |");
    }
}

/**
 * @brief 
 * 
 * @param clients 
 * @param loc 
 */
void listClientsByGeocode(Client* clients, char loc[]) {
    int count = 0;
    
    while (clients != NULL) {
        if (strcmp(clients->address, fromLocationToGeocode(loc)) == 0) {
            count++;
            // 
            printf("\n|    %-7d %-20s %-0.2d-%-0.02d-%-8.4d %-18.09d %-20s %-15.09d %-13.2f %-29s %-11s    |", 
                clients->id, clients->name, clients->birthDate.day, clients->birthDate.month, 
                clients->birthDate.year, clients->phoneNumber, fromGeocodeToLocation(clients->address), clients->nif, 
                clients->balance, clients->email, clients->password);
        }
        clients = clients->next;
    }

    if (count == 0) {
        printf("\n|                                                                                                                                                                   |");
        printf("\n|                                                           There are no Clients listed in this location!                                                           |"); 
        printf("\n|                                                                                                                                                                   |");
    }
}

#pragma endregion

#pragma region Save_Functions

/**
 * @brief 
 * 
 * @param grafo 
 * @return int 
 */
int saveGrafo_bin(Grafo* grafo) {
    // this C code opens a file called "Grafo.bin" 
    // in write mode ("wb") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo.bin", "wb"); // Open file in binary write mode
    if (fp != NULL)
    {
        Grafo* aux = grafo;
        while (aux != NULL)
        {
            // Write the entire struct to the binary file
            fwrite(aux, sizeof(Grafo), 1, fp);
            aux = aux->next; // Move to the next record
        }
        fclose(fp); // Close the binary file
        return(1);
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @return int 
 */
int saveGrafo_txt(Grafo* grafo) {
    // this C code opens a file called "Grafo.txt" 
    // in write mode ("w") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Text_Files/Grafo_Files/Grafo.txt", "w");
    // checks if the file is empty or not
    if (fp != NULL)
    {
        Grafo* aux = grafo;
        while (aux != NULL) {
            fprintf(fp, "%s\n", fromGeocodeToLocation(aux->vertex));
            aux = aux->next;
        }
        fclose(fp); // closes the text file
        return(1);
    }
    return(0);
}

// erro, try to fix it
/**
 * @brief 
 * 
 * @param grafo 
 * @return int 
 */
int saveAdjacent_bin(Grafo* grafo) {
    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo_Adjacents.bin", "wb");

    if (fp != NULL) {
        Grafo* aux = grafo;
        while (aux != NULL) {
            Adjacent* adj = aux->adjacent;

            if (adj != NULL) {
                while (adj != NULL) {
                    fwrite(aux->vertex, sizeof(char), TAM, fp);
                    fwrite(adj->vertex, sizeof(char), TAM, fp);
                    fwrite(&adj->weight, sizeof(float), 1, fp);
                    adj = adj->next;
                }
            }
            aux = aux->next;
        }

        fclose(fp);
        return(1);
    }
    return(0);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @return int 
 */
int saveAdjacent_txt(Grafo* grafo) {
    // this C code opens a file called "Grafo.txt" 
    // in write mode ("w") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Text_Files//Grafo_Files/Grafo_Adjacents.txt", "w");
    // checks if the file is empty or not
    if (fp != NULL)
    {
        Grafo* aux = grafo;
        while (aux != NULL) {
            Adjacent* adj = aux->adjacent;

            if (adj != NULL) {
                while (adj != NULL) {
                    fprintf(fp, "%s;%s;%.2f\n", fromGeocodeToLocation(aux->vertex), fromGeocodeToLocation(adj->vertex), adj->weight);
                    adj = adj->next;
                }
            }
            aux = aux->next;
        }
        fclose(fp); // closes the text file
        return(1);
    }
    return(0);
}
 
 /**
 * @brief 
 * 
 * @param grafo 
 * @return int 
 */
int saveGrafoMeios_bin(Grafo* grafo) {
    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo_Meios.bin", "wb");

    if (fp != NULL) {
        Grafo* currentGrafo = grafo;

        while (currentGrafo != NULL) {
            fwrite(currentGrafo->vertex, sizeof(char), TAM, fp);

            if (currentGrafo->meio == NULL) {
                int meioCode = -1;
                fwrite(&meioCode, sizeof(int), 1, fp); // Writes -1 if there is no means at the vertex
            } else {
                Meio* currentMeio = currentGrafo->meio;
                while (currentMeio != NULL) {
                    fwrite(&(currentMeio->code), sizeof(int), 1, fp);
                    currentMeio = currentMeio->next;
                }
            }
            currentGrafo = currentGrafo->next;
        }

        fclose(fp);
        return(1);
    }

    return(0);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @return int 
 */
int saveGrafoMeios_txt(Grafo* grafo) {
    FILE* fp = fopen("../data/Text_Files/Grafo_Files/Grafo_Meios.txt", "w");

    if (fp != NULL) {
        Grafo* currentGrafo = grafo;

        while (currentGrafo != NULL) {
            fprintf(fp, "%s;", fromGeocodeToLocation(currentGrafo->vertex));

            if (currentGrafo->meio == NULL) {
                fprintf(fp, "NULL"); // Writes "NULL" if there is no means at the vertex
            } else {
                Meio* currentMeio = currentGrafo->meio;
                while (currentMeio != NULL) {
                    fprintf(fp, "%d;", currentMeio->code);
                    currentMeio = currentMeio->next;
                }
            }
            fprintf(fp, "\n");

            currentGrafo = currentGrafo->next;
        }
        fclose(fp);
        return(1);
    }
    return(0);
}


int saveGrafoClients_bin(Grafo* grafo) {
    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo_Clients.bin", "wb");

    if (fp != NULL) {
        Grafo* currentGrafo = grafo;

        while (currentGrafo != NULL) {
            fwrite(currentGrafo->vertex, sizeof(char), TAM, fp);

            if (currentGrafo->client == NULL) {
                int clientID = -1;
                fwrite(&clientID, sizeof(int), 1, fp); // Writes -1 if there is no means at the vertex
            } else {
                Client* currentClient = currentGrafo->client;
                while (currentClient != NULL) {
                    fwrite(&(currentClient->id), sizeof(int), 1, fp);
                    currentClient = currentClient->next;
                }
            }
            currentGrafo = currentGrafo->next;
        }

        fclose(fp);
        return(1);
    }

    return(0);
}


int saveGrafoClients_txt(Grafo* grafo) {
    FILE* fp = fopen("../data/Text_Files/Grafo_Files/Grafo_Clients.txt", "w");

    if (fp != NULL) {
        Grafo* currentGrafo = grafo;

        while (currentGrafo != NULL) {
            fprintf(fp, "%s;", fromGeocodeToLocation(currentGrafo->vertex));

            if (currentGrafo->client == NULL) {
                fprintf(fp, "NULL"); // Writes "NULL" if there is no means at the vertex
            } else {
                Client* currentClient = currentGrafo->client;
                while (currentClient != NULL) {
                    fprintf(fp, "%d;", currentClient->id);
                    currentClient = currentClient->next;
                }
            }
            fprintf(fp, "\n");

            currentGrafo = currentGrafo->next;
        }
        fclose(fp);
        return(1);
    }
    return(0);
}

#pragma endregion

#pragma region Read_Functions

/**
 * @brief 
 * 
 * @return Grafo* 
 */
Grafo* readGrafo_bin() {
    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo.bin", "rb"); // Open file in binary read mode
    Grafo* grafo = NULL; // Create a new NULL linked list
    if (fp != NULL) {
        while (1) {
            Grafo* new = (Grafo*)malloc(sizeof(Grafo));
            // Read each struct from the binary file
            size_t result = fread(new, sizeof(Grafo), 1, fp);
            if (result != 1) {
                free(new); // Free the dynamically allocated memory
                break; // Exit the loop if there are no more records to read
            }
            // Insert the read record into the linked list
            grafo = createVertex(grafo, fromGeocodeToLocation(new->vertex));
        }

        fclose(fp); // Close the binary file
    }
    return(grafo);
}

/**
 * @brief 
 * 
 * @return Grafo* 
 */
Grafo* readGrafo_txt() {
    char vertex[TAM];
    // creating variables to keep the information of the records in the text file

    FILE* fp = fopen("../data/Text_Files/Grafo_Files/Grafo.txt","r"); // opens the "Records_Meio" text file

    Grafo* grafo = NULL; // creates a new NULL linked list

    if (fp != NULL) { // checks if the text file is empty
        char line[1024];
        // the fgets function is used to read a line of text from a file and store it in a character buffer. 
        // the first argument is a pointer to the buffer that will store the line read.
        // the second argument is the buffer size. In this case, sizeof(line) returns the size of the line buffer in bytes.
        // the third argument is a pointer to the file from which the line is to be read.
        while (fgets(line, sizeof(line), fp))
        {
            // returns the information of each record and gives them to the linked list
            sscanf(line, "%[^\n]\n", vertex);
            grafo = createVertex(grafo, vertex);
            // insert the records in the linked list
        }
        fclose(fp);
    }
    return(grafo);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @return Grafo* 
 */
Grafo* readAdjacents_bin(Grafo* grafo) {
    char vOrigin[TAM], vDestiny[TAM];
    float weight = 0.0;

    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo_Adjacents.bin", "rb");

    if (fp != NULL) {
        while (fread(vOrigin, sizeof(char), TAM, fp) == TAM) {
            fread(vDestiny, sizeof(char), TAM, fp);
            fread(&weight, sizeof(float), 1, fp);

            createEdge(grafo, vOrigin, vDestiny, weight);
        }

        fclose(fp);
    }
    return(grafo);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @return Grafo* 
 */
// Mais tarde tentar arranjar .bin readFile
Grafo* readAdjacents_txt(Grafo* grafo) {
    char vOrigin[TAM], vDestiny[TAM];
    float weight = 0.0;
    // creating variables to keep the information of the records in the text file

    FILE* fp = fopen("../data/Text_Files//Grafo_Files/Grafo_Adjacents.txt","r"); // opens the "Records_Meio" text file
    
    if (fp != NULL) { // checks if the text file is empty
        char line[1024];
        // the fgets function is used to read a line of text from a file and store it in a character buffer. 
        // the first argument is a pointer to the buffer that will store the line read.
        // the second argument is the buffer size. In this case, sizeof(line) returns the size of the line buffer in bytes.
        // the third argument is a pointer to the file from which the line is to be read.
        while (fgets(line, sizeof(line), fp))
        {
            // returns the information of each record and gives them to the linked list
            sscanf(line, "%[^;];%[^;];%f\n", vOrigin, vDestiny, &weight);
            createEdge(grafo, vOrigin, vDestiny, weight);
        }
        fclose(fp);
    }
    return(grafo);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param meios 
 * @return Grafo* 
 */
Grafo* readGrafoMeios_bin(Grafo* grafo, Meio* meios) {
    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo_Meios.bin", "rb");

    if (fp != NULL) {
        char vertex[TAM];

        while (fread(vertex, sizeof(vertex), 1, fp) == 1) {
            int meioCount;
            fread(&meioCount, sizeof(meioCount), 1, fp);

            Grafo* currentVertex = findVertex(grafo, vertex);

            if (currentVertex != NULL) {
                for (int i = 0; i < meioCount; i++) {
                    int meioId;
                    fread(&meioId, sizeof(meioId), 1, fp);

                    // Adds the meio to the vertex in the graph
                    addMeiosToVertex(grafo, meios, currentVertex->vertex, meioId);
                }
            }
        }
        fclose(fp);
    }
    return(grafo);
}

/**
 * @brief 
 * 
 * @param grafo 
 * @param meios 
 * @return Grafo* 
 */
Grafo* readGrafoMeios_txt(Grafo* grafo, Meio* meios) {
    FILE* fp = fopen("../data/Text_Files/Grafo_Files/Grafo_Meios.txt", "r");

    if (fp != NULL) {
        char line[1024];

        while (fgets(line, sizeof(line), fp)) {
            char vertex[TAM];
            char* meioToken;

            // Extract the vertex of the line
            sscanf(line, "%[^;]", vertex);

            // Find the corresponding vertex in the graph
            Grafo* currentVertex = findVertex(grafo, vertex); // possivel erro em vertex, talvez 'fromlocationtogeocode'

            if (currentVertex != NULL) {
                // Extracts the media from the line
                meioToken = strtok(line, ";"); // Ignores the vertex field
                meioToken = strtok(NULL, ";"); // Jump to the first meio

                while (meioToken != NULL) {
                    int meioId = atoi(meioToken);

                    // Adds the meio to the vertex in the graph
                    addMeiosToVertex(grafo, meios, currentVertex->vertex, meioId);

                    meioToken = strtok(NULL, ";"); // Jump to the next meio
                }
            }
        }
        fclose(fp);
    }
    return(grafo);
}


Grafo* readGrafoClients_bin(Grafo* grafo, Client* clients) {
    FILE* fp = fopen("../data/Binary_Files/Grafo_Files/Grafo_Clients.bin", "rb");

    if (fp != NULL) {
        char vertex[TAM];

        while (fread(vertex, sizeof(vertex), 1, fp) == 1) {
            int clientCount;
            fread(&clientCount, sizeof(clientCount), 1, fp);

            Grafo* currentVertex = findVertex(grafo, vertex);

            if (currentVertex != NULL) {
                for (int i = 0; i < clientCount; i++) {
                    int clientID;
                    fread(&clientID, sizeof(clientID), 1, fp);

                    // Adds the client to the vertex in the graph
                    addClientsToVertex(grafo, clients, currentVertex->vertex, clientID);
                }
            }
        }
        fclose(fp);
    }
    return(grafo);
}


Grafo* readGrafoClients_txt(Grafo* grafo, Client* clients) {
    FILE* fp = fopen("../data/Text_Files/Grafo_Files/Grafo_Clients.txt", "r");

    if (fp != NULL) {
        char line[1024];

        while (fgets(line, sizeof(line), fp)) {
            char vertex[TAM];
            char* clientToken;

            // Extract the vertex of the line
            sscanf(line, "%[^;]", vertex);

            // Find the corresponding vertex in the graph
            Grafo* currentVertex = findVertex(grafo, vertex); // possivel erro em vertex, talvez 'fromlocationtogeocode'

            if (currentVertex != NULL) {
                // Extracts the media from the line
                clientToken = strtok(line, ";"); // Ignores the vertex field
                clientToken = strtok(NULL, ";"); // Jump to the first meio

                while (clientToken != NULL) {
                    int clientID = atoi(clientToken);

                    // Adds the client to the vertex in the graph
                    addClientsToVertex(grafo, clients, currentVertex->vertex, clientID);

                    clientToken = strtok(NULL, ";"); // Jump to the next meio
                }
            }
        }
        fclose(fp);
    }
    return(grafo);
}

#pragma endregion
