
#include <xcc/xcc.h>

static FILE* input_file_stream = NULL;

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "No input(s).\n");
        return EXIT_FAILURE;
    }

    while (*++argv) {
        input_file_stream = fopen(*argv, "r");

        if (input_file_stream == NULL) {
            fprintf(stderr, "[Error] Failed to open file: %s\n", *argv);
            continue;
        }

        printf("%d\n", lex(input_file_stream));

        fclose(input_file_stream);
    }

    return EXIT_SUCCESS;
}
