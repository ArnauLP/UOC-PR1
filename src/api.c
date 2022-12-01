#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "../include/api.h"
#include "../include/data.h"
#include "../include/movie.h"
#include "../include/cinema.h"
#include "../include/purchase.h"

void appDataInit(tAppData *object) {
    /* Set parent folder as the default path */
    strcpy(object->path, "../");

    /* Initialize the movie table */
    movieTableInit(&(object->movies));

    /* Initialize the cinemas table */
    cinemaTableInit(&(object->cinemas));

    /* Initialize the purchases table */
    purchaseTableInit(&(object->purchases));
}

void appDataLoad(tAppData *object, tError *retVal) {
    char path[MAX_LINE];
    *retVal = OK;

    /* Load the table of cinemas */
    snprintf(path, MAX_PATHNAME + MAX_FILENAME, "%scinemas.txt", object->path);
    cinemaTableLoad(&(object->cinemas), path, retVal);
    if (*retVal != OK) {
        printf("ERROR: Error reading the file of cinemas\n");
    }

    /* Load the table of movies */
    snprintf(path, MAX_PATHNAME + MAX_FILENAME, "%smovies.txt", object->path);
    movieTableLoad(&(object->movies), path, retVal);
    if (*retVal != OK) {
        printf("ERROR: Error reading the file of movies\n");
    }

    /* Load the table of purchases */
    snprintf(path, MAX_PATHNAME + MAX_FILENAME, "%spurchases.txt", object->path);
    purchaseTableLoad(&(object->purchases), path, retVal);
    if (*retVal != OK) {
        printf("ERROR: Error reading the file of purchases\n");
    }
}

void appDataSave(tAppData object, tError *retVal) {
    char path[MAX_LINE];
    *retVal = OK;

    /* Save the table of cinemas */
    snprintf(path, MAX_PATHNAME + MAX_FILENAME, "%scinemas.txt", object.path);
    cinemaTableSave(object.cinemas, path, retVal);
    if (*retVal != OK) {
        printf("ERROR: Error saving the file of cinemas\n");
    }

    /* Save the table of movies */
    snprintf(path, MAX_PATHNAME + MAX_FILENAME, "%smovies.txt", object.path);
    movieTableSave(object.movies, path, retVal);
    if (*retVal != OK) {
        printf("ERROR: Error saving the file of movies\n");
    }

    /* Save the table of purchases */
    snprintf(path, MAX_PATHNAME + MAX_FILENAME, "%spurchases.txt", object.path);
    purchaseTableSave(object.purchases, path, retVal);
    if (*retVal != OK) {
        printf("ERROR: Error saving the file of purchases\n");
    }
}

void appDataSetPath(tAppData *object, const char *path) {
    strncpy(object->path, path, MAX_PATHNAME);
}


/*********************** 
 *        API
 **********************/

void getSession(tAppData object, tCinemaId cinemaId, tScreenId screenId, tSessionId sessionId,
                tSession *session, tError *retVal) {

    int i, j, k;
    *retVal = OK;

    /* Check if there is a cinema with this id */
    i = cinemaTableFind(object.cinemas, cinemaId);
    if (i != NO_CINEMA) {
        j = screenTableFind(object.cinemas.table[i].screens, screenId);
        if (j != NO_SCREEN) {
            k = sessionTableFind(object.cinemas.table[i].screens.table[j].sessions, sessionId);
            if (k != NO_SESSION) {
                sessionCpy(session, object.cinemas.table[i].screens.table[j].sessions.table[k]);
            } else
                *retVal = ERR_ENTRY_NOT_FOUND;
        } else
            *retVal = ERR_ENTRY_NOT_FOUND;
    } else
        *retVal = ERR_ENTRY_NOT_FOUND;
}

void getScreen(tAppData object, tCinemaId cinemaId, tScreenId screenId, tScreen *screen, tError *retVal) {

    int i, j;
    *retVal = OK;

    /* Check if there is a cinema with this id */
    i = cinemaTableFind(object.cinemas, cinemaId);
    if (i != NO_CINEMA) {
        j = screenTableFind(object.cinemas.table[i].screens, screenId);
        if (j != NO_SCREEN)
            screenCpy(screen, object.cinemas.table[i].screens.table[j]);
        else
            *retVal = ERR_ENTRY_NOT_FOUND;
    } else {
        *retVal = ERR_ENTRY_NOT_FOUND;
    }
}

void getPurchases(tAppData object, tPurchaseTable *result) {
    *result = object.purchases;
}

void getCinemas(tAppData object, tCinemaTable *result) {
    *result = object.cinemas;
}

void getCinema(tAppData object, tCinemaId cinemaId, tCinema *cinema, tError *retVal) {

    int i;
    *retVal = OK;

    /* Check if there is a cinema with this id */
    i = cinemaTableFind(object.cinemas, cinemaId);
    if (i != NO_CINEMA) {
        cinemaCpy(cinema, object.cinemas.table[i]);
    } else {
        *retVal = ERR_ENTRY_NOT_FOUND;
    }
}

void addCinema(tAppData *object, tCinema cinema, tError *retVal) {
    *retVal = OK;
    tCinema tmp;

    /* Check if there is another cinema with the same id */
    getCinema(*object, cinema.cinemaId, &tmp, retVal);
    if (*retVal == OK) {
        *retVal = ERR_DUPLICATED_ENTRY;
    } else {
        /* Add the new cinema using the cinema table method */
        cinemaTableAdd(&(object->cinemas), cinema, retVal);
    }
}

void getMovies(tAppData object, tMovieTable *result) {
    *result = object.movies;
}

void getMovie(tAppData object, tMovieId id, tMovie *movie, tError *retVal) {

    int i;
    *retVal = OK;

    /* Check if there is a movie with this id */
    i = movieTableFind(object.movies, id);
    if (i != NO_MOVIE) {
        movieCpy(movie, object.movies.table[i]);
    } else {
        *retVal = ERR_ENTRY_NOT_FOUND;
    }
}

void addMovie(tAppData *object, tMovie movie, tError *retVal) {
    *retVal = OK;
    tMovie tmpMovie;

    /* Check if there is another movie with the same id */
    getMovie(*object, movie.movieId, &tmpMovie, retVal);
    if (*retVal == OK) {
        *retVal = ERR_DUPLICATED_ENTRY;
    } else {
        /* Add the new movie using the movie table method */
        movieTableAdd(&(object->movies), movie, retVal);
    }
}

bool checkTimeFits(tTime startTime, tTime durationTime, tTime endTime) {
    timeAdd(&startTime, durationTime);
    return timeCmp(startTime, endTime) <= 0;
}

void addSession(tAppData *object, tCinemaId cinemaId, tScreenId screenId, tMovieId movieId, tError *retVal) {

    *retVal = OK;
    int nSessions, iCinema, iMovie, iScreen;
    tTime startTime, gapTime, movieTime, endTime;
    tSession newSession, prevSession;
    tMovie prevMovie;

    timeInit(&startTime);
    timeInit(&gapTime);
    timeInit(&movieTime);
    timeInit(&endTime);

    iCinema = cinemaTableFind(object->cinemas, cinemaId);
    iMovie = movieTableFind(object->movies, movieId);

    if (iCinema == NO_CINEMA)
        *retVal = ERR_NO_CINEMA;
    else if (iMovie == NO_MOVIE)
        *retVal = ERR_NO_MOVIE;
    else {
        iScreen = screenTableFind(object->cinemas.table[iCinema].screens, screenId);
        if (iScreen == NO_SCREEN)
            *retVal = ERR_NO_SCREEN;
        else {
            nSessions = object->cinemas.table[iCinema].screens.table[iScreen].sessions.nSessions;
            if (nSessions > 0) {

                /* get the previuous session */
                sessionCpy(&prevSession,
                           object->cinemas.table[iCinema].screens.table[iScreen].sessions.table[nSessions - 1]);

                /* get the previuous session's movie  */
                getMovie(*object, prevSession.movieId, &prevMovie, retVal);

/**************** EX 3A *******************/








/******************************************/
            }
#ifdef TYPEDEF_COMPLETED
            else {
                timeCpy( &startTime, object->cinemas.table[iCinema].openingTime );
            }            
            timeCpy(&movieTime, object->movies.table[iMovie].duration);
            timeCpy(&endTime, object->cinemas.table[iCinema].closingTime);
#endif
            if (checkTimeFits(startTime, movieTime, endTime)) {
                sessionInit(&newSession);
                newSession.sessionId = screenId * 10 + nSessions + 1;
                newSession.movieId = movieId;
                newSession.busySeats = 0;
                timeCpy(&newSession.time, startTime);
                sessionTableAdd(&object->cinemas.table[iCinema].screens.table[iScreen].sessions, newSession, retVal);
                *retVal = OK;
            } else
                *retVal = ERR_NO_FREE_GAP;
        }
    }
}

void removeMovie(tAppData *object, tMovie movie) {
    /* Call the method from the movies table*/
    movieTableDel(&(object->movies), movie);
}

bool isMovieProgrammed(tAppData object, tMovie movie) {
    bool found = false;

/**************** EX 3B **********************/









/*********************************************/

    return found;
}

void processPurchase(tPurchase *purchase, tCinemaTable *cinemas, tError *retVal) {
    int pCinema, pScreen, pSession;
    int rows, seatsPerRow, selectedRow, selectedSeat;

    pCinema = cinemaTableFind(*cinemas, purchase->cinemaId);
    pScreen = screenTableFind(cinemas->table[pCinema - 1].screens, purchase->screenId);
    pSession = sessionTableFind(cinemas->table[pCinema - 1].screens.table[pScreen - 1].sessions,
                                purchase->sessionId);

    rows = cinemas->table[pCinema - 1].screens.table[pScreen - 1].rows;
    seatsPerRow = cinemas->table[pCinema - 1].screens.table[pScreen - 1].seatsPerRow;

    /* Find seats  */
    findSeats(cinemas->table[pCinema - 1].screens.table[pScreen - 1].sessions.table[pSession - 1],
              rows, seatsPerRow, purchase->purchasedSeats, &selectedRow, &selectedSeat);
    if (selectedSeat != NO_ROW && selectedSeat != NO_SEAT_IN_ROW) {
        /* Assign seats  */
        assignSeats(&cinemas->table[pCinema - 1].screens.table[pScreen - 1].sessions.table[pSession - 1],
                    purchase->purchasedSeats, selectedRow, selectedSeat);
        printf("Purchase has been successfuly processed. Seats has been assigned\n");
    } else
        printf("Purchase has not been successfuly processed. Unable to assign consecutive seats\n");

    *retVal = true;
}

void processAllPurchases(tAppData *object, tError *retVal) {
    int i = 0;

    *retVal = OK;

    while ((i < object->purchases.nPurchases) && (*retVal == OK)) {
        /* process the purchase */
        if (purchaseDataIsCorrect(*object, object->purchases.table[i]) &&
            !object->purchases.table[i].assignedSeats) {
            processPurchase(&object->purchases.table[i], &object->cinemas, retVal);
        }
        i++;
    }
}
