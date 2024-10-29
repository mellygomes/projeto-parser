#include "AnalisadorSintatico/Sintatico.h"
#include "AnalisadorLexico/src/HashTable/hashtable.h"
#include "AnalisadorLexico/src/SimbolTable/simboltable.h"
#include "AnalisadorLexico/Lexico.h"

int main() {
    AnalisadorLexico *lex = malloc(sizeof(AnalisadorLexico));
    if (lex == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    Token token;
    No *TS = NULL;
    char *tbl[TAM];

    InicializarAnalizadorLexico(lex);           //lê o arquivo fonte a ser analisado, insere o conteudo na fita e inicia as demais variáveis
    InserirPalavrasReservadas(tbl);             //Insere as palavras reservadas na lista
    Inserir(&TS, "\0");                         //Para que a tabela não inicie vazia
    IniciarToken(&token);                       //inicia as variáveis do token, alocando memoria para as strings
    printf("\n");   
    AnaliseProgram(lex, tbl, TS);               //inicia a analise sintática
    printf("Analise finalizada sem erros!\n");
    Imprimir(TS);                               //Imprime a tabela de simbolos gerada pelo analisador léxico

    //liberação das memórias alocadas
    LiberarMemoriaToken(&token);                
    free(TS);
    free(lex);
    return 0;
}
