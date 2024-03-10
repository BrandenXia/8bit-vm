#include <stdlib.h>
#include <string.h>
#include "compiler/parser.h"

#define count_verbs(tokens) ({ \
    unsigned int count = 0; \
    for (unsigned int i = 0; i < tokens.len; i++) { \
        if (tokens.tokens[i].type == AST_VERB) count++; \
    } \
    count; \
})

static inline inst_t verb_to_inst(char *verb) {
    if (strcmp(verb, "IMMEDIATE") == 0) return INST_IMMEDIATE;
    if (strcmp(verb, "COMPUTE") == 0) return INST_COMPUTE;
    if (strcmp(verb, "COPY") == 0) return INST_COPY;
    if (strcmp(verb, "JUMP") == 0) return INST_JUMP;
    return -1;
}

static inline compute_op_t compute_op_from_string(char *op) {
    if (strcmp(op, "OR") == 0) return COMPUTE_OR;
    if (strcmp(op, "NAND") == 0) return COMPUTE_NAND;
    if (strcmp(op, "NOR") == 0) return COMPUTE_NOR;
    if (strcmp(op, "AND") == 0) return COMPUTE_AND;
    if (strcmp(op, "ADD") == 0) return COMPUTE_ADD;
    if (strcmp(op, "SUB") == 0) return COMPUTE_SUB;
    if (strcmp(op, "MUL") == 0) return COMPUTE_MUL;
    if (strcmp(op, "DIV") == 0) return COMPUTE_DIV;
    return -1;
}

static inline reg_id_t reg_id_from_string(char *reg) {
    if (strcmp(reg, "IO") == 0) return IO;

    int id = (reg_id_t) strtol(reg, NULL, 10);
    if (id < 0 || id > 4) exit(1);

    return id;
}

static inline jump_op_t jump_op_from_string(char *op) {
    if (strcmp(op, "NEVER") == 0) return JUMP_NEVER;
    if (strcmp(op, "ZERO") == 0) return JUMP_ZERO;
    if (strcmp(op, "NEG") == 0) return JUMP_NEG;
    if (strcmp(op, "NOT_POS") == 0) return JUMP_NOT_POS;
    if (strcmp(op, "ALWAYS") == 0) return JUMP_ALWAYS;
    if (strcmp(op, "NOT_ZERO") == 0) return JUMP_NOT_ZERO;
    if (strcmp(op, "NOT_NEG") == 0) return JUMP_NOT_NEG;
    if (strcmp(op, "POS") == 0) return JUMP_POS;
    return -1;
}

ast_statements_t parse_statement(ast_tokens_t tokens) {
    ast_statements_t statements;
    statements.len = 0;
    statements.statements = calloc(sizeof(ast_statement_t), count_verbs(tokens));

    unsigned int statement_count = 0;
    unsigned int i = 0;
    while (i < tokens.len) {
        if (tokens.tokens[i].type == AST_VERB) {
            statements.statements[statement_count].inst = verb_to_inst(tokens.tokens[i].value);
            i++;
            switch (statements.statements[statement_count].inst) {
                case INST_IMMEDIATE:
                    statements.statements[statement_count].obj.immediate = strtol(tokens.tokens[i].value, NULL, 10);
                    break;
                case INST_COMPUTE:
                    statements.statements[statement_count].obj.compute = compute_op_from_string(tokens.tokens[i].value);
                    break;
                case INST_COPY:
                    statements.statements[statement_count].obj.copy.src = reg_id_from_string(tokens.tokens[i].value);
                    i++;
                    statements.statements[statement_count].obj.copy.dst = reg_id_from_string(tokens.tokens[i].value);
                    break;
                case INST_JUMP:
                    statements.statements[statement_count].obj.jump = jump_op_from_string(tokens.tokens[i].value);
                    break;
            }
            statement_count++;
        }
        i++;
    }

    statements.len = statement_count;
    return statements;
}
