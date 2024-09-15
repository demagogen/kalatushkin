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
            if (strcmp(TextData->LineData[line_index].lines_pointers, TextData->LineData[line_index + 1].lines_pointers) > 0) {

                swap(&(TextData->LineData[line_index].lines_pointers), &(TextData->LineData[line_index + 1].lines_pointers), sizeof(char*));
                swap(&(TextData->LineData[line_index].lines_lengths ), &(TextData->LineData[line_index + 1].lines_lengths ),  sizeof(int  ));
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
            const char* line1 = TextData->LineData[line_index].lines_pointers     + TextData->LineData[line_index].lines_lengths - 2;
            const char* line2 = TextData->LineData[line_index + 1].lines_pointers + TextData->LineData[line_index + 1].lines_lengths - 2;
            printf("and here and here and here and here\n");
            printf("%s\n%s\n", line1, line2);
            if (strcmp(line1, line2) < 0) {
printf("maybe here?\n");
printf("%p\n%p\n", TextData->LineData[line_index].lines_pointers, TextData->LineData[line_index + 1].lines_pointers);
printf("%d\n%d\n", TextData->LineData[line_index].lines_lengths, TextData->LineData[line_index + 1].lines_lengths  );
                swap(&(TextData->LineData[line_index].lines_pointers), &(TextData->LineData[line_index + 1].lines_pointers), sizeof(char*));
                swap(&(TextData->LineData[line_index].lines_lengths ), &(TextData->LineData[line_index + 1].lines_lengths ), sizeof(int  ));
printf("almsot lamost lamost lamost lamost lamost\n");
            }
        }
    }

    return 0;
}




int my_qsort(void *array, size_t el_size, int start, int end, compare_func_t compare_function)
{
    assert(array != nullptr);
    assert(el_size != 0);

    int separator = start;

    if (start <= end) {

        swap((array + start * el_size), (array + (separator * el_size)), el_size);

        for (int i_index = start + 1; i_index <= end; i_index++)
        {
            if (compare_function((char*)(array + i_index*el_size), (array + start*el_size))  < 0)
            {
                separator++;
                swap((array + separator * el_size), (array + i_index * el_size), el_size);
            }
        }
    }

    swap((array + start * el_size), (array + separator * el_size), el_size);
    my_qsort(array, el_size, start, separator - 1, compare_function);
    my_qsort(array, el_size, separator + 1, end, compare_function);

    return 0;
}




int compare_strings(const void *line_struct1, const void *line_struct2) {
    LINE_DATA *LineData1 = (LINE_DATA*)line_struct1;
    LINE_DATA *LineData2 = (LINE_DATA*)line_struct2;

    printf("%p %p\n", LineData1->lines_pointers, LineData2->lines_pointers);

    if (int result = strcmp (LineData1->lines_pointers, LineData2->lines_pointers) > 0) {
        swap(&(LineData1->lines_pointers), &(LineData2->lines_pointers), sizeof(char*));
        swap(&(LineData1->lines_lengths ), &(LineData2->lines_lengths ), sizeof(int *));
        return result;
    }
    else {
    return result;
    }
}
