#include <stdlib.h>
#include "compiler/ast.h"

void ast_free_tokens(ast_tokens_t tokens) {
    for (size_t i = 0; i < tokens.len; i++) {
        free(tokens.tokens[i].value);
    }
    free(tokens.tokens);
}

void ast_free_statements(ast_statements_t statements) {
    free(statements.statements);
}
