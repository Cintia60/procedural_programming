## Funcionalidades

### Carregar/guardar dados nos ficheiros  
Ao iniciar o programa, os dados dos ficheiros são lidos e as informações do doente são colocadas na lista de doentes, enquanto os registos são inseridos na fila de registos do respetivo doente.  
**Função:**  
```c
void lerDadosDoentes(const char *nome_arquivo, dLista lista_pacientes);
```

### Inserir doente  
Os doentes são inseridos por ordem alfabética. Sempre que um doente é inserido, os dados são acrescentados no ficheiro `dados_doentes.txt`.  
**Função:**  
```c
void insere(dLista lista, struct doente p1);
```

### Eliminar doente  
Ao eliminar um doente da lista, a memória associada ao nó do doente e aos seus registos é libertada. Depois, os dados da lista são reescritos nos ficheiros.  
**Função:**  
```c
void elimina(dLista lista, int chave);
```

### Listar doentes por ordem alfabética  
A lista de doentes já se encontra ordenada por nomes, bastando apenas imprimi-la.  
**Função:**  
```c
void imprime(dLista lista);
```

### Registar tensões, peso e altura num determinado dia  
Os registos dos doentes são inseridos por ordem de datas e armazenados no ficheiro `registros_doentes.txt`.  
**Função:**  
```c
void insere_registro(dLista lista, int id_doente, struct registo novo_registro);
```

### Apresentar todas as informações de um doente  
A busca do doente é feita pelo ID, seguida da impressão de todos os seus registos.  
**Função:**  
```c
dLista pesquisa(dLista lista, int chave);
```

### Listar doentes com tensões máximas acima de um determinado valor (por ordem decrescente)  
A estrutura `doente` contém um ponteiro extra (`*maior_tensao_max`) para o registo com a maior tensão máxima. Já a estrutura `registo` contém um ponteiro (`*next_tensao`) para o próximo registo com tensão máxima menor. Isso permite percorrer a lista por ordem decrescente.  
**Função:**  
```c
void listar_doentes_com_tensao_acima(dLista lista, int valor);
```

### Proteções de input  
- **Validação geral:** Todos os inputs são lidos como strings e validados antes de serem convertidos para inteiros.
- **Data:** Apenas inteiros válidos podem ser inseridos para dia, mês e ano. Além disso, datas de registo não podem ser anteriores à data de nascimento do paciente.
- **Telefone:** Deve estar entre `910000000` e `939999999`.
- **Tensão:** A tensão mínima de um paciente não pode ser maior que a sua tensão máxima.
- **Campos sem proteção:** Nome, número do cartão de cidadão e e-mail podem conter qualquer caractere, mas não podem estar vazios.
