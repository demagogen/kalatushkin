#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "text_data.h"

int main(int argc, const char *argv[]) {
    TEXT_DATA TextData;
    FILE *fp = NULL;

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

    printf("hello");
    fill_text(fp, &TextData);
    print_text(&TextData);

    return 0;
}
