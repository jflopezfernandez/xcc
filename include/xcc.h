
#ifndef PROJECT_INCLUDES_XCC_H
#define PROJECT_INCLUDES_XCC_H

#ifndef PROJECT_INCLUDES_CONFIG_H
#define PROJECT_INCLUDES_CONFIG_H
#include <config.h>
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

typedef enum {
    FALSE = 0,
    TRUE  = !FALSE
} bool_t;

#include <xcc/lex.h>

#endif /** PROJECT_INCLUDES_XCC_H */
