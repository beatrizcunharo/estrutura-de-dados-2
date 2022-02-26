/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef  HEAP_H_INCLUDED
#define  HEAP_H_INCLUDED
#include "No.h"
class Heap {

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

        void insereHeapMinima(No* noHeapMinima, int *comparacoes);
        No* recuperaHeapMinima(int *comparacoes);
        void heapifyMinima(int indice, int *comparacoes);
        void constroiHeapMinima(int *comparacoes);

        // FUNÇÕES AUX

        void troca(No** a, No** b);
        bool ehRaiz();

    private:
    
        long tamanho;
        long capacidade;
        No *raiz;
        No **arrayNos;
};

#endif // HEAP_H_INCLUDED
