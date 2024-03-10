#include <stdlib.h>
#include <string.h>
#include "compiler/lexer.h"

#define count_char(source, c) ({ \
    char *s = (char *)source; \
    size_t i = 0; \
    for (i = 0; s[i]; s[i] == c ? i++ : *s++); \
    i; \
})

ast_tokens_t lexer_tokenize(const char *source) {
    ast_token_t *tokens;
    unsigned int start, token_count;

    int size = count_char(source, ' ') + count_char(source, '\n') * 2 + 1;
    tokens = calloc(sizeof(ast_token_t), size);
    tokens[0].type = AST_VERB;

    start = token_count = 0;

    for (unsigned int i = 0;source[i] != '\0'; i++) {
        if (source[i] == ' ' || source[i] == '\0' || source[i] == '\n') {
            // copy the string
            tokens[token_count].value = malloc(i - start + 1);
            strncpy(tokens[token_count].value, source + start, i - start);
            tokens[token_count].value[i - start] = '\0';
            token_count++;

            tokens[token_count].type = AST_NOUN;
            start = i + 1;

            if (source[i] == '\n') {
                tokens[token_count].type = NEWLINE;
                tokens[token_count].value = NULL;
                token_count++;

                tokens[token_count].type = AST_VERB;
                start = i + 1;
            }
        }
    }

    ast_tokens_t node = {tokens, token_count};
    return node;
}