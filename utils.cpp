#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "utils.h"
#include "color_scheme.h"

#define ull unsigned long long


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

    TextData->LineData[line_pointer_index].lines_pointers =         &(TextData->text[check_digit_index]);
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




//int swap(void *value1, void *value2, size_t size) {
//    assert(value1);
//    assert(value2);
//
//    ERROR_DATA error_inf = PROGRAM_ERROR;
//    if (!value1 || !value2 || size == 0) {
//        error_inf = MEMORY_ERROR;
//        error_data_enum(error_inf);
//        graphic_printf(RED, BOLD, "null pointer in swap\n");
//    }
//
//    void* temp = &value1;
//    value1 = value2;
//    value2 = temp;
//
//    return 0;
//}

int swap(void *value1, void *value2, size_t size) {
    assert(value1);
    assert(value2);
    assert(size);

    ull* array_ull1 = (ull* ) value1;
    ull* array_ull2 = (ull* ) value2;
    size_t iteration_number = size / sizeof(ull);

    for (size_t index = 0; index < iteration_number; index++) {
        ull buffer        = array_ull1[index];
        array_ull1[index] = array_ull2[index];
        array_ull2[index] = buffer;
    }

    if ((size - iteration_number * sizeof(ull)) / sizeof(int) == 1) {
        int* array_int1 = (int* ) ((int* ) array_ull1 + sizeof(ull) * iteration_number);
        int* array_int2 = (int* ) ((int* ) array_ull2 + sizeof(ull) * iteration_number);
        int buffer    = array_int1[0];
        array_int1[0] = array_int2[0];
        array_int2[0] = buffer;
    }

    if ((size - iteration_number * sizeof(ull) - sizeof(int)) / sizeof(short int) == 1) {
        short int* array_sint1 = (short int* ) ((short int* ) array_ull1 + sizeof(ull) * iteration_number + sizeof(int));
        short int* array_sint2 = (short int* ) ((short int* ) array_ull2 + sizeof(ull) * iteration_number + sizeof(int));
        short int buffer = array_sint1[0];
        array_sint1[0]   = array_sint2[0];
        array_sint2[0]   = buffer;
    }

    if ((size - iteration_number * sizeof(ull) - sizeof(int) - sizeof(short int)) / sizeof(char) == 1) {
        char* array_char1 = (char* ) ((char* ) array_ull1 + sizeof(ull) * iteration_number + sizeof(int) + sizeof(short int));
        char* array_char2 = (char* ) ((char* ) array_ull2 + sizeof(ull) * iteration_number + sizeof(int) + sizeof(short int));
        char buffer    = array_char1[0];
        array_char1[0] = array_char2[0];
        array_char2[0] = buffer;
    }

    return 0;
}
