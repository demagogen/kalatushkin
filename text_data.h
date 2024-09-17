#ifndef TEXT_DATA_H_
#define TEXT_DATA_H_

struct LINE_DATA {
    int lines_lengths    = 0;
    char *lines_pointers = NULL;
};

struct TEXT_DATA {
    int digits            = 0;
    int lines             = 0;
    LINE_DATA *LineData   = NULL;
    char  *text           = NULL;
};

int count_digits(FILE *file_handle, TEXT_DATA *TextData);
int separate_text_on_strings (TEXT_DATA *TextData);
int sort_endings             (TEXT_DATA *TextData);
int fill_text                (FILE *fp, TEXT_DATA *TextData);
int count_strings            (TEXT_DATA *TextData);
int fill_lines_pointers      (TEXT_DATA *TextData);
int print_text               (TEXT_DATA *TextData);
int free_text_data           (TEXT_DATA *TextData);

#endif

