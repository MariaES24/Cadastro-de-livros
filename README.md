# 📚 Sistema de Cadastro de Livros em C

Aplicação de terminal desenvolvida em linguagem C para gerenciamento de um catálogo de livros.

O projeto implementa operações CRUD completas utilizando:
- alocação dinâmica de memória (`malloc`, `realloc`, `free`)
- manipulação de arquivos binários (`fwrite`, `fread`)
- structs
- ponteiros
- tratamento de strings UTF-8
- interface textual em ASCII

---

## ✨ Funcionalidades

- ✅ Cadastrar livros
- ✅ Listar livros cadastrados
- ✅ Buscar livro por código
- ✅ Editar informações
- ✅ Excluir livros
- ✅ Persistência automática em arquivo `.dat`

Cada livro possui:
- `titulo`
- `autor`
- `ano`
- `codigo`

---

## 🧠 Conceitos utilizados

Este projeto foi desenvolvido com foco em prática de fundamentos da linguagem C:

- Structs
- Ponteiros
- Alocação dinâmica
- Manipulação de memória
- Arquivos binários
- Modularização de funções
- Tratamento de entrada
- Strings
- Terminal/CLI

---

## 🗂 Estrutura do projeto

```text
├── main.c
├── livros.dat
├── README.md
├── main.bin (Quando Compilado)
└── main.exe (Quando Compilado)
```

| Arquivo | Descrição |
|---|---|
| `main.c` | Código-fonte principal |
| `livros.dat` | Persistência binária dos livros |
| `README.md` | Documentação do projeto |

---

## ⚙️ Compilação

### Linux

```bash
gcc main.c -o main.bin
./main.bin
```

### Windows (MinGW)

```bash
gcc main.c -o main.exe
./main.exe
```

---

## 🖥 Interface

```text
+----------------------------------------------------------+
|              SISTEMA DE CADASTRO DE LIVROS               |
+----------------------------------------------------------+
|                                                          |
|   [1] Cadastrar                                          |
|   [2] Listar                                             |
|   [3] Buscar                                             |
|   [4] Editar                                             |
|   [5] Excluir                                            |
|   [0] Sair                                               |
|                                                          |
+----------------------------------------------------------+
```

---

## 📖 Exemplo de listagem

```text
+----------------------------------------------------------+
| Livro : #1                                               |
+----------------------------------------------------------+
| Titulo : Dom Casmurro                                    |
| Autor  : Machado de Assis                                |
| Ano    : 1899                                            |
| Codigo : 001                                             |
+----------------------------------------------------------+
```

---

## 💾 Persistência de dados

Os livros são armazenados automaticamente em arquivo binário utilizando:

```c
fwrite()
fread()
```

Os dados permanecem salvos mesmo após o encerramento do programa.

---

## 🌎 UTF-8

O projeto possui tratamento de caracteres UTF-8 para manter o alinhamento correto de textos com acentuação no terminal.

Exemplo:
- São Paulo
- José
- Álvares

---

## 📄 Licença

Projeto desenvolvido para fins de estudo e prática da linguagem C.