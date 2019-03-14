#include "addBook.h"
void addBook(Bib *bib)
{
//    char *newIsbn = "";
    int isNotAborted;
    char isbn[BUFFERSIZE];

    do{
        printf("ISBN-13 eingeben (13 Ziffern) ([ENTER] zum Abbrechen): ");
        getUserInput(isbn);

        isNotAborted = !isAborted(isbn);
        if(isNotAborted){
            // if in first loop allocate the newisbn
//            if(strlen(newIsbn) == 0){
//                newIsbn = calloc(1, 1);
//            }
    //      // realloc newIsbn and zero content from the loop before
//            newIsbn = realloc(newIsbn, (strlen(isbn)+1)*sizeof(char));
//            memset(isbn, 0, strlen(isbn));

            // delete all other characters not being a digit from isbn and add the null terminator at the end
            int j=0;
            for(int i=0; i<strlen(isbn); i++){
                if(isdigit(isbn[i])){
                    isbn[j] = isbn[i];
                    j++;
                }
            }
            isbn[j] = '\0';
            printf("isbn: %s\n", isbn);

            if(strlen(isbn)!=13){
                printf("ERROR: Die ISBN muss 13 Ziffern lang sein\n");
            }
        }
    } while(strlen(isbn)!=13 && isNotAborted);

    if(isNotAborted){
        char title[BUFFERSIZE];
        printf("Titel eingeben ([ENTER] zum Abbrechen): ");
        getUserInput(title);

        if(!isAborted(title)){
            char author[BUFFERSIZE];
            printf("Autor eingeben ([ENTER] zum Abbrechen): ");
            getUserInput(author);

            if(!isAborted(author)){
                int isNumber;
                char numberof[BUFFERSIZE];
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
//                    // remove trailing and leading spaces
//                    isbn = trimwhitespace(newIsbn);
//                    title = trimwhitespace(title);
//                    author = trimwhitespace(author);
//                    // convert Umlaute to corresponding characters
//                    title = replaceUmlauts(title);
//                    author = replaceUmlauts(author);

                    // remove trailing and leading spaces

                    // funktioniert nicht, wenn whitespace vorne ist
                    trimwhitespace(isbn);
                    trimwhitespace(title);
                    trimwhitespace(author);
                    // convert Umlaute to corresponding characters
                    replaceUmlauts(title);
                    replaceUmlauts(author);

                    // ask user if input was correct
                    printf("---------\n");
                    printf("ISBN  : %s\n", isbn);
                    printf("Titel : %s\n", title);
                    printf("Autor : %s\n", author);
                    printf("Anzahl: %s\n", numberof);
                    char choice[BUFFERSIZE];
                    char *allowedChars = "jn";
                    do{
                        printf("Sind die obigen Angaben korrekt? [J][N]: ");
                        getUserInput(choice);
                        *choice = tolower(*choice);
                    } while(wrongCharInput(choice, allowedChars));

                    printf("---------\n");
                    if(choice[0] == 'j'){
                        // create new Book array and adding information to this new added book-array-element
                        newBook(bib);
                        printf("ISBN  : %s\n", isbn);
                        printf("Titel : %s\n", title);
                        printf("Autor : %s\n", author);
                        printf("Anzahl: %s\n", numberof);

                        writeStringToArrayNode(bib, 'i', isbn);
                        writeStringToArrayNode(bib, 't', title);
                        writeStringToArrayNode(bib, 'a', author);
                        writeStringToArrayNode(bib, 'n', numberof);
                        writeStringToArrayNode(bib, 'b', "");

//                        printf("isbn  : %s\n", bib->array[bib->used].isbn);
//                        printf("title : %s\n", bib->array[bib->used].title);
//                        printf("author: %s\n", bib->array[bib->used].author);
//                        printf("anzahl: %s\n", bib->array[bib->used].numberof);
//                        printf("borrow: %s\n", bib->array[bib->used].borrowlist);

                        // increase bib-used-parameter
//                        printf("bib used: %d", bib->used);
                        bib->used = bib->used+1;
//                        printf("books used: %d", bib->used);

                        // save bib to text-file
                        saveBooks(bib);
                    }
                    if(choice[0] == 'n'){
                        addBook(bib);
                    }
                }
//                freeTempString(numberof);
            }
//            freeTempString(author);
        }
//        freeTempString(title);
    }
//    freeTempString(isbn);
}
