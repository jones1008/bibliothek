#include "addBook.h"
void addBook(Array *books)
{
    // TODO: ENTER zum Abbrechen
    char *newIsbn = "";
    int isNotAborted;
    char *isbn = calloc(1, 1);

//    printf("books used: %d\n", books->used);
//    printf("books size: %d\n", books->size);
//    printf("first book title: %s\n", books->array[0].title);

    // TODO memset variables in new call so it wont crash

    do{
//        printf("sizeof isbn: %d\n", sizeof(isbn));
        printf("ISBN-13 eingeben (13 Ziffern) ([ENTER] zum Abbrechen): ");
        getUserInput(isbn);
//        printf("isbnInput: %s\n", isbn);
//        printf("sizeof isbn: %d\n", sizeof(isbn));

        isNotAborted = !isAborted(isbn);
        if(isNotAborted){
            // if in first loop allocate the newisbn
            if(strlen(newIsbn) == 0){
                newIsbn = calloc(1, 1);
            }
    //      // realloc newIsbn and zero content from the loop before
            newIsbn = realloc(newIsbn, strlen(isbn));
            memset(newIsbn, 0, strlen(isbn));

            // delete all other characters not being a digit from isbn and add the null terminator at the end
            int j=0;
            for(int i=0; i<strlen(isbn); i++){
                if(isdigit(isbn[i])){
    //                printf("%c\n", isbn[i]);
                    newIsbn[j] = isbn[i];
                    j++;
                }
            }
            newIsbn[j] = '\0';

            if(strlen(newIsbn)!=13){
                printf("ERROR: Die ISBN muss 13 Ziffern lang sein\n");
            }
        }

//    } while(strlen(isbn)!=13);
    } while(strlen(newIsbn)!=13 && isNotAborted);

    if(isNotAborted){
        char *title = calloc(1, 1);
        printf("Titel eingeben ([ENTER] zum Abbrechen): ");
        getUserInput(title);
        // TODO: verify isbn-pattern (repeat while wrong)

        if(!isAborted(title)){
            char *author = calloc(1, 1);
            printf("Autor eingeben ([ENTER] zum Abbrechen): ");
            getUserInput(author);

            if(!isAborted(author)){
                int isNumber;
                char *numberof = calloc(1, 1);
                do{
                    printf("Anzahl Exemplare eingeben ([ENTER] zum Abbrechen): ");
                    getUserInput(numberof);

                    isNumber = 1;

                    isNotAborted = !isAborted(numberof);
                    if(isNotAborted){
                        for(int i=0;i<strlen(numberof); i++){
                            if (!isdigit(numberof[i]))
                            {
                                isNumber=0;
                                printf ("ERROR: Gib eine Nummer ein!\n");
                                break;
                            }
                        }
                    }
                } while(isNotAborted && !isNumber);

                if(isNotAborted){
                    // remove trailing and leading spaces
                    isbn = trimwhitespace(newIsbn);
                    title = trimwhitespace(title);
                    author = trimwhitespace(author);
                    // TODO: convert Umlaute to corresponding characters

                    // ask user if input was correct
                    printf("---------\n");
                    printf("ISBN  : %s\n", newIsbn);
                    printf("Titel : %s\n", title);
                    printf("Autor : %s\n", author);
                    printf("Anzahl: %s\n", numberof);
                    char *choice = calloc(1, 1);
                    char *allowedChars = "jn";
                    do{
                        printf("Sind die obigen Angaben korrekt? [J][N]: ");
                        getUserInput(choice);
                        *choice = tolower(*choice);
                    } while(wrongCharInput(choice, allowedChars));

                    printf("---------\n");
                    if(choice[0] == 'j'){
                        // TODO: in Array speichern und saveBooks()

                        // TODO: evtl in function? newBook()
                        if (books->used == books->size){
                            printf("increasing book structure\n");
                            books->size *= 2;
                            books->array = (book *)realloc(books->array, books->size * sizeof(book));
                        }
                        printf("ISBN  : %s\n", newIsbn);
                        printf("Titel : %s\n", title);
                        printf("Autor : %s\n", author);
                        printf("Anzahl: %s\n", numberof);

                        printf("strlen(newIsbn): %d\n", strlen(numberof));

                        writeStringToArrayNode(books, 'i', newIsbn);
                        writeStringToArrayNode(books, 't', title);
                        writeStringToArrayNode(books, 'a', author);
                        writeStringToArrayNode(books, 'n', numberof);
//                        writeStringToArrayNode(books, 'b', "\n");
                        writeStringToArrayNode(books, 'b', "");

                        printf("isbn  : %s\n", books->array[books->used].isbn);
                        printf("title : %s\n", books->array[books->used].title);
                        printf("author: %s\n", books->array[books->used].author);
                        printf("anzahl: %s\n", books->array[books->used].numberof);
                        printf("borrow: %s\n", books->array[books->used].borrowlist);

                        books->used = books->used+1;
                        saveBooks(books);
                    }
                    if(choice[0] == 'n'){
                        addBook(books);
                    }
                }
                freeTempString(numberof);
            }
            freeTempString(author);
        }
        freeTempString(title);
    }
    freeTempString(isbn);
}
