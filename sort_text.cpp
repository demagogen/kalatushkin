#include <cstddef>
#include <assert.h>
#include <string.h>

#include "sort_text.h"
#include "text_data.h"

int bubble_sort(TEXT_DATA *TextData) {
    assert(TextData);

    for (size_t sort_index = 0; sort_index < TextData->lines; sort_index++) {
        for (size_t line_index = 0; line_index < TextData->lines - sort_index - 1; line_index++) {
            if (strcmp(TextData->lines_pointers[line_index], TextData->lines_pointers[line_index + 1]) > 0) {
                char* change_pointer_helper = TextData->lines_pointers[line_index];
                TextData->lines_pointers[line_index] = TextData->lines_pointers[line_index + 1];
                TextData->lines_pointers[line_index + 1] = change_pointer_helper;
            }
        }
    }

    return 0;
}
