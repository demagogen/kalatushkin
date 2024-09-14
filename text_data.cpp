#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <cstdio>


#include "text_data.h"
#include "utils.h"
#include "sort_text.h"

int fill_text(FILE *fp, TEXT_DATA *TextData) {
    assert(fp);
    assert(TextData);

          TextData->text = (char*) calloc(TextData->digits + 1, sizeof(char));
    fread(TextData->text, sizeof(char), TextData->digits, fp);

    separate_text_on_strings(TextData);
    fill_lines_pointers     (TextData);

    return 0;
}




int separate_text_on_strings(TEXT_DATA *TextData) {
    assert(TextData);

    TextData->lines = -1; //cause after first iteration will be first string with 0 number

    for (size_t digit_index = 0; digit_index < TextData->digits; digit_index++) { //TextData->digits - 1 cause
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

    TextData->lines_pointers[line_pointer_index] =        TextData->text ;
    TextData->lines_lengths [line_pointer_index] = strlen(TextData->text);

    printf("%d\n", TextData->digits);
    for (size_t digit_index = 0; digit_index < TextData->digits; digit_index++) { //digit_index interval under TextData->digits - 1!
        if (TextData->text[digit_index] == '\0') {

            delete_extra_spaces(TextData, digit_index, line_pointer_index);

            line_pointer_index++;
        }
    }

    return 0;
}




int print_text(TEXT_DATA *TextData) {
    assert(TextData);

    for (size_t line_index = 0; line_index < TextData->lines; line_index++) { //works, but almost dont understand why TextData->lines - 1
        if (TextData->text[line_index] != '\0' || TextData->text[line_index] != '\n') {

            if (TextData->lines_lengths[line_index] == 0) {
                continue;
            }

            printf("%10p %10d %10d ", TextData->lines_pointers[line_index], line_index, TextData->lines_lengths[line_index]);
            printf("(");
            fputs(TextData->lines_pointers[line_index], stdout);
            printf(")");
            printf("\n");
        }
    }

    return 0;
}




int free_text_data(TEXT_DATA *TextData) {
    assert(TextData);

    free(TextData->lines_lengths );
    free(TextData->lines_pointers);
    free(TextData->text          );

    return 0;
}
