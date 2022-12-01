#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {
    MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_MOVIE,
    MAIN_MENU_CINEMA, MAIN_MENU_PURCHASE, MAIN_MENU_STAT,
    MAIN_MENU_EXIT
} tMainMenuOptions;

/* Define the movies management menu options type */
typedef enum {
    MOVIE_MENU_LIST, MOVIE_MENU_ADD, MOVIE_MENU_DEL,
    MOVIE_MENU_CLEAR_ALL, MOVIE_MENU_SELECT_MOVIES,
    MOVIE_MENU_EXIT
} tMovieMenuOptions;

/* Define the purchases management menu options type */
typedef enum {
    PURCHASE_MENU_LIST, PURCHASE_MENU_TICKETS, PURCHASE_MENU_PRINT_TICKETS,
    PURCHASE_MENU_VIEW_SESSION_OCCUPATION,
    PURCHASE_MENU_PROCESS_PURCHASES, PURCHASE_MENU_EXIT
} tPurchaseMenuOptions;

/* Define the cinemas management menu options type */
typedef enum {
    CINEMA_MENU_LIST, CINEMA_MENU_ADD,
    CINEMA_MENU_LIST_SESSIONS, CINEMA_MENU_ADD_SESSION,
    CINEMA_MENU_TYPE,
    CINEMA_MOVIES_MULTISCREEN,
    CINEMA_MENU_EXIT
} tCinemaMenuOptions;

/* Define the stats menu options type */
typedef enum {
    STAT_MENU_MOVIE_AVG_DURATION,
    STAT_MENU_MOVIE_INCOME_PER_RATE,
    STAT_MENU_NUM_CINEMA_AVG_OCCUPATION,
    STAT_MENU_EXIT
} tStatMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the movie management menu options */
void printMovieMenuOptions();

/* Get the option for the movie management menu */
tMovieMenuOptions getMovieMenuOption();

/* Perform the actions for the movie management menu */
void movieMenu(tAppData *appData);

/* Print the cinemas management menu options */
void printCinemaMenuOptions();

/* Get the option for the cinemas management menu */
tCinemaMenuOptions getCinemaMenuOption();

/* Perform the actions for the cinemas management menu */
void cinemaMenu(tAppData *appData);

/* Print the purchases menu options */
void printPurchaseMenuOptions();

/* Get the option for the purchase menu */
tPurchaseMenuOptions getPurchaseMenuOption();

/* Perform the actions for the purchase menu */
void purchaseMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the stats menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the stats menu */
void statMenu(tAppData appData);
