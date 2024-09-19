#pragma GCC diagnostic ignored "-Wpointer-arith"

#include <cstddef>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sort_text.h"
#include "text_data.h"
#include "utils.h"
#include "color_scheme.h"

#define LINE_DATA_DEFINE(type, struct_param, line_struct, object) type struct_param = (*((LINE_DATA* )line_struct)).object;

int compare_strings_starts(const void *line_struct1, const void *line_struct2) {
	assert(line_struct1 && "compare strings assert fucked up");
	assert(line_struct2);

    LINE_DATA_DEFINE(char*, letter1_ptr, line_struct1, lines_pointers);
    LINE_DATA_DEFINE(char*, letter2_ptr, line_struct2, lines_pointers);

    LINE_DATA_DEFINE(size_t, line1_length, line_struct1, lines_lengths);
    LINE_DATA_DEFINE(size_t, line2_length, line_struct2, lines_lengths);

    size_t letter1_index = 0;
    size_t letter2_index = 0;

    while (letter1_index < line1_length && letter2_index < line2_length) {
        printf("%c %c\n", letter1_ptr[letter1_index], letter2_ptr[letter2_index]);
        while (!is_letter(letter1_ptr[letter1_index]) && !is_apostrophe(letter1_ptr[letter1_index])) {
            letter1_index++;
        }
        while (!is_letter(letter2_ptr[letter2_index]) && !is_apostrophe(letter2_ptr[letter2_index])) {
            letter2_index++;
        }
        if (letter1_ptr[letter1_index] != letter2_ptr[letter2_index]) {
            return (int) (letter1_ptr[letter1_index] - letter2_ptr[letter2_index]);
        }
        else {
            letter1_index++;
            letter2_index++;
            continue;
        }
    }
    return 0;
}

int compare_strings_ends(const void* line_struct1, const void* line_struct2) {
	assert(line_struct1);
	assert(line_struct2);

    LINE_DATA_DEFINE(char*, letter1_ptr, line_struct1, lines_pointers);
    LINE_DATA_DEFINE(char*, letter2_ptr, line_struct2, lines_pointers);

    LINE_DATA_DEFINE(size_t, line1_length, line_struct1, lines_lengths);
    LINE_DATA_DEFINE(size_t, line2_length, line_struct2, lines_lengths);

    size_t letter1_index = 0;
    size_t letter2_index = 0;

    while (letter1_index < line1_length && letter2_index < line2_length) {
        while (!is_letter(letter1_ptr[line1_length - letter1_index])) {
            letter1_index++;
        }
        while (!is_letter(letter2_ptr[line2_length - letter2_index])) {
            letter2_index++;
        }
        if (letter1_ptr[line1_length - letter1_index] != letter2_ptr[line2_length - letter2_index]) {
            return (int) (letter1_ptr[line1_length - letter1_index] - letter2_ptr[line2_length - letter2_index]);
        }
        else {
            letter1_index++;
            letter2_index++;
            continue;
        }
    }
    return 0;
}

int custom_qsort(void* array, size_t el_count, size_t el_size, compare_func_t compare_func) {
    assert(array);
    assert(compare_func);

    partition(array, el_count, el_size, compare_func);

    return 0;
}

int is_letter(const char symbol) {
    return (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z');
}

int is_apostrophe(const char symbol) {
    return (symbol == '\'');
}

int partition(void* array, size_t el_count, size_t el_size, compare_func_t compare_func) {
    if (el_count == 1) {
        return 0;
    }

    size_t left_side  = 0;
    size_t right_side = el_count - 1;
    size_t separator  = el_count / 2;

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
