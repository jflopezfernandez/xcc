
#include <xcc/xcc.h>

static void constant(void);
static void identifier(void);
static void type_specifier(void);
static void end_of_input(void);
static void primary_expression(void);
static void postfix_expression(void);
static void unary_expression(void);
static void assignment_expression(void);
static void expression(void);
static void expression_statement(void);
static void statement(void);
static void statement_list(void);
static void compound_statement(void);
static void initializer(void);
static void pointer(void);
static void direct_declarator(void);
static void declarator(void);
static void init_declarator(void);
static void init_declarator_list(void);
static void declaration_specifiers(void);
static void declaration();
static void declaration_list(void);
static void external_declaration(void);

void constant(void) {
    //
}

void identifier(void) {
    if (!next_token_is(NUMBER_OR_IDENTIFIER)) {
        fprintf(stderr, "[Error] Identifier expected on line %lu.\n", get_current_line_number());
        exit(EXIT_FAILURE);
    }

    advance();
}

void type_specifier(void) {
    if (next_token_is(TYPE_SPECIFIER)) {
        advance();
    }
}

void end_of_input(void) {
    if (!next_token_is(SEMICOLON)) {
        fprintf(stderr, "[Error] End of statement expected on line %lu.\n", get_current_line_number());
        exit(EXIT_FAILURE);
    }

    advance();
}

void primary_expression(void) {
    token_t next_token = get_next_token();

    switch (next_token) {
        case NUMBER_OR_IDENTIFIER: {
            advance();
        } break;
    }
}

void postfix_expression(void) {
    primary_expression();
}

void unary_expression(void) {
    postfix_expression();
}

void assignment_expression(void) {
    unary_expression();
}

void expression(void) {
    assignment_expression();

    if (next_token_is(COMMA)) {
        advance();
        expression();
    }
}

void expression_statement(void) {
    expression();

    if (!next_token_is(SEMICOLON)) {
        fprintf(stderr, "[Error] End of statement expected on line %lu.\n", get_current_line_number());
        exit(EXIT_FAILURE);
    }

    advance();
}

void statement(void) {
    expression_statement();
}

void statement_list(void) {
    statement();

    // Optional: next statement
}

void compound_statement(void) {
    if (!next_token_is(LEFT_SQUIGGLY)) {
        fprintf(stderr, "Left brace expected\n");
        exit(EXIT_FAILURE);
    }

    advance();

    declaration_list(); // Optional
    statement_list();   // Optional

    if (!next_token_is(RIGHT_SQUIGGLY)) {
        fprintf(stderr, "Right brace expected\n");
        exit(EXIT_FAILURE);
    }

    advance();
}

void initializer(void) {
    assignment_expression();
}

void pointer(void) {
    /** @todo type_qualifier_list */
}

void direct_declarator(void) {
    identifier();
}

void declarator(void) {
    if (next_token_is(ASTERISK)) {
        advance();
        pointer();
    }

    direct_declarator();
}

void init_declarator(void) {
    declarator();

    if (next_token_is(EQUAL_SIGN)) {
        advance();
        initializer();
    }
}

void init_declarator_list(void) {
    init_declarator();

    if (next_token_is(COMMA)) {
        advance();
        init_declarator();
    }
}

void declaration_specifiers(void) {
    token_t next_token = get_next_token();

    switch (next_token) {
        case TYPE_SPECIFIER: {
            advance();
        } break;

        default: {
            fprintf(stderr, "[Error] Not implemented yet.\n");
            fprintf(stderr, "Token: %s\n", get_token_type_string(next_token));
            exit(EXIT_FAILURE);
        } break;
    }
}

void declaration() {
    // type_specifier();
    // identifier();
    // end_of_input();

    declaration_specifiers();
    init_declarator_list();

    if (!next_token_is(SEMICOLON)) {
        fprintf(stderr, "[Error] End of statement expected, on line %lu.\n", get_current_line_number());
        exit(EXIT_FAILURE);
    }

    advance();
}

void declaration_list(void) {
    declaration();

    if (!next_token_is(END_OF_INPUT)) {
        declaration_list();
    }
}

void external_declaration(void) {
    declaration_list();
}

void translation_unit(void) {
    external_declaration();

    if (!next_token_is(END_OF_INPUT)) {
        translation_unit();
    }
}
