#include "jogo.h"

//CRUD BÁSICO DO BÁSICO(TRIVIALKKKKK)
//Preferi usar binário pra salvar ao invez de txt porque no txt estava dando alguns bugs, professor.

Node* cadastrarJogo(Node* cabeca, int* proximo_id) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    if (novoNode == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return cabeca;
    }

    printf("\n--- Cadastro de Novo Jogo ---\n");
    printf("Nome do Jogo: ");
    fgets(novoNode->jogo.nome, 100, stdin);
    novoNode->jogo.nome[strcspn(novoNode->jogo.nome, "\n")] = 0;

    printf("Genero: ");
    fgets(novoNode->jogo.genero, 50, stdin);
    novoNode->jogo.genero[strcspn(novoNode->jogo.genero, "\n")] = 0;

    printf("Plataforma: ");
    fgets(novoNode->jogo.plataforma, 50, stdin);
    novoNode->jogo.plataforma[strcspn(novoNode->jogo.plataforma, "\n")] = 0;
    
    printf("Ano de Lancamento: ");
    scanf("%d", &novoNode->jogo.ano);
    
    printf("Preco (ex: 59.99): ");
    scanf("%f", &novoNode->jogo.preco);
    getchar(); // Limpa o buffer do teclado

    novoNode->jogo.id = *proximo_id;
    (*proximo_id)++;
    novoNode->proximo = NULL;

    if (cabeca == NULL) {
        printf("Jogo cadastrado com sucesso com o ID %d!\n", novoNode->jogo.id);
        return novoNode;
    }

    Node* atual = cabeca;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novoNode;

    printf("Jogo cadastrado com sucesso com o ID %d!\n", novoNode->jogo.id);
    return cabeca;
}

void listarJogos(Node* cabeca) {
    if (cabeca == NULL) {
        printf("\nNenhum jogo cadastrado na biblioteca.\n");
        return;
    }
    printf("\n--- Minha Biblioteca de Jogos ---\n");
    Node* atual = cabeca;
    while (atual != NULL) {
        printf("------------------------------------\n");
        printf("ID: %d\n", atual->jogo.id);
        printf("Nome: %s\n", atual->jogo.nome);
        printf("Genero: %s\n", atual->jogo.genero);
        printf("Ano: %d\n", atual->jogo.ano);
        printf("Plataforma: %s\n", atual->jogo.plataforma);
        printf("Preco: R$ %.2f\n", atual->jogo.preco);
        printf("------------------------------------\n");
        atual = atual->proximo;
    }
}

void editarJogo(Node* cabeca, int id_para_editar) {
    Node* atual = cabeca;
    while (atual != NULL && atual->jogo.id != id_para_editar) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Jogo com ID %d nao encontrado.\n", id_para_editar);
        return;
    }

    printf("\nEditando Jogo: %s (ID: %d)\n", atual->jogo.nome, atual->jogo.id);
    printf("Deixe em branco para nao alterar.\n");

    char buffer[100];

    printf("Novo nome (%s): ", atual->jogo.nome);
    fgets(buffer, 100, stdin);
    if (strcmp(buffer, "\n") != 0) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(atual->jogo.nome, buffer);
    }
    
    printf("Jogo atualizado com sucesso!\n");
}

Node* excluirJogo(Node* cabeca, int id_para_excluir) {
    Node* atual = cabeca;
    Node* anterior = NULL;

    // Procura o nó a ser excluído, mantendo o ponteiro para o anterior
    while (atual != NULL && atual->jogo.id != id_para_excluir) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Jogo com ID %d nao encontrado.\n", id_para_excluir);
        return cabeca;
    }

    // Caso 1: O nó a ser excluído é a cabeça da lista
    if (anterior == NULL) {
        cabeca = atual->proximo;
    } 
    // Caso 2: O nó está no meio ou no fim
    else {
        anterior->proximo = atual->proximo;
    }

    printf("Jogo '%s' (ID: %d) excluido com sucesso.\n", atual->jogo.nome, atual->jogo.id);
    free(atual);
    return cabeca;
}

//Parte que manipula os arquviso.

void salvarJogos(Node* cabeca, const char* nome_arquivo) {

    FILE* arquivo = fopen(nome_arquivo, "wb"); // Salva em binário
    if (arquivo == NULL) return;
    Node* atual = cabeca;
    while (atual != NULL) {
        fwrite(&atual->jogo, sizeof(Jogo), 1, arquivo);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

Node* carregarJogos(const char* nome_arquivo, int* proximo_id) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) return NULL;
    Node* cabeca = NULL;
    Node* atual = NULL;
    Jogo temp_jogo;
    int maior_id = 0;

    while (fread(&temp_jogo, sizeof(Jogo), 1, arquivo) == 1) {
        Node* novoNode = (Node*)malloc(sizeof(Node));
        novoNode->jogo = temp_jogo;
        novoNode->proximo = NULL;
        if (novoNode->jogo.id > maior_id) maior_id = novoNode->jogo.id;

        if (cabeca == NULL) {
            cabeca = novoNode;
            atual = novoNode;
        } else {
            atual->proximo = novoNode;
            atual = novoNode;
        }
    }
    fclose(arquivo);
    *proximo_id = maior_id + 1;
    return cabeca;
}


//Merge Sort(Achei complicado de implementar)

Node* sortedMerge(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    Node* result = NULL;
    if (a->jogo.id <= b->jogo.id) {
        result = a;
        result->proximo = sortedMerge(a->proximo, b);
    } else {
        result = b;
        result->proximo = sortedMerge(a, b->proximo);
    }
    return result;
}
void frontBackSplit(Node* source, Node** frontRef, Node** backRef) {
    Node* fast; Node* slow;
    slow = source; fast = source->proximo;
    while (fast != NULL) {
        fast = fast->proximo;
        if (fast != NULL) {
            slow = slow->proximo;
            fast = fast->proximo;
        }
    }
    *frontRef = source; *backRef = slow->proximo;
    slow->proximo = NULL;
}
void mergeSort(Node** cabecaRef) {
    Node* cabeca = *cabecaRef; Node* a; Node* b;
    if ((cabeca == NULL) || (cabeca->proximo == NULL)) return;
    frontBackSplit(cabeca, &a, &b);
    mergeSort(&a); mergeSort(&b);
    *cabecaRef = sortedMerge(a, b);
}
int buscaBinariaRecursiva(Jogo array[], int inicio, int fim, int id_procurado) {
    if (fim >= inicio) {
        int meio = inicio + (fim - inicio) / 2;
        if (array[meio].id == id_procurado) return meio;
        if (array[meio].id > id_procurado) return buscaBinariaRecursiva(array, inicio, meio - 1, id_procurado);
        return buscaBinariaRecursiva(array, meio + 1, fim, id_procurado);
    }
    return -1;
}
Jogo* buscarJogoPorId_BuscaBinaria(Node* cabeca, int id_procurado) {
    if (cabeca == NULL) return NULL;
    int n = 0; Node* temp = cabeca;
    while (temp != NULL) { n++; temp = temp->proximo; }
    Jogo* vetorJogos = (Jogo*)malloc(n * sizeof(Jogo));
    if(vetorJogos == NULL) return NULL;
    temp = cabeca;
    for (int i = 0; i < n; i++) { vetorJogos[i] = temp->jogo; temp = temp->proximo; }
    

    int indice = buscaBinariaRecursiva(vetorJogos, 0, n - 1, id_procurado);

    if (indice != -1) {
        // Aloca memória para retornar uma cópia, evitando problemas de ponteiro
        Jogo* jogoEncontrado = (Jogo*)malloc(sizeof(Jogo));
        *jogoEncontrado = vetorJogos[indice];
        free(vetorJogos);
        return jogoEncontrado;
    }
    free(vetorJogos); 
    return NULL;
}

//Funções extras

void listarPorPlataforma(Node* cabeca) {
    char plataforma[50];
    int encontrou = 0;
    printf("\nDigite a plataforma para filtrar (ex: PC, PlayStation, Xbox): ");
    fgets(plataforma, 50, stdin);
    plataforma[strcspn(plataforma, "\n")] = 0;

    Node* atual = cabeca;
    while(atual != NULL) {
        if (strcasecmp(atual->jogo.plataforma, plataforma) == 0) { // strcasecmp ignora maiúsculas/minúsculas
            if (!encontrou) printf("\n--- Jogos para a plataforma '%s' ---\n", plataforma);
            printf("ID: %d, Nome: %s, Ano: %d\n", atual->jogo.id, atual->jogo.nome, atual->jogo.ano);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrou) printf("Nenhum jogo encontrado para a plataforma '%s'.\n", plataforma);
}

void listarPorGenero(Node* cabeca) {
    char genero[50];
    int encontrou = 0;
    printf("\nDigite o genero para filtrar (ex: RPG, Acao, Estrategia): ");
    fgets(genero, 50, stdin);
    genero[strcspn(genero, "\n")] = 0;

    Node* atual = cabeca;
    while(atual != NULL) {
        if (strcasecmp(atual->jogo.genero, genero) == 0) {
            if (!encontrou) printf("\n--- Jogos do genero '%s' ---\n", genero);
            printf("ID: %d, Nome: %s, Plataforma: %s\n", atual->jogo.id, atual->jogo.nome, atual->jogo.plataforma);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrou) printf("Nenhum jogo encontrado para o genero '%s'.\n", genero);
}

void calcularValorTotal(Node* cabeca) {
    float total = 0.0;
    Node* atual = cabeca;
    while(atual != NULL) {
        total += atual->jogo.preco;
        atual = atual->proximo;
    }
    printf("\nO valor total da sua biblioteca de jogos e: R$ %.2f\n", total);
}

void contarTotalDeJogos(Node* cabeca) {
    int count = 0;
    Node* atual = cabeca;
    while(atual != NULL) {
        count++;
        atual = atual->proximo;
    }
    printf("\nVoce tem um total de %d jogo(s) na sua biblioteca.\n", count);
}