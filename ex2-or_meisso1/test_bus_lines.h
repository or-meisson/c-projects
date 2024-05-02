#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H

#include "sort_bus_lines.h"

/**
 * checks if the BusLine array is sorted by distance
 * @param start
 * @param end
 * @return 1 if sorted by distance, 0 if not sorted by distance
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * checks if the BusLine array is sorted by duration
 * @param start
 * @param end
 * @return 1 if sorted by duration, 0 if not sorted by duration
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
 * checks if the busLines are sorted by name
 * @param start
 * @param end
 * @return 1 if sorted by name, 0 if not sorted by name
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * checks if the buslines before the sort and after the sort have the same
 * elements
 * @param start_sorted
 * @param end_sorted
 * @param start_original
 * @param end_original
 * @return 1 if have the same elements 0 if not
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);

#endif //EX2_REPO_TESTBUSLINES_H
