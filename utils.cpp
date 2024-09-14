#include <string.h>
#include <assert.h>

#include "utils.h"

int delete_extra_spaces(TEXT_DATA *TextData, size_t start_digit_index, size_t line_pointer_index) {
    assert(TextData);

    size_t check_digit_index = start_digit_index + 1;
    while (TextData->text[check_digit_index] == ' '  ||

           TextData->text[check_digit_index] == '\'') {
           check_digit_index++;
           }

    TextData->lines_pointers[line_pointer_index] = &(TextData->text[check_digit_index]);
    TextData->lines_lengths [line_pointer_index] = strlen( &(TextData->text[check_digit_index]) );

    return 0;
}
