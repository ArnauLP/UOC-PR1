#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cinema.h"
#include "../include/purchase.h"
#include "../include/movie.h"

/* The content of the fields of the purchase structure is written into the string str */
void getPurchaseStr(tPurchase purchase, int maxSize, char *str) {
    char tempStr[MAX_LINE];
    int i;

    /* Build the string */
    snprintf(str, maxSize - 1, "%d %d %d %d %d %.2f",
             (int) purchase.cinemaId, (int) purchase.screenId, (int) purchase.sessionId, purchase.purchasedSeats,
             (int) purchase.assignedSeats, purchase.price);

    if (purchase.assignedSeats) {
        for (i = 0; i < purchase.purchasedSeats; i++) {
            strcpy(tempStr, str);
            snprintf(str, maxSize - 1, "%s %d %d", tempStr, purchase.seats[i].row, purchase.seats[i].seatInRow);
        }
    }
}

void initPurchase(tPurchase *purchase) {
    int i;

    purchase->cinemaId = NO_CINEMA;
    purchase->screenId = NO_SCREEN;
    purchase->sessionId = NO_SESSION;
    purchase->assignedSeats = 0;
    purchase->price = 0.0;
    purchase->purchasedSeats = 0;
    for (i = 0; i < MAX_SEATS_PER_PURCHASE; i++) {
        purchase->seats[i].row = NO_ROW;
        purchase->seats[i].seatInRow = NO_SEAT_IN_ROW;
    }
}

tSeat seats[MAX_SEATS_PER_PURCHASE];
float price;

bool purchaseDataIsCorrect(tAppData appData, tPurchase purchase) {
    bool isCorrect = false;
    int pCinema, pScreen, pSession;

    pCinema = cinemaTableFind(appData.cinemas, purchase.cinemaId);
    if (pCinema != NO_CINEMA) {
        pScreen = screenTableFind(appData.cinemas.table[pCinema - 1].screens, purchase.screenId);
        if (pScreen != NO_SCREEN) {
            pSession = sessionTableFind(appData.cinemas.table[pCinema - 1].screens.table[pScreen - 1].sessions,
                                        purchase.sessionId);
            isCorrect = pSession != NO_SESSION;
        }
    }

    return isCorrect;
}

void createPurchase(tPurchase *purchase, tCinemaId cinemaId, tScreenId screenId, tSessionId sessionId,
                    int number, int selectedRow, int selectedSeat) {
    int i;

    initPurchase(purchase);
    purchase->cinemaId = cinemaId;
    purchase->screenId = screenId;
    purchase->sessionId = sessionId;
    purchase->purchasedSeats = number;
    purchase->assignedSeats = (selectedRow != NO_ROW) && (selectedSeat != NO_SEAT_IN_ROW);
    if (purchase->assignedSeats) {
        for (i = 0; i < number; i++) {
            purchase->seats[i].row = selectedRow;
            purchase->seats[i].seatInRow = selectedSeat + i;
        }
    }
    purchase->price = number *= PRICE_PER_TICKET;
}

/* The content of the string str is parsed into the fields of the purchase structure */
void getPurchaseObject(const char *str, tPurchase *purchase) {
    int i, row, seatInRow, auxCinemaId, auxScreenId, auxSessionId, auxAssignedSeats;
    char buffer[MAX_LINE];

    /* clear previous purchase data */
    initPurchase(purchase);

    /* read purchase data */
    sscanf(str, "%d %d %d %d %d %f %[^\n]s",
           &auxCinemaId, &auxScreenId, &auxSessionId, &purchase->purchasedSeats,
           &auxAssignedSeats, &purchase->price, buffer);

    purchase->cinemaId = (tCinemaId) auxCinemaId;
    purchase->screenId = (tScreenId) auxScreenId;
    purchase->sessionId = (tSessionId) auxSessionId;
    if (auxAssignedSeats > 0)
        purchase->assignedSeats = true;
    else
        purchase->assignedSeats = false;

    if (purchase->assignedSeats) {
        for (i = 0; i < purchase->purchasedSeats; i++) {
            sscanf(buffer, "%d %d %[^\n]s", &row, &seatInRow, buffer);
            purchase->seats[i].row = row;
            purchase->seats[i].seatInRow = seatInRow;
        }
    }
}

void purchaseCpy(tPurchase *dst, tPurchase src) {
    int i;

    dst->cinemaId = src.cinemaId;
    dst->screenId = src.screenId;
    dst->sessionId = src.sessionId;
    dst->assignedSeats = src.assignedSeats;
    dst->price = src.price;
    dst->purchasedSeats = src.purchasedSeats;
    for (i = 0; i < MAX_SEATS_PER_PURCHASE; i++) {
        dst->seats[i].row = src.seats[i].row;
        dst->seats[i].seatInRow = src.seats[i].seatInRow;
    }
}

int purchaseCmp(tPurchase p1, tPurchase p2) {
    int result = 0;

    if (p1.cinemaId > p2.cinemaId)
        result = 1;
    else if (p1.cinemaId < p2.cinemaId)
        result = -1;
    else {
        if (p1.screenId > p2.screenId)
            result = 1;
        else if (p1.screenId < p2.screenId)
            result = -1;
        else {
            if (p1.sessionId > p2.sessionId)
                result = 1;
            else if (p1.sessionId < p2.sessionId)
                result = -1;
            else {
                if (p1.purchasedSeats > p2.purchasedSeats)
                    result = 1;
                else if (p1.purchasedSeats < p2.purchasedSeats)
                    result = -1;
                else {
                    if (p1.price > p2.price)
                        result = 1;
                    else if (p1.price < p2.price)
                        result = -1;
                }
            }
        }
    }

    return result;
}

void purchaseTableInit(tPurchaseTable *purchasesTable) {

    purchasesTable->nPurchases = 0;
}

void purchaseTableAdd(tPurchaseTable *tabPurchases, tPurchase purchase, tError *retVal) {

    *retVal = OK;

    /* Check if there enough space for the new purchase */
    if (tabPurchases->nPurchases >= MAX_PURCHASES)
        *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new purchase to the end of the table */
        purchaseCpy(&tabPurchases->table[tabPurchases->nPurchases], purchase);
        tabPurchases->nPurchases++;
    }
}

void purchaseTableSave(tPurchaseTable tabPurchases, const char *filename, tError *retVal) {

    *retVal = OK;

    FILE *fout = NULL;
    int i;
    char str[MAX_LINE];

    /* Open the output file */
    if ((fout = fopen(filename, "w")) == 0) {
        *retVal = ERR_CANNOT_WRITE;
    } else {
        /* Save general purchase data to the file */
        for (i = 0; i < tabPurchases.nPurchases; i++) {
            getPurchaseStr(tabPurchases.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }

        /* Close the file */
        fclose(fout);
    }
}

void purchaseTableLoad(tPurchaseTable *tabPurchases, const char *filename, tError *retVal) {
    char line[MAX_LINE];
    tPurchase newPurchase;
    FILE *fin = NULL;
    *retVal = OK;

    /* Initialize the output table */
    purchaseTableInit(tabPurchases);

    /* Open the input file */
    if ((fin = fopen(filename, "r")) != NULL) {

        /* Read all the purchases */
        while (!feof(fin) && tabPurchases->nPurchases < MAX_PURCHASES) {
            /* Read the purchase object */
            line[0] = '\0';
            fgets(line, MAX_LINE - 1, fin);
            line[MAX_LINE - 1] = '\0';
            if (strlen(line) > 0) {
                /* Obtain the object */
                getPurchaseObject(line, &newPurchase);
                /* Add the new purchase to the output table */
                purchaseTableAdd(tabPurchases, newPurchase, retVal);
            }
        }
        /* Close the file */
        fclose(fin);

    } else {
        *retVal = ERR_CANNOT_READ;
    }
}
