#include "sort_bus_lines.h"

void swap (BusLine *a, BusLine *b)
{
  BusLine temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort (BusLine *start, BusLine *end)
{
  size_t buslines_num = end - start;
  size_t i, j;
  for (i = 0; i < buslines_num; i++)
  {
    for (j = 0; j < buslines_num - i - 1; j++)
    {
      if ((strcmp ((start + j + 1)->name, (start + j)->name)) < 0)
      {
        swap ((start + j), (start + j + 1));
      }
    }
  }
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  size_t buslines_num = end - start;
  int small_idx = -1;
  BusLine *pivot = end - 1;
  size_t j;
  for (j = 0; j < buslines_num - 1; j++)
  {
    if (sort_type == DURATION)
    {
      if ((start + j)->duration <= pivot->duration)
      {
        small_idx++;
        swap (start + small_idx, start + j);
      }
    }
    else
    {
      if ((start + j)->distance < pivot->distance)
      {
        small_idx++;
        swap (start + small_idx, start + j);
      }

    }
  }
  swap (start + small_idx + 1, pivot);
  return start + small_idx + 1;

}

void quick_sort (BusLine *start, BusLine *end, SortType E)
{
  if (start < end - 1)
  {
    BusLine *pivot = partition (start, end, E);
    quick_sort (start, pivot, E);
    quick_sort (pivot + 1, end, E);
  }
}