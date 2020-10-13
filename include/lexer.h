
#ifndef PROJECT_INCLUDES_LEX_H
#define PROJECT_INCLUDES_LEX_H

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

typedef enum {
    NONE,
    END_OF_INPUT,
    SEMICOLON,
    COMMA,
    EQUAL_SIGN,
    ASTERISK,
    TYPE_SPECIFIER,
    NUMBER_OR_IDENTIFIER,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_SQUIGGLY,
    RIGHT_SQUIGGLY,
    MULTI_LINE_COMMENT_START,
    MULTI_LINE_COMMENT_END
} token_t;

typedef enum {
    VOID,
    CHAR,
    SHORT,
    INTEGER,
    LONG,
    FLOAT,
    DOUBLE
} type_specifier_t;

size_t get_current_line_number(void);

const char* get_token_type_string(token_t token);

token_t get_next_token(void);

void advance(void);

bool_t next_token_is(token_t token);

bool_t next_token_is_not(token_t token);

#endif /** PROJECT_INCLUDES_LEX_H */
