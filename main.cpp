#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h> //useless header

#include "text_data.h"
#include "utils.h"
#include "sort_text.h"
#include "color_scheme.h"

int main(int argc, const char *argv[]) {
    ERROR_DATA error_inf = PROGRAM_ERROR;
    TEXT_DATA TextData = {};
    FILE *input_file_handle = NULL;

    if (argc == 2) {
        input_file_handle = fopen(argv[1], "rb");
        if (!input_file_handle) {
            error_inf = FILE_ERROR;
            error_data_enum(error_inf);
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return -1;
        }

        count_digits(input_file_handle, &TextData);
    }
    else {
        error_inf = INPUT_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "error\nfile name was not entered\n");
        return -1;
    }

    fill_text      (input_file_handle, &TextData);
    //sort_endings   (&TextData);
    bubble_sort    (&TextData);
    //my_qsort       (TextData.LineData, sizeof(LINE_DATA), 0, TextData.lines, compare_strings_starts);
    //qsort          (TextData.LineData, TextData.lines, sizeof(LINE_DATA), compare_strings_ends);
    print_text     (stdout, &TextData);
    free_text_data (&TextData);

    return 0;
}
