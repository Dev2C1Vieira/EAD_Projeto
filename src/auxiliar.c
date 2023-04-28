// codigo para guardar dados em arquivos de texto
int saveRecords_Meio(Meio* start)
{
    // this C code opens a file called "Registros_Medio.txt" 
    // in write mode ("w") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Text_Files/Records_Meio.txt", "w");
    // checks if the file is empty or not
    if (fp != NULL)
    {
        Meio* aux = start;
        while (aux != NULL)
        {
            // saves in the text file each field of a respective record separated by ';'
            fprintf(fp, "%d;%s;%f;%f;%f;%d;%d;%s\n", aux->code, aux->type, aux->battery, 
                aux->autonomy, aux->cost, aux->idClient, aux->status, aux->location);
            aux = aux->next; // moves to the next record
        }
        fclose(fp); // closes the text file
        return(1);
    }
    
    return(0);
}

// codigo para guardar dados em arquivos binarios
int saveRecords_Meio(Meio* start)
{
    // this C code opens a file called "Registros_Medio.bin" 
    // in write mode ("wb") and stores the file pointer in a FILE* variable called fp.
    FILE* fp = fopen("../data/Binary_Files/Records_Meio.bin", "wb");

    // checks if the file was opened correctly
    if (fp != NULL)
    {
        Meio* aux = start;
        while (aux != NULL)
        {
            // write data to binary file
            fwrite(&aux->code, sizeof(int), 1, fp);
            fwrite(aux->type, sizeof(char), strlen(aux->type)+1, fp);
            fwrite(&aux->battery, sizeof(float), 1, fp);
            fwrite(&aux->autonomy, sizeof(float), 1, fp);
            fwrite(&aux->cost, sizeof(float), 1, fp);
            fwrite(&aux->idClient, sizeof(int), 1, fp);
            fwrite(&aux->status, sizeof(int), 1, fp);
            fwrite(aux->location, sizeof(char), strlen(aux->location)+1, fp);

            aux = aux->next; // move to the next record
        }
        fclose(fp); // close the binary file
        return(1);
    }
    return(0);
}


// codigo para ler dados de arquivos de texto
Meio* readrecords_Meio() {
    int code, idclient, status;
    float bat, aut, cost;
    char type[50], loc[50];
    // creating variables to keep the information of the records in the text file

    FILE* fp = fopen("../data/Text_Files/Records_Meio.txt","r"); // opens the "Records_Meio" text file

    Meio* meios = NULL; // creates a new NULL linked list
    
    if (fp != NULL) { // checks if the text file is empty
        char line[1024];
        // the fgets function is used to read a line of text from a file and store it in a character buffer. 
        // the first argument is a pointer to the buffer that will store the line read.
        // the second argument is the buffer size. In this case, sizeof(line) returns the size of the line buffer in bytes.
        // the third argument is a pointer to the file from which the line is to be read.
        while (fgets(line, sizeof(line), fp))
        {
            // returns the information of each record and gives them to the linked list
            sscanf(line, "%d;%[^;];%f;%f;%f;%d;%d;%[^\n]\n", &code, type, &bat, &aut, &cost, &idclient, &status, loc);
            meios = insertNewRecord_Meio(meios, type, bat, aut, cost, idclient, status, loc);
            // insert the records in the linked list
        }
        fclose(fp);
    }
    return(meios);
}

// codigo para ler dados de arquivos binarios
Meio* readrecords_Meio() {
    int code, idclient, status;
    float bat, aut, cost;
    char type[50], loc[50];

    // opens the "Records_Meio" binary file
    FILE* fp = fopen("../data/Binary_Files/Records_Meio.bin","rb");

    Meio* meios = NULL; // creates a new NULL linked list

    if (fp != NULL) { // checks if the binary file is empty
        while (fread(&code, sizeof(int), 1, fp) == 1 &&
               fread(type, sizeof(char), 50, fp) == 50 &&
               fread(&bat, sizeof(float), 1, fp) == 1 &&
               fread(&aut, sizeof(float), 1, fp) == 1 &&
               fread(&cost, sizeof(float), 1, fp) == 1 &&
               fread(&idclient, sizeof(int), 1, fp) == 1 &&
               fread(&status, sizeof(int), 1, fp) == 1 &&
               fread(loc, sizeof(char), 50, fp) == 50) {

            // insert the record into the linked list
            meios = insertNewRecord_Meio(meios, type, bat, aut, cost, idclient, status, loc);
        }
        fclose(fp);
    }
    return(meios);
}

// Outro exemplo para arquivos binarios
Meio* readrecords_Meio() {
    FILE* fp = fopen("../data/Binary_Files/Records_Meio.bin","rb");

    Meio* meios = NULL; // creates a new NULL linked list

    if (fp != NULL) { // checks if the binary file is empty
        Meio current;
        while (fread(&current, sizeof(Meio), 1, fp) == 1) {

            // insert the record into the linked list
            meios = insertNewRecord_Meio(meios, current.type, current.battery, current.autonomy, 
                current.cost, current.idClient, current.status, current.location);
        }
        fclose(fp);
    }
    return(meios);
}