#include "../lib/funcoes.h"

dLista dListaCria() {
    dLista aux;
    aux = (dLista)malloc(sizeof(noListaDoente));
    if (aux != NULL) {
        aux->doenteLista.id = 0;
        aux->doenteLista.record_head = NULL;
        aux->doenteLista.maior_tensao_max=NULL;
        aux->next = NULL;
    }
    return aux;
}

int vazia(dLista lista) {
    if (lista->next == NULL)
        return 1; // Lista vazia
    else
        return 0; // Lista não vazia
}

dLista pListadestroi(dLista lista) {
    dLista temp_ptr;
    while (!vazia(lista)) {
        temp_ptr = lista;
        lista = lista->next;
        
        // Libera a memória associada à lista de registros do paciente
        noListaRegisto *registo_atual = temp_ptr->doenteLista.record_head;
        while (registo_atual != NULL) {
            noListaRegisto *temp_registo = registo_atual;
            registo_atual = registo_atual->next;
            free(temp_registo);
        }

        free(temp_ptr);
    }
    return NULL;
}

void procura(dLista lista, int chave, dLista *ant, dLista *atual) {
    *ant = lista;
    *atual = lista->next;
    while (*atual != NULL && (*atual)->doenteLista.id != chave) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if (*atual != NULL && (*atual)->doenteLista.id != chave) {
        *atual = NULL; // Elemento não encontrado
    }
}

void procura_nome(dLista lista, const char* chave, dLista *ant, dLista *atual) {
    *ant = lista;
    *atual = lista->next;
    while (*atual != NULL && strcmp((*atual)->doenteLista.name, chave) < 0) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if (*atual != NULL && strcmp((*atual)->doenteLista.name, chave) != 0) {
        *atual = NULL; // Elemento não encontrado
    }
}

void atualizarArquivosTexto(dLista lista_pacientes) {
    // Reescreve o arquivo de texto de doentes
    FILE *arquivo_doentes = fopen("dados_doentes.txt", "w");
    if (arquivo_doentes != NULL) {
        dLista aux_doentes = lista_pacientes->next;
        while (aux_doentes != NULL) {
            fprintf(arquivo_doentes, "%d\n", aux_doentes->doenteLista.id);
            fprintf(arquivo_doentes, "%s\n", aux_doentes->doenteLista.name);
            fprintf(arquivo_doentes, "%02d/%02d/%04d\n", aux_doentes->doenteLista.birth_date.dia, aux_doentes->doenteLista.birth_date.mes, aux_doentes->doenteLista.birth_date.ano);
            fprintf(arquivo_doentes, "%s\n", aux_doentes->doenteLista.citizen_card);
            fprintf(arquivo_doentes, "%d\n", aux_doentes->doenteLista.phone);
            fprintf(arquivo_doentes, "%s\n", aux_doentes->doenteLista.email);
            aux_doentes = aux_doentes->next;
        }
        fclose(arquivo_doentes);
    } else {
        printf("Erro ao abrir o arquivo de doentes para escrita.\n");
    }

    // Reescreve o arquivo de texto de registros
    FILE *arquivo_registros = fopen("registros_doentes.txt", "w");
    if (arquivo_registros != NULL) {
        dLista aux_pacientes = lista_pacientes->next;
        while (aux_pacientes != NULL) {
            rLista aux_registros = aux_pacientes->doenteLista.record_head;
            while (aux_registros != NULL) {
                fprintf(arquivo_registros, "%d\n", aux_pacientes->doenteLista.id);
                fprintf(arquivo_registros, "%02d/%02d/%04d\n", aux_registros->registoLista.date.dia, aux_registros->registoLista.date.mes, aux_registros->registoLista.date.ano);
                fprintf(arquivo_registros, "%d\n", aux_registros->registoLista.max_blood_pressure);
                fprintf(arquivo_registros, "%d\n", aux_registros->registoLista.min_blood_pressure);
                fprintf(arquivo_registros, "%d\n", aux_registros->registoLista.weight);
                fprintf(arquivo_registros, "%d\n", aux_registros->registoLista.height);
                aux_registros = aux_registros->next;
            }
            aux_pacientes = aux_pacientes->next;
        }
        fclose(arquivo_registros);
    } else {
        printf("Erro ao abrir o arquivo de registros para escrita.\n");
    }
}


void elimina(dLista lista, int chave) {
    dLista ant, atual;
    procura(lista, chave, &ant, &atual);
    if (atual != NULL) {
        ant->next = atual->next;
        free(atual);
    }
    atualizarArquivosTexto(lista);
}

void insere(dLista lista, struct doente p1) {
    dLista no, ant, inutil;
    no = (dLista)malloc(sizeof(noListaDoente));
    if (no != NULL) {
        // Converte o nome do paciente para maiúsculas
        for (int i = 0; p1.name[i] != '\0'; i++) {
            p1.name[i] = toupper(p1.name[i]);
        }
        no->doenteLista = p1;
        no->doenteLista.record_head=NULL;
        no->doenteLista.maior_tensao_max=NULL;
        procura_nome(lista, p1.name, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

// Função de comparação de datas
int compara_data(data d1, data d2) {
    if (d1.ano < d2.ano) {
        return -1;
    } else if (d1.ano > d2.ano) {
        return 1;
    } else {
        if (d1.mes < d2.mes) {
            return -1;
        } else if (d1.mes > d2.mes) {
            return 1;
        } else {
            if (d1.dia < d2.dia) {
                return -1;
            } else if (d1.dia > d2.dia) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

void procura_data(noListaRegisto* head, struct registo novo_registro, noListaRegisto** ant, noListaRegisto** atual) {
    *ant = NULL;
    *atual = head;
    
   while (*atual != NULL && compara_data((*atual)->registoLista.date, novo_registro.date) < 0) {
        *ant = *atual;
        *atual = (*atual)->next;
    }
}


void insere_registro(dLista lista, int id_doente, struct registo novo_registro) {
    dLista ant, atual;

    procura(lista, id_doente, &ant, &atual);

    if (atual == NULL) {
        printf("Doente com ID %d não encontrado.\n", id_doente);
        return;
    }

    noListaRegisto* novo_no_registo = (noListaRegisto*)malloc(sizeof(noListaRegisto));
    if (novo_no_registo == NULL) {
        printf("Erro ao alocar memória para o novo registro.\n");
        return;
    }

    novo_no_registo->registoLista = novo_registro;
    novo_no_registo->registoLista.next_tensao = NULL;

    noListaRegisto* ant_registro = NULL;
    noListaRegisto* atual_registro = NULL;
    
    procura_data(atual->doenteLista.record_head, novo_registro, &ant_registro, &atual_registro);

    if (ant_registro == NULL) {
        novo_no_registo->next = atual->doenteLista.record_head;
        atual->doenteLista.record_head = novo_no_registo;
    } else {
        novo_no_registo->next = ant_registro->next;
        ant_registro->next = novo_no_registo;
    }

    // Atualizar maior_tensao_max e next_tensao
    struct registo* prev_tensao = NULL;
    struct registo* current_tensao = atual->doenteLista.maior_tensao_max;
    while (current_tensao != NULL && current_tensao->max_blood_pressure > novo_registro.max_blood_pressure) {
        prev_tensao = current_tensao;
        current_tensao = current_tensao->next_tensao;
    }

    if (prev_tensao == NULL) {
        novo_no_registo->registoLista.next_tensao = atual->doenteLista.maior_tensao_max;
        atual->doenteLista.maior_tensao_max = &novo_no_registo->registoLista;
    } else {
        novo_no_registo->registoLista.next_tensao = prev_tensao->next_tensao;
        prev_tensao->next_tensao = &novo_no_registo->registoLista;
    }

}

void listar_doentes_com_tensao_acima(dLista lista, int valor) {
    dLista atual = lista;
    while (atual != NULL) {
        struct registo* reg_atual = atual->doenteLista.maior_tensao_max;
        int encontrou = 0;
        
        while (reg_atual != NULL && reg_atual->max_blood_pressure > valor) {
            if (!encontrou) {
                printf("\nDoente ID: %d, Nome: %s\n", atual->doenteLista.id, atual->doenteLista.name);
                encontrou = 1;
            }
            printf("Tensão Máxima: %d\n",
                 reg_atual->max_blood_pressure);
            reg_atual = reg_atual->next_tensao;
        }
        atual = atual->next;
    }
}



// Função para pesquisar um elemento na lista
dLista pesquisa(dLista lista, int chave) {
    dLista ant, atual;
    procura(lista, chave, &ant, &atual);
    return atual;
}

void imprime(dLista lista) {
    dLista aux = lista->next; // Salta o nó cabeçalho
    while (aux) {
        printf("%s\n", aux->doenteLista.name);
        aux = aux->next;
    }
}

void lerDadosDoentes(const char *nome_arquivo, dLista lista_pacientes) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de doentes.\n");
        return;
    }

    struct doente novo_doente;

    while (fscanf(arquivo, "%d\n", &novo_doente.id) != EOF) {
        // Atribui valores padrão aos membros da estrutura doente
        novo_doente.birth_date.dia = 0;
        novo_doente.birth_date.mes = 0;
        novo_doente.birth_date.ano = 0;
        novo_doente.phone = 0;
        novo_doente.name[0] = '\0';
        novo_doente.citizen_card[0] = '\0';
        novo_doente.email[0] = '\0';

        // Ler os dados do doente
        fgets(novo_doente.name,TAMANHO_MAXIMO,arquivo);
        //fscanf(arquivo,"%[^\n]",novo_doente.name);
        fscanf(arquivo, "%d/%d/%d\n", &novo_doente.birth_date.dia, &novo_doente.birth_date.mes, &novo_doente.birth_date.ano);
        fgets(novo_doente.citizen_card,TAMANHO_MAXIMO,arquivo);
        //fscanf(arquivo,"%[^\n]",novo_doente.citizen_card);
        fscanf(arquivo, "%d\n", &novo_doente.phone); 
        fgets(novo_doente.email,TAMANHO_MAXIMO,arquivo);
        //fscanf(arquivo,"%[^\n]",novo_doente.email);

        // Insere o novo doente na lista de pacientes
        insere(lista_pacientes, novo_doente);
    }

    fclose(arquivo);
}

void lerRegistros(const char *nome_arquivo, dLista lista_pacientes) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de registros.\n");
        return;
    }

    int id_doente;
    struct registo novo_registo;

    while (fscanf(arquivo, "%d", &id_doente) != EOF) {
        // Atribui valores padrão aos membros da estrutura registo
        novo_registo.date.dia = 0;
        novo_registo.date.mes = 0;
        novo_registo.date.ano = 0;
        novo_registo.max_blood_pressure = 0;
        novo_registo.min_blood_pressure = 0;
        novo_registo.weight = 0;
        novo_registo.height = 0;

        // Lê os dados do registro
        fscanf(arquivo, "%d/%d/%d", &novo_registo.date.dia, &novo_registo.date.mes, &novo_registo.date.ano);
        fscanf(arquivo, "%d", &novo_registo.max_blood_pressure);
        fscanf(arquivo, "%d", &novo_registo.min_blood_pressure);
        fscanf(arquivo, "%d", &novo_registo.weight);
        fscanf(arquivo, "%d", &novo_registo.height);

        // Insere o novo registro na lista de registros do paciente correspondente
        insere_registro(lista_pacientes, id_doente, novo_registo);
    }

    fclose(arquivo);
}











