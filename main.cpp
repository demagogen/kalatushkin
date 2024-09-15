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
    FILE *fp = NULL   ;

    if (argc == 2) {
        fp = fopen(argv[1], "rb");
        fseek(fp, 0, SEEK_END);
        TextData.digits = ftell(fp);
        fseek(fp, 0, SEEK_SET);
    }
    else {
        error_inf = INPUT_ERROR;
        error_data_enum(error_inf);
        graphic_printf(RED, BOLD, "error\nfile name was not entered\n");
        return -1;
    }

    fill_text     (fp, &TextData);
    //sort_endings  (    &TextData);
    //bubble_sort   (    &TextData);
    //my_qsort      (TextData.LineData, sizeof(LINE_DATA), 0, TextData.lines - 1, compare_strings);
    qsort(TextData.LineData, TextData.lines, sizeof(LINE_DATA), compare_strings);
    print_text    (    &TextData);
    free_text_data(    &TextData);

    return 0;
}
