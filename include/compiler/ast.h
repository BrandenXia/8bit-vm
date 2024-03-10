#ifndef INC_8BIT_VM_AST_H
#define INC_8BIT_VM_AST_H

#include "vm/instruction.h"

typedef struct {
    enum {
        AST_VERB,
        AST_NOUN,
        NEWLINE,
    } type;
    char *value;
} ast_token_t;

typedef struct {
    ast_token_t *tokens;
    size_t len;
} ast_tokens_t;

typedef struct {
    inst_t inst;
    union {
        reg_t immediate;
        compute_op_t compute;
        struct {
            reg_id_t src;
            reg_id_t dst;
        } copy;
        jump_op_t jump;
    } obj;
} ast_statement_t;

typedef struct {
    ast_statement_t *statements;
    size_t len;
} ast_statements_t;

void ast_free_tokens(ast_tokens_t tokens);

void ast_free_statements(ast_statements_t statements);

#endif //INC_8BIT_VM_AST_H
