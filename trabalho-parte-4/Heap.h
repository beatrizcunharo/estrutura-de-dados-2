/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include "No.h"

class Heap
{

public:
    // CONSTRUTOR

    Heap(long capacidade);

    // DESTRUTOR

    ~Heap();

    // GETS

    long getTamanho();
    long getCapacidade();
    No *getRaiz();
    No **getArrayNos();

    // SETS

    void setTamanho(long tamanho);
    void setCapacidade(long capacidade);
    void setRaiz(No *raiz);
    void setArrayNos(No **arrayNos);
    void setNoArrayNos(No *no, int indice);

    // OUTRAS FUNÇÕES

    void inserirHeapMinima(No *noHeapMinima, int *comparacoes);
    No *retirarMinima(int *comparacoes);
    bool ehRaiz();
    void troca(No **a, No **b);
    void heapifyMinima(int idx, int *comparacoes);
    void construirHeapMinima(int *comparacoes);

private:
    long tamanho;
    long capacidade;
    No *raiz;
    No **arrayNos;
};

#endif // HEAP_H_INCLUDED
