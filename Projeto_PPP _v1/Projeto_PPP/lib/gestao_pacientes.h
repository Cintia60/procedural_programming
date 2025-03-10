#ifndef GESTAO_PACIENTES_H
#define GESTAO_PACIENTES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#define TAMANHO_MAXIMO 50 // Tamanho máximo da entrada do usuário

// Definição da estrutura data
typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

// Definição da estrutura registo
struct registo
{
    int patient_id;
    data date;
    int max_blood_pressure;
    int min_blood_pressure;
    int weight;
    int height;
    struct registo* next_tensao; // ponteiro para o próximo registro com tensão máxima menor
};
typedef struct registo Registo;

// Definição da estrutura noListaRegisto
typedef struct noListaRegisto {
    Registo registoLista;
    struct noListaRegisto *next;
} noListaRegisto;

typedef noListaRegisto* rLista;

// Definição da estrutura doente
struct doente
{
    int id;
    char name[TAMANHO_MAXIMO+1];
    data birth_date;
    char citizen_card[TAMANHO_MAXIMO+1];
    int phone;
    char email[TAMANHO_MAXIMO+1];
    noListaRegisto *record_head; // Referência para a lista de registros clínicos
    struct registo* maior_tensao_max; // ponteiro para o registro com a maior tensão máxima
};

typedef struct doente Doente;

typedef struct noListaDoente {
    Doente doenteLista;
    struct noListaDoente *next;
} noListaDoente;

typedef noListaDoente* dLista;



#endif
