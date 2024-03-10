#include <stdlib.h>
#include "compiler/ast.h"
#include "compiler/compiler.h"
#include "compiler/lexer.h"
#include "compiler/parser.h"

byte_t statement_to_mem(ast_statement_t statement) {
    byte_t mem = 0;
    mem |= statement.inst << 6;

    switch (statement.inst) {
        case INST_IMMEDIATE:
            mem |= statement.obj.immediate;
            break;
        case INST_COMPUTE:
            mem |= statement.obj.compute;
            break;
        case INST_COPY:
            mem |= statement.obj.copy.src << 3;
            mem |= statement.obj.copy.dst;
            break;
        case INST_JUMP:
            mem |= statement.obj.jump;
            break;
    }

    return mem;
}

mem_t compile(const char *source) {
    ast_tokens_t tokens = lexer_tokenize(source);
    ast_statements_t statements = parse_statement(tokens);

    mem_t mem;
    mem.size = statements.len;
    mem.bytes = malloc(sizeof(byte_t) * statements.len);

    for (size_t i = 0; i < statements.len; i++) {\
        mem.bytes[i] = statement_to_mem(statements.statements[i]);
    }

    ast_free_tokens(tokens);
    ast_free_statements(statements);

    return mem;
}
