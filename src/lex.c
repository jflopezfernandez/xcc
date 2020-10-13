
#include <xcc/xcc.h>

static char* yytext = "";
static size_t yyleng = 0;
static size_t yylineno = 0;

token_t lex(FILE* input_file_stream) {
    static char input_buffer[128] = { 0 };
    char* current = yytext + yyleng;

    while (TRUE) {
        while (!*current) {
            current = input_buffer;

            if (!fgets(input_buffer, 128, input_file_stream)) {
                *current = '\0';
                return EOI;
            }

            ++yylineno;

            while (isspace(*current)) {
                ++current;
            }
        }

        for (/* No initialization */; *current; ++current) {
            yytext = current;
            yyleng = 1;

            switch (*current) {
                case '\n': /** Fallthrough */
                case '\t': /** Fallthrough */
                case ' ': break;
                case EOF: return EOI;
                case ';': return SEMI;
                case '+': return PLUS;
                case '*': return TIMES;
                case '(': return LP;
                case ')': return RP;
                default: {
                    if (!isalnum(*current)) {
                        fprintf(stderr, "[Error] Illegal input: %c\n", *current);
                        exit(EXIT_FAILURE);
                    }

                    while (isalnum(*current)) {
                        ++current;
                    }

                    yyleng = current - yytext;
                } return NUM_OR_ID;
            }
        }
    }
}
