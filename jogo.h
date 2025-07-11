#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char genero[50];
    int ano;
    char plataforma[50];
    float preco;
} Jogo;

// Nó da lista de jogos
typedef struct Node {
    Jogo jogo;
    struct Node* proximo;
} Node;


// CRUD Básico
Node* cadastrarJogo(Node* cabeca, int* proximo_id);
void listarJogos(Node* cabeca);
void editarJogo(Node* cabeca, int id_para_editar);
Node* excluirJogo(Node* cabeca, int id_para_excluir);

// Algoritmos
void mergeSort(Node** cabecaRef);
Jogo* buscarJogoPorId_BuscaBinaria(Node* cabeca, int id_procurado);

// Funções dos Arquivos
void salvarJogos(Node* cabeca, const char* nome_arquivo);
Node* carregarJogos(const char* nome_arquivo, int* proximo_id);

// Funções Extras
void listarPorPlataforma(Node* cabeca);
void listarPorGenero(Node* cabeca);
void calcularValorTotal(Node* cabeca);
void contarTotalDeJogos(Node* cabeca);

#endif 