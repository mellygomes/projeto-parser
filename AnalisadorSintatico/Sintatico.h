#ifndef SINTATICO_H
#define SINTATICO_H 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../AnalisadorLexico/Lexico.h"

void initToken(AnalisadorLexico *lex, char *tbl[], No *TS);
void match(AnalisadorLexico *lex, char *tbl[], No *TS, char *expected);

void Program(AnalisadorLexico *lex, char *tbl[], No *TS);
void VarDeclarations(AnalisadorLexico *lex, char *tbl[], No *TS);
void VarDeclaration(AnalisadorLexico *lex, char *tbl[], No *TS);
void CodeBlock(AnalisadorLexico *lex, char *tbl[], No *TS);
void CommandLine(AnalisadorLexico *lex, char *tbl[], No *TS);
void Expression(AnalisadorLexico *lex, char *tbl[], No *TS);
void SimpleExpression(AnalisadorLexico *lex, char *tbl[], No *TS);
void Factor(AnalisadorLexico *lex, char *tbl[], No *TS);
void Termo(AnalisadorLexico *lex, char *tbl[], No *TS);
void Atribuition(AnalisadorLexico *lex, char *tbl[], No *TS);
void ConditionalStatement(AnalisadorLexico *lex, char *tbl[], No *TS);
void RepetitionStatement(AnalisadorLexico *lex, char *tbl[], No *TS);

#endif