#ifndef FICHEIROS_H
#define FICHEIROS_H

#include "gestao_pacientes.h"

bool idJaAtribuido(dLista lista, int id);
void lerLinha(char *string, int tamanho);
int contemApenasDigitos(const char *string);
int lerInteiro();
int lerInteiroData(int min, int max);

#endif