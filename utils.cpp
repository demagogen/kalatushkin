#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h> // TODO unused header

#include "utils.h"
#include "color_scheme.h"




int delete_extra_spaces(TEXT_DATA *TextData, size_t start_digit_index, size_t line_pointer_index) {
    assert(TextData);

    ERROR_DATA error_inf = PROGRAM_ERROR;

    if (!TextData) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "*TextData null pointer in delete_extra_spaces\n");
        return -1;
    }

    size_t check_digit_index = start_digit_index + 1;
    while (TextData->text[check_digit_index] == ' '  ||
           TextData->text[check_digit_index] == '\'') {
           check_digit_index++;
           }

    TextData->LineData[line_pointer_index].lines_pointers = &(TextData->text[check_digit_index]);
    TextData->LineData[line_pointer_index].lines_lengths  = strlen( &(TextData->text[check_digit_index]) );

    return 0;
}



// TODO remove
//int delete_punctuation_endings(TEXT_DATA *TextData) {
//    assert(TextData);
//
//    ERROR_DATA error_inf = PROGRAM_ERROR;
//
//    if (!TextData) {
//        error_inf = MEMORY_ERROR;
//        error_data_enum(error_inf);
//        graphic_printf(RED, BOLD, "*TextData null pointer in delete_punctuation_endings\n");
//        return -1;
//    }
//
//    for (size_t digit_index = TextData->digits; digit_index > 1; digit_index--) {
//        if (TextData->text[digit_index] == '\0' && strchr(punctuation, TextData->text[digit_index - 1]) != 0) {
//            printf("start\n");
//            TextData->text[digit_index - 1] = '\0';
//        }
//    }
//
//    return 0;
//}




const char* error_data_enum(ERROR_DATA error_inf){
    switch(error_inf) {
        case PROGRAM_ERROR:
            return "PROGRAM_ERROR";
            break;

        case INPUT_ERROR:
            return "INPUT_ERROR";
            break;

        case MEMORY_ERROR:
            return "MEMORY_ERROR";
            break;

        case FILE_ERROR:
            return "FILE_ERROR";
            break;

        case ALLOCATION_ERROR:
            return "ALLOCATION_ERROR";
            break;

        default:
            return "UNKNOWN_ERROR";
            break;
    }
}




int swap(void *value1, void *value2, size_t size) {
    assert(value1);
    assert(value2);

    ERROR_DATA error_inf = PROGRAM_ERROR;

    if (!value1 || !value2 || size == 0) {
        error_inf = MEMORY_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "null pointer in swap\n");
    }

    void *change_helper = calloc(1, size); // TODO get rid of calloc (maybe use for cycle...)
    if (change_helper == NULL) {
        perror("Failed to allocate memory");
        return -1;
    }

    memcpy(change_helper, value1, size);
    memcpy(value1, value2, size);
    memcpy(value2, change_helper, size);

    free(change_helper);

    return 0;
}
