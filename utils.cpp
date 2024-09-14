#include <string.h>
#include <assert.h>
#include <stdlib.h>

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




int swap(void *value1, void *value2, size_t size) {
    assert(value1);
    assert(value2);

    void *change_helper = calloc(1, size);
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
