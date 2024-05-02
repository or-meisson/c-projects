#include "test_bus_lines.h"

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  size_t buslines_num = end - start;
  if (buslines_num <= 1)
  {
    return 1;
  }
  for (size_t i = 0; i < buslines_num - 1; i++)
  {
    if ((start + i + 1)->distance < (start + i)->distance)
    {
      return 0;
    }
  }
  return 1;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  size_t buslines_num = end - start;
  if (buslines_num <= 1)
  {
    return 1;
  }
  for (size_t i = 0; i < buslines_num - 1; i++)
  {
    if ((start + i + 1)->duration < (start + i)->duration)
    {
      return 0;
    }
  }
  return 1;
}

int is_sorted_by_name (BusLine *start, BusLine *end)
{
  size_t buslines_num = end - start;
  if (buslines_num <= 1)
  {
    return 1;
  }
  for (size_t i = 0; i < buslines_num - 1; i++)
  {
    BusLine *cur_ptr = (start + i);
    BusLine *next_ptr = (start + i + 1);
    if (strcmp (cur_ptr->name, next_ptr->name) > 0)
    { return 0; }

  }
  return 1;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  size_t buslines_num_original = end_original - start_original;
  size_t buslines_num_sorted = end_sorted - start_sorted;
  if (buslines_num_original != buslines_num_sorted)
  { return 0; }
  {
    size_t num_reviewed = 0;
    for (size_t i = 0; i < buslines_num_original; i++)
    {
      if (num_reviewed == buslines_num_sorted)
      { return 0; }
      num_reviewed = 0;
      for (size_t j = 0; j < buslines_num_sorted; j++)
      {
        if ((start_original + i) == (start_sorted + j))
        {
          break;
        }
        num_reviewed += 1;
      }
      num_reviewed += 1;
    }
  }
  return 1;
}