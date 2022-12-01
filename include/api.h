#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appDataInit(tAppData *object);

/* Load the application data from file */
void appDataLoad(tAppData *object, tError *error);

/* Save the application data to a file */
void appDataSave(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appDataSetPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Get the session information */
void getSession(tAppData object, tCinemaId cinemaId, tScreenId screenId, tSessionId sessionId,
                tSession *session, tError *retVal);

/* Get the screen information */
void getScreen(tAppData object, tCinemaId cinemaId, tScreenId screenId, tScreen *screen, tError *retVal);

/* Return a table with the movies */
void getMovies(tAppData object, tMovieTable *result);

/* Get the movie information */
void getMovie(tAppData object, tMovieId movieId, tMovie *movie, tError *retVal);

/* Add a new movie */
void addMovie(tAppData *object, tMovie movie, tError *retVal);

/* Add a new session of the movieId to a cinemas's screen */
void addSession(tAppData *object, tCinemaId cinemaId, tScreenId screenId, tMovieId movieId, tError *retVal);

/* Says if a certain movie is programmed in any screen of any cinema */
bool isMovieProgrammed(tAppData object, tMovie movie);

/* Remove a certain movie */
void removeMovie(tAppData *object, tMovie movie);

/* Return the table of cinemas */
void getCinemas(tAppData object, tCinemaTable *result);

/* Get the cinema information */
void getCinema(tAppData object, tCinemaId cinemaId, tCinema *cinema, tError *retVal);

/* Add a new cinema */
void addCinema(tAppData *object, tCinema cinema, tError *retVal);

/* Return a table with the purchases */
void getPurchases(tAppData object, tPurchaseTable *result);

/* Processes a single purchase */
void processPurchase(tPurchase *purchase, tCinemaTable *cinemas, tError *retVal);

/* Processes all purchases */
void processAllPurchases(tAppData *object, tError *retVal);
