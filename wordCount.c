#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc != 3) {
        wprintf(L"Usage: %S [-c | -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *option = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        wprintf(L"Unable to open file: %S\n", filename);
        return 1;
    }

    int char_count = 0;
    int word_count = 0;
    int in_word = 0;
    wchar_t ch;

    while ((ch = fgetwc(file)) != WEOF) {
        char_count++;

        if (ch == L' ' || ch == L',' || ch == L'\n' || ch == L'\t') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            word_count++;
        }
    }

    fclose(file);

    if (strcmp(option, "-c") == 0) {
        wprintf(L"字母个数：%d\n", char_count);
    } else if (strcmp(option, "-w") == 0) {
        wprintf(L"单词数：%d\n", word_count);
    } else {
        wprintf(L"Invalid option: %S\n", option);
        return 1;
    }

    return 0;
}
