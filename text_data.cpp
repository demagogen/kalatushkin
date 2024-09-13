#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>

#include "text_data.h"

int fill_text(FILE *fp, TEXT_DATA *TextData) {
    assert(fp);
    assert(TextData);

    TextData->text = (char*) calloc(TextData->digits + 1, sizeof(char));
    fread(TextData->text, sizeof(char), TextData->digits, fp);

    separate_text_on_strings(TextData);
    fill_lines_pointers(TextData);

    return 0;
}




int separate_text_on_strings(TEXT_DATA *TextData) {
    assert(TextData);

    TextData->lines = 0;

    for (size_t digit_index = 0; digit_index < TextData->digits; digit_index++) {
        if (TextData->text[digit_index] == '\n') {
            TextData->text[digit_index]  = '\0';
            TextData->lines++;
        }
    }

    return 0;
}




int fill_lines_pointers(TEXT_DATA *TextData) {
    assert(TextData);

    size_t line_pointer_index = 0;
    TextData->lines_pointers = (char **) calloc(TextData->digits, sizeof(char *));
    TextData->lines_lengths  = (int   *) calloc(TextData->lines , sizeof(int   ));

    TextData->lines_pointers[line_pointer_index] = TextData->text;
    TextData->lines_lengths [line_pointer_index] = strlen(TextData->text);

    printf("%d\n", TextData->digits);
    for (size_t digit_index = 0; digit_index < TextData->digits - 1; digit_index++) { //digit_index interval under TextData->digits - 1!
        if (TextData->text[digit_index] == '\0') {
            TextData->lines_pointers[line_pointer_index] = &(TextData->text[digit_index + 1]);
            /********/
            TextData->lines_lengths [line_pointer_index] = strlen( &(TextData->text[digit_index + 1]) );
            /********/
            printf("%10p %10d\n", TextData->lines_pointers[line_pointer_index], TextData->lines_lengths[line_pointer_index]);

            line_pointer_index++;
            }
        }

    return 0;
}




int print_text(TEXT_DATA *TextData) {
    assert(TextData);

    printf("TextData->lines = %d\n", TextData->lines);

    for (size_t line_index = 0; line_index < TextData->lines - 1; line_index++) { //works, but almost dont understand why TextData->lines - 1
        //printf("%10p\n", TextData->lines_pointers[line_index]);
        fputs(TextData->lines_pointers[line_index], stdout);
        printf("\n");
    }

    return 0;
}
