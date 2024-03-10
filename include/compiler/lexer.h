#ifndef INC_8BIT_VM_LEXER_H
#define INC_8BIT_VM_LEXER_H

#include "compiler/ast.h"

ast_tokens_t lexer_tokenize(const char *source);

#endif //INC_8BIT_VM_LEXER_H
