#include <stdbool.h>

/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

/* Uncomment the line below once you've completed the exercise 1A*/
//#define TYPEDEF_COMPLETED

#define MAX_CINEMAS 5
#define MAX_SCREENS 5
#define MAX_SESSIONS 5
#define MAX_NAME 15+1
#define MAX_DOC_NUMBER 9+1
#define MAX_MOVIES 50
#define MAX_PURCHASES 50
#define MAX_PATHNAME 255
#define MAX_FILENAME 25
#define MAX_LINE 514
#define NO_CINEMA -1
#define NO_SCREEN -1
#define NO_SESSION -1
#define NO_MOVIE -1
#define NO_PURCHASE -1
#define NO_ROW -1
#define NO_SEAT_IN_ROW -1

#define MAX_ROWS 10
#define MAX_SEATS_PER_ROW 10
#define MAX_SEATS_PER_PURCHASE 6
#define MINUTES_BETWEEN_MOVIES 20
#define PRICE_PER_TICKET 8.50

/* Definition of the error type. */
typedef enum {
    OK = 1, ERROR = 0, ERR_CANNOT_READ = -1, ERR_CANNOT_WRITE = -2,
    ERR_MEMORY = -3, ERR_DUPLICATED_ENTRY = -4, ERR_INVALID_DATA = -5,
    ERR_ENTRY_NOT_FOUND = -6,
    ERR_NO_MOVIE = -7, ERR_NO_CINEMA = -8, ERR_NO_SCREEN = -9,
    ERR_NO_SESSION = -10, ERR_NO_FREE_GAP = -11
} tError;

typedef enum {
    FREE, PURCHASED, UNAVAILABLE, DISABLED
} tSeatStatus;

typedef int tSessionId;
typedef int tScreenId;
typedef int tCinemaId;
typedef int tMovieId;

typedef struct {
    int day;
    int month;
    int year;
} tDate;

typedef struct {
    int hour;
    int minute;
} tTime;

typedef struct {
    tSessionId sessionId;
    tMovieId movieId;
    tTime time;
    tSeatStatus seats[MAX_ROWS][MAX_SEATS_PER_ROW];
    int busySeats;
} tSession;

typedef struct {
    tSession table[MAX_SESSIONS];
    int nSessions;
} tSessionTable;

typedef struct {
    tScreenId screenId;
    int capacity;
    int rows;
    int seatsPerRow;
    tSessionTable sessions;
} tScreen;

typedef struct {
    tScreen table[MAX_SCREENS];
    int nScreens;
} tScreenTable;

typedef enum {
    PREMIERE, RERELEASE, INDIE, OTHER
} tCinemaType;

typedef struct {
    tCinemaId cinemaId;
    tCinemaType type;
    char name[MAX_NAME];
    char city[MAX_NAME];
    tTime openingTime;
    tTime closingTime;
    tScreenTable screens;
} tCinema;

typedef struct {
    tCinema table[MAX_CINEMAS];
    int nCinemas;
} tCinemaTable;

typedef enum {
    G_RATED, PG_RATED, PG13_RATED, R_RATED, NC17_RATED
} tMovieRate;

typedef struct {
    tMovieId movieId;
/**************** EX 1A *******************/




/******************************************/
} tMovie;

typedef struct {
    tMovie table[MAX_MOVIES];
    int nMovies;
} tMovieTable;

typedef struct {
    int row, seatInRow;
} tSeat;

typedef struct {
    tCinemaId cinemaId;
    tScreenId screenId;
    tSessionId sessionId;
    int purchasedSeats;
    bool assignedSeats;
    tSeat seats[MAX_SEATS_PER_PURCHASE];
    float price;
} tPurchase;

typedef struct {
    tPurchase table[MAX_PURCHASES];
    int nPurchases;
} tPurchaseTable;

/* Definition of the application data structure */
typedef struct {
    /* Path where data will be stored */
    char path[MAX_PATHNAME];

    /* Cinemas table */
    tCinemaTable cinemas;

    /* Movies table */
    tMovieTable movies;

    /* Purchases table */
    tPurchaseTable purchases;

} tAppData;

/*********************** 
 *    COMMON HEADERS
 **********************/

/* Compares two given times */
int timeCmp(tTime t1, tTime t2);

/* Copies t2 time onto t1 */
void timeCpy(tTime *t1, tTime t2);

/* Accumulates t1 time onto t2 */
void timeAdd(tTime *t1, tTime t2);

/* Initializes time t1 to 00:00 */
void timeInit(tTime *t1);

/* Compare two dates */
int dateCmp(tDate d1, tDate d2);

/* Copy a date onto another date */
void dateCpy(tDate *d1, tDate d2);

#endif /*__DATA_H*/
