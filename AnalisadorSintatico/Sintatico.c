#include "Sintatico.h"
#include "../AnalisadorLexico/Lexico.h"
#include <ctype.h>

//variaavel global para evitar o consumo de tokens
Token token;
int verify = 0;
void initToken(AnalisadorLexico *lex, char *tbl[], No *TS) {
    token = getToken(lex, tbl, TS);
    for(int i = 0; token.valor[i]; i++){
     token.valor[i] = tolower(token.valor[i]);
    }
}

void match(AnalisadorLexico *lex, char *tbl[], No *TS, char *expected) {
    // Compara o valor do lookahead com o esperado
    if (strcmp(token.valor, expected) == 0) {
        // Avança o lookahead para o próximo token
        token = getToken(lex, tbl, TS);
        for(int i = 0; token.valor[i]; i++){
            token.valor[i] = tolower(token.valor[i]);
        }

    } else {
        // Reporta um erro de sintaxe
        printf("ERRO: Token '%s' invalido (linha: %i, coluna: %i)\n", token.valor, token.linha, token.coluna);
        exit(EXIT_FAILURE);
    }
}

void Program(AnalisadorLexico *lex, char *tbl[], No *TS) {
    initToken(lex, tbl, TS);

    match(lex, tbl, TS, "program");

    if (strcmp(token.nome, "ID") == 0) {
        match(lex, tbl, TS, token.valor);
    } else {
        printf("Erro: identificador esperado apos 'program'.\n");
        exit(EXIT_FAILURE);
    }

    match(lex, tbl, TS, ";");

    VarDeclarations(lex, tbl, TS);
    CodeBlock(lex, tbl, TS);
    match(lex, tbl, TS, ".");
}


void VarDeclarations(AnalisadorLexico *lex, char *tbl[], No *TS) {
    match(lex, tbl, TS, "var");
    VarDeclaration(lex, tbl, TS);
}

void VarDeclaration(AnalisadorLexico *lex, char *tbl[], No *TS) {
    if (strcmp(token.nome, "ID") != 0) {
        printf("Erro: identificador esperado apos 'program'.\n");
        exit(EXIT_FAILURE);
    } else {
        match(lex, tbl, TS, token.valor);

        if (strcmp(token.valor, ":") != 0) {
            while (strcmp(token.valor, ",") == 0) {
                match(lex, tbl, TS, ",");
                if (strcmp(token.nome, "ID") == 0) {
                    match(lex, tbl, TS, token.valor);
                    continue;
                } else {
                    printf("ERRO: Expected an id 1\n");
                    exit(EXIT_FAILURE);
                }   
            }
        }

        match(lex, tbl, TS, ":");

        if ((strcmp(token.valor, "integer") != 0) && (strcmp(token.valor, "real") != 0) && (strcmp(token.valor, "boolean") != 0)) {
            printf("ERRO: Missing type in var declaration");
            exit(EXIT_FAILURE);  
        } else {
            match(lex, tbl, TS, token.valor);
            match(lex, tbl, TS, ";");
        }
    }
}

void CodeBlock(AnalisadorLexico *lex, char *tbl[], No *TS) {
    //antes de iniciar analise do bloco de codigo, verifica se uma nova lista de declarações não iniciou 
    while (strcmp(token.nome, "ID") == 0) { // se sim, VarDeclaration é chamada para analisar
        VarDeclaration(lex, tbl, TS);
    }
    
    match(lex, tbl, TS, "begin");
    CommandLine(lex, tbl, TS);
}

void CommandLine(AnalisadorLexico *lex, char *tbl[], No *TS) {
    if (strcmp(token.nome, "ID") == 0) {
        match(lex, tbl, TS, token.valor);
        Atribuition(lex, tbl, TS);

        if (strcmp(token.valor, ";") == 0) {
            match(lex, tbl, TS, ";");
            CommandLine(lex, tbl, TS);
        } else if (strcmp(token.valor, "end") == 0) {
            match(lex, tbl, TS, token.valor);
            return;
        }

    } else if (strcmp(token.valor, "begin") == 0) {
        match(lex, tbl, TS, "begin");
        CommandLine(lex, tbl, TS);

        if (strcmp(token.valor, ";") == 0) {
            match(lex, tbl, TS, ";");
            CommandLine(lex, tbl, TS);
        } else if (strcmp(token.valor, "end") == 0) {
            match(lex, tbl, TS, token.valor);
            return;
        }
    
    } else if (strcmp(token.valor, "if") == 0) {
        match(lex, tbl, TS, "if");
        ConditionalStatement(lex, tbl, TS);
    } else if (strcmp(token.valor, "while") == 0) {
        match(lex, tbl, TS, "while");
        RepetitionStatement(lex, tbl, TS);
    } else {
        printf("ERRO: command section expected (linha: %i, coluna: %i)", token.linha, token.coluna); 
        exit(EXIT_FAILURE);  
    }   
}

void Expression(AnalisadorLexico *lex, char *tbl[], No *TS) {
    SimpleExpression(lex, tbl, TS);

    if ((strcmp(token.valor, "=") ==  0) || (strcmp(token.valor, "<>") ==  0)
    || (strcmp(token.valor, "<") ==  0) || (strcmp(token.valor, ">") ==  0)
    || (strcmp(token.valor, "<=") ==  0) || (strcmp(token.valor, ">=") ==  0)) {
        match(lex, tbl, TS, token.valor);
        SimpleExpression(lex, tbl, TS);    
    }
}

void SimpleExpression(AnalisadorLexico *lex, char *tbl[], No *TS) {
    if ((strcmp(token.valor, "+") ==  0) || (strcmp(token.valor, "-") ==  0)) {
        match(lex, tbl, TS, token.valor);     
    }

    Termo(lex, tbl, TS);

    if ((strcmp(token.valor, "+") ==  0) || (strcmp(token.valor, "-") ==  0)) {
        match(lex, tbl, TS, token.valor);
        Termo(lex, tbl, TS);     
    }
}

void Termo(AnalisadorLexico *lex, char *tbl[], No *TS) {
    Factor(lex, tbl, TS);

    if ((strcmp(token.valor, "*") ==  0) || (strcmp(token.valor, "/") ==  0)) {
        match(lex, tbl, TS, token.valor);
        Factor(lex, tbl, TS);     
    }
}

void Factor(AnalisadorLexico *lex, char *tbl[], No *TS) {
    if ((strcmp(token.nome, "NUM-INT") ==  0) || (strcmp(token.nome, "NUM-FLT") ==  0)
    || (strcmp(token.nome, "NUM-EXP") ==  0) || (strcmp(token.nome, "ID") ==  0)) {
        match(lex, tbl, TS, token.valor);
    } else if ((strcmp(token.valor, "(") ==  0) && (verify == 0)){
        verify++;
        match(lex, tbl, TS, token.valor);
        Expression(lex, tbl, TS);
        if (strcmp(token.valor, ")") == 0) {
            match(lex, tbl, TS, ")");
            verify = 0;
        }

    } else {
        printf("ERRO: Invalid syntax for expression (linha: %i, coluna: %i)", token.linha, token.coluna);
        exit(EXIT_FAILURE);
    }
}

void Atribuition(AnalisadorLexico *lex, char *tbl[], No *TS) {
    match(lex, tbl, TS, ":=");
    Expression(lex, tbl, TS);  
}

void ConditionalStatement(AnalisadorLexico *lex, char *tbl[], No *TS) {
    Expression(lex, tbl, TS);

    if (strcmp(token.valor, "then") == 0) {
        match(lex, tbl, TS, "then");
        CommandLine(lex, tbl, TS);

        if (strcmp(token.valor, "else") == 0) {
            match(lex, tbl, TS, "else");
            CommandLine(lex, tbl, TS);
        }   
    } 
}

void RepetitionStatement(AnalisadorLexico *lex, char *tbl[], No *TS) {
    Expression(lex, tbl, TS);

    if (strcmp(token.valor, "do") == 0) {
        match(lex, tbl, TS, "do");
        CommandLine(lex, tbl, TS);
    } 
}
