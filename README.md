# Cadastro de Livros (C)

Aplicacao de terminal para gerenciar um pequeno catalogo de livros, feito em C.

## Funcionalidades

- Cadastrar livros com `titulo`, `autor`, `ano` e `codigo`
- Listar todos os livros cadastrados
- Buscar livro por codigo
- Editar dados de um livro existente
- Excluir livro por codigo

## Estrutura do projeto

- `main.c`: contem toda a logica da aplicacao e o menu principal

## Requisitos

- Compilador C (`gcc` ou equivalente)

## Como compilar e executar

### Linux

```bash
gcc main.c -o main.bin
./main.bin
```

### Windows (MinGW, por exemplo)

```bash
gcc main.c -o main.exe
./main.exe
```

## Como usar

Ao executar, o programa exibe o menu:

```
+==========================================================+
|              SISTEMA DE CADASTRO DE LIVROS               |
+==========================================================+
|                                                          |
|   [1] Cadastrar                                          |
|   [2] Listar                                             |
|   [3] Buscar                                             |
|   [4] Editar                                             |
|   [5] Excluir                                            |
|   [0] Sair                                               |
|                                                          |
+==========================================================+
```

A listagem e o resultado da busca exibem cada livro em um "card":

```
+----------------------------------------------------------+
| Livro  : #1                                              |
+----------------------------------------------------------+
| Titulo : São josé dos campos                             |
| Autor  : Julio                                           |
| Ano    : 1998                                            |
| Codigo : 001                                             |
+----------------------------------------------------------+
```

## Observacoes

- Capacidade maxima atual: ate `100` livros (`struct Livro livros[100]`)
- Layout em ASCII puro — funciona em qualquer terminal (Linux, Windows Terminal, cmd.exe legado) sem precisar configurar code page
- O alinhamento das bordas trata corretamente caracteres acentuados (UTF-8) via helper `utf8_len()`