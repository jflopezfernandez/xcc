
#include <xcc/xcc.h>

// typedef enum {
//     NONE,
//     EOI,
//     SEMI,
//     PLUS,
//     MINUS,
//     TIMES,
//     DIV,
//     MODULUS,
//     LP,
//     RP,
//     NUM_OR_ID
// } token_t;


// static const char *tokens[] = {
//     "None",
//     "End of Input",
//     "Semi-colon",
//     "Plus Sign",
//     "Minus Sign",
//     "Multiplication Sign",
//     "Division Sign",
//     "Modulus Operator",
//     "Left Parenthesis",
//     "Right Parenthesis",
//     "Number or Identifier"
// };

// typedef enum {
//     NONE,
//     END_OF_INPUT,
//     SEMICOLON,
//     COMMA,
//     EQUAL_SIGN,
//     ASTERISK,
//     TYPE_SPECIFIER,
//     NUMBER_OR_IDENTIFIER,
//     LEFT_PAREN,
//     RIGHT_PAREN,
//     LEFT_SQUIGGLY,
//     RIGHT_SQUIGGLY,
//     MULTI_LINE_COMMENT_START,
//     MULTI_LINE_COMMENT_END
// } token_t;

static const char *tokens[] = {
    "None",
    "End of Input",
    "Semicolon",
    "Comma",
    "Equal Sign",
    "Asterisk",
    "Type Specifier",
    "Number or Identifier",
    "Left Parenthesis",
    "Right Parenthesis",
    "Left Squiggly",
    "Right Squiggly",
    "Multi-line Comment Start",
    "Multi-line Comment End"
};

const char* get_token_type_string(token_t token) {
    return tokens[token];
}

// typedef enum {
//     VOID,
//     CHAR,
//     SHORT,
//     INTEGER,
//     LONG,
//     FLOAT,
//     DOUBLE
// } type_specifier_t;

static const char *type_specifiers[] = {
    "void",
    "char",
    "short",
    "int",
    "long",
    "float",
    "double"
};

/**
 * @todo Implement a hash table look up.
 *
 */
static bool_t is_type_specifier(char* string, size_t length) {
    if (length == 0) {
        length = strlen(string);
    }

    for (size_t i = 0; i < ((sizeof type_specifiers) / (sizeof (*type_specifiers))); ++i) {
        if (strncmp(string, type_specifiers[i], length) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

static const char* get_type_specifier_string(type_specifier_t type_specifier) {
    return type_specifiers[type_specifier];
}

static char* yytext = "";
static size_t yyleng = 0;
static size_t yylineno = 0;
static bool_t in_comment = FALSE;

size_t get_current_line_number(void) {
    return yylineno;
}

static token_t lex(void) {
    static char input_buffer[128] = { 0 };
    char* current = yytext + yyleng;

    while (TRUE) {
        while (!*current) {
            current = input_buffer;

            if (!fgets(input_buffer, 128, current_file)) {
                *current = '\0';
                return END_OF_INPUT;
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
                /**
                 * Continue keeping track of the line number
                 * within the current source file, even if
                 * we're in a multi-line comment.
                 *
                 */
                case '\n': ++yylineno;
                case '/': {
                    if ((in_comment == FALSE) && (*(current + 1) == '*')) {
                        ++current;
                        in_comment = TRUE;
                        return MULTI_LINE_COMMENT_START;
                    }
                } /** Fallthrough */
                case '*': {
                    if ((in_comment == TRUE) && (*(current + 1) == '/')) {
                        ++current;
                        in_comment = FALSE;
                        return MULTI_LINE_COMMENT_END;
                    } else {
                        return ASTERISK;
                    }
                }
                case '\t': /** Fallthrough */
                case ' ': break;

                case EOF: return END_OF_INPUT;

                case ';': return SEMICOLON;
                case ',': return COMMA;
                case '=': return EQUAL_SIGN;
                //case '*': return ASTERISK;

                // case '+': return PLUS;
                // case '-': return MINUS;
                // case '*': return TIMES;
                // case '/': return DIV;
                // case '%': return MODULUS;
                // case '(': return LP;
                // case ')': return RP;
                
                default: {
                    if (!isalnum(*current)) {
                        fprintf(stderr, "[Error] Illegal input: %c\n", *current);
                        exit(EXIT_FAILURE);
                    }

                    while (isalnum(*current)) {
                        ++current;
                    }

                    yyleng = current - yytext;

                    /**
                     * @note The runtime complexity of the
                     * lexical analyzer is ballooning out of
                     * control.
                     *
                     * @todo Use a hash table for type
                     * checks and comparisons.
                     *
                     */
                    for (size_t i = 0; i < ((sizeof type_specifiers) / (sizeof *type_specifiers)); ++i) {
                        if (strncmp(type_specifiers[i], yytext, strlen(type_specifiers[i])) == 0) {
                            return TYPE_SPECIFIER;
                        }
                    }

                    // if (is_type_specifier(yytext, yyleng)) {
                    //     printf("Type specifier: %.*s\n", yyleng, yytext);
                    //     return TYPE_SPECIFIER;
                    // }

                    // if (strncmp(yytext, "void", yyleng) == 0) {
                    //     return TYPE_SPECIFIER;
                    // } else if (strncmp(yytext, "char", yyleng) == 0) {
                    //     return TYPE_SPECIFIER;
                    // } else if (strncmp(yytext, "int", yyleng) == 0) {
                    //     return TYPE_SPECIFIER;
                    // } else if (strncmp(yytext, "double", yyleng) == 0) {
                    //     return TYPE_SPECIFIER;
                    // }
                } return NUMBER_OR_IDENTIFIER;
            }
        }
    }
}

static token_t lookahead = NONE;

token_t get_next_token(void) {
    if (lookahead == NONE) {
        advance();
    }

    return lookahead;
}

void advance(void) {
    lookahead = lex();

    //printf("Current Token: %s\n", get_token_type_string(lookahead));

    // for (size_t i = 0; i < 120; ++i) {
    //     putchar(' ');
    // }

    // printf("Lookahead: %s\n", get_token_type_string(lookahead));
}

bool_t next_token_is(token_t token) {
    if (lookahead == NONE) {

        // for (size_t i = 0; i < 120; ++i) {
        //     putchar(' ');
        // }

        // printf("Lookahead: %s\n", get_token_type_string(lookahead));
        
        advance();
    }

    return (lookahead == token);
}

bool_t next_token_is_not(token_t token) {
    return !next_token_is(token);
}
