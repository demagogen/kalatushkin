#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "text_data.h"
#include "utils.h"
#include "sort_text.h"
#include "color_scheme.h"

int main(int argc, const char *argv[]) {
    ERROR_DATA error_inf = PROGRAM_ERROR;
    TEXT_DATA TextData = {};
    FILE* input_file_handle  = NULL;
    FILE* output_file_handle = stdout;

    if (argc == 2) {
        input_file_handle = fopen(argv[1], "rb");
        if (!input_file_handle) {
            error_inf = FILE_ERROR;
            error_data_enum(error_inf);
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return -1;
        }
    }
    else if (argc == 3) {
        input_file_handle = fopen(argv[1], "rb");
        if (!input_file_handle) {
            error_inf = FILE_ERROR;
            error_data_enum(error_inf);
            graphic_printf(RED, BOLD, "null pointer input_file_handle in main\n");
            return -1;
        }
        output_file_handle = fopen(argv[2], "w");
        if (!output_file_handle) {
            error_inf = FILE_ERROR;
            error_data_enum(error_inf);
            graphic_printf(RED, BOLD, "null pointer output_file in main\n");
            return -1;
        }
        fprintf(stderr, "out file: %p\n", output_file_handle);
    }
    else {
        error_inf = INPUT_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "error\nfile name was not entered\n");
        return -1;
    }

    count_symbols  (input_file_handle, &TextData);
    fill_text      (input_file_handle, &TextData);
    //qsort          (TextData.LineData, TextData.lines, sizeof(LINE_DATA), compare_strings_starts);
    custom_qsort   (TextData.LineData, TextData.lines, sizeof(LINE_DATA), compare_strings_ends);
    print_text     (output_file_handle, &TextData);
    free_text_data (&TextData);

    fclose(input_file_handle);
    fclose(output_file_handle);

    return 0;
}
