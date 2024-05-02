#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10
#define LINE_LEN 60
#define LINE_NAME_LEN 20
#define MAX_DURATION 100
#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MIN_DISTANCE 0

/**
 * enum for status of command or success/failure
 */
enum Status
{
    E_FAILURE,
    E_SUCCESS,
    E_BY_DURATION,
    E_BY_DISTANCE,
    E_BY_NAME,
    E_TEST
};

/**
 * a function that receives the users input and checks if its valid
 * returns its status based on the command given
 */
int get_and_validate_command (int argc, char *argv[])
{
  char *command = argv[1];
  if (argc != 2)
  {
    fprintf (stdout, "USAGE: Wrong argument number\n");
    return E_FAILURE;
  }
  if (strcmp (command, "by_duration") == 0)
  {
    return E_BY_DURATION;
  }
  if (strcmp (command, "by_distance") == 0)
  {
    return E_BY_DISTANCE;
  }
  if (strcmp (command, "by_name") == 0)
  {
    return E_BY_NAME;
  }
  if (strcmp (command, "test") == 0)
  {
    return E_TEST;
  }
  printf ("USAGE: Wrong command\n");
  return E_FAILURE;
}

/**
 * checks if the line name given is valid
 */
int check_line_name_validity (const char line_name[])
{
  int i = 0;
  while (line_name[i] != '\0')
  {
    if (!islower(line_name[i]) && !isdigit(line_name[i]))
    {
      return E_FAILURE;
    }
    i++;
  }
  return E_SUCCESS;
}

/**
receives the line info input from the user and checks if its valid
 */
int get_and_validate_line_info (size_t i, BusLine *all_bus)
{
  char line_info_str[LINE_LEN];
  fprintf (stdout, "Enter line info. Then enter\n");
  fgets (line_info_str, sizeof (line_info_str), stdin);
  char line_name[LINE_NAME_LEN];
  int distance, duration;
  int res = sscanf (line_info_str, "%[^,],%d,%d", line_name,
                    &distance, &duration);
  if (res != 3)
  {
    fprintf (stdout, "ERROR: input failed, try again\n");
    return E_FAILURE;
  }
  int line_name_len = sizeof line_name / sizeof line_name[0];
  int is_name_valid = check_line_name_validity (line_name);
  if (is_name_valid == E_FAILURE)
  {
    fprintf (stdout, "ERROR: bus name should contain"
                     " only digits and small chars\n");
    return E_FAILURE;
  }
  if (distance != (int) distance || distance > MAX_DISTANCE ||
      distance < MIN_DISTANCE)
  {
    fprintf (stdout, "ERROR: distance should be"
                     " an integer between 0 and 1000\n");
    return E_FAILURE;
  }
  if (duration != (int) duration || duration > MAX_DURATION ||
      duration < MIN_DURATION)
  {
    fprintf (stdout, "ERROR: duration should be"
                     " an integer between 10 and 100\n");
    return E_FAILURE;
  }
  for (int j = 0; j < line_name_len; j++)
  {
    all_bus[i].name[j] = line_name[j];
  }
  all_bus[i].distance = distance;
  all_bus[i].duration = duration;
  return E_SUCCESS;
}

/**
receives the num of lines input from the user and checks if its valid
 */
size_t get_and_validate_num_of_lines ()
{
  char num_of_lines_str[LINE_LEN];
  fprintf (stdout, "Enter number of lines. Then enter\n");
  fgets (num_of_lines_str, sizeof num_of_lines_str, stdin);
  size_t num_of_lines = (size_t) strtol (num_of_lines_str,
                                         NULL, BASE);
  if (num_of_lines <= 0)
  {
    fprintf (stdout, "ERROR: Number of lines should be"
                     " a positive integer\n");
    return E_FAILURE;
  }
  size_t i = 0;
  while (num_of_lines_str[i + 1] != '\0')
  {
    if (isdigit(num_of_lines_str[i]) == 0)
    {
      fprintf (stdout, "ERROR: Number of lines should be"
                       " a positive integer\n");
      return E_FAILURE;
    }
    i++;
  }
  return num_of_lines;
}

/**
tests if the sort by distance function is ok
 */
void test1_2 (BusLine *dest, size_t all_lines_len)
{
  BusLine *original_start_ptr = &dest[0];
  BusLine *original_end_ptr = &dest[all_lines_len - 1];
  quick_sort (dest, dest + all_lines_len, DISTANCE);
  if (is_sorted_by_distance (original_start_ptr, original_end_ptr))
  {
    fprintf (stdout, "TEST 1 PASSED.sorted by distance.\n");
  }
  else
  { fprintf (stdout, "TEST 1 FAILED.not sorted by distance.\n"); }
  BusLine *sorted_start_ptr = &dest[0];
  BusLine *sorted_end_ptr = &dest[all_lines_len - 1];
  if (is_equal (sorted_start_ptr, sorted_end_ptr,
                original_start_ptr, original_end_ptr))
  {
    fprintf (stdout, "TEST 2 PASSED.equal elements.\n");
  }
  else
  { fprintf (stdout, "TEST 2 FAILED.non equal elements.\n"); }
}

/**
tests if the sort by duration function is ok
 */
void test3_4 (BusLine *dest, size_t all_lines_len)
{
  BusLine *original_start_ptr = &dest[0];
  BusLine *original_end_ptr = &dest[all_lines_len];
  quick_sort (dest, dest + all_lines_len, DURATION);
  if (is_sorted_by_duration (original_start_ptr, original_end_ptr))
  {
    fprintf (stdout, "TEST 3 PASSED.sorted by duration.\n");
  }
  else
  { fprintf (stdout, "TEST 3 FAILED.not sorted by duration.\n"); }
  BusLine *sorted_start_ptr = &dest[0];
  BusLine *sorted_end_ptr = &dest[all_lines_len];
  if (is_equal (sorted_start_ptr, sorted_end_ptr,
                original_start_ptr, original_end_ptr))
  {
    fprintf (stdout, "TEST 4 PASSED.equal elements.\n");
  }
  else
  { fprintf (stdout, "TEST 4 FAILED.non equal elements.\n"); }
}

/**
tests if the sort by name function is ok
 */
void test5_6 (BusLine *dest, size_t all_lines_len)
{
  BusLine *original_start_ptr = &dest[0];
  BusLine *original_end_ptr = &dest[all_lines_len - 1];
  bubble_sort (dest, dest + all_lines_len);
  if (is_sorted_by_name (original_start_ptr, original_end_ptr))
  {
    fprintf (stdout, "TEST 5 PASSED.sorted by name.\n");
  }
  else
  { fprintf (stdout, "TEST 5 FAILED.not sorted by name.\n"); }
  BusLine *sorted_start_ptr = &dest[0];
  BusLine *sorted_end_ptr = &dest[all_lines_len - 1];
  if (is_equal (sorted_start_ptr, sorted_end_ptr,
                original_start_ptr, original_end_ptr))
  {
    fprintf (stdout, "TEST 6 PASSED.equal elements.\n");
  }
  else
  { fprintf (stdout, "TEST 6 FAILED.non equal elements.\n"); }
}

/**
prints the bus lines after sorted
 */
void print_sorted_array (BusLine *all_bus, size_t all_lines_len)
{
  size_t i = 0;
  while (i < all_lines_len)
  {
    fprintf (stdout, "%s,%d,%d\n", all_bus[i].name,
             all_bus[i].distance, all_bus[i].duration);
    i++;
  }
}

/**
 * a function that operates the tests and validates.
 */
int test (BusLine *all_bus, size_t all_lines_len)
{
  BusLine *dest = (BusLine *) malloc (all_lines_len * sizeof (BusLine));
  if (dest == NULL)
  {
    fprintf (stdout, "ERROR: memory allocation failed\n");
    return E_FAILURE;
  }
  memcpy (dest, all_bus, all_lines_len * sizeof (BusLine));
  test1_2 (dest, all_lines_len);
  test3_4 (dest, all_lines_len);
  test5_6 (dest, all_lines_len);
  free (dest);
  return E_SUCCESS;
}

/**
 * runs quick sort by distance and prints the result
 */
void run_quick_sort_by_distance (BusLine *all_bus, size_t all_lines_len)
{
  quick_sort (all_bus,
              all_bus + all_lines_len, DISTANCE);
  print_sorted_array (all_bus, all_lines_len);
}

/**
 * runs quick sort by duration and prints the result
 */
void run_quick_sort_by_duration (BusLine *all_bus, size_t all_lines_len)
{
  quick_sort (all_bus,
              all_bus + all_lines_len, DURATION);
  print_sorted_array (all_bus, all_lines_len);
}

/**
 * runs bubble sort by name and prints the result
 */
void run_bubble_sort (BusLine *all_bus, size_t all_lines_len)
{
  bubble_sort (all_bus, all_bus + all_lines_len);
  print_sorted_array (all_bus, all_lines_len);
}

/**
the main function that operates the program
 */
int main (int argc, char *argv[])
{
  int status = get_and_validate_command (argc, argv);
  if (status == E_FAILURE)
  {
    return EXIT_FAILURE;
  }
  size_t num_of_lines = get_and_validate_num_of_lines ();
  while (num_of_lines == 0)
  {
    num_of_lines = get_and_validate_num_of_lines ();
  }
  BusLine *all_bus = (BusLine *) malloc (num_of_lines * sizeof (BusLine));
  if (all_bus == NULL)
  {
    fprintf (stdout, "ERROR: memory allocation failed\n");
    return EXIT_FAILURE;
  }
  for (size_t i = 0; i < num_of_lines; i++)
  {
    int check = get_and_validate_line_info (i, all_bus);
    while (check == E_FAILURE)
    {
      check = get_and_validate_line_info (i, all_bus);
    }
  }
  size_t all_lines_len = num_of_lines;
  if (status == E_BY_NAME)
  {
    run_bubble_sort (all_bus, all_lines_len);
  }
  if (status == E_BY_DISTANCE)
  {
    run_quick_sort_by_distance (all_bus, all_lines_len);
  }
  if (status == E_BY_DURATION)
  {
    run_quick_sort_by_duration (all_bus, all_lines_len);
  }
  if (status == E_TEST)
  {
    int is_test_ok = test (all_bus, all_lines_len);
    if (!is_test_ok)
    {
      free (all_bus);
      return EXIT_FAILURE;
    }
  }
  free (all_bus);
  return EXIT_SUCCESS;
}