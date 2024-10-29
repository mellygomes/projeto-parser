// #include "src/Pilha/pilha.h"
#include "Sintatico.h"
#include "../AnalisadorLexico/Lexico.h"

//lista de regras sintaticas
void AnaliseProgram(AnalisadorLexico *lex, char *tbl[], No *TS) {
    Token token;
    IniciarToken(&token);
    token = getToken(lex, tbl, TS);

    if (strcmp(token.valor, "program") != 0) {
        printf("ERRO: o programa não foi iniciado corretamente\n");
        exit(EXIT_FAILURE);
    } else {
        token = getToken(lex, tbl, TS);
        if (strcmp(token.nome, "ID") != 0) {
            printf("Missing program identifier\n");
            exit(EXIT_FAILURE);
        } else  {
            token = getToken(lex, tbl, TS);
            if (strcmp(token.valor, ";") != 0) {
                printf("Expect token ';' before a code block\n");
                exit(EXIT_FAILURE);
            } else {
                VarDeclarations(lex, tbl, TS);
                CodeBlock(lex, tbl, TS);
                token = getToken(lex, tbl, TS);
                if (strcmp(token.valor, ".") != 0) {
                    printf("Expect token '.' before the end of a code block\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

void VarDeclarations(AnalisadorLexico *lex, char *tbl[], No *TS) {
    Token token;
    IniciarToken(&token);
    token = getToken(lex, tbl, TS);

    if (strcmp(token.valor, "var") != 0) {
        printf("ERRO: You must do var declaration");
        exit(EXIT_FAILURE);
    } else {
        token = getToken(lex, tbl, TS);
        VarDeclaration(lex, tbl, TS, token);
    }
}

void VarDeclaration(AnalisadorLexico *lex, char *tbl[], No *TS, Token token) {
    if (strcmp(token.nome, "ID") != 0) {
        printf("ERRO: You must do var declaration (linha: %i)", token.linha);
        exit(EXIT_FAILURE);
    } else {
        token = getToken(lex, tbl, TS);
        if (strcmp(token.valor, ":") != 0) {
            while (strcmp(token.valor, ",") == 0) {
                token = getToken(lex, tbl, TS);
                if (strcmp(token.nome, "ID") == 0) {
                    token = getToken(lex, tbl, TS);
                    continue;
                } else {
                    printf("ERRO: Expected an id 1\n");
                    exit(EXIT_FAILURE);
                }   
            }

            if (strcmp(token.valor, ":") != 0) {
                printf("ERRO: Expected token ':' in (linha: %i)\n", token.linha);
                exit(EXIT_FAILURE);    
            }
        }
        
        token = getToken(lex, tbl, TS);
        if ((strcmp(token.valor, "integer") != 0) && (strcmp(token.valor, "real") != 0) && (strcmp(token.valor, "boolean") != 0)) {
            printf("ERRO: Missing type in var declaration");
            exit(EXIT_FAILURE);  
        } else {
            token = getToken(lex, tbl, TS);
            if (strcmp(token.valor, ";") != 0) {
                printf("ERRO: token ';' Expected (linha: %i)", token.linha); 
                exit(EXIT_FAILURE);       
            }
        }
    }
}

void CodeBlock(AnalisadorLexico *lex, char *tbl[], No *TS) {
    Token token;
    IniciarToken(&token);
    token = getToken(lex, tbl, TS);

    while (strcmp(token.nome, "ID") == 0) {
        VarDeclaration(lex, tbl, TS, token);
        token = getToken(lex, tbl, TS);
    }

    if (strcmp(token.valor, "begin") != 0) {
        printf("ERRO: command section expected (linha: %i)", token.linha); 
        exit(EXIT_FAILURE);
    } else {
        return;
    }
}
 