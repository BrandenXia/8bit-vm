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

#define str_to_enum(str, enum, prefix) \
    if (strcmp(str, #enum) == 0) return prefix ## _ ## enum

#define str_to_enum_inst(str, enum) \
    str_to_enum(str, enum, INST)

#define str_to_enum_comp(str, enum) \
    str_to_enum(str, enum, COMPUTE)

#define str_to_enum_jump(str, enum) \
    str_to_enum(str, enum, JUMP)

static inline inst_t verb_to_inst(char *verb) {
    str_to_enum_inst(verb, IMMEDIATE);
    str_to_enum_inst(verb, COMPUTE);
    str_to_enum_inst(verb, COPY);
    str_to_enum_inst(verb, JUMP);
    return -1;
}

static inline compute_op_t compute_op_from_string(char *op) {
    str_to_enum_comp(op, OR);
    str_to_enum_comp(op, NAND);
    str_to_enum_comp(op, NOR);
    str_to_enum_comp(op, AND);
    str_to_enum_comp(op, ADD);
    str_to_enum_comp(op, SUB);
    str_to_enum_comp(op, MUL);
    str_to_enum_comp(op, DIV);
    return -1;
}

static inline reg_id_t reg_id_from_string(char *reg) {
    if (strcmp(reg, "IO") == 0) return IO;

    int id = (reg_id_t) strtol(reg, NULL, 10);
    if (id < 0 || id > 4) exit(1);

    return id;
}

static inline jump_op_t jump_op_from_string(char *op) {
    str_to_enum_jump(op, NEVER);
    str_to_enum_jump(op, ZERO);
    str_to_enum_jump(op, NEG);
    str_to_enum_jump(op, NOT_POS);
    str_to_enum_jump(op, ALWAYS);
    str_to_enum_jump(op, NOT_ZERO);
    str_to_enum_jump(op, NOT_NEG);
    str_to_enum_jump(op, POS);
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
