#include <stdlib.h>	 // Essa biblioteca é para alocar os dados na memória
#include <stdio.h>	 // Essa biblioteca  é para arquivo padrão de entrada e saida - (para usar print e scan)
#include <locale.h>	 // Essa biblioteca é para caracter especial - PARA WINDOWS
#include <string.h>	 // Essa biblioteca é para mecher com Texto
#include <stdbool.h> // Essa biblioteca é expecifica para o bool funcionar nesse padrão C

struct Livro
{
	int ano;
	char autor[100];
	char titulo[50];
	char codigo[15];
};

struct Livro livros[100];
int total = 0;

void limpar_terminal(){
	#ifdef _WIN32 // Se o sistema operacional for Windows
		system("cls"); // Limpa o terminal no Windows
	#else
		system("clear"); // Limpa o terminal no Linux
	#endif
}

void pause_terminal(){
	printf("Pressione ENTER para continuar...");
	getchar(); // Espera o usuário pressionar ENTER
}

// Conta caracteres UTF-8 (acentos contam como 1, não como 2 bytes)
int utf8_len(const char *s) {
	int len = 0;
	while (*s) {
		if ((*s & 0xC0) != 0x80) len++;
		s++;
	}
	return len;
}

// Imprime uma linha do "card" com padding correto para acentos
void imprimir_campo(const char *label, const char *valor) {
	int padding = 47 - utf8_len(valor);
	if (padding < 0) padding = 0;
	printf("| %s%s%*s |\n", label, valor, padding, "");
}

void imprimir_campo_int(const char *label, int valor) {
	char buf[32];
	snprintf(buf, sizeof(buf), "%d", valor);
	imprimir_campo(label, buf);
}

void listar(){   // LISTAGEM
	printf("+==========================================================+\n");
	printf("|                   LISTAGEM DE LIVROS                     |\n");
	printf("+==========================================================+\n\n");

	if (total == 0) {
		printf("  Nenhum livro cadastrado.\n\n");
		pause_terminal();
		return;
	}
	for (int i = 0; i < total; i++) { // for também é minha estrutura de repetição
		char header[32];
		snprintf(header, sizeof(header), "#%d", i + 1);
		printf("+----------------------------------------------------------+\n");
		imprimir_campo("Livro  : ", header);
		printf("+----------------------------------------------------------+\n");
		imprimir_campo    ("Titulo : ", livros[i].titulo);
		imprimir_campo    ("Autor  : ", livros[i].autor);
		imprimir_campo_int("Ano    : ", livros[i].ano);
		imprimir_campo    ("Codigo : ", livros[i].codigo);
		printf("+----------------------------------------------------------+\n\n");
	}
	pause_terminal(); // pause - pausou o sistema
}

int buscar(char codigo[15]) {  // BUSCA
 	for (int i = 0; i < total; i++) { 
 		if (strcmp(livros[i].codigo, codigo) == 0) // Se o código do livro for IGUAL ao código digitado pelo usuário = 0
 			return i;
 	}	
 	return -1;
}

void editar() {  // EDIÇÃO
    char codigo[100];

    printf("+==========================================================+\n");
    printf("|                     EDITAR LIVRO                         |\n");
    printf("+==========================================================+\n\n");

    printf("  Digite o codigo do livro que deseja editar: ");
    scanf(" %[^\n]", codigo);
    scanf("%*[^\n]"); scanf("%*c");

    int i = buscar(codigo);

    printf("\n");
    if (i != -1) {
        printf("  Novo titulo : ");
        scanf(" %[^\n]", livros[i].titulo);
        scanf("%*[^\n]"); scanf("%*c");

        printf("  Novo autor  : ");
        scanf("%99[^\n]", livros[i].autor);
        scanf("%*[^\n]"); scanf("%*c");

        printf("  Novo ano    : ");
        scanf("%d", &livros[i].ano);
        scanf("%*[^\n]"); scanf("%*c");

        printf("\n  >> Livro atualizado com sucesso!\n\n");
    } else {
        printf("  >> Livro nao encontrado!\n\n");
    }

    pause_terminal();
}

void excluir() {  // EXCLUSÃO
    char codigo[100];

    printf("+==========================================================+\n");
    printf("|                     EXCLUIR LIVRO                        |\n");
    printf("+==========================================================+\n\n");

    printf("  Digite o codigo do livro que deseja excluir: ");
    scanf(" %[^\n]", codigo);
    scanf("%*[^\n]"); scanf("%*c");

    int i = buscar(codigo);

    printf("\n");
    if (i != -1) {
        for (int j = i; j < total - 1; j++) {
            livros[j] = livros[j + 1];
        }
        total--;

        printf("  >> Livro excluido com sucesso!\n\n");
    } else {
        printf("  >> Livro nao encontrado!\n\n");
    }

    pause_terminal();
}

void cadastrar(){   // CADASTRO
	printf("+==========================================================+\n");
	printf("|                    CADASTRAR LIVRO                       |\n");
	printf("+==========================================================+\n\n");

	printf("  Codigo : ");
	scanf(" %[^\n]", livros[total].codigo);  // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	int i = buscar(livros[total].codigo);

	if (i != -1) {
		printf("\n  >> Livro ja cadastrado!\n\n");
		livros[total].codigo[0] = '\0';
		livros[total].autor[0] = '\0';
		livros[total].ano = 0;
		livros[total].titulo[0] = '\0';
		pause_terminal();
		return;
	}

	printf("  Autor  : ");
	scanf(" %[^\n]", livros[total].autor); // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	printf("  Ano    : ");
	scanf("%d", &livros[total].ano);
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	printf("  Titulo : ");
	scanf(" %[^\n]", livros[total].titulo);  // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	total++;

	limpar_terminal();
	printf("  >> Livro cadastrado com sucesso!\n\n");
	pause_terminal();
}

int main(void){

	bool continua = true;
	limpar_terminal(); // limpa a tela

	while (continua == true){ // while é minha estrutura de repetição
		limpar_terminal();	 // limpa a tela
		printf("+==========================================================+\n");
		printf("|              SISTEMA DE CADASTRO DE LIVROS               |\n");
		printf("+==========================================================+\n");
		printf("|                                                          |\n");
		printf("|   [1] Cadastrar                                          |\n");
		printf("|   [2] Listar                                             |\n");
		printf("|   [3] Buscar                                             |\n");
		printf("|   [4] Editar                                             |\n");
		printf("|   [5] Excluir                                            |\n");
		printf("|   [0] Sair                                               |\n");
		printf("|                                                          |\n");
		printf("+==========================================================+\n");
		printf("\n  >> Escolha uma opcao: ");

		int valor;

		scanf("%d", &valor);
		scanf("%*[^\n]"); scanf("%*c");

		switch (valor){ // é minha função de comparação
			case 0:{
				continua = false;
				limpar_terminal();	 // limpa a tela
				break;
			}
			case 1:{
				limpar_terminal();	 // limpa a tela
				cadastrar();
				break;
			}
			case 2:{
				limpar_terminal();	 // limpa a tela
				listar();
				break;
			}
			case 3: {
				limpar_terminal();	 // limpa a tela
				char codigo[100];

				printf("+==========================================================+\n");
				printf("|                     BUSCAR LIVRO                         |\n");
				printf("+==========================================================+\n\n");
				printf("  Digite o codigo para buscar: ");
				scanf(" %[^\n]", codigo);
				scanf("%*[^\n]"); scanf("%*c");

				int i = buscar(codigo);

				printf("\n");
				if (i != -1) {
					printf("+----------------------------------------------------------+\n");
					printf("| Livro encontrado!                                        |\n");
					printf("+----------------------------------------------------------+\n");
					imprimir_campo    ("Titulo : ", livros[i].titulo);
					imprimir_campo    ("Autor  : ", livros[i].autor);
					imprimir_campo_int("Ano    : ", livros[i].ano);
					imprimir_campo    ("Codigo : ", livros[i].codigo);
					printf("+----------------------------------------------------------+\n\n");
				} else {
					printf("  >> Livro nao encontrado!\n\n");
				}

				pause_terminal();
				break;
			}
			case 4:{
				limpar_terminal();	 // limpa a tela
				editar();
				break;
			}
			case 5:{
				limpar_terminal();	 // limpa a tela
				excluir();
				break;
			}
			default:{
				printf("Valor invalido!\n");
				pause_terminal(); // pause - pausou o sistema
				break;
			}
		}
	}
	return 0;
}
