#include "searchBooks.h"

void searchBooks(Array *books)
{
    char *menuHeader = "BUCH SUCHEN";
    printMenuHeader(menuHeader);

    // get user search input
    char *searchString = calloc(1, 1);
    // TODO: Benutzer die M�glichkeit geben, es abzubrechen (nur ENTER?)
    // TODO: Benutzer die M�glichkeit geben, erneut zu suchen, ohne zum Men� zur�ckkehren zu m�ssen
    getUserInput(searchString, "Suchtext eingeben (IBSN, Buchtitel, Buchautor):");

    // pass searchString to the search-function
    foundBooks foundBooks;
    search(books, &foundBooks, searchString);

    // loop over foundBooks
    printf("\n");
    if(foundBooks.size > 0){
        // TODO: pagination when more than 4 books
        for(int i=0; i<foundBooks.size; i++){
            printf("Autor    : %s\n", foundBooks.array[i]->author);
            printf("Titel    : %s\n", foundBooks.array[i]->title);
            printf("ISBN     : %s\n", foundBooks.array[i]->isbn);
            printf("Anzahl   : %s\n", foundBooks.array[i]->numberof);
            printf("Ausleiher: %s\n", foundBooks.array[i]->borrowlist);
            // add Line if it isn't the last found book
            if(i+1<foundBooks.size){
                printf("---------\n");
            }
        }
        // TODO: Abspr�nge zum Bearbeiten/Ausleihen etc. hier einbauen (switch case)?
    } else{
        printf("Keine B%ccher mit '%s' gefunden\n", ue, searchString);
    }
    printf("\n");

    // free searchString allocation
    freeTempString(searchString);

    // TODO: vielleicht zusammen in eine Function?
    showReturnToMenu();
    printMenuEnding(strlen(menuHeader));
}

