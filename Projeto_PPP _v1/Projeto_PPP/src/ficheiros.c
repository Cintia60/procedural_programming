#include "../lib/ficheiros.h"


bool idJaAtribuido(dLista lista, int id) {
    dLista aux = lista->next; // Começa do primeiro nó (ignorando o nó cabeçalho)
    while (aux != NULL) {
        if (aux->doenteLista.id == id) {
            return true; // ID já está atribuído a um doente na lista
        }
        aux = aux->next;
    }
    return false; // ID não está atribuído a nenhum doente na lista
}
// Função para ler uma linha de entrada do usuário
void lerLinha(char *string, int tamanho) {
    fgets(string, tamanho, stdin); // Usa fgets para ler a linha
    // Remove o caractere de nova linha (\n) se estiver presente
    if (string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }
}

// Função para verificar se uma string contém apenas dígitos
int contemApenasDigitos(const char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) {
            return 0; // Se qualquer caractere não for um dígito, retorna falso
        }
    }
    return 1; // Se todos os caracteres forem dígitos, retorna verdadeiro
}
// Função para ler um número inteiro validado do usuário
int lerInteiro() {
    char input[TAMANHO_MAXIMO];
    lerLinha(input, TAMANHO_MAXIMO); // Lê a entrada do usuário como uma string
    // Verifica se a entrada está vazia
    if (input[0] == '\0') {
        printf("Entrada inválida! Por favor, insira um valor.\n");
        return -1; // Retorna um valor inválido
    }

    // Verifica se a entrada contém apenas dígitos
    if (!contemApenasDigitos(input)) {
        printf("Entrada inválida! Por favor, insira um número inteiro.\n");
        return -1; // Retorna um valor inválido
    }

    // Converte a entrada para um número inteiro e retorna
    return atoi(input);
}

// Função para ler um número inteiro validado do usuário
int lerInteiroData(int min, int max) {
    char input[TAMANHO_MAXIMO];
    lerLinha(input, TAMANHO_MAXIMO); // Lê a entrada do usuário como uma string

    // Verifica se a entrada contém apenas dígitos
    if (!contemApenasDigitos(input)) {
        printf("Entrada inválida! Por favor, insira um número inteiro.\n");
        return -1; // Retorna um valor inválido
    }

    // Converte a entrada para um número inteiro
    int valor = atoi(input);

    // Verifica se o valor está dentro do intervalo permitido
    if (valor < min || valor > max) {
        printf("Entrada inválida! Por favor, insira um valor entre %d e %d.\n", min, max);
        return -1; // Retorna um valor inválido
    }

    return valor; // Retorna o valor válido
}
