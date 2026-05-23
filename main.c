#include <stdlib.h>	 // Essa biblioteca é para alocar os dados na memória
#include <stdio.h>	 // Essa biblioteca  é para arquivo padrão de entrada e saida - (para usar print e scan)
#include <locale.h>	 // Essa biblioteca é para caracter especial - PARA WINDOWS
#include <string.h>	 // Essa biblioteca é para mecher com Texto
#include <stdbool.h> // Essa biblioteca é expecifica para o bool funcionar nesse padrão C

struct Livro
{
	int ano;
	char autor[50];
	char titulo[50];
	char codigo[15];
};

struct Livro *livros = NULL;
int total = 0;

/* Função para limpar o terminal */
void limpar_terminal(){
	#ifdef _WIN32 // Se o sistema operacional for Windows
		system("cls"); // Limpa o terminal no Windows
	#else
		system("clear"); // Limpa o terminal no Linux
	#endif
}

/*
 * Função para pausar o terminal até que o usuário pressione ENTER
 * Usado para evitar que o programa feche imediatamente após uma ação.
 */
void pause_terminal(){
	printf("Pressione ENTER para continuar...");
	getchar(); // Espera o usuário pressionar ENTER
}

/**
 * Conta caracteres UTF-8 (acentos contam como 1, não como 2 bytes)
 *
 * @param s String a ser contada
 * @return Número de caracteres UTF-8
 */
int utf8_len(const char *s) {
	int len = 0;
	while (*s) {
		if ((*s & 0xC0) != 0x80) len++;
		s++;
	}
	return len;
}

/**
 * Imprime uma linha do "card" com padding correto para acentos
 *
 * @param label Rótulo do campo
 * @param valor Valor do campo
 */
void imprimir_campo(const char *label, const char *valor) {
	int padding = 47 - utf8_len(valor);
	if (padding < 0) padding = 0;
	printf("| %s%s%*s |\n", label, valor, padding, "");
}

/**
 * Imprime uma linha do "card" com padding correto para acentos
 *
 * @param label Rótulo do campo
 * @param valor Valor do campo
 */
void imprimir_campo_int(const char *label, int valor) {
	char buf[32];
	snprintf(buf, sizeof(buf), "%d", valor);
	imprimir_campo(label, buf);
}

/**
 * Imprime as informações de um livro em um "card" formatado
 *
 * @param livro Estrutura do livro a ser impressa
 */
void imprimir_livro (struct Livro livro){ 
	printf("+----------------------------------------------------------+\n");
	imprimir_campo    ("Codigo : ", livro.codigo);
	imprimir_campo    ("Titulo : ", livro.titulo);
	imprimir_campo    ("Autor  : ", livro.autor);
	imprimir_campo_int("Ano    : ", livro.ano);
	printf("+----------------------------------------------------------+\n\n");
}

/*
 * Função de listagem de livros
 * Exibe todos os livros cadastrados em uma tabela formatada.
 */
void listar(){
	printf("+----------------------------------------------------------+\n");
	printf("|                   LISTAGEM DE LIVROS                     |\n");
	printf("+----------------------------------------------------------+\n\n");

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
		imprimir_livro(livros[i]);
	}
	pause_terminal(); // pause - pausou o sistema
}

/**
 * Função de busca de um livro
 * O usuário digita o código do livro que deseja buscar.
 * O programa busca o livro e, se encontrado, retorna o índice.
 *
 * @param codigo Código do livro a ser buscado
 * @return Índice do livro encontrado ou -1 se não encontrado
 */
int buscar(char codigo[15]) {  // BUSCA
 	for (int i = 0; i < total; i++) { 
 		if (strcmp(livros[i].codigo, codigo) == 0) // Se o código do livro for IGUAL ao código digitado pelo usuário = 0
 			return i;
 	}	
 	return -1;
}

/*
 * Função de edição de um livro
 * O usuário digita o código do livro que deseja editar.
 * O programa busca o livro e, se encontrado, permite a atualização dos dados.
 */
void editar() {
    char codigo[15];

    printf("+----------------------------------------------------------+\n");
    printf("| Editar Livro :                                           |\n");
    printf("+----------------------------------------------------------+\n\n");

    printf("  Digite o codigo do livro que deseja editar: ");
    scanf(" %14[^\n]", codigo);
    scanf("%*[^\n]"); scanf("%*c");

    int i = buscar(codigo);

    printf("\n");
    if (i != -1) {
        printf("  Novo titulo : ");
        scanf(" %49[^\n]", livros[i].titulo);
        scanf("%*[^\n]"); scanf("%*c");

        printf("  Novo autor  : ");
        scanf(" %49[^\n]", livros[i].autor);
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

/*
 * Função de exclusão de um livro
 * O usuário digita o código do livro que deseja excluir.
 * O programa busca o livro e, se encontrado, remove da lista.
 * A remoção é feita deslocando os livros seguintes para preencher o espaço vazio.
 */
void excluir() {
    char codigo[15];

    printf("+----------------------------------------------------------+\n");
    printf("| Excluir Livro :                                          |\n");
    printf("+----------------------------------------------------------+\n\n");

    printf("  Digite o codigo do livro que deseja excluir: ");
    scanf(" %14[^\n]", codigo);
    scanf("%*[^\n]"); scanf("%*c");

    int i = buscar(codigo);

    printf("\n");
    if (i != -1) {
        for (int j = i; j < total - 1; j++) {
            livros[j] = livros[j + 1];
        }
        total--;
		livros = realloc(livros, total * sizeof(struct Livro));

        printf("  >> Livro excluido com sucesso!\n\n");
    } else {
        printf("  >> Livro nao encontrado!\n\n");
    }

    pause_terminal();
}

void cadastrar(){   // CADASTRO
	printf("+----------------------------------------------------------+\n");
	printf("|                    CADASTRAR LIVRO                       |\n");
	printf("+----------------------------------------------------------+\n\n");

	livros = realloc(livros, (total + 1) * sizeof(struct Livro));

	if (livros == NULL) {
		printf("Erro de memoria!\n");
		return;
	}

	printf("  Codigo : ");
	scanf(" %14[^\n]", livros[total].codigo);  // esta limitando até meu máximo de caracter mencionado
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
	scanf(" %49[^\n]", livros[total].autor); // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	printf("  Ano    : ");
	scanf("%d", &livros[total].ano);
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	printf("  Titulo : ");
	scanf(" %49[^\n]", livros[total].titulo);  // esta limitando até meu máximo de caracter mencionado
	scanf("%*[^\n]"); scanf("%*c");  // limpa o buffer do terminal

	total++;

	limpar_terminal();
	printf("  >> Livro cadastrado com sucesso!\n\n");
	pause_terminal();
}

void salvar_binario() {

	// Abre (ou cria) o arquivo "livros.dat"
    // "wb" significa:
    // w = write (escrita)
    // b = binary (modo binário)
    FILE *arquivo = fopen("livros.dat", "wb");

    // Verifica se houve erro ao abrir o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    // Salva a quantidade total de livros no arquivo
    //
    // fwrite(
    //     &total               -> endereço da variável total
    //     sizeof(int)          -> tamanho de um inteiro
    //     1                    -> quantidade de itens
    //     arquivo              -> arquivo onde será salvo
    // );
    //
    // Isso grava o número total de livros antes dos dados
    fwrite(&total, sizeof(int), 1, arquivo);

    // Salva todos os livros no arquivo
    //
    // livros                  -> ponteiro para o primeiro livro
    // sizeof(struct Livro)    -> tamanho de UM livro
    // total                   -> quantidade de livros
    // arquivo                 -> arquivo destino
    //
    // O fwrite percorre a memória e grava tudo em sequência
    fwrite(livros, sizeof(struct Livro), total, arquivo);

    // Fecha o arquivo
    // Importante para garantir que tudo seja salvo corretamente
    fclose(arquivo);
}

void carregar_binario() {

    // Abre o arquivo "livros.dat" em modo leitura binária
    // r = read (leitura)
    // b = binary (modo binário)
    FILE *arquivo = fopen("livros.dat", "rb");

    // Se o arquivo não existir, inicia com lista vazia
    if (arquivo == NULL)
        return;

    // Lê do arquivo a quantidade total de livros
    //
    // fread(
    //     &total      -> onde o valor será armazenado
    //     sizeof(int) -> tamanho de um inteiro
    //     1           -> le a unica lista que pode existir de livros
    //     arquivo
    // );
    fread(&total, sizeof(int), 1, arquivo);

    // Se tem livros, aloca um bloco de memória suficiente para armazenar todos
    livros = malloc(total * sizeof(struct Livro));

    // Verifica se houve erro ao alocar memória
    if (livros == NULL) {
        printf("  >> Erro de memoria!\n");
        fclose(arquivo);
        return;
    }

    // Lê todos os livros do arquivo
    //
    // livros                  -> destino do dado
    // sizeof(struct Livro)    -> tamanho de cada livro
    // total                   -> quantidade de livros
    // arquivo                 -> arquivo origem
    //
    // Os bytes do arquivo são copiados diretamente para a memória
    fread(livros, sizeof(struct Livro), total, arquivo);

    // Fecha o arquivo
    fclose(arquivo);
}

int main(void){

	bool continua = true;
	limpar_terminal(); // limpa a tela

	carregar_binario();

	while (continua == true){ // while é minha estrutura de repetição
		limpar_terminal();	 // limpa a tela
		printf("+----------------------------------------------------------+\n");
		printf("|              SISTEMA DE CADASTRO DE LIVROS               |\n");
		printf("+----------------------------------------------------------+\n");
		printf("|                                                          |\n");
		printf("|   [1] Cadastrar                                          |\n");
		printf("|   [2] Listar                                             |\n");
		printf("|   [3] Buscar                                             |\n");
		printf("|   [4] Editar                                             |\n");
		printf("|   [5] Excluir                                            |\n");
		printf("|   [0] Sair                                               |\n");
		printf("|                                                          |\n");
		printf("+----------------------------------------------------------+\n");
		printf("\n  >> Escolha uma opcao: ");

		int valor;

		scanf("%d", &valor);
		scanf("%*[^\n]"); scanf("%*c");
		limpar_terminal();	 // limpa a tela

		switch (valor){ // é minha função de comparação
			case 0:{
				continua = false;
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
				char codigo[15];

				printf("+----------------------------------------------------------+\n");
				printf("|                     BUSCAR LIVRO                         |\n");
				printf("+----------------------------------------------------------+\n\n");
				printf("  Digite o codigo para buscar: ");
				scanf(" %[^\n]", codigo);
				scanf("%*[^\n]"); scanf("%*c");

				int i = buscar(codigo);

				printf("\n");
				if (i != -1) {
					printf("+----------------------------------------------------------+\n");
					printf("| Livro encontrado!                                        |\n");
					imprimir_livro(livros[i]);
				} else {
					printf("  >> Livro nao encontrado!\n\n");
				}

				pause_terminal();
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
				pause_terminal(); // pause - pausou o sistema
				break;
			}
		}
	}

	salvar_binario();
	limpar_terminal();	 // limpa a tela
	free(livros);
	return 0;
}
