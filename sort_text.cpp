#include <cstddef>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sort_text.h"
#include "text_data.h"
#include "utils.h"
#include "color_scheme.h"

int compare_strings_starts(const void *line_struct1, const void *line_struct2) {
    assert(line_struct1);
    assert(line_struct2);

    LINE_DATA* LineData1 = (LINE_DATA* )line_struct1;
    LINE_DATA* LineData2 = (LINE_DATA* )line_struct2;

    // TODO skip punctuation symbols except apostrophe
    return strcmp(LineData1->lines_pointers, LineData2->lines_pointers);
}

int compare_strings_ends(const void* line_struct1, const void* line_struct2) {
    assert(line_struct1);
    assert(line_struct2);

    LINE_DATA* LineData1 = (LINE_DATA* )line_struct1;
    LINE_DATA* LineData2 = (LINE_DATA* )line_struct2;

    const char* line1_end = LineData1->lines_pointers + LineData1->lines_lengths - 3;
    const char* line2_end = LineData2->lines_pointers + LineData2->lines_lengths - 3;

    // TODO write correct comparator
    return strcmp(LineData1->lines_pointers, LineData2->lines_pointers);
}

int custom_qsort(void* array, size_t el_count, size_t el_size, compare_func_t compare_func) {
    assert(array);
    assert(compare_func);

    if (el_count == 1) {
        return 0;
    }

    // TODO write separate case for 2 elems

    size_t left_side = 0;
    size_t right_side = el_count - 1;
    //size_t separator = rand() % el_count;
    size_t separator = el_count / 2;

    // TODO partition function
    while (left_side < right_side) {
        while (compare_func (array + left_side * el_size, array + separator * el_size) < 0 && left_side < el_count) {
            left_side++;
        }
        while (compare_func (array + separator * el_size, array + right_side * el_size) < 0 && right_side > 0) {
            right_side--;
        }

        if (left_side <= right_side) {
            swap(array + left_side * el_size, array + right_side * el_size, el_size);

            if (separator == left_side) {
                separator = right_side;
            }
            else if (separator == right_side) {
                separator = left_side;
            }

            left_side++;
            right_side--;
        }
    }

    if (right_side > 0) {
        custom_qsort(array, right_side + 1, el_size, compare_func);
    }
    if (left_side < el_count - 1) {
        custom_qsort(array + left_side * el_size, el_count - left_side, el_size, compare_func);
    }

    return 0;
}
