
#include <xcc/xcc.h>

FILE* current_file = NULL;

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "No input(s).\n");
        return EXIT_FAILURE;
    }

    while (*++argv) {
        current_file = fopen(*argv, "r");

        if (current_file == NULL) {
            fprintf(stderr, "[Error] Failed to open file: %s\n", *argv);
            continue;
        }

        //statements();

        printf("Compiling file: %s\n", *argv);
        translation_unit();

        fclose(current_file);
    }

    return EXIT_SUCCESS;
}
