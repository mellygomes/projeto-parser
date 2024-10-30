#ifndef SINTATICO_H
#define SINTATICO_H 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../AnalisadorLexico/Lexico.h"

void AnaliseProgram(AnalisadorLexico *lex, char *tbl[], No *TS);
void VarDeclarations(AnalisadorLexico *lex, char *tbl[], No *TS);
void VarDeclaration(AnalisadorLexico *lex, char *tbl[], No *TS, Token token);
void CodeBlock(AnalisadorLexico *lex, char *tbl[], No *TS);
void CommandLine(AnalisadorLexico *lex, char *tbl[], No *TS);
void Atribuition(AnalisadorLexico *lex, char *tbl[], No *TS);
// void Conditional(AnalisadorLexico *lex, char *tbl[], No *TS);
// void Repetitive(AnalisadorLexico *lex, char *tbl[], No *TS);
// void Expression(AnalisadorLexico *lex, char *tbl[], No *TS);
// void SimpleExpression(AnalisadorLexico *lex, char *tbl[], No *TS);
// void Factor(AnalisadorLexico *lex, char *tbl[], No *TS, Token token);

#endif