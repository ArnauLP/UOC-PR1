#include <stdio.h>
#include <string.h>

#include "../include/data.h"
#include "../include/menu.h"
#include "../include/cinema.h"
#include "../include/movie.h"
#include "../include/purchase.h"

int getOption(int numOptions) {
    int option = 0;

    while (option < 1 || option > numOptions) {
        /* Read the input */
        printf(">> ");
        scanf("%u", &option);
        getchar();

        /* Check the user input */
        if (option < 1 || option > numOptions) {
            printf("Incorrect option.\n");
        }
    }
    return option;
}

void readMovie(tMovie *movie, tError *retVal) {

    *retVal = ERROR;
/**************** EX 2 *******************/
    movie->income = 0;

    *retVal = ERROR;

    char buffer[MAX_LINE];
    int number, length, hour, minute, i, rows, seatsPerRow;
    tScreen screen;

    while (*retVal == ERROR) {
        printf("Movie id (integer between 1 and %d):\n>> ", MAX_CINEMAS);
        scanf("%d", &number);
        if (number >= 1 && number <= MAX_CINEMAS) {
            movie->movieId = (tMovieId) (number);
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Movie title (max %d char, no spaces):\n>> ", MAX_NAME - 1);
        scanf("%s", buffer);
        length = strlen(buffer);
        if (length < MAX_NAME) {
            strncpy(movie->title, buffer, MAX_NAME);
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Movie duration (format HH:MM):\n>> ");
        scanf("%d:%d", &hour, &minute);
        if (hour >= 0 && minute >= 0 && minute <= 59) {
            movie->duration.hour = hour;
            movie->duration.minute = minute;
            *retVal = OK;
        }
    }

    //TODO: POSAR ENUMS
    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Movie rate (1 digit being (0 = G_RATED, 1 = PG_RATED, 2 = PG13_RATED, 3 = R_RATED, 4 = NC17_RATED) ):\n>> ");
        scanf("%d", &number);
        if (number >= 0 && number <= 4) {
            movie->rate = (tMovieRate) (number);
            *retVal = OK;
        }
    }

    printf("Movie income: ");
    scanf("%f", &movie->income);

/*****************************************/
}

void readCinema(tCinema *cinema, tError *retVal) {

    *retVal = ERROR;

    char buffer[MAX_LINE];
    int number, length, hour, minute, i, rows, seatsPerRow;
    tScreen screen;

    while (*retVal == ERROR) {
        printf("Cinema id (integer between 1 and %d):\n>> ", MAX_CINEMAS);
        scanf("%d", &number);
        if (number >= 1 && number <= MAX_CINEMAS) {
            cinema->cinemaId = (tCinemaId) (number);
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Cinema name (max %d char, no spaces):\n>> ", MAX_NAME - 1);
        scanf("%s", buffer);
        length = strlen(buffer);
        if (length < MAX_NAME) {
            strncpy(cinema->name, buffer, MAX_NAME);
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Cinema city (max %d char, no spaces):\n>> ", MAX_NAME - 1);
        scanf("%s", buffer);
        length = strlen(buffer);
        if (length < MAX_NAME) {
            strncpy(cinema->city, buffer, MAX_NAME);
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Cinema type (1 digit being 0=PREMIERE 1=RERELEASE 2=INDIE 3=OTHER):\n>> ");
        scanf("%d", &number);
        if (number >= 0 && number <= 3) {
            cinema->type = (tCinemaType) (number);
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Cinema opening time (format HH:MM):\n>> ");
        scanf("%d:%d", &hour, &minute);
        if (hour >= 0 && minute >= 0 && minute <= 59) {
            cinema->openingTime.hour = hour;
            cinema->openingTime.minute = minute;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Cinema closing time (format HH:MM):\n>> ");
        scanf("%d:%d", &hour, &minute);
        if (hour >= 0 && minute >= 0 && minute <= 59) {
            cinema->closingTime.hour = hour;
            cinema->closingTime.minute = minute;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Cinema number of screens (integer greater or equal to 1 and less or equal to %d)\n>> ", MAX_SCREENS);
        scanf("%d", &number);
        if (number >= 1 && number <= MAX_SCREENS) {
            *retVal = OK;
        }
    }

    i = 0;
    screenTableInit(&cinema->screens);
    while ((i < number) && (*retVal == OK)) {
        printf("Screen #%d capacity. Described as rows x seats in each row (format ROWSxSEATS)\n>> ", i + 1);
        scanf("%d%[^0-9]%d", &rows, buffer, &seatsPerRow);
        if (rows >= 1 && rows <= MAX_ROWS && seatsPerRow >= 1 && seatsPerRow <= MAX_SEATS_PER_ROW) {
            screen.screenId = (cinema->cinemaId * 10) + i + 1;
            screen.rows = rows;
            screen.seatsPerRow = seatsPerRow;
            screen.capacity = rows * seatsPerRow;
            screen.sessions.nSessions = 0;
            screenTableAdd(&cinema->screens, screen, retVal);
            i++;
        } else
            printf("Number of rows must be between 1 and %d, seats per row must be between 1 and %d.\n>> ", MAX_ROWS,
                   MAX_SEATS_PER_ROW);
    }
}

void printSession(tSession session, int rows, int seatsPerRow, int index) {
    char sessionStr[MAX_LINE];
    getSessionStr(session, rows, seatsPerRow, MAX_LINE, sessionStr, false);
    printf("[%u] - %s\n", index, sessionStr);
}

void printSessionTable(tSessionTable table, int rows, int seatsPerRow) {

    int i;

    if (table.nSessions == 0) {
        printf("No sessions.\n");
    } else {
        for (i = 0; i < table.nSessions; i++) {
            printSession(table.table[i], rows, seatsPerRow, i + 1);
        }
    }
}

void printScreen(tScreen cinema, int index) {
    char screenStr[MAX_LINE];
    getScreenStr(cinema, MAX_LINE, screenStr);
    printf("[%u] - %s\n", index, screenStr);
}

void printScreenTable(tScreenTable table) {

    int i;

    if (table.nScreens == 0) {
        printf("No screens.\n");
    } else {
        for (i = 0; i < table.nScreens; i++) {
            printScreen(table.table[i], i + 1);
        }
    }
}

void printCinema(tCinema cinema, int index) {
    char cinemaStr[MAX_LINE];
    getCinemaStr(cinema, MAX_LINE, cinemaStr);
    printf("[%u] - %s\n", index, cinemaStr);
}

void printCinemaTable(tCinemaTable table) {

    int i;

    if (table.nCinemas == 0) {
        printf("No cinemas.\n");
    } else {
        for (i = 0; i < table.nCinemas; i++) {
            printCinema(table.table[i], i + 1);
        }
    }
}

void printMovie(tMovie movie, int index) {
    char movieStr[MAX_LINE];
    getMovieStr(movie, MAX_LINE, movieStr);
    printf("[%u] - %s\n", index, movieStr);
}

void printMovieTable(tMovieTable table) {
    int i;

    if (table.nMovies == 0) {
        printf("No movies.\n");
    } else {
        for (i = 0; i < table.nMovies; i++) {
            printMovie(table.table[i], i + 1);
        }
    }
}

void printPurchase(tPurchase purchase, int index) {
    char purchaseStr[MAX_LINE];
    getPurchaseStr(purchase, MAX_LINE, purchaseStr);
    printf("[%u] - %s\n", index, purchaseStr);
}

void printPurchaseTable(tPurchaseTable table) {

    int i;

    if (table.nPurchases == 0) {
        printf("No purchases.\n");
    } else {
        for (i = 0; i < table.nPurchases; i++) {
            printPurchase(table.table[i], i + 1);
        }
    }
}

/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Main Menu \n");
    printf("=======================\n");
    printf("1) Load data from file\n");
    printf("2) Save data to file\n");
    printf("3) Manage movies\n");
    printf("4) Manage cinemas\n");
    printf("5) Manage purchases\n");
    printf("6) View statistics\n");
    printf("7) Exit\n");
}

tMainMenuOptions getMainMenuOption() {
    /* Convert to the correct type */
    return (tMainMenuOptions) (getOption(7) - 1);
}

void mainMenu(tAppData *appData) {
    tMainMenuOptions option;
    tError retVal;

    /* Assign the data path */
    appDataSetPath(appData, "../");

    /* Start the menu */

    /* Show list of options and ask the user for an option */
    printMainMenuOptions();
    option = getMainMenuOption();

    while (option != MAIN_MENU_EXIT) {
        /* Do the action for the given option */
        if (option == MAIN_MENU_LOAD) {
            appDataLoad(appData, &retVal);
            if (retVal == OK) {
                printf("Data loaded\n");
            } else {
                printf("No previous data loaded\n");
            }
        } else if (option == MAIN_MENU_SAVE) {
            appDataSave(*appData, &retVal);
            if (retVal == OK) {
                printf("Data saved\n");
            } else {
                printf("Cannot save the data\n");
            }
        } else if (option == MAIN_MENU_MOVIE) {
            movieMenu(appData);
        } else if (option == MAIN_MENU_CINEMA) {
            cinemaMenu(appData);
        } else if (option == MAIN_MENU_PURCHASE) {
            purchaseMenu(appData);
        } else if (option == MAIN_MENU_STAT) {
            statMenu(*appData);
        }

        /* Show list of options and ask the user for an option */
        printMainMenuOptions();
        option = getMainMenuOption();
    }
}

/*********************************
 **   MOVIE MANAGEMENT MENU **
*********************************/
void printMovieMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Manage Movies\n");
    printf("=======================\n");
    printf("1) List movies\n");
    printf("2) Add movie\n");
    printf("3) Delete movie\n");
    printf("4) Clear all movies\n");
    printf("5) Select movies filtered by income\n");
    printf("6) Exit\n");
}

tMovieMenuOptions getMovieMenuOption() {
    /* Convert to the correct type */
    return (tMovieMenuOptions) (getOption(6) - 1);
}

void movieMenu(tAppData *appData) {
    tMovieMenuOptions option;
    tMovie newMovie;
    tMovieTable movieTable, resultTable;
    char movieStr[MAX_LINE];
    int i, pos = 0, skipped;
    float income;
    tError retVal;

    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printMovieMenuOptions();
    option = getMovieMenuOption();

    while (option != MOVIE_MENU_EXIT) {
        /* Do the action for the given option */
        if (option == MOVIE_MENU_LIST) {
            getMovies(*appData, &movieTable);
            printMovieTable(movieTable);
        } else if (option == MOVIE_MENU_ADD) {
            printf("Enter the information for the new movie:\n");
            readMovie(&newMovie, &retVal);
            getMovieStr(newMovie, MAX_LINE, movieStr);
            if (retVal == OK) {
                addMovie(appData, newMovie, &retVal);
                if (retVal == OK) {
                    printf("Movie added: %s\n", movieStr);
                } else if (retVal == ERR_DUPLICATED_ENTRY) {
                    printf("Duplicated movie not added: %s\n", movieStr);
                } else {
                    printf("No more space. Movie not added: %s\n", movieStr);
                }
            } else {
                printf("Error in input. Movie not added: \n%s\n", movieStr);
            }
        } else if (option == MOVIE_MENU_DEL) {
            getMovies(*appData, &movieTable);
            /* Print the movies */
            printMovieTable(movieTable);

            if (movieTable.nMovies > 0) {
                /* Ask the number of the register to be removed */
                printf("Enter the number of the movie to delete:\n");
                pos = getOption(movieTable.nMovies);

                /* Remove the selected movie */
                if (isMovieProgrammed(*appData, movieTable.table[pos - 1]))
                    printf("This movie could not be removed because it is programmed in, at least, one cinema\n");
                else
                    removeMovie(appData, movieTable.table[pos - 1]);
            }
        } else if (option == MOVIE_MENU_CLEAR_ALL) {
            skipped = 0;
            getMovies(*appData, &movieTable);
            for (i = movieTable.nMovies - 1; i >= 0; i--) {
                if (isMovieProgrammed(*appData, movieTable.table[i]))
                    skipped++;
                else
                    removeMovie(appData, movieTable.table[i]);
            }
            if (skipped > 0)
                printf("Some movies cannot not be removed because they're programmed in, at least, one cinema\n");

        } else if (option == MOVIE_MENU_SELECT_MOVIES) {

            printf("Maximum income to filter movies:\n");
            scanf("%f", &income);
            getMovies(*appData, &movieTable);
            movieTableSelectMovies(movieTable, income, &resultTable);
            printMovieTable(resultTable);

        }

        /* Show list of options and ask the user for an option */
        printMovieMenuOptions();
        option = getMovieMenuOption();
    }
}

/********************************
 **   CINEMA MANAGEMENT MENU **
********************************/
void printCinemaMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Manage cinemas\n");
    printf("=======================\n");
    printf("1) List cinemas\n");
    printf("2) Add cinema\n");
    printf("3) List sessions\n");
    printf("4) Add session\n");
    printf("5) List cinemas by type\n");
    printf("6) List multiscreen cinemas\n");
    printf("7) Exit\n");
}

tCinemaMenuOptions getCinemaMenuOption() {
    /* Convert to the correct type */
    return (tCinemaMenuOptions) (getOption(7) - 1);
}

void cinemaMenu(tAppData *appData) {
    tError retVal = OK;
    tCinemaMenuOptions option;
    tCinemaTable cinemaTable, typeTable, multiscreenTable;
    tMovieTable movieTable;
    tCinema newCinema;
    char cinemaStr[MAX_LINE];
    int type, pCinema, pScreen, pMovie, nScreens;
    int cinemaId, screenId, movieId;
    int i, j, k, rows, seatsPerRow;

    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printCinemaMenuOptions();
    option = getCinemaMenuOption();

    while (option != CINEMA_MENU_EXIT) {
        /* Do the action for the given option */
        if (option == CINEMA_MENU_LIST) {
            getCinemas(*appData, &cinemaTable);
            printCinemaTable(cinemaTable);
        } else if (option == CINEMA_MENU_ADD) {
            readCinema(&newCinema, &retVal);
            getCinemaStr(newCinema, MAX_LINE, cinemaStr);
            if (retVal == OK) {
                addCinema(appData, newCinema, &retVal);
                if (retVal == ERR_DUPLICATED_ENTRY) {
                    printf("ERROR: A cinema with the same ID already exists\n");
                } else {
                    printf("Cinema added: %s\n", cinemaStr);
                }
            } else {
                printf("Error in input. Cinema not added: \n%s\n", cinemaStr);
            }
        } else if (option == CINEMA_MENU_ADD_SESSION) {

            getCinemas(*appData, &cinemaTable);
            /* Print the cinemas */
            printCinemaTable(cinemaTable);

            if (cinemaTable.nCinemas > 0) {
                /* Ask the number of the cinema  */
                printf("Enter the number of the cinema:\n");
                pCinema = getOption(cinemaTable.nCinemas);

                /* Print the screens */
                printScreenTable(cinemaTable.table[pCinema - 1].screens);
                nScreens = cinemaTable.table[pCinema - 1].screens.nScreens;
                if (nScreens > 0) {
                    /* Ask the number of the screen  */
                    printf("Enter the number of the screen:\n");
                    pScreen = getOption(nScreens);

                    getMovies(*appData, &movieTable);
                    /* Print the movies */
                    printMovieTable(movieTable);
                    if (movieTable.nMovies > 0) {
                        /* Ask the number of the cinema  */
                        printf("Enter the number of the movie:\n");
                        pMovie = getOption(movieTable.nMovies);

                        /* Try to add the session */
                        cinemaId = cinemaTable.table[pCinema - 1].cinemaId;
                        screenId = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].screenId;
                        movieId = movieTable.table[pMovie - 1].movieId;

                        addSession(appData, cinemaId, screenId, movieId, &retVal);

                        if (retVal == OK) {
                            printf("Session added\n");
                        } else if (retVal == ERR_NO_FREE_GAP) {
                            printf("No gap in the screen schedule. Unable to add the session\n");
                        } else {
                            printf("Inconsistent data. Session not added\n");
                        }
                    }
                }
            }

        } else if (option == CINEMA_MENU_LIST_SESSIONS) {

            getCinemas(*appData, &cinemaTable);
            for (i = 0; i < cinemaTable.nCinemas; i++) {
                printCinema(cinemaTable.table[i], i + 1);

                for (j = 0; j < cinemaTable.table[i].screens.nScreens; j++) {
                    printf("\t");
                    printScreen(cinemaTable.table[i].screens.table[j], j + 1);
                    rows = cinemaTable.table[i].screens.table[j].rows;
                    seatsPerRow = cinemaTable.table[i].screens.table[j].seatsPerRow;

                    for (k = 0; k < cinemaTable.table[i].screens.table[j].sessions.nSessions; k++) {
                        printf("\t\t");
                        printSession(cinemaTable.table[i].screens.table[j].sessions.table[k], rows, seatsPerRow, k + 1);
                    }
                }
            }

        } else if (option == CINEMA_MENU_TYPE) {
            getCinemas(*appData, &cinemaTable);
            printf("Cinema type (1 digit being 0=PREMIERE 1=RERELEASE 2=INDIE 3=OTHER):\n>> ");
            scanf("%d", &type);
            cinemaTableFilterByType(cinemaTable, (tCinemaType) type, &typeTable);
            printCinemaTable(typeTable);
        } else if (option == CINEMA_MOVIES_MULTISCREEN) {
            getCinemas(*appData, &cinemaTable);
            cinemaTableFilterByMultiscreen(cinemaTable, &multiscreenTable);
            printCinemaTable(multiscreenTable);
        }

        /* Show list of options and ask the user for an option */
        printCinemaMenuOptions();
        option = getCinemaMenuOption();
    }
}

/*********************
 **   PURCHASE MENU **
**********************/

void printTickets(tPurchase purchase, tCinema cinema, tScreen screen, tSession session, tMovie movie) {
/**************** EX 5 *******************/
/*
 * a partir d’una compra, del cinema, la sala, la sessió i la pel·lícula, mostri per pantalla tots els tiquets
 * de cadascuna de les localitats adquirides en la compra. Per cada tiquet s’ha de mostrar: nom del cinema,
 * títol de la pel·lícula, número de sala, hora d’inici de la sessió, fila i seient.
*/

    //mostrar tiquets
    printf("Ticket 1 [Test]");
//mostrar tot

    for (int i = 0; i < purchase.purchasedSeats; ++i) {
        printf("Nom del cinema: %s", cinema.name);
        printf("Nom pel·lícula: %s", movie.title);
        printf("ID de la sessio: %d", session.sessionId);
        printf("Hora d' inici: %d", cinema.openingTime.hour);
        printf("Fila: %d", purchase.seats[i].row); //fila
        printf("Seient: %d", purchase.seats[i].seatInRow);// seient
    }
/*****************************************/
}

void printPurchaseMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Purchase \n");
    printf("=======================\n");
    printf("1) List purchases\n");
    printf("2) Purchase tickets for a movie\n");
    printf("3) Print purchase tickets\n");
    printf("4) View session occupation\n");
    printf("5) Assign seats to pendant purchases\n");
    printf("6) Exit\n");
}

tPurchaseMenuOptions getPurchaseMenuOption() {
    /* Convert to the correct type */
    return (tPurchaseMenuOptions) (getOption(6) - 1);
}

void purchaseMenu(tAppData *appData) {
    tError retVal;
    tPurchaseMenuOptions option;
    tCinemaTable cinemaTable;
    tPurchaseTable purchaseTable;
    int pCinema, pScreen, pSession, pPurchase, pMovie, movieId;
    int nScreens, nSessions, rows, seatsPerRow;
    int selectedSeat, selectedRow, number;
    tPurchase purchase;
    tCinema cinema;
    tScreen screen;
    tSession session;
    tMovie movie;
    bool ok;

    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printPurchaseMenuOptions();
    option = getPurchaseMenuOption();

    while (option != PURCHASE_MENU_EXIT) {
        /* Do the action for the given option */
        if (option == PURCHASE_MENU_TICKETS) {

            getCinemas(*appData, &cinemaTable);
            /* Print the cinemas */
            printCinemaTable(cinemaTable);

            if (cinemaTable.nCinemas > 0) {
                /* Ask the number of the cinema  */
                printf("Enter the number of the cinema:\n");
                pCinema = getOption(cinemaTable.nCinemas);

                /* Print the screens */
                printScreenTable(cinemaTable.table[pCinema - 1].screens);
                nScreens = cinemaTable.table[pCinema - 1].screens.nScreens;
                if (nScreens > 0) {
                    /* Ask the number of the screen  */
                    printf("Enter the number of the screen:\n");
                    pScreen = getOption(nScreens);

                    /* Print the sessions */
                    rows = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].rows;
                    seatsPerRow = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].seatsPerRow;
                    printSessionTable(cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions, rows,
                                      seatsPerRow);
                    nSessions = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions.nSessions;
                    if (nSessions > 0) {
                        /* Ask the number of the session  */
                        printf("Enter the number of the session:\n");
                        pSession = getOption(nSessions);

                        /* Ask the number of seats  */
                        ok = false;
                        while (!ok) {
                            printf("Enter the number of seats (value between %d and %d):\n>> ", 1,
                                   MAX_SEATS_PER_PURCHASE);
                            scanf("%d", &number);
                            ok = (number > 0 && number <= MAX_SEATS_PER_PURCHASE);
                        }

                        /* Find seats  */
                        findSeats(
                                cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions.table[pSession - 1],
                                rows, seatsPerRow, number, &selectedRow, &selectedSeat);
                        if (selectedSeat != NO_ROW && selectedSeat != NO_SEAT_IN_ROW) {
                            /* Assign seats  */
                            assignSeats(&appData->cinemas.table[pCinema - 1].screens.table[pScreen - 1].sessions.table[
                                                pSession - 1],
                                        number, selectedRow, selectedSeat);

                            /* Create a purchase  */
                            createPurchase(&purchase,
                                           cinemaTable.table[pCinema - 1].cinemaId,
                                           cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].screenId,
                                           cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions.table[
                                                   pSession - 1].sessionId,
                                           number, selectedRow, selectedSeat);

                            /* Add the purchase  */
                            purchaseTableAdd(&appData->purchases, purchase, &retVal);

                            /* Update the movie income */
                            movieId = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions.table[
                                    pSession - 1].movieId;
                            pMovie = movieTableFind(appData->movies, movieId);
                            if (pMovie == NO_MOVIE)
                                printf("Seats successfully assigned. Purchase confirmed.\n");
#ifdef TYPEDEF_COMPLETED
                            else {
                                appData->movies.table[pMovie].income += purchase.price;
                                printf("Seats successfully assigned. Purchase confirmed. Movie '%s'.\n",
                                       appData->movies.table[pMovie].title);
                            }
#endif
                        } else
                            printf("Unable to assign %d consecutive seats in this session. Purchase cancelled\n",
                                   number);
                    }
                }
            }

        } else if (option == PURCHASE_MENU_VIEW_SESSION_OCCUPATION) {

            getCinemas(*appData, &cinemaTable);
            /* Print the cinemas */
            printCinemaTable(cinemaTable);

            if (cinemaTable.nCinemas > 0) {
                /* Ask the number of the cinema  */
                printf("Enter the number of the cinema:\n");
                pCinema = getOption(cinemaTable.nCinemas);

                /* Print the screens */
                printScreenTable(cinemaTable.table[pCinema - 1].screens);
                nScreens = cinemaTable.table[pCinema - 1].screens.nScreens;
                if (nScreens > 0) {
                    /* Ask the number of the screen  */
                    printf("Enter the number of the screen:\n");
                    pScreen = getOption(nScreens);

                    /* Print the sessions */
                    rows = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].rows;
                    seatsPerRow = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].seatsPerRow;
                    printSessionTable(cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions, rows,
                                      seatsPerRow);
                    nSessions = cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions.nSessions;
                    if (nSessions > 0) {
                        /* Ask the number of the session  */
                        printf("Enter the number of the session:\n");
                        pSession = getOption(nSessions);
                        /* Pretty-print the session seat map */
                        printSessionSeatMap(
                                cinemaTable.table[pCinema - 1].screens.table[pScreen - 1].sessions.table[pSession - 1],
                                rows, seatsPerRow);
                    }
                }
            }

        } else if (option == PURCHASE_MENU_PRINT_TICKETS) {

            getPurchases(*appData, &purchaseTable);
            /* Print the purchases */
            printPurchaseTable(purchaseTable);

            if (purchaseTable.nPurchases > 0) {
                /* Ask the number of the purchase  */
                printf("Enter the number of the purchase:\n");
                pPurchase = getOption(purchaseTable.nPurchases);

                /* Get the required information for the tickets */
                getCinema(*appData, purchaseTable.table[pPurchase - 1].cinemaId, &cinema, &retVal);
                getScreen(*appData, purchaseTable.table[pPurchase - 1].cinemaId,
                          purchaseTable.table[pPurchase - 1].screenId, &screen, &retVal);
                getSession(*appData, purchaseTable.table[pPurchase - 1].cinemaId,
                           purchaseTable.table[pPurchase - 1].screenId,
                           purchaseTable.table[pPurchase - 1].sessionId, &session, &retVal);
                getMovie(*appData, session.movieId, &movie, &retVal);

                /* do the printing */
                printTickets(purchaseTable.table[pPurchase - 1], cinema, screen, session, movie);
            }

        } else if (option == PURCHASE_MENU_PROCESS_PURCHASES) {

            processAllPurchases(appData, &retVal);

        } else if (option == PURCHASE_MENU_LIST) {

            getPurchases(*appData, &purchaseTable);
            /* Print the purchases */
            printPurchaseTable(purchaseTable);
        }

        /* Show list of options and ask the user for an option */
        printPurchaseMenuOptions();
        option = getPurchaseMenuOption();
    }
}

/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Stats \n");
    printf("=======================\n");
    printf("1) Get average movie duration\n");
    printf("2) Get movies income per rate\n");
    printf("3) Get average cinemas occupation of a city\n");
    printf("4) Exit\n");
}

tStatMenuOptions getStatMenuOption() {
    /* Convert to the correct type */
    return (tStatMenuOptions) (getOption(4) - 1);
}

void statMenu(tAppData appData) {
    tStatMenuOptions option;
    tMovieTable movieTable;
    tCinemaTable cinemaTable;
    char cityStr[MAX_LINE];
    float gRated, pgRated, pg13Rated, rRated, nc17Rated;
    tTime avgTime;

    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printStatMenuOptions();
    option = getStatMenuOption();

    while (option != STAT_MENU_EXIT) {
        /* Do the action for the given option */
        if (option == STAT_MENU_MOVIE_AVG_DURATION) {
            getMovies(appData, &movieTable);
            movieTableGetAvgDuration(movieTable, &avgTime);
            printf("Average movie duration is: %2d:%2d\n", avgTime.hour, avgTime.minute);

        } else if (option == STAT_MENU_MOVIE_INCOME_PER_RATE) {
            getMovies(appData, &movieTable);
            movieTableGetIncomePerRate(movieTable,
                                       &gRated, &pgRated, &pg13Rated, &rRated, &nc17Rated);

            printf("Income of G-RATED movies is: %.2f\n", gRated);
            printf("Income of PG-RATED movies is: %.2f\n", pgRated);
            printf("Income of PG13-RATED movies is: %.2f\n", pg13Rated);
            printf("Income of R-RATED movies is: %.2f\n", rRated);
            printf("Income of NC17-RATED movies is: %.2f\n", nc17Rated);

        } else if (option == STAT_MENU_NUM_CINEMA_AVG_OCCUPATION) {
            getCinemas(appData, &cinemaTable);
            printf("City where cinema is (max %d char, no spaces):\n>> ", MAX_NAME - 1);
            scanf("%s", cityStr);
            convertToUpper(cityStr);
            printf("Average occupation of cinemas in %s is %.2f %%\n",
                   cityStr, cinemaTableComputeAverageOccupation(cinemaTable, cityStr));
        }

        /* Show list of options and ask the user for an option */
        printStatMenuOptions();
        option = getStatMenuOption();
    }
}
