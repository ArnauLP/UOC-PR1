#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/movie.h"

void getMovieStr(tMovie movie, int maxSize, char *str) {
#ifdef TYPEDEF_COMPLETED
    snprintf(str,maxSize-1,"%d %s %02d:%02d %d %.2f",
        movie.movieId, movie.title, movie.duration.hour, movie.duration.minute,
        movie.rate, movie.income);
#endif
}

void getMovieObject(const char *str, tMovie *movie) {
#ifdef TYPEDEF_COMPLETED
    int id= 0, rate= 0;
    sscanf(str, "%d %s %d:%d %d %f", &(id), movie->title, &movie->duration.hour,
        &movie->duration.minute, &rate, &movie->income);
    movie->movieId = (tMovieId)(id);
    movie->rate= (tMovieRate)(rate);
#endif
}

int dateCmp(tDate d1, tDate d2) {

    int result;

    result = 0;

    if (d1.year > d2.year)
        result = 1;
    else if (d1.year < d2.year)
        result = -1;
    else {
        if (d1.month > d2.month)
            result = 1;
        else if (d1.month < d2.month)
            result = -1;
        else {
            if (d1.day > d2.day)
                result = 1;
            else if (d1.day < d2.day)
                result = -1;
        }
    }

    return result;
}

void dateCpy(tDate *d1, tDate d2) {
    d1->year = d2.year;
    d1->month = d2.month,
            d1->day = d2.day;
}

void movieTableInit(tMovieTable *movieTable) {

    movieTable->nMovies = 0;
}

void convertToUpper(char *string) {
    int i, len;
    char originalChar;

    len = strlen(string);
    for (i = 0; i < len; i++) {
        originalChar = string[i];
        if (originalChar >= 'a' && originalChar <= 'z')
            string[i] = originalChar + 'A' - 'a';
    }
}

int strcmpUpper(char *s1, char *s2) {
    int result = 0;
    char string1[MAX_LINE];
    char string2[MAX_LINE];

    strcpy(string1, s1);
    strcpy(string2, s2);
    convertToUpper(string1);
    convertToUpper(string2);

    result = strcmp(string1, string2);

    return result;
}

int movieCmp(tMovie m1, tMovie m2) {

    int result = 0;
/**************** EX 6B *******************/












/******************************************/

    return result;
}

void movieCpy(tMovie *dst, tMovie src) {
/**************** EX 6A *******************/







/*****************************************/
}

/*
 * donada una taula de tipus tMovieTable i una pel·lícula de tipus tMovie, afegeixi
la pel·lícula dins la taula. Si no hi ha espai en la taula per afegir la pel·lícula,
haureu de retornar el codi ERR_MEMORY en la variable retVal. Altrament,
retorneu OK.
 */
void movieTableAdd(tMovieTable *tabMovie, tMovie movie, tError *retVal) {

    *retVal = OK;

/**************** EX 1B *******************/

    bool found = false;
    int i = 0;

    strcpy(tabMovie->table->title, movie.title);
    tabMovie->table->duration = movie.duration;
    tabMovie->table->rate = movie.rate;
    tabMovie->table->income = movie.income;

/******************************************/
}

int movieTableFind(tMovieTable tabMovie, tMovieId id) {

    int idx = NO_MOVIE;

    int i = 0;
    while (i < tabMovie.nMovies && idx == NO_MOVIE) {
        /* Check if the id is the same */
        if (tabMovie.table[i].movieId == id) {
            idx = i;
        }
        i++;
    }

    return idx;
}

void movieTableDel(tMovieTable *tabMovie, tMovie movie) {
/**************** EX 1C *******************/








/******************************************/
}

void movieTableSave(tMovieTable tabMovie, const char *filename, tError *retVal) {

    *retVal = OK;

    FILE *fout = NULL;
    int i;
    char str[MAX_LINE];

    /* Open the output file */
    if ((fout = fopen(filename, "w")) == 0) {
        *retVal = ERR_CANNOT_WRITE;
    } else {

        /* Save all movies to the file */
        for (i = 0; i < tabMovie.nMovies; i++) {
            getMovieStr(tabMovie.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }

        /* Close the file */
        fclose(fout);
    }
}

void movieTableLoad(tMovieTable *tabMovie, const char *filename, tError *retVal) {

    *retVal = OK;

    FILE *fin = NULL;
    char line[MAX_LINE];
    tMovie newMovie;

    /* Initialize the output table */
    movieTableInit(tabMovie);

    /* Open the input file */
    if ((fin = fopen(filename, "r")) != NULL) {

        /* Read all the lines */
        while (!feof(fin) && tabMovie->nMovies < MAX_MOVIES) {
            /* Remove any content from the line */
            line[0] = '\0';
            /* Read one line (maximum 511 chars) and store it in "line" variable */
            fgets(line, MAX_LINE - 1, fin);
            /* Ensure that the string is ended by 0*/
            line[MAX_LINE - 1] = '\0';
            if (strlen(line) > 0) {
                /* Obtain the object */
                getMovieObject(line, &newMovie);
                /* Add the new movie to the output table */
                movieTableAdd(tabMovie, newMovie, retVal);
            }
        }
        /* Close the file */
        fclose(fin);

    } else {
        *retVal = ERR_CANNOT_READ;
    }
}

void movieTableSelectMovies(tMovieTable movies, float maxIncome, tMovieTable *result) {
    int i;
    tError retVal;
    bool selected = false;

    movieTableInit(result);
    for (i = 0; i < movies.nMovies; i++) {
#ifdef TYPEDEF_COMPLETED
        selected= (movies.table[i].income < maxIncome);
#endif
        if (selected) {
            movieTableAdd(result, movies.table[i], &retVal);
        }
    }
}

void movieTableGetAvgDuration(tMovieTable tabMovie, tTime *avgTime) {
/**************** EX 8B *******************/










/*******************************************/
}

void movieTableGetIncomePerRate(tMovieTable tabMovie,
                                float *gRated, float *pgRated, float *pg13Rated, float *rRated, float *nc17Rated) {
    *gRated = 0.0;
    *pgRated = 0.0;
    *pg13Rated = 0.0;
    *rRated = 0.0;
    *nc17Rated = 0.0;

/**************** EX 8C *******************/











/******************************************/
}

