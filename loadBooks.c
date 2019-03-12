#include "loadBooks.h"
void loadBooks(Array *books)
{
    //https://codereview.stackexchange.com/questions/44649/dynamic-array-of-structs-in-c
    // initialize array
    int initialSize = 1;
    // Allocate initial space
    books->array = (book *)calloc(initialSize * sizeof(book), sizeof(int));
    books->used = 0;           // no elements used
    books->size = initialSize; // available nr of elements

    // read every line of the csv-file and write data to the array
    char buffer[1024];
    char *line, *records;
    char delimiter[] = ";";
    FILE *dataFile = fopen("data.csv", "r");
    if(dataFile == NULL){
        printf("ERROR: Datenbank-Datei kann nicht gelesen werden!");
    }
    while((line=fgets(buffer,sizeof(buffer),dataFile))!=NULL){
        // skip empty lines
        if(!(line[0] == '\n')){
            // initialize books structure
            // TODO: wird size tatsächlich gebraucht?
            if (books->used == books->size){
                books->size *= 2;
                books->array = (book *)realloc(books->array, books->size * sizeof(book));
            }
            records = strtok(line, delimiter);

            int index = 0;
            while(records){
    //            printf("%s", records);
                switch(index){
                    case 0:
                        // insert isbn
//                        books->array[books->used].isbn = malloc(strlen(records));
//                        strncpy(books->array[books->used].isbn, records, strlen(records));
//                        books->array[books->used].isbn[strlen(records)-1] = 0;
                        // TODO: use strncpy instead?
                        writeStringToArrayNode(books, 'i', records);
//                        books->array[books->used].isbn = (char*)malloc(strlen(records) + 1);
//                        strcpy(books->array[books->used].isbn, records);
                        break;
                    case 1:
                        // insert title
//                        books->array[books->used].title = malloc(strlen(records));
//                        strncpy(books->array[books->used].title, records, strlen(records));
//                        books->array[books->used].title[strlen(records)-1] = 0;
                        writeStringToArrayNode(books, 't', records);
//                        books->array[books->used].title = (char*)malloc(strlen(records) + 1);
//                        strcpy(books->array[books->used].title, records);
                        break;
                    case 2:
                        // insert author
//                        books->array[books->used].author = malloc(strlen(records));
//                        strncpy(books->array[books->used].title, records, strlen(records));
//                        books->array[books->used].title[strlen(records)-1] = 0;
                        writeStringToArrayNode(books, 'a', records);
//                        books->array[books->used].author = (char*)malloc(strlen(records) + 1);
//                        strcpy(books->array[books->used].author, records);
                        break;
                    case 3:
                        // insert numberof
                        writeStringToArrayNode(books, 'n', records);
//                        books->array[books->used].numberof = (char*)malloc(strlen(records) + 1);
//                        strcpy(books->array[books->used].numberof, records);
                        break;
                    case 4:
                        // insert borrowlist and delete last newline-char if there is one
                        writeStringToArrayNode(books, 'b', records);
//                        books->array[books->used].borrowlist = (char*)malloc(strlen(records) + 1);
//                        strcpy(books->array[books->used].borrowlist, records);
//                        if(books->array[books->used].borrowlist[strlen(books->array[books->used].borrowlist)-1] == '\n'){
//                            books->array[books->used].borrowlist[strlen(books->array[books->used].borrowlist)-1] = 0;
//                        }
                        break;
                }
    //            printf("%d:%s\n", index, records);
                records = strtok(NULL, delimiter);
                index++;
            }
    //        printf("\n");
            books->used++;
        }
    }
    fclose(dataFile);
}
