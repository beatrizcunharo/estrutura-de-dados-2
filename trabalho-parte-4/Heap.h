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

class Heap 
{

    public:

        // CONSTRUTOR

        Heap(long capacidade);

        // DESTRUTOR

        ~Heap();
        
        // GETS E SETS

        long getTamanho();
        void setTamanho(long tamanho);
        long getCapacidade();
        void setCapacidade(long capacidade);
        No *getRaiz();
        void setRaiz(No *raiz);
        No **getArrayNos();
        void setArrayNos(No **arrayNos);
        void setNoArrayNos(No *no, int indice);

        // OUTRAS FUNÇÕES
        
        void inserirHeapMinima(No* minHeapNode, int *comparacoes);
        No* puxarMinima(int *comparacoes);
        bool eRaiz();
        void troca(No** a, No** b);
        void heapfyMinima(int idx, int *comparacoes);
        void constroiHeap(int *comparacoes);

    private:
        long tamanho;
        long capacidade;
        No *raiz;
        No **arrayNos;
};

#endif // HEAP_H_INCLUDED
