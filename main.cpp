#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "text_data.h"
#include "utils.h"
#include "sort_text.h"

int main(int argc, const char *argv[]) {
    TEXT_DATA TextData;
    FILE *fp = NULL   ;

    printf("hello");

    if (argc == 2) {
        fp = fopen(argv[1], "rb");
        fseek(fp, 0, SEEK_END);
        TextData.digits = ftell(fp);
        fseek(fp, 0, SEEK_SET);
    }
    else {
        printf("error\nfile name was not entered\n");
        return -1;
    }

    fill_text     (fp, &TextData);
    bubble_sort   (    &TextData);
    print_text    (    &TextData);
    free_text_data(    &TextData);

    return 0;
}
