#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cinema.h"

void getSessionStr(tSession session, int rows, int seatsPerRow, int maxSize, char *str, bool seatsMap) {
    char tempStr[MAX_LINE];
    int i, j;

    /* Build the string */
    snprintf(str, maxSize - 1, "%d %d %02d:%02d %d",
             (int) session.sessionId, (int) session.movieId,
             session.time.hour, session.time.minute, session.busySeats);

    /* Add the seats map information if required */
    if (seatsMap) {
        for (i = 0; i < rows; i++) {
            for (j = 0; j < seatsPerRow; j++) {
                strcpy(tempStr, str);
                snprintf(str, maxSize - 1, "%s %d", tempStr, (int) (session.seats[i][j]));
            }
        }
    }
}

void getScreenStr(tScreen screen, int maxSize, char *str) {

    /* Build the string */
    snprintf(str, maxSize - 1, "%d %d %d %d %d",
             (int) screen.screenId, screen.capacity, screen.rows, screen.seatsPerRow, screen.sessions.nSessions);
}

/* The content of the fields of the cinema structure is written into the string str */
void getCinemaStr(tCinema cinema, int maxSize, char *str) {

    /* Build the string */
    snprintf(str, maxSize - 1, "%d %d %s %s %02d:%02d %02d:%02d %d",
             (int) cinema.cinemaId, cinema.type, cinema.name, cinema.city,
             cinema.openingTime.hour, cinema.openingTime.minute,
             cinema.closingTime.hour, cinema.closingTime.minute,
             cinema.screens.nScreens);
}

void printSessionSeatMap(tSession session, int rows, int seatsPerRow) {

    int i, j;

    printf("SEAT  ");
    for (i = 0; i < seatsPerRow; i++)
        printf("%d ", i);
    printf("\n");

    for (i = rows - 1; i >= 0; i--) {
        printf("ROW %d ", i);
        for (j = 0; j < seatsPerRow; j++) {
            if (session.seats[i][j] == FREE ||
                session.seats[i][j] == DISABLED)
                printf("_ ");
            else
                printf("X ");
        }
        printf("\n");
    }

    printf("     ");
    for (i = 0; i < seatsPerRow; i++)
        printf("--");
    printf("-\n");

    printf("     ");
    for (i = 0; i < seatsPerRow; i++)
        printf("--");
    printf("-\n");
}

/* The content of the string str is parsed into the fields of the session structure */
void getSessionObject(const char *str, int rows, int seatsPerRow, tSession *session) {

    char buffer[MAX_LINE];
    int auxSessionId, auxMovieId, auxSeatStatus, i, j;

    sessionInit(session);

    /* read session data */
    sscanf(str, "%d %d %d:%d %d %[^\n]s",
           &auxSessionId, &auxMovieId,
           &session->time.hour, &session->time.minute, &session->busySeats, buffer);

    session->sessionId = (tSessionId) auxSessionId;
    session->movieId = (tMovieId) auxMovieId;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < seatsPerRow; j++) {
            sscanf(buffer, "%d %[^\n]s", &auxSeatStatus, buffer);
            session->seats[i][j] = (tSeatStatus) (auxSeatStatus);
        }
    }
}

/* The content of the string str is parsed into the fields of the screen structure */
void getScreenObject(const char *str, tScreen *screen) {

    int auxId;

    /* read screen data */
    sscanf(str, "%d %d %d %d %d",
           &auxId, &screen->capacity, &screen->rows, &screen->seatsPerRow, &screen->sessions.nSessions);

    screen->screenId = (tScreenId) auxId;
}

/* The content of the string str is parsed into the fields of the cinema structure */
void getCinemaObject(const char *str, tCinema *cinema) {

    int auxId, auxType;

    /* read cinema data */
    sscanf(str, "%d %d %s %s %d:%d %d:%d %d",
           &auxId, &auxType, cinema->name, cinema->city, &cinema->openingTime.hour,
           &cinema->openingTime.minute, &cinema->closingTime.hour, &cinema->closingTime.minute,
           &cinema->screens.nScreens);

    cinema->cinemaId = (tCinemaId) auxId;
    cinema->type = (tCinemaType) auxType;
}

int timeCmp(tTime t1, tTime t2) {
    int result;

    result = 0;

    if (t1.hour > t2.hour)
        result = 1;
    else if (t1.hour < t2.hour)
        result = -1;
    else {
        if (t1.minute > t2.minute)
            result = 1;
        else if (t1.minute < t2.minute)
            result = -1;
    }

    return result;
}

void timeCpy(tTime *t1, tTime t2) {
    t1->hour = t2.hour;
    t1->minute = t2.minute;
}

void timeAdd(tTime *t1, tTime t2) {
    int minutes;
    int hours;

    minutes = t1->minute + t2.minute;
    hours = t1->hour + t2.hour + (minutes / 60);
    minutes = minutes % 60;

    t1->hour = hours;
    t1->minute = minutes;
}

void timeInit(tTime *t1) {
    t1->hour = 0;
    t1->minute = 0;
}

void sessionCpy(tSession *dst, tSession src) {
    int i, j;
    dst->sessionId = src.sessionId;
    dst->movieId = src.movieId;
    timeCpy(&dst->time, src.time);
    dst->busySeats = src.busySeats;
    for (i = 0; i < MAX_ROWS; i++)
        for (j = 0; j < MAX_SEATS_PER_ROW; j++)
            dst->seats[i][j] = src.seats[i][j];
}

void screenCpy(tScreen *dst, tScreen src) {
    int i;
    dst->screenId = src.screenId;
    dst->capacity = src.capacity;
    dst->rows = src.rows;
    dst->seatsPerRow = src.seatsPerRow;
    dst->sessions.nSessions = src.sessions.nSessions;
    for (i = 0; i < src.sessions.nSessions; i++)
        sessionCpy(&dst->sessions.table[i], src.sessions.table[i]);
}

void cinemaCpy(tCinema *dst, tCinema src) {
    int i;
    dst->cinemaId = src.cinemaId;
    dst->type = src.type;
    strcpy(dst->name, src.name);
    strcpy(dst->city, src.city);
    timeCpy(&dst->openingTime, src.openingTime);
    timeCpy(&dst->closingTime, src.closingTime);
    dst->screens.nScreens = src.screens.nScreens;
    for (i = 0; i < src.screens.nScreens; i++)
        screenCpy(&dst->screens.table[i], src.screens.table[i]);
}

int cinemaCmp(tCinema c1, tCinema c2) {
    int result = 0;

    result = strcmp(c1.name, c2.name);
    if (result == 0) {
        result = strcmp(c1.city, c2.city);
        if (result == 0) {
            result = strcmp(c1.city, c2.city);
            if (result == 0) {
                if (c1.type > c2.type)
                    result = 1;
                else if (c1.type < c2.type)
                    result = -1;
                else {
                    if (c1.screens.nScreens > c2.screens.nScreens)
                        result = 1;
                    else if (c1.screens.nScreens < c2.screens.nScreens)
                        result = -1;
                    else {
                        result = timeCmp(c1.openingTime, c2.openingTime);
                        if (result == 0)
                            result = timeCmp(c1.closingTime, c2.closingTime);
                    }
                }
            }
        }
    }

    return result;
}

void sessionInit(tSession *session) {

    int i, j;

    session->sessionId = NO_SESSION;
    session->movieId = NO_MOVIE;
    session->time.hour = 0;
    session->time.minute = 0;
    session->busySeats = 0;
    for (i = 0; i < MAX_ROWS; i++)
        for (j = 0; j < MAX_SEATS_PER_ROW; j++)
            session->seats[i][j] = FREE;
}

void sessionTableInit(tSessionTable *sessionTable) {

    sessionTable->nSessions = 0;
}

void sessionTableAdd(tSessionTable *tabSessions, tSession session, tError *retVal) {

    *retVal = OK;

    /* Check if there is enough space for the new session */
    if (tabSessions->nSessions >= MAX_SESSIONS)
        *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new session to the end of the table */
        sessionCpy(&tabSessions->table[tabSessions->nSessions], session);
        tabSessions->nSessions++;
    }
}

int sessionTableFind(tSessionTable tabSessions, tSessionId id) {

    int idx = NO_SESSION;

    int i = 0;
    while (i < tabSessions.nSessions && idx == NO_SESSION) {
        /* Check if the id is the same */
        if (id == tabSessions.table[i].sessionId) {
            idx = i;
        }
        i++;
    }

    return idx;
}

void screenTableInit(tScreenTable *screenTable) {

    screenTable->nScreens = 0;
}

void screenTableAdd(tScreenTable *tabScreens, tScreen screen, tError *retVal) {

    *retVal = OK;

    /* Check if there is enough space for the new screen */
    if (tabScreens->nScreens >= MAX_SCREENS)
        *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new screen to the end of the table */
        screenCpy(&tabScreens->table[tabScreens->nScreens], screen);
        tabScreens->nScreens++;
    }
}

int screenTableFind(tScreenTable tabScreens, tScreenId id) {

    int idx = NO_SCREEN;

    int i = 0;
    while (i < tabScreens.nScreens && idx == NO_SCREEN) {
        /* Check if the id is the same */
        if (id == tabScreens.table[i].screenId) {
            idx = i;
        }
        i++;
    }

    return idx;
}

void cinemaTableInit(tCinemaTable *cinemaTable) {

    cinemaTable->nCinemas = 0;
}

void cinemaTableAdd(tCinemaTable *tabCinemas, tCinema cinema, tError *retVal) {

    *retVal = OK;

    /* Check if there enough space for the new cinema */
    if (tabCinemas->nCinemas >= MAX_CINEMAS)
        *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new cinema to the end of the table */
        cinemaCpy(&tabCinemas->table[tabCinemas->nCinemas], cinema);
        tabCinemas->nCinemas++;
    }

}

int cinemaTableFind(tCinemaTable tabCinemas, tCinemaId id) {

    int idx = NO_CINEMA;

    int i = 0;
    while (i < tabCinemas.nCinemas && idx == NO_CINEMA) {
        /* Check if the id is the same */
        if (id == tabCinemas.table[i].cinemaId) {
            idx = i;
        }
        i++;
    }

    return idx;
}

void cinemaTableSave(tCinemaTable tabCinemas, const char *filename, tError *retVal) {

    *retVal = OK;

    FILE *fout = NULL;
    int i, j, k, rows, seatsPerRow;
    char str[MAX_LINE];

    /* Open the output file */
    if ((fout = fopen(filename, "w")) == 0) {
        *retVal = ERR_CANNOT_WRITE;
    } else {

        /* Save all cinemas to the file */
        for (i = 0; i < tabCinemas.nCinemas; i++) {
            getCinemaStr(tabCinemas.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);

            /* Save all screens within the cinema */
            for (j = 0; j < tabCinemas.table[i].screens.nScreens; j++) {
                getScreenStr(tabCinemas.table[i].screens.table[j], MAX_LINE, str);
                rows = tabCinemas.table[i].screens.table[j].rows;
                seatsPerRow = tabCinemas.table[i].screens.table[j].seatsPerRow;
                fprintf(fout, "%s\n", str);

                /* Save all sessions within the cinema */
                for (k = 0; k < tabCinemas.table[i].screens.table[j].sessions.nSessions; k++) {
                    getSessionStr(tabCinemas.table[i].screens.table[j].sessions.table[k],
                                  rows, seatsPerRow, MAX_LINE, str, true);
                    fprintf(fout, "%s\n", str);
                }
            }
        }

        /* Close the file */
        fclose(fout);
    }
}

void cinemaTableLoad(tCinemaTable *tabCinemas, const char *filename, tError *retVal) {

    *retVal = OK;

    FILE *fin = NULL;
    char line[MAX_LINE];
    tCinema newCinema;

    int j, k, rows, seatsPerRow;

    /* Initialize the output table */
    cinemaTableInit(tabCinemas);

    /* Open the input file */
    if ((fin = fopen(filename, "r")) != NULL) {

        /* Read all the cinemas */
        while (!feof(fin) && tabCinemas->nCinemas < MAX_CINEMAS) {
            /* Remove any content from the line */
            line[0] = '\0';
            /* Read one line (maximum 511 chars) and store it in "line" variable */
            fgets(line, MAX_LINE - 1, fin);
            /* Ensure that the string is ended by 0*/
            line[MAX_LINE - 1] = '\0';
            if (strlen(line) > 0) {
                /* Obtain the object */
                getCinemaObject(line, &newCinema);

                /* Load all screens within the cinema */
                for (j = 0; j < newCinema.screens.nScreens; j++) {
                    line[0] = '\0';
                    fgets(line, MAX_LINE - 1, fin);
                    line[MAX_LINE - 1] = '\0';
                    if (strlen(line) > 0) {
                        getScreenObject(line, &newCinema.screens.table[j]);
                        rows = newCinema.screens.table[j].rows;
                        seatsPerRow = newCinema.screens.table[j].seatsPerRow;

                        /* Load all sessions within the cinema */
                        for (k = 0; k < newCinema.screens.table[j].sessions.nSessions; k++) {
                            line[0] = '\0';
                            fgets(line, MAX_LINE - 1, fin);
                            line[MAX_LINE - 1] = '\0';
                            if (strlen(line) > 0)
                                getSessionObject(line, rows, seatsPerRow,
                                                 &newCinema.screens.table[j].sessions.table[k]);
                        }
                    }
                }
                /* Add the new cinema to the output table */
                cinemaTableAdd(tabCinemas, newCinema, retVal);
            }
        }
        /* Close the file */
        fclose(fin);

    } else {
        *retVal = ERR_CANNOT_READ;
    }
}

void cinemaTableFilterByType(tCinemaTable tabCinemas, tCinemaType type, tCinemaTable *result) {

/**************** EX 7A *******************/
/*l’acció cinemaTableFilterByType que,
a partir d’una taula de cinemes i un tipus de cinema, retorni (en una segona
taula) els cinemes que compleixin que són del tipus indicat.*/

//conditions





/*******************************************/
}

void cinemaTableFilterByMultiscreen(tCinemaTable tabCinemas, tCinemaTable *result) {

/**************** EX 7B *******************/







/*******************************************/
}

void cinemaTableGetMultiscreenPremiereCinemas(tCinemaTable tabCinemas, tCinemaTable *result) {
/**************** EX 7C *******************/



/******************************************/
}

float screenAverageOccupation(tScreen screen) {
    float avgOcc = 0.0;
    int i, busySeats = 0, totalSeats = 0;

    for (i = 0; i < screen.sessions.nSessions; i++) {
        busySeats += screen.sessions.table[i].busySeats;
        totalSeats += screen.capacity;
    }

    if (totalSeats > 0)
        avgOcc = 100.0 * (float) busySeats / (float) totalSeats;

    return avgOcc;
}

float cinemaAverageOccupation(tCinema cinema) {
    float avgOcc = 0.0;
    int i, totalScreens = 0;

    for (i = 0; i < cinema.screens.nScreens; i++) {
        avgOcc += screenAverageOccupation(cinema.screens.table[i]);
        totalScreens++;
    }

    if (totalScreens > 0)
        avgOcc = avgOcc / (float) totalScreens;

    return avgOcc;
}

float cinemaTableComputeAverageOccupation(tCinemaTable tabCinema, char *city) {
    float avgOcc = 0.0;

/**************** EX 8A *******************/








/******************************************/

    return avgOcc;
}

void assignSeats(tSession *session, int number, int selectedRow, int selectedSeat) {
/**************** EX 4B *******************/







/******************************************/
}

void findSeats(tSession session, int rows, int seatsPerRow, int numberOfSeats,
               int *selectedRow, int *selectedSeat) {
    bool found = false;

/**************** EX 4A *******************/

















/******************************************/

    if (!found) {
        *selectedRow = NO_ROW;
        *selectedSeat = NO_SEAT_IN_ROW;
    }
}
