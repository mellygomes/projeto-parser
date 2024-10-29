## Analisador sintático
                        
### Utilizar pilha, há dois métodos (top e bottom-up)

- eliminar retrocessos;
- eliminar ambiguidade.

### Cada regra sera um procedimento;

- Os prcedimentos chamarão outrosa procedimentos, cada um é uma opção que o programa pode seguir;

#### Linha pra compilar:
- gcc AnalisadorLexico/Lexico.c AnalisadorLexico/src/SimbolTable/simboltable.c AnalisadorLexico/src/HashTable/hashtable.c AnalisadorSintatico/Sintatico.c main.c -o parser.exe
- ./parcer.exe
