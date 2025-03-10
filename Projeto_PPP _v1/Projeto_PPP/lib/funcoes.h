#ifndef FUNCOES_H
#define FUNCOES_H

#include "gestao_pacientes.h"

dLista dListaCria();
int vazia(dLista lista);
dLista pListadestroi(dLista lista);
void procura(dLista lista, int chave, dLista *ant, dLista *atual);
void procura_nome(dLista lista, const char* chave, dLista *ant, dLista *atual);
void atualizarArquivosTexto(dLista lista_pacientes);
void elimina(dLista lista, int chave);
void insere(dLista lista, struct doente p1);
int compara_data(data d1, data d2);
void procura_data(noListaRegisto* head, struct registo novo_registro, noListaRegisto** ant, noListaRegisto** atual);
void insere_registro(dLista lista, int id_doente, struct registo novo_registro);
void listar_doentes_com_tensao_acima(dLista lista, int valor);
dLista pesquisa(dLista lista, int chave);
void imprime(dLista lista);
void lerDadosDoentes(const char *nome_arquivo, dLista lista_pacientes);
void lerRegistros(const char *nome_arquivo, dLista lista_pacientes);

#endif