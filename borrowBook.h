#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "structure.h"
#include "saveBooks.h"
#include "search.h"

void borrowBook(Array *books);
void actualBorrowBook(Array *books, book *book);

#endif
