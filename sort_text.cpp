#include <cstddef>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sort_text.h"
#include "text_data.h"
#include "utils.h"
#include "color_scheme.h"




int bubble_sort(TEXT_DATA *TextData) {
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;

    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "*TextData null pointer in bubble_sort\n");
        return -1;
    }

    for (size_t sort_index = 0; sort_index < TextData->lines; sort_index++) {
        for (size_t line_index = 0; line_index < TextData->lines - sort_index - 1; line_index++) {
            if (strcmp(TextData->lines_pointers[line_index], TextData->lines_pointers[line_index + 1]) > 0) {

                swap(&(TextData->lines_pointers[line_index]), &(TextData->lines_pointers[line_index + 1]), sizeof(char*));
                swap(&(TextData->lines_lengths [line_index]),  &(TextData->lines_lengths [line_index + 1]),  sizeof(int  ));
            }
        }
    }

    return 0;
}




int sort_endings(TEXT_DATA *TextData) {
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;

    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "*TextData null pointer in sort_endings\n");
        return -1;
    }

    const char *punctuation = ".,!?:-'`";
    for (size_t sort_index = 0; sort_index < TextData->lines; sort_index++) {
        for (size_t line_index = 0; line_index < TextData->lines - sort_index - 1; line_index++) {
            printf("obvious obvious obvious obvious\n");
            const char* line1 = TextData->lines_pointers[line_index]     + TextData->lines_lengths[line_index] - 2;
            const char* line2 = TextData->lines_pointers[line_index + 1] + TextData->lines_lengths[line_index + 1] - 2;
            printf("and here and here and here and here\n");
            printf("%s\n%s\n", line1, line2);
            if (strcmp(line1, line2) < 0) {
printf("maybe here?\n");
printf("%p\n%p\n", TextData->lines_pointers[line_index], TextData->lines_pointers[line_index + 1]);
printf("%d\n%d\n", TextData->lines_lengths [line_index], TextData->lines_lengths [line_index + 1]);
                swap(&(TextData->lines_pointers[line_index]), &(TextData->lines_pointers[line_index + 1]), sizeof(char*));
                swap(&(TextData->lines_lengths [line_index]), &(TextData->lines_lengths [line_index + 1]), sizeof(int  ));
printf("almsot lamost lamost lamost lamost lamost\n");
            }
        }
    }

    return 0;
}




int partition(void *array, int start, int end, size_t size, compare_func_t comparing_function) {
    assert(array);

    ERROR_DATA error_inf = PROGRAM_ERROR;

    if (!array) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "null pointer on array in partition\n");
        return -1;
    }

    if (start < end) {
        int pivotIndex = rand() % end;
        void *separator = (char *)array + pivotIndex * size;
        int i_index = start;
        int j_index = end;

        while (i_index <= j_index) {
            while (comparing_function((char *)array + i_index * size, separator) < 0) i_index++;
            while (comparing_function((char *)array + j_index * size, separator) > 0) j_index--;

            if (i_index <= j_index) {
                swap((char *)array + i_index * size, (char *)array + j_index * size, size);
                i_index++;
                j_index--;
            }
        }

        partition(array, start, j_index, size, comparing_function);
        partition(array, i_index, end, size, comparing_function);
    }

    return 0;
}





int my_qsort(void *array, size_t quantity, size_t elSize, compare_func_t comparing_function) {
    assert(array);

    ERROR_DATA error_inf = PROGRAM_ERROR;

    if (!array) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "null pointer on array in my_qsort\n");
        return -1;
    }

    partition(array, 0, quantity - 1, elSize, comparing_function);

    return 0;
}




int compare_strings(const void *line1, const void *line2) {
    const char *str1 = *((const char **)line1);
    const char *str2 = *((const char **)line2);
    return strcmp(str1, str2);
}
