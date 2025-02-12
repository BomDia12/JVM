# JVM

Neste repositório temos o código fonte do projeto de JVM, que conta com um interpretador de arquivos `.class`, e um leitor exibidor de arquivos `.class`.

## Desenvolvimento da JVM

Este projeto foi desenvolvido em C, e foi dividido nos seguintes módulos:

- main.c: módulo principal do leitor exibidor, apenas chama os outros módulos
- bytecode.h: módulo responsável por ler os bytecodes e armazenar os mnemônicos
- reader.h: módulo responsável por ler os arquivos .class
- output.h: módulo responsável por imprimir os resultados do leitor exibidor
- header.h: módulo responsável por ler e armazenar as informações do cabeçalho do arquivo .class
- attributes.h: módulo responsável por lidar com as seções de atributos no .class, e armazenar as informações de cada atributo
- instructions.h: módulo responsável por armazenar os mnemônicos dos bytecodes, e aponta para as funções que lidam cada opcode
- interpreter.h: módulo responsável por rodar funções e retornar os resultados
- object.h: módulo responsável por armazenar, criar e lidar com objetos
- string.h: módulo responsável por armazenar, criar e lidar com strings
- array.h: módulo responsável por armazenar, criar e lidar com arrays
- Módulos de instruções:
  - arithmetic.h: módulo responsável por lidar com as instruções de aritmética
  - loads.h: módulo responsável por lidar com as instruções de carregamento
  - stores.h: módulo responsável por lidar com as instruções de armazenamento
  - table.h: módulo responsável por lidar com as instruções de tabelas
  - invoke.h: módulo responsável por lidar com as instruções de invocação
  - conditional.h: módulo responsável por lidar com as instruções de condicional, e jumps
  - returns.h: módulo responsável por lidar com as instruções de retorno
  - stackops.h: módulo responsável por lidar com as instruções de operações de pilha
  - wide.h: módulo responsável por lidar com a instrução wide

## Como rodar o projeto

No Linux, basta executar o arquivo `run.sh`, que irá compilar o projeto e executar o leitor exibidor.
No Windows, você precisará compilar o projeto manualmente, e executar o arquivo `main.exe`.

## Como usar o projeto

Para usar o projeto, basta executar o arquivo `run.sh` ou `main.exe`, e fornecer o caminho do arquivo `.class` que deseja ler como um argumento. Todos os arquivos `.class` devem estar na pasta `exemplos`. Para rodar em modo de leitura, basta adicionar o argumento `-show`.

Exemplo:

```
./main.exe ./exemplos/Belote.class
```
