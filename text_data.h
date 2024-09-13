#ifndef TEXT_DATA_H_
#define TEXT_DATA_H_

struct TEXT_DATA {
    int digits            = 0;
    int lines             = 0;
    int   *lines_lengths  = NULL;
    char  *text           = NULL;
    char **lines_pointers = NULL;
};

int fill_text                (FILE *fp, TEXT_DATA *TextData);
int separate_text_on_strings (TEXT_DATA *TextData);
int fill_lines_pointers      (TEXT_DATA *TextData);
int print_text               (TEXT_DATA *TextData);
int free_text_data           (TEXT_DATA *TextData);

#endif

