#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../include/data.h"
#include "../include/test.h"
#include "../include/movie.h"
#include "../include/cinema.h"
#include "../include/purchase.h"
#include "../include/api.h"

#define MOVIE1 "1 TOY_STORY 01:30 0 25.00"
#define MOVIE2 "2 BATMAN 02:00 1 0.00"
#define MOVIE3 "3 SUPERMAN 01:45 2 0.00"
#define MOVIE4 "4 SPIDERMAN 01:50 3 200.00"
#define MOVIE5 "5 SHREK 01:35 4 150.00"
#define MOVIE6 "6 GLADIATOR 01:50 4 750.00"

#define CINEMA1 "1 0 COLISEUM BARCELONA 16:00 23:00 1"
#define CINEMA1_SCREEN1 "11 100 10 10 1"
#define CINEMA1_SCREEN1_SESSION1 "111 1 16:00 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"

#define CINEMA2 "2 0 BOSQUE BARCELONA 15:30 22:30 2"
#define CINEMA2_SCREEN1 "21 50 10 5 1"
#define CINEMA2_SCREEN1_SESSION1 "211 2 15:30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"
#define CINEMA2_SCREEN2_SESSION1 "221 3 15:30 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"

#define CINEMA3 "3 1 DANTE BARCELONA 16:00 23:30 1"
#define CINEMA4 "4 2 VERDI BARCELONA 16:00 23:30 6"
#define CINEMA5 "5 3 IMAX BARCELONA 10:00 22:30 4"

#define PURCHASE1 "1 11 111 2 1 17.00 5 5 5 6"
#define PURCHASE2 "1 11 111 3 1 25.00 5 7 5 8 5 9"

void runTests() {
    int passedTest = 0;
    int totalTest = 0;
    float percent = 0.0;

    printf("===============================================\n");
    printf("====       PRACTICAL ACTIVITY TESTS        ====\n");
    printf("===============================================\n");

    testTableOperation(&totalTest, &passedTest);
    testSessionProgramming(&totalTest, &passedTest);
    testSeatsAssignment(&totalTest, &passedTest);
    testCpyCmp(&totalTest, &passedTest);
    testCinemasFilters(&totalTest, &passedTest);
    testStatistics(&totalTest, &passedTest);

    if (totalTest > 0)
        percent = (float) passedTest / totalTest * 100.0;
    else {
        percent = 0.0;
    }

    printf("===================================\n");
    printf("====       TEST SUMMARY        ====\n");
    printf("===================================\n");
    printf("\tPR: Passed %d of %d [%0.2f%%]\n", passedTest, totalTest, percent);
    printf("===================================\n");
}

void testTableOperation(int *totalTest, int *passedTest) {
    tMovie movie1, movie2, movie3, movie4, movie5;
    tMovieTable movies;
    tError retVal;
    int i, before, after;

    movieTableInit(&movies);
    getMovieObject(MOVIE1, &movie1);
    getMovieObject(MOVIE2, &movie2);
    getMovieObject(MOVIE3, &movie3);
    getMovieObject(MOVIE4, &movie4);
    getMovieObject(MOVIE5, &movie5);

    printf("=================================================\n");
    printf(" TABLE OPERATIONS: ADDITION (Exercise 1B)\n");
    printf("=================================================\n");

    movieTableAdd(&movies, movie1, &retVal);
    printf("\nTest 1.1: Addition in empty table");
    (*totalTest)++;
    if (retVal == OK &&
        movies.nMovies == 1 &&
        movieTableFind(movies, 1) == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour adding a movie into an empty table\n");
    }

    movieTableAdd(&movies, movie2, &retVal);
    printf("\nTest 1.2: Addition in non-empty table");
    (*totalTest)++;
    if (retVal == OK &&
        movies.nMovies == 2 &&
        movieTableFind(movies, 2) == 1) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour adding a movie into a non-empty table\n");
    }

    printf("\nTest 1.3: Addition of movies while there's enough room in table");
    i = 2;
    retVal = OK;
    while (i < MAX_MOVIES && retVal == OK) {
        movie2.movieId = i + 1;
        movieTableAdd(&movies, movie2, &retVal);
        i++;
    }
    (*totalTest)++;
    if (retVal == OK &&
        movies.nMovies == MAX_MOVIES) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour adding several movies into a table)\n");
    }

    printf("\nTest 1.4: Addition of movie in a full table");
    retVal = OK;
    movieTableAdd(&movies, movie3, &retVal);
    (*totalTest)++;
    if (retVal == ERR_MEMORY &&
        movies.nMovies == MAX_MOVIES) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour adding a movie into a full table (should not be permitted)\n");
    }

    printf("=================================================\n");
    printf(" TABLE OPERATIONS: DELETION (Exercise 1C)\n");
    printf("=================================================\n");

    printf("\nTest 1.5: Deletion in full table: non-existing movie");
    (*totalTest)++;
    movie2.movieId = MAX_MOVIES + 1;
    movieTableDel(&movies, movie2);
    if (movies.nMovies == MAX_MOVIES) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour in deletion: non existing movie must have no effect on the table\n");
    }

    printf("\nTest 1.6: Deletion in full table: existing movie");
    (*totalTest)++;
    movie2.movieId = MAX_MOVIES;
    movieTableDel(&movies, movie2);
    if (movies.nMovies == MAX_MOVIES - 1) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour in deletion: existing movie must decrease number of stored movies\n");
    }

    printf("\nTest 1.7: Deletion of every movie in a table");
    (*totalTest)++;
    movie2.movieId = MAX_MOVIES - 1;
    retVal = OK;
    while (movie2.movieId > 0 && retVal == OK) {
        before = movies.nMovies;
        movieTableDel(&movies, movie2);
        after = movies.nMovies;
        retVal = (after == before - 1);
        movie2.movieId--;
    }
    if (retVal == OK &&
        movies.nMovies == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour in deletion of table\n");
    }

    printf("\nTest 1.8: Deletion of a movie in an empty table");
    (*totalTest)++;
    movie2.movieId = 2;
    movieTableDel(&movies, movie2);
    if (movies.nMovies == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour in deletion of a movie in an empty table\n");
    }

    printf("\nTest 1.9: Deletion requires movies displacement to fill the gap");
    movieTableAdd(&movies, movie1, &retVal);
    movieTableAdd(&movies, movie2, &retVal);
    movieTableAdd(&movies, movie3, &retVal);
    (*totalTest)++;
    movieTableDel(&movies, movie1);
    if (movies.nMovies == 2 &&
        movies.table[0].movieId == 2 &&
        movies.table[1].movieId == 3) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour in deletion, incorrect gap management\n");
    }
}

void testSessionProgramming(int *totalTest, int *passedTest) {

    tAppData appData;
    tMovie movie1, movie2, movie3, movie4, movie5, newMovie;
    tCinema cinema1, cinema2;
    tScreen newScreen;
    tSession newSession;
    tError retVal;
    int rows, seatsPerRow;
    bool found;

    appDataInit(&appData);

    /* add 5 movies */
    getMovieObject(MOVIE1, &movie1);
    getMovieObject(MOVIE2, &movie2);
    getMovieObject(MOVIE3, &movie3);
    getMovieObject(MOVIE4, &movie4);
    getMovieObject(MOVIE5, &movie5);
    addMovie(&appData, movie1, &retVal);
    addMovie(&appData, movie2, &retVal);
    addMovie(&appData, movie3, &retVal);
    addMovie(&appData, movie4, &retVal);
    addMovie(&appData, movie5, &retVal);

    /* add the cinema 1: one cinema with one screen */
    getCinemaObject(CINEMA1, &cinema1);
    getScreenObject(CINEMA1_SCREEN1, &cinema1.screens.table[0]);
    rows = cinema1.screens.table[0].rows;
    seatsPerRow = cinema1.screens.table[0].seatsPerRow;
    getSessionObject(CINEMA1_SCREEN1_SESSION1, rows, seatsPerRow, &cinema1.screens.table[0].sessions.table[0]);
    addCinema(&appData, cinema1, &retVal);

    /* add the cinema 2: one cinema with two screens */
    getCinemaObject(CINEMA2, &cinema2);
    getScreenObject(CINEMA2_SCREEN1, &cinema2.screens.table[1]);
    rows = cinema2.screens.table[0].rows;
    seatsPerRow = cinema2.screens.table[0].seatsPerRow;
    getSessionObject(CINEMA2_SCREEN1_SESSION1, rows, seatsPerRow, &cinema2.screens.table[0].sessions.table[0]);
    rows = cinema2.screens.table[1].rows;
    seatsPerRow = cinema2.screens.table[1].seatsPerRow;
    getSessionObject(CINEMA2_SCREEN2_SESSION1, rows, seatsPerRow, &cinema2.screens.table[1].sessions.table[0]);
    addCinema(&appData, cinema2, &retVal);

    printf("=================================================\n");
    printf(" SESSION ADDITION (Exercise 3A)\n");
    printf("=================================================\n");

    printf("\nTest 3.1: Addition in a non-existing cinema");
    addSession(&appData, 3, 11, 1, &retVal);
    (*totalTest)++;
    if (retVal == ERR_NO_CINEMA) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour adding a session into non existing cinema\n");
    }

    printf("\nTest 3.2: Addition in a non-existing screen");
    addSession(&appData, 1, 12, 1, &retVal);
    (*totalTest)++;
    if (retVal == ERR_NO_SCREEN) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour adding a session into non existing screen\n");
    }

    printf("\nTest 3.3: Addition of a non-existing movie");
    addSession(&appData, 1, 11, 6, &retVal);
    (*totalTest)++;
    if (retVal == ERR_NO_MOVIE) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected behaviour adding a non-existing movie)\n");
    }

    printf("\nTest 3.4: Addition of an existing movie in a valid cinema and screen");
    addSession(&appData, 1, 11, 2, &retVal);
    sessionCpy(&newSession, appData.cinemas.table[0].screens.table[0].sessions.table[1]);
    (*totalTest)++;
    if (retVal == OK &&
        newSession.time.hour == 17 &&
        newSession.time.minute == 50 &&
        newSession.movieId == 2 &&
        newSession.sessionId == 112) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected %2d:%2d and returned %2d:%2d)\n", 17, 50, newSession.time.hour,
               newSession.time.minute);
    }

    printf("\nTest 3.5: Addition of a different movie in a valid cinema and screen");
    addSession(&appData, 1, 11, 3, &retVal);
    sessionCpy(&newSession, appData.cinemas.table[0].screens.table[0].sessions.table[2]);
    (*totalTest)++;
    if (retVal == OK &&
        newSession.time.hour == 20 &&
        newSession.time.minute == 10 &&
        newSession.movieId == 3 &&
        newSession.sessionId == 113) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected session start time)\n");
    }

    printf("\nTest 3.6: Addition of a movie that does not fit");
    addSession(&appData, 1, 11, 2, &retVal);
    (*totalTest)++;
    if (retVal == ERR_NO_FREE_GAP) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected addition of a session in a full-scheduled screen)\n");
    }

    printf("\nTest 3.7: Addition of the first session in a cinema's screen");
    newScreen.screenId = 23;
    newScreen.capacity = 25;
    newScreen.rows = 5;
    newScreen.seatsPerRow = 5;
    sessionTableInit(&newScreen.sessions);
    screenTableAdd(&appData.cinemas.table[1].screens, newScreen, &retVal);
    addSession(&appData, 2, 23, 1, &retVal);
    sessionCpy(&newSession, appData.cinemas.table[1].screens.table[2].sessions.table[0]);
    (*totalTest)++;
    if (retVal == OK &&
        newSession.time.hour == 15 &&
        newSession.time.minute == 30 &&
        newSession.movieId == 1 &&
        newSession.sessionId == 231) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected session start time)\n");
    }

    printf("=================================================\n");
    printf(" PROGRAMMED SESSIONS (Exercise 3B)\n");
    printf("=================================================\n");

    printf("\nTest 3.8: Check a non-existing movie");
    newMovie.movieId = 6;
    found = isMovieProgrammed(appData, newMovie);
    (*totalTest)++;
    if (found == false) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected found of a non-existing movie in the cinemas program)\n");
    }

    printf("\nTest 3.9: Check an existing non programmed movie");
    found = isMovieProgrammed(appData, movie5);
    (*totalTest)++;
    if (found == false) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected found of a non programmed movie in the cinemas program)\n");
    }

    printf("\nTest 3.10: Check an existing programmed movie");
    found = isMovieProgrammed(appData, movie1);
    (*totalTest)++;
    if (found == true) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unable to find a programmed movie)\n");
    }

    printf("\nTest 3.11: Check a different existing programmed movie");
    found = isMovieProgrammed(appData, movie2);
    (*totalTest)++;
    if (found == true) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unable to find a programmed movie)\n");
    }

    printf("\nTest 3.12: Check, again, a different existing programmed movie");
    found = isMovieProgrammed(appData, movie3);
    (*totalTest)++;
    if (found == true) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unable to find a programmed movie)\n");
    }
}

void testSeatsAssignment(int *totalTest, int *passedTest) {

    tSession session1, session2, session3;
    int selectedRow, selectedSeat, i;

    getSessionObject(CINEMA1_SCREEN1_SESSION1, 10, 10,
                     &session1); // 10 x 10 matrix with 5 occupied seats in the middle of the room
    getSessionObject(CINEMA2_SCREEN1_SESSION1, 10, 5, &session2); // 10 x 5 matrix without occupied seats
    getSessionObject(CINEMA2_SCREEN1_SESSION1, 10, 5, &session3); // 10 x 5 matrix without occupied seats

    printf("=================================================\n");
    printf(" FINDING SEATS (Exercise 4A)\n");
    printf("=================================================\n");

    printf("\nTest 4.1: Find 1 seat in an empty room");
    findSeats(session2, 10, 5, 1, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 5 && selectedSeat == 2) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 5, 2, selectedRow,
               selectedSeat);
    }

    printf("\nTest 4.2: Number of seats to find fits from middle to end of row");
    findSeats(session2, 10, 5, 3, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 5 && selectedSeat == 2) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 5, 2, selectedRow,
               selectedSeat);
    }

    printf("\nTest 4.3: Number of seats to find does not fit from middle to end of row");
    findSeats(session2, 10, 5, 4, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 5 && selectedSeat == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 5, 0, selectedRow,
               selectedSeat);
    }

    printf("\nTest 4.4: Number of seats to find equals to seats per row");
    findSeats(session2, 10, 5, 5, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 5 && selectedSeat == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 2, 0, selectedRow,
               selectedSeat);
    }

    printf("\nTest 4.5: Number of seats to find greater than seats per row");
    findSeats(session2, 10, 5, 6, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == NO_ROW && selectedSeat == NO_SEAT_IN_ROW) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (impossible to find %d seats together in a row of %d seats)\n", 6, 5);
    }

    printf("\nTest 4.6: Number of seats to find has perfect fit with available sets in row");
    findSeats(session1, 10, 10, 5, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 5 && selectedSeat == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 5, 0, selectedRow,
               selectedSeat);
    }

    printf("\nTest 4.7: Number of seats to find forces to go a row back");
    findSeats(session1, 10, 10, 6, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 6 && selectedSeat == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 6, 0, selectedRow,
               selectedSeat);
    }
    for (i = 5; i < 9; i++)
        session1.seats[i][5] = PURCHASED;

    printf("\nTest 4.8: Number of seats to find requires to go to the last row of the room");
    findSeats(session1, 10, 10, 6, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 9 && selectedSeat == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 9, 0, selectedRow,
               selectedSeat);
    }
    session1.seats[9][5] = PURCHASED;

    printf("\nTest 4.9: Number of seats to find requires to go to the first row of the room");
    findSeats(session1, 10, 10, 6, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == 0 && selectedSeat == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected row %d - seat %d but returned row %d - seat %d)\n", 0, 0, selectedRow,
               selectedSeat);
    }

    printf("=================================================\n");
    printf(" ASSIGNING SEATS (Exercise 4B)\n");
    printf("=================================================\n");

    printf("\nTest 4.10: Null assignment");
    assignSeats(&session2, 0, 2, 5);
    (*totalTest)++;
    if (session2.seats[2][5] != PURCHASED &&
        session2.busySeats == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (null assignment has effect on seat map)\n");
    }

    printf("\nTest 4.11: First assignment");
    assignSeats(&session2, 2, 2, 5);
    (*totalTest)++;
    if (session2.seats[2][5] == PURCHASED &&
        session2.seats[2][6] == PURCHASED &&
        session2.busySeats == 2) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected 2 seats assignment in the room but returned %d)\n", session2.busySeats);
    }

    printf("\nTest 4.12: Assignment of already assigned seats");
    assignSeats(&session2, 2, 2, 5);
    (*totalTest)++;
    if (session2.seats[2][5] == PURCHASED &&
        session2.seats[2][6] == PURCHASED &&
        session2.busySeats == 2) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected 2 seats assignment in the room but returned %d)\n", session2.busySeats);
    }

    printf("\nTest 4.13: Assignment of all seats in the room");
    for (i = 0; i < 10; i++)
        assignSeats(&session3, 5, i, 0);
    (*totalTest)++;
    if (session3.busySeats == 50) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected 50 seats assignment in the room but returned %d)\n", session3.busySeats);
    }

    printf("\nTest 4.14: Check full session");
    findSeats(session3, 10, 5, 1, &selectedRow, &selectedSeat);
    (*totalTest)++;
    if (selectedRow == NO_ROW && selectedSeat == NO_SEAT_IN_ROW) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected found seat in full room, coordinates [%d, %d])\n", selectedRow, selectedSeat);
    }
}

void testCpyCmp(int *totalTest, int *passedTest) {

    tMovie d1, d2, d4, d5;
    bool equals = false;

    printf("==================================\n");
    printf(" MOVIES COPY (Exercise 6A)\n");
    printf("==================================\n");

    printf("\nTest 6.1: Copy movies");
    (*totalTest)++;
    getMovieObject(MOVIE2, &d2);
    movieCpy(&d1, d2);
#ifdef TYPEDEF_COMPLETED
    equals= (strcmp(d2.title, d1.title)==0 && 
        d2.duration.hour == d1.duration.hour &&
        d2.duration.minute == d1.duration.minute &&
        d2.rate == d1.rate &&
        (fabs(d2.income - d1.income) < 0.001));
#endif
    if (equals) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (different values found after copying movies)\n");
    }

    printf("==================================\n");
    printf(" MOVIES COMPARISON (Exercise 6B)\n");
    printf("==================================\n");

    printf("\nTest 6.2: Compare equal movies");
    (*totalTest)++;
    getMovieObject(MOVIE1, &d1);
    if (movieCmp(d1, d1) == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 6.3: Comparison, first movie greater than second (by title)");
    (*totalTest)++;
    getMovieObject(MOVIE4, &d4);
    getMovieObject(MOVIE5, &d5);
    if (movieCmp(d4, d5) > 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 6.4: Comparison, second movie lower than second");
    (*totalTest)++;
    if (movieCmp(d5, d4) < 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 6.5: Compare case-unsensitive strings");
    (*totalTest)++;
    movieCpy(&d2, d1);
#ifdef TYPEDEF_COMPLETED
    strcpy(d2.title, "toy_story");
#endif
    if (movieCmp(d1, d2) == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }
}

void testCinemasFilters(int *totalTest, int *passedTest) {
    tCinema cinema1, cinema2, cinema3, cinema4, cinema5;
    tCinemaTable cinemas, result;
    tError retVal;

    cinemaTableInit(&cinemas);

    printf("==================================\n");
    printf(" CINEMAS FILTERS (Exercise 7)\n");
    printf("==================================\n");

    printf("\nTest 7.1: Filter by type on an empty table");
    (*totalTest)++;
    cinemaTableFilterByType(cinemas, PREMIERE, &result);
    if (result.nCinemas == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 7.2: Get multiscreen cinemas on an empty table");
    (*totalTest)++;
    cinemaTableFilterByMultiscreen(cinemas, &result);
    if (result.nCinemas == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 7.3: Get multiscreen premiere cinemas on an empty table");
    (*totalTest)++;
    cinemaTableGetMultiscreenPremiereCinemas(cinemas, &result);
    if (result.nCinemas == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    getCinemaObject(CINEMA1, &cinema1);
    getCinemaObject(CINEMA2, &cinema2);
    getCinemaObject(CINEMA3, &cinema3);
    getCinemaObject(CINEMA4, &cinema4);
    getCinemaObject(CINEMA5, &cinema5);
    cinemaTableAdd(&cinemas, cinema1, &retVal);
    cinemaTableAdd(&cinemas, cinema2, &retVal);
    cinemaTableAdd(&cinemas, cinema3, &retVal);
    cinemaTableAdd(&cinemas, cinema4, &retVal);
    cinemaTableAdd(&cinemas, cinema5, &retVal);

    printf("\nTest 7.4: Filter by type PREMIER on a table of cinemas");
    (*totalTest)++;
    cinemaTableFilterByType(cinemas, PREMIERE, &result);
    if (result.nCinemas == 2) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 7.5: Filter by type RERELEASE on a table of cinemas");
    (*totalTest)++;
    cinemaTableFilterByType(cinemas, RERELEASE, &result);
    if (result.nCinemas == 1) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 7.6: Filter by type INDIE on a table of cinemas");
    (*totalTest)++;
    cinemaTableFilterByType(cinemas, INDIE, &result);
    if (result.nCinemas == 1) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 7.7: Filter by type OTHER on a table of cinemas");
    (*totalTest)++;
    cinemaTableFilterByType(cinemas, OTHER, &result);
    if (result.nCinemas == 1) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 7.8: Get multiscreen cinemas on table of cinemas");
    (*totalTest)++;
    cinemaTableFilterByMultiscreen(cinemas, &result);
    if (result.nCinemas == 3 &&
        result.table[0].cinemaId == 2 &&
        result.table[1].cinemaId == 4 &&
        result.table[2].cinemaId == 5) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }

    printf("\nTest 7.9: Get multiscreen premiere cinemas (filter combination)");
    (*totalTest)++;
    cinemaTableGetMultiscreenPremiereCinemas(cinemas, &result);
    if (result.nCinemas == 1 &&
        result.table[0].cinemaId == 2) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL\n");
    }
}

void testStatistics(int *totalTest, int *passedTest) {
    float gRated, pgRated, pg13Rated, rRated, nc17Rated, avg;
    int rows, seatsPerRow;
    tCinemaTable cinemas;
    tCinema cinema1, cinema2;
    tMovie movie1, movie2, movie3, movie4, movie5, movie6;
    tMovieTable movies;
    tTime avgTime;
    tError retVal;

    /* cinema 1: one cinema with one screen */
    getCinemaObject(CINEMA1, &cinema1);
    getScreenObject(CINEMA1_SCREEN1, &cinema1.screens.table[0]);
    rows = cinema1.screens.table[0].rows;
    seatsPerRow = cinema1.screens.table[0].seatsPerRow;
    getSessionObject(CINEMA1_SCREEN1_SESSION1, rows, seatsPerRow, &cinema1.screens.table[0].sessions.table[0]);

    /* add the cinema 2: one cinema with two screens */
    getCinemaObject(CINEMA2, &cinema2);
    getScreenObject(CINEMA2_SCREEN1, &cinema2.screens.table[1]);
    rows = cinema2.screens.table[0].rows;
    seatsPerRow = cinema2.screens.table[0].seatsPerRow;
    getSessionObject(CINEMA2_SCREEN1_SESSION1, rows, seatsPerRow, &cinema2.screens.table[0].sessions.table[0]);
    rows = cinema2.screens.table[1].rows;
    seatsPerRow = cinema2.screens.table[1].seatsPerRow;
    getSessionObject(CINEMA2_SCREEN2_SESSION1, rows, seatsPerRow, &cinema2.screens.table[1].sessions.table[0]);

    cinemaTableInit(&cinemas);

    printf("=================================================\n");
    printf(" STATISTICS (Exercise 8)\n");
    printf("=================================================\n");

    printf("\nTest 8.1: Average occupation of an empty table of cinemas");
    (*totalTest)++;
    avg = cinemaTableComputeAverageOccupation(cinemas, "BARCELONA");
    if (fabs(avg) < 0.001) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected non null average result.\n");
    }

    cinemaTableAdd(&cinemas, cinema2, &retVal);

    printf("\nTest 8.2: Average occupation of cinemas of a city with no cinemas");
    (*totalTest)++;
    avg = cinemaTableComputeAverageOccupation(cinemas, "MADRID");
    if (fabs(avg) < 0.001) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected non null average result.\n");
    }

    printf("\nTest 8.3: Average occupation of cinemas with null occupation");
    (*totalTest)++;
    avg = cinemaTableComputeAverageOccupation(cinemas, "BARCELONA");
    if (fabs(avg) < 0.001) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected 0 but returned %.2f)\n", avg);
    }

    cinemaTableInit(&cinemas);
    cinemaTableAdd(&cinemas, cinema1, &retVal);

    printf("\nTest 8.4: Average occupation of one cinema with non null occupation");
    (*totalTest)++;
    avg = cinemaTableComputeAverageOccupation(cinemas, "BARCELONA");
    if (fabs(avg - 5.0) < 0.001) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected occupation %.2f but returned %.2f\n", 5.0, avg);
    }

    cinemaTableAdd(&cinemas, cinema2, &retVal);

    printf("\nTest 8.5: Average occupation of two cinemas with non null occupation");
    (*totalTest)++;
    avg = cinemaTableComputeAverageOccupation(cinemas, "BARCELONA");
    if (fabs(avg - 2.5) < 0.001) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (expected occupation %.2f but returned %.2f\n", 2.5, avg);
    }

    getMovieObject(MOVIE1, &movie1);
    getMovieObject(MOVIE2, &movie2);
    getMovieObject(MOVIE3, &movie3);
    getMovieObject(MOVIE4, &movie4);
    getMovieObject(MOVIE5, &movie5);
    getMovieObject(MOVIE6, &movie6);
    movieTableInit(&movies);

    printf("\nTest 8.6: Average duration of an empty movies table");
    (*totalTest)++;
    movieTableGetAvgDuration(movies, &avgTime);
    if (avgTime.hour == 0 && avgTime.minute == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected number average result. Expected %d:%d and returned %d:%d)\n", 0, 0,
               avgTime.hour, avgTime.minute);
    }

    movieTableAdd(&movies, movie1, &retVal);

    printf("\nTest 8.7: Average duration of a single movie");
    (*totalTest)++;
    movieTableGetAvgDuration(movies, &avgTime);
    if (avgTime.hour == 1 && avgTime.minute == 30) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected number average result. Expected %d:%d and returned %d:%d)\n", 1, 30,
               avgTime.hour, avgTime.minute);
    }

    movieTableAdd(&movies, movie2, &retVal);

    printf("\nTest 8.8: Average duration of two movies");
    (*totalTest)++;
    movieTableGetAvgDuration(movies, &avgTime);
    if (avgTime.hour == 1 && avgTime.minute == 45) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected number average result. Expected %02d:%02d and returned %02d:%02d)\n", 1, 45,
               avgTime.hour, avgTime.minute);
    }

    movieTableAdd(&movies, movie3, &retVal);
    movieTableAdd(&movies, movie4, &retVal);
    movieTableAdd(&movies, movie5, &retVal);

    printf("\nTest 8.9: Average duration of five movies");
    (*totalTest)++;
    movieTableGetAvgDuration(movies, &avgTime);
    if (avgTime.hour == 1 && avgTime.minute == 44) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected number average result. Expected %02d:%02d and returned %02d:%02d)\n", 2, 8,
               avgTime.hour, avgTime.minute);
    }

    movieTableInit(&movies);

    printf("\nTest 8.10: Income per rates of an empty movies table");
    (*totalTest)++;
    movieTableGetIncomePerRate(movies, &gRated, &pgRated, &pg13Rated, &rRated, &nc17Rated);
    if (gRated == 0.0 && pgRated == 0.0 && pg13Rated == 0.0 && rRated == 0.0 && nc17Rated == 0.0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected results. Expected zero values and returned non-zero values)\n");
    }

    movieTableAdd(&movies, movie1, &retVal);
    movieTableAdd(&movies, movie2, &retVal);
    movieTableAdd(&movies, movie3, &retVal);
    movieTableAdd(&movies, movie4, &retVal);
    movieTableAdd(&movies, movie5, &retVal);

    printf("\nTest 8.11: Income per rates of a non-empty table (one movie per range)");
    (*totalTest)++;
    movieTableGetIncomePerRate(movies, &gRated, &pgRated, &pg13Rated, &rRated, &nc17Rated);
    if (gRated == 25.0 && pgRated == 0.0 && pg13Rated == 0.0 && rRated == 200.0 && nc17Rated == 150.0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (Expected %.2f, %.2f, %.2f, %.2f %.2f but returned %.2f, %.2f, %.2f, %.2f, %.2f)\n",
               25.0, 0.0, 0.0, 200.0, 150.0, gRated, pgRated, pg13Rated, rRated, nc17Rated);
    }

    movieTableAdd(&movies, movie6, &retVal);

    printf("\nTest 8.12: Income per rates of a non-empty table (several movies per range)");
    (*totalTest)++;
    movieTableGetIncomePerRate(movies, &gRated, &pgRated, &pg13Rated, &rRated, &nc17Rated);

    if (gRated == 25.0 && pgRated == 0.0 && pg13Rated == 0.0 && rRated == 200.0 && nc17Rated == 900.0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (Expected %.2f, %.2f, %.2f, %.2f %.2f but returned %.2f, %.2f, %.2f, %.2f, %.2f)\n",
               25.0, 0.0, 0.0, 200.0, 900.0, gRated, pgRated, pg13Rated, rRated, nc17Rated);
    }
}

void testSelection(int *totalTest, int *passedTest) {
    tMovieTable movies, result;
    tMovie movie1, movie2, movie3, movie4, movie5;
    tError retVal;

    printf("=================================================\n");
    printf(" MOVIE SELECTION \n");
    printf("=================================================\n");

    printf("\nTest 1: Select movies on an empty table");
    (*totalTest)++;
    movieTableInit(&movies);
    movieTableInit(&result);

    movieTableSelectMovies(movies, 5000.0, &result);
    if (result.nMovies == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0,
               result.nMovies);
    }

    getMovieObject(MOVIE1, &movie1);
    getMovieObject(MOVIE2, &movie2);
    getMovieObject(MOVIE3, &movie3);
    getMovieObject(MOVIE4, &movie4);
    movieTableAdd(&movies, movie1, &retVal);
    movieTableAdd(&movies, movie2, &retVal);
    movieTableAdd(&movies, movie3, &retVal);
    movieTableAdd(&movies, movie4, &retVal);

    printf("\nTest 2: Movies with income lower than 10000 euros");
    (*totalTest)++;
    movieTableSelectMovies(movies, 10000.0, &result);
    if (result.nMovies == 0) {
        printf("\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0,
               result.nMovies);
    }

    getMovieObject(MOVIE5, &movie5);
    movieTableAdd(&movies, movie5, &retVal);

    printf("\nTest 3: Movies with income lower than 20000 euros");
    (*totalTest)++;
    movieTableSelectMovies(movies, 20000.0, &result);;
    if (result.nMovies == 2) {
        if ((movieCmp(result.table[0], movie1) != 0) ||
            (movieCmp(result.table[1], movie5) != 0)) {
            printf("\n\t-> FAIL (Values are not correct)\n");
        } else {
            printf("\n\t-> OK\n");
            (*passedTest)++;
        }
    } else {
        printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2,
               result.nMovies);
    }
}