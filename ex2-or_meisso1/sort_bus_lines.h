#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
#include <string.h>

#define NAME_LEN 21
/**
 * a struct of buslines that include their name, distance and duration
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

/**
 * enum for two types of quick sort
 */
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * swaps pointers of two elements
 * @param a
 * @param b
 */
void swap (BusLine *a, BusLine *b);

/**
 * sorts a list of bus lines by name
 * @param start pointer to the starting index
 * @param end pointer to the ending index
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * sorts a list of bus lines by distance or by duration
 */
void quick_sort (BusLine *start, BusLine *end, SortType E);

/**
 * helping function to quick sort
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);


// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
