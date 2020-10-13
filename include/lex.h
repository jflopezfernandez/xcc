
#ifndef PROJECT_INCLUDES_LEX_H
#define PROJECT_INCLUDES_LEX_H

typedef enum {
    EOI,
    SEMI,
    PLUS,
    TIMES,
    LP,
    RP,
    NUM_OR_ID
} token_t;

token_t lex(FILE* input_file_stream);

#endif /** PROJECT_INCLUDES_LEX_H */
