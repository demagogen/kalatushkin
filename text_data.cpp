#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <cstdio>


#include "text_data.h"
#include "utils.h"
#include "color_scheme.h"




int count_digits(FILE *file_handle, TEXT_DATA *TextData) {
    assert(file_handle);
    assert(TextData);

    //TODO maybe better to return count digits and put it in TextData in main
    ERROR_DATA error_inf = PROGRAM_ERROR;
    if (!TextData) {
        error_inf = ALLOCATION_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "*TextData null pointer in count_digits\n");
        return -1;
    }

    fseek(file_handle, 0, SEEK_END); //TODO fstat safer faster
    TextData->digits = ftell(file_handle);
    fseek(file_handle, 0, SEEK_SET);

    return 0;
}




int fill_text(FILE *file_handle, TEXT_DATA *TextData) {
    assert(file_handle);
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;
    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "*TextData null pointer in fill_text\n");
        return -1;
    }

    if (!file_handle) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "*fp null pointer in fill_text\n");
        return -1;
    }

    TextData->text = (char*) calloc(TextData->digits + 1, sizeof(char));
    if (!TextData->text) {
        error_inf = ALLOCATION_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "calloc allocation error in fill_text\n");
        return -1;
    }

    fread(TextData->text, sizeof(char), TextData->digits, file_handle);

    separate_text_on_strings   (TextData);
    count_strings              (TextData);
    //delete_punctuation_endings (TextData);
    fill_lines_pointers        (TextData);

    return 0;
}




int separate_text_on_strings(TEXT_DATA *TextData) {
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;
    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "*fp null pointer in separate_text_on_strings\n");
        return -1;
    }

    for (size_t digit_index = 0; digit_index < TextData->digits; digit_index++) {
        if (TextData->text[digit_index] == '\n') {
            TextData->text[digit_index] =  '\0';
        }
    }

    return 0;
}




int count_strings(TEXT_DATA *TextData) {
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;
    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        return -1;
    }

    TextData->lines = -1;

    for (size_t digit_index = 0; digit_index < TextData->digits; digit_index++) {
        if (TextData->text[digit_index] == '\0') {
            TextData->lines++;
        }
    }

    return 0;
}




int fill_lines_pointers(TEXT_DATA *TextData) {
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;
    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        return -1;
    }

    size_t line_pointer_index = 0;
    TextData->LineData = (LINE_DATA*) calloc(TextData->digits, sizeof(LINE_DATA));
    TextData->LineData[line_pointer_index].lines_pointers =        TextData->text;
    TextData->LineData[line_pointer_index].lines_lengths  = strlen(TextData->text);

    printf("%d\n", TextData->digits);
    for (size_t digit_index = 0; digit_index < TextData->digits; digit_index++) {
        if (TextData->text[digit_index] == '\0') {

            delete_extra_spaces(TextData, digit_index, line_pointer_index);

            line_pointer_index++;
        }
    }

    return 0;
}




int print_text(FILE *file_handle, TEXT_DATA *TextData) {
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;
    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        return -1;
    }

    for (size_t line_index = 0; line_index < TextData->lines; line_index++) {
        if (TextData->text[line_index] != '\0' || TextData->text[line_index] != '\n') {

            if (TextData->LineData[line_index].lines_lengths == 0) {
                continue;
            }

printf("%10p %10d %10d ", TextData->LineData[line_index].lines_pointers, line_index, TextData->LineData[line_index].lines_lengths);
printf("(");
            fputs(TextData->LineData[line_index].lines_pointers, file_handle);
printf(")");
printf("\n");
        }
    }

    return 0;
}




int free_text_data(TEXT_DATA *TextData) {
    assert(TextData);

    free(TextData->LineData);
    free(TextData->text);

    return 0;
}
