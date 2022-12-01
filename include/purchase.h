#include "data.h"

/* Get a textual representation of a purchase */
void getPurchaseStr(tPurchase purchase, int maxSize, char *str);

/* Get a purchase object from its textual representation */
void getPurchaseObject(const char *str, tPurchase *purchase);

/* Copy the purchase data in src to dst*/
void purchaseCpy(tPurchase *dst, tPurchase src);

/* Compares the purchase data of p1 and p2*/
int purchaseCmp(tPurchase p1, tPurchase p2);

/* Checks if a purchase data is correct */
bool purchaseDataIsCorrect(tAppData appData, tPurchase purchase);

/* Creates a purchase with the given data */
void createPurchase(tPurchase *purchase, tCinemaId cinemaId, tScreenId screenId, tSessionId sessionId,
                    int number, int selectedRow, int selectedSeat);

/* Initializes the given purchases table */
void purchaseTableInit(tPurchaseTable *purchasesTable);

/* Add a new purchase to the table of purchases */
void purchaseTableAdd(tPurchaseTable *tabPurchases, tPurchase purchase, tError *retVal);

/* Load the table of purchases from a file */
void purchaseTableLoad(tPurchaseTable *tabPurchases, const char *filename, tError *retVal);

/* Save a table of purchases to a file */
void purchaseTableSave(tPurchaseTable tabPurchases, const char *filename, tError *retVal);

