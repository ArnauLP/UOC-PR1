#include "data.h"

/* Get a textual representation of a session within the screen */
void getSessionStr(tSession session, int rows, int seatsPerRow, int maxSize, char *str, bool seatsMap);

/* Get a textual representation of a screen within the cinema */
void getScreenStr(tScreen screen, int maxSize, char *str);

/* Get a textual representation of a cinema */
void getCinemaStr(tCinema cinema, int maxSize, char *str);

/* Get a session object from its textual representation */
void getSessionObject(const char *str, int rows, int seatsPerRow, tSession *session);

/* Get a screen object from its textual representation */
void getScreenObject(const char *str, tScreen *screen);

/* Get a cinema object from its textual representation */
void getCinemaObject(const char *str, tCinema *cinema);

/* Inits a session */
void sessionInit(tSession *session);

/* Copy the session data in src to dst*/
void sessionCpy(tSession *dst, tSession src);

/* Copy the screen data in src to dst*/
void screenCpy(tScreen *dst, tScreen src);

/* Copy the cinema data in src to dst*/
void cinemaCpy(tCinema *dst, tCinema src);

/* Compares the cinema data of p1 and p2*/
int cinemaCmp(tCinema p1, tCinema p2);

/* Initializes the given sessions table */
void sessionTableInit(tSessionTable *sessionTable);

/* Add a new session to the table of sessions */
void sessionTableAdd(tSessionTable *tabSessions, tSession session, tError *retVal);

/* Find a session in the table */
int sessionTableFind(tSessionTable tabSessions, tSessionId id);

/* Initializes the given screens table */
void screenTableInit(tScreenTable *screenTable);

/* Add a new screen to the table of screens */
void screenTableAdd(tScreenTable *tabScreens, tScreen screen, tError *retVal);

/* Find a screen in the table */
int screenTableFind(tScreenTable tabScreens, tScreenId id);

/* Initializes the given cinemas table */
void cinemaTableInit(tCinemaTable *cinemaTable);

/* Add a new cinema to the table of cinemas */
void cinemaTableAdd(tCinemaTable *tabCinemas, tCinema cinema, tError *retVal);

/* Find a cinema in the table */
int cinemaTableFind(tCinemaTable tabCinemas, tCinemaId id);

/* Load the table of cinemas from a file */
void cinemaTableLoad(tCinemaTable *tabCinemas, const char *filename, tError *retVal);

/* Save a table of cinemas to a file */
void cinemaTableSave(tCinemaTable tabCinemas, const char *filename, tError *retVal);

/* Obtain from a table of cinemas those of a given type */
void cinemaTableFilterByType(tCinemaTable tabCinemas, tCinemaType type, tCinemaTable *result);

/* Obtain from a table of cinemas those that are multi-screen */
void cinemaTableFilterByMultiscreen(tCinemaTable tabCinemas, tCinemaTable *result);

/* Obtain from a table of cinemas those that are of type premiere and multi-screen */
void cinemaTableGetMultiscreenPremiereCinemas(tCinemaTable tabCinemas, tCinemaTable *result);

/* Obtain the average occupacion of the given screen */
float screenAverageOccupation(tScreen screen);

/* Obtain the average occupacion of the given cinema */
float cinemaAverageOccupation(tCinema cinema);

/* Obtain from a table of cinemas the average occupation by city */
float cinemaTableComputeAverageOccupation(tCinemaTable tabCinema, char *city);

/* Prints the session' seat map */
void printSessionSeatMap(tSession session, int rows, int seatsPerRow);

/* Assigns a number of seats in the selected row and seat */
void assignSeats(tSession *session, int number, int selectedRow, int selectedSeat);

/* Finds a number of consecutive seats in the given session */
void findSeats(tSession session, int rows, int seatsPerRow, int numberOfSeats,
               int *selectedRow, int *selectedSeat);

