#include "../lib/ficheiros.h"
#include "../lib/funcoes.h"

int main() {
    dLista lista_pacientes = dListaCria(); // Cria a lista de pacientes
    int option;
    // Ler os dados dos doentes do arquivo "dados_doentes.txt"
    lerDadosDoentes("dados_doentes.txt", lista_pacientes);
    //Ler os registros dos doentes do arquivo "registros_doentes.txt"
    lerRegistros("registros_doentes.txt", lista_pacientes);

    do {
        printf("===== Menu =====\n");
        printf("1. Introduzir dados de um novo doente.\n");
        printf("2. Eliminar um doente existente.\n");
        printf("3. Listar todos os doentes por ordem alfabética.\n");
        printf("4. Apresentar toda a informação de um determinado doente.\n");
        printf("5. Registar as tensões, o peso e a altura de um determinado doente num determinado dia.\n");
        printf("6. Listar os doentes com tensões máximas acima de um determinado valor (por ordem decrescente das mesmas).\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

         option = lerInteiro(); // Lê a opção do usuário

        switch(option) {
            case 1:
    printf("===== Introduzir dados de um novo doente =====\n");
    struct doente novo_doente;
    printf("ID do doente: ");
    novo_doente.id = lerInteiro();
    if (novo_doente.id == -1) continue; // Volta para o início do loop se a entrada for inválida
    
    // Verifica se o ID já está atribuído na lista
    if (idJaAtribuido(lista_pacientes, novo_doente.id)) {
        printf("ID já atribuído a outro doente. Por favor, insira um ID único.\n");
        continue; // Volta para o início do loop
    }
    
    printf("Nome do doente: ");
    lerLinha(novo_doente.name, sizeof(novo_doente.name));
    if (strlen(novo_doente.name) == 0) {
                    printf("Nome inválido! Por favor, insira um nome.\n");
                    continue; // Volta para o início do loop
                }
    printf("Dia de nascimento do doente: ");
novo_doente.birth_date.dia = lerInteiroData(1, 31);
if (novo_doente.birth_date.dia == -1) continue; // Volta para o início do loop se a entrada for inválida
printf("Mês de nascimento do doente: ");
novo_doente.birth_date.mes = lerInteiroData(1, 12);
if (novo_doente.birth_date.mes == -1) continue; // Volta para o início do loop se a entrada for inválida
printf("Ano de nascimento do doente: ");
novo_doente.birth_date.ano = lerInteiroData(1900, 2024);
if (novo_doente.birth_date.ano == -1) continue; // Volta para o início do loop se a entrada for inválida

    printf("Número do cartão de cidadão: ");
    lerLinha(novo_doente.citizen_card, sizeof(novo_doente.citizen_card));
    if (strlen(novo_doente.citizen_card) == 0) {
                    printf("Número de cartão de cidadão inválido! Por favor, insira um número de cartão de cidadão.\n");
                    continue; // Volta para o início do loop
                }
    printf("Telefone do doente: ");
    novo_doente.phone=lerInteiroData(910000000,939999999);
    if (novo_doente.phone == -1) continue;
    printf("Email do doente: ");
    lerLinha(novo_doente.email, sizeof(novo_doente.email));
    if (strlen(novo_doente.email) == 0) {
                    printf("Email inválido! Por favor, insira um email.\n");
                    continue; // Volta para o início do loop
                }
    insere(lista_pacientes, novo_doente);
    FILE *arquivo = fopen("dados_doentes.txt", "a");
        if (arquivo != NULL) {
            fprintf(arquivo, "%d\n", novo_doente.id);
            fprintf(arquivo, "%s\n", novo_doente.name);
            fprintf(arquivo, "%02d/%02d/%04d\n", novo_doente.birth_date.dia, novo_doente.birth_date.mes, novo_doente.birth_date.ano);
            fprintf(arquivo, "%s\n", novo_doente.citizen_card);
            fprintf(arquivo, "%d\n", novo_doente.phone);
            fprintf(arquivo, "%s\n", novo_doente.email);
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo de doentes para escrita.\n");
        }
    printf("Novo doente inserido com sucesso!\n");
    break;

            case 2:
    printf("===== Eliminar um doente existente =====\n");
    printf("ID do doente a eliminar: ");
    int id_a_eliminar=lerInteiro();
    dLista doente_a_eliminar = pesquisa(lista_pacientes, id_a_eliminar);
    if (doente_a_eliminar != NULL) {
        // Libera a memória associada à lista de registros desse doente
        rLista registo_atual = doente_a_eliminar->doenteLista.record_head;
        while (registo_atual != NULL) {
            rLista registo_temp = registo_atual;
            registo_atual = registo_atual->next;
            free(registo_temp);
        }
        // Remove o doente da lista principal e libera sua memória
        elimina(lista_pacientes, id_a_eliminar);
        printf("Doente eliminado com sucesso!\n");
    } else {
        printf("Doente não encontrado.\n");
    }
    break;

            case 3:
    printf("===== Listar todos os doentes por ordem alfabética =====\n");
    if(vazia(lista_pacientes)){
        printf("não tem nenhum doente na lista\n");
    }
    imprime(lista_pacientes);
    break;

            case 4:
    printf("===== Apresentar toda a informação de um determinado doente =====\n");
    printf("ID do doente a pesquisar: ");
    int id_a_pesquisar=lerInteiro();
    dLista doente_encontrado = pesquisa(lista_pacientes, id_a_pesquisar);
    if (doente_encontrado != NULL) {
        printf("ID: %d\n", doente_encontrado->doenteLista.id);
        printf("Nome: %s\n", doente_encontrado->doenteLista.name);
        printf("Data de Nascimento: %d/%d/%d\n", doente_encontrado->doenteLista.birth_date.dia, doente_encontrado->doenteLista.birth_date.mes, doente_encontrado->doenteLista.birth_date.ano);
        printf("Número do Cartão de Cidadão: %s\n", doente_encontrado->doenteLista.citizen_card);
        printf("Telefone: %d\n", doente_encontrado->doenteLista.phone);
        printf("Email: %s\n", doente_encontrado->doenteLista.email);
        
        // Exibindo informações dos registros, se houver
        printf("===== Registros do Doente =====\n");
        rLista registo_atual = doente_encontrado->doenteLista.record_head;
        while (registo_atual != NULL) {
            printf("ID: %d\n", id_a_pesquisar);
            printf("Data do Registo: %d/%d/%d\n", registo_atual->registoLista.date.dia, registo_atual->registoLista.date.mes, registo_atual->registoLista.date.ano);
            printf("Tensão Máxima: %d\n", registo_atual->registoLista.max_blood_pressure);
            printf("Tensão Mínima: %d\n", registo_atual->registoLista.min_blood_pressure);
            printf("Peso: %d\n", registo_atual->registoLista.weight);
            printf("Altura: %d\n", registo_atual->registoLista.height);
            registo_atual = registo_atual->next;
        }
    } else {
        printf("Doente não encontrado.\n");
    }
    break;


            case 5:
    printf("===== Registar as tensões, o peso e a altura de um determinado doente num determinado dia =====\n");
    printf("ID do doente: ");
    int id_doente_registo=lerInteiro();
    // Verifica se o ID do doente existe na lista de pacientes
if (!idJaAtribuido(lista_pacientes, id_doente_registo)) {
    printf("ID do doente não encontrado. Não é possível inserir o registro.\n");
    continue; // Volta para o início do loop
}
    struct registo novo_registo;
    printf("Dia do registo (DD/MM/AAAA): ");
novo_registo.date.dia = lerInteiroData(1, 31);
if (novo_registo.date.dia == -1) continue; // Volta para o início do loop se a entrada for inválida
printf("Mês do registo (DD/MM/AAAA): ");
novo_registo.date.mes = lerInteiroData(1, 12);
if (novo_registo.date.mes == -1) continue; // Volta para o início do loop se a entrada for inválida
printf("Ano do registo (DD/MM/AAAA): ");
novo_registo.date.ano = lerInteiroData(1900, 2024);
if (novo_registo.date.ano == -1) continue; // Volta para o início do loop se a entrada for inválida
dLista paciente = pesquisa(lista_pacientes, id_doente_registo);
    if (paciente != NULL) {
        if (novo_registo.date.ano < paciente->doenteLista.birth_date.ano ||
            (novo_registo.date.ano == paciente->doenteLista.birth_date.ano &&
             novo_registo.date.mes < paciente->doenteLista.birth_date.mes) ||
            (novo_registo.date.ano == paciente->doenteLista.birth_date.ano &&
             novo_registo.date.mes == paciente->doenteLista.birth_date.mes &&
             novo_registo.date.dia < paciente->doenteLista.birth_date.dia)) {
            printf("A data do registo não pode ser anterior à data de nascimento do paciente. Por favor, insira uma data válida.\n");
            break; // Sai do switch case
        }
    } 

    printf("Tensão máxima: ");
    novo_registo.max_blood_pressure=lerInteiro();
    printf("Tensão mínima: ");
    novo_registo.min_blood_pressure=lerInteiro();
    // Verifica se a tensão mínima é maior que a máxima
    if (novo_registo.min_blood_pressure > novo_registo.max_blood_pressure) {
        printf("A tensão mínima não pode ser maior que a máxima. Por favor, insira um valor válido.\n");
        break; 
    }
    printf("Peso: ");
    novo_registo.weight=lerInteiro();
    printf("Altura: ");
    novo_registo.height=lerInteiro();
    insere_registro(lista_pacientes, id_doente_registo, novo_registo);
    FILE *arquivo2 = fopen("registros_doentes.txt", "a");
            if (arquivo2 != NULL) {
                fprintf(arquivo2, "%d\n", id_doente_registo);
                fprintf(arquivo2, "%02d/%02d/%04d\n", novo_registo.date.dia, novo_registo.date.mes, novo_registo.date.ano);
                fprintf(arquivo2, "%d\n", novo_registo.max_blood_pressure);
                fprintf(arquivo2, "%d\n", novo_registo.min_blood_pressure);
                fprintf(arquivo2, "%d\n", novo_registo.weight);
                fprintf(arquivo2, "%d\n", novo_registo.height);
                fclose(arquivo2);
            } else {
                printf("Erro ao abrir o arquivo de registros para escrita.\n");
            }
    printf("Registo inserido com sucesso!\n");
    break;
    case 6:
    
                printf("Digite o valor da tensão máxima: ");
                int tensao=lerInteiro();
                listar_doentes_com_tensao_acima(lista_pacientes, tensao);
                break;

            case 0:
    printf("===== Sair =====\n");
    // Libera a memória associada à lista de pacientes
    lista_pacientes = pListadestroi(lista_pacientes);
    printf("Memória liberada. Encerrando o programa.\n");
    break;

            default:
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
        }
    } while(option != 0);

    return 0;
}

