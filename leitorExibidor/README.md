# Leitor exibidor de arquivos .class

Neste repositório temos o código fonte do projeto de leitor exibidor de arquivos `.class`.

## Desenvolvimento do leitor exibidor de arquivos .class

Este projeto foi desenvolvido em C, e foi dividido nos seguintes módulos:

- main.c: módulo principal do leitor exibidor, apenas chama os outros módulos
- bytecode.h: módulo responsável por ler os bytecodes e armazenar os mnemônicos
- reader.h: módulo responsável por ler os arquivos .class
- output.h: módulo responsável por imprimir os resultados do leitor exibidor
- header.h: módulo responsável por ler e armazenar as informações do cabeçalho do arquivo .class
- instructions.h: módulo responsável por armazenar os mnemônicos dos bytecodes
- attributes.h: módulo responsável por lidar com as seções de atributos no .class
  - A decisão de usar um módulo separado para lidar com os atributos foi feita para facilitar a separação, uma vez que os diferentes tipos de atributos resultam em diferentes estruturas de dados, que tem que ser tratadas de formas muito diferentes.

## Como rodar o projeto

No Linux, basta executar o arquivo `run.sh`, que irá compilar o projeto e executar o leitor exibidor.
No Windows, você precisará compilar o projeto manualmente, e executar o arquivo `main.exe`.

## Como usar o projeto

Para usar o projeto, basta executar o arquivo `run.sh` ou `main.exe`, e fornecer o caminho do arquivo `.class` que deseja ler como um argumento.

Exemplo:

```
./main.exe Belote.class
```

## TODO:
 - Strings
 - Objetos
 - multianewarray
