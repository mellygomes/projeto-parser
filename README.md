# ParserAnalisador
## Léxico e Sintático para a linguagem MicroPascal

Compilador parcial para MicroPascal, implementado em C, com suporte à análise léxica, análise sintática baseada em gramática LL(1) e início da análise semântica. O projeto identifica tokens válidos, valida construções sintáticas conforme uma gramática definida em EBNF e realiza as primeiras etapas da verificação semântica, como o controle de identificadores por meio de tabela de símbolos.

## Para executar

- Compilar todos os arquivos .c
```Bash
- gcc AnalisadorLexico/Lexico.c AnalisadorLexico/src/SimbolTable/simboltable.c AnalisadorLexico/src/HashTable/hashtable.c AnalisadorSintatico/Sintatico.c main.c -o parser.exe
```
- Executar o parser.exe
```Bash
- ./parcer.exe
```
