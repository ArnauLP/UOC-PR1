/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Test the table addition and deletion */
void testTableOperation(int *totalTest, int *passedTest);

/* Test the programming of sessions */
void testSessionProgramming(int *totalTest, int *passedTest);

/* Test the seats assignment */
void testSeatsAssignment(int *totalTest, int *passedTest);

/* Test the cinemas filtering actions */
void testCinemasFilters(int *totalTest, int *passedTest);

/* Test the copy and comparison of movies */
void testCpyCmp(int *totalTest, int *passedTest);

/* Test the selection calls */
void testSelection(int *totalTest, int *passedTest);

/* Test the statistics calls */
void testStatistics(int *totalTest, int *passedTest);

