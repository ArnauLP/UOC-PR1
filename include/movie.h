#include "data.h"

/* Get a textual representation of a movie */
void getMovieStr(tMovie movie, int maxSize, char *str);

/* Get a movie object from its textual representation */
void getMovieObject(const char *str, tMovie *movie);

/* Compare two dates */
int dateCmp(tDate d1, tDate d2);

/* Compares two strings in uppercase */
int strcmpUpper(char *s1, char *s2);

/* Converts an string to upper case */
void convertToUpper(char *string);

/* Compare two movies */
int movieCmp(tMovie movie1, tMovie movie2);

/* Copy the movie data in src to dst*/
void movieCpy(tMovie *dst, tMovie src);

/* Initialize the table of movies */
void movieTableInit(tMovieTable *table);

/* Add a new movie to the table of movies */
void movieTableAdd(tMovieTable *table, tMovie movie, tError *retVal);

/* Find a movie in the table and returns its position */
int movieTableFind(tMovieTable table, tMovieId id);

/* Remove the first occurence of a movie in the table */
void movieTableDel(tMovieTable *table, tMovie movie);

/* Load the table of movies from a file */
void movieTableLoad(tMovieTable *table, const char *filename, tError *retVal);

/* Save a table of movies to a file */
void movieTableSave(tMovieTable table, const char *filename, tError *retVal);

/* Selects movies to promote (those with a maximum income) */
void movieTableSelectMovies(tMovieTable movies, float maxIncome, tMovieTable *result);

/* Calculates the average movie duration  */
void movieTableGetAvgDuration(tMovieTable tabMovie, tTime *time);

/* Calculates the income per movie rate */
void movieTableGetIncomePerRate(tMovieTable tabMovie,
                                float *gRated, float *pgRated, float *pg13Rated, float *rRated, float *nc17Rated);
