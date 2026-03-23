#include <stdlib.h>	 // Essa biblioteca é para alocar os dados na memória
#include <stdio.h>	 // Essa biblioteca  é para arquivo padrão de entrada e saida - (para usar print e scan)
#include <locale.h>	 // Essa biblioteca é para caracter especial - PARA WINDOWS
#include <string.h>	 // Essa biblioteca é para mecher com Texto
#include <stdbool.h> // Essa biblioteca é expecifica para o bool funcionar nesse padrão C

struct Livro
{
	int ano;
	char autor[100];
	char titulo[100];
	char codigo[100];
};

struct Livro livros[100];
int total = 0;

void cadastrar(){   // CADASTRO
	system("cls");	 // limpa a tela

	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	printf("Autor: \n");
	scanf(" %[^\n]", livros[total].autor); // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal
	
	printf("Ano: \n");
	scanf("%d", &livros[total].ano);
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	printf("Titulo: \n");
	scanf(" %[^\n]", livros[total].titulo);  // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	printf("Codigo: \n");
	scanf("%99[^\n]", livros[total].codigo);  // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	total++;
}
void listar(){   // LISTAGEM
	system("cls");	 // limpa a tela
	for (int i = 0; i < total; i++) { // for também é minha estrutura de repetição
		printf("Livro %d\n", i+1);
		printf("Titulo: %s \n", livros[i].titulo);
		printf("Ano: %d \n", livros[i].ano);
		printf("Codigo: %s \n", livros[i].codigo);
		printf("Autor: %s \n", livros[i].autor);
		printf("----------------------------------------------------------\n");
	}		
	system("pause"); // pause - pausou o sistema
}

int buscar(char codigo[100]) {  // BUSCA
 	for (int i = 0; i < total; i++) { 
 		if (strcmp(livros[i].codigo, codigo) == 0) // Se o código do livro for IGUAL ao código digitado pelo usuário = 0
 			return i;
 	}	
 	return -1;
}

void editar() {  // EDIÇÃO
    char codigo[100];

    printf("Digite o codigo do livro que deseja editar: \n");
    scanf(" %[^\n]", codigo);
    scanf("%*[^\n]"); scanf("%*c");

    int i = buscar(codigo);

    if (i != -1) {
        printf("Novo titulo: \n");
        scanf(" %[^\n]", livros[i].titulo);
        scanf("%*[^\n]"); scanf("%*c");

        printf("Novo autor: \n");
        scanf("%99[^\n]", livros[i].autor);
        scanf("%*[^\n]"); scanf("%*c");

        printf("Novo ano: \n");
        scanf("%d", &livros[i].ano);
        scanf("%*[^\n]"); scanf("%*c");

        printf("Livro atualizado com sucesso!\n");
    } else {
        printf("Livro nao encontrado!\n");
    }

    system("pause");
}

void excluir() {  // EXCLUSÃO
    char codigo[100];

    printf("Digite o codigo do livro que deseja excluir: \n");
    scanf(" %[^\n]", codigo);
    scanf("%*[^\n]"); scanf("%*c");

    int i = buscar(codigo);

    if (i != -1) {
        for (int j = i; j < total - 1; j++) {
            livros[j] = livros[j + 1];
        }
        total--;

        printf("Livro excluido com sucesso!\n");
    } else {
        printf("Livro nao encontrado!\n");
    }

    system("pause");
}

int main(void){

	bool continua = true;
	system("cls"); // limpa a tela

	while (continua == true){ // while é minha estrutura de repetição
		system("cls");	 // limpa a tela
		printf("Menu\n");
		printf("1. Cadastrar\n");
		printf("2. Listar\n");
		printf("3. Buscar\n");
		printf("4. Editar\n");
		printf("5. Excuir\n");
		printf("0. Sair\n");

		int valor;

		scanf("%d", &valor);

		switch (valor){ // é minha função de comparação
			case 0:{
				continua = false;
				system("cls");	 // limpa a tela
				break;
			}
			case 1:{
				cadastrar();
				break;
			}
			case 2:{
				listar();
				break;
			}
			case 3: {
				char codigo[100];

				printf("Digite o codigo para buscar: \n");
				scanf(" %[^\n]", codigo);
				scanf("%*[^\n]"); scanf("%*c");

				int i = buscar(codigo);

				if (i != -1) {
					printf("Livro encontrado!\n");
					printf("Titulo: %s\n", livros[i].titulo);
					printf("Autor: %s\n", livros[i].autor);
					printf("Ano: %d\n", livros[i].ano);
					printf("Codigo: %s\n", livros[i].codigo);
				} else {
					printf("Livro nao encontrado!\n");
				}

				system("pause");
				break;
			}	
			case 4:{
				editar();
				break;
			}
			case 5:{
				excluir();
				break;
			}
			default:{
				printf("Valor invalido!\n");
				system("pause"); // pause - pausou o sistema
				break;
			}
		}
	}
	return 0;
}
