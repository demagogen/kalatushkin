#ifndef SORT_TEXT_H_
#define SORT_TEXT_H_

#include <cstdio>

#include "text_data.h"

typedef int (*compare_func_t)(const void *, const void *);

int bubble_sort            (TEXT_DATA *TextData);
int sort_endings           (TEXT_DATA *TextData);
void my_qsort              (void *array, size_t el_size, int start, int end, compare_func_t compare_function);
int compare_strings_starts (const void *line1, const void *line2);
int compare_strings_ends   (const void *line_struct1, const void *line_struct2);

#endif
