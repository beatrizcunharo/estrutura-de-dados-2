/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef  HUFFMAN_H_INCLUDED
#define  HUFFMAN_H_INCLUDED
#include "Heap.h"
#include "No.h"

#define TAMANHO 256
#define METADE 128

class Huffman 
{

    public:

        // CONSTRUTOR

        Huffman(long tamanhoOriginal);

        // DESTRUTOR

        ~Huffman();

        // GETS

        double getTamanhoComprimido();

        // OUTRAS FUNÇÕES

        Heap* criarHeapMinima(char *dados, long *frequencia, long tamanho, int *comparacoes);
        No* construirArvore(char *dados, long *frequencia, long tamanho, int *comparacoes);
        void codificar(char *dados, long *frequencia, long tamanho, int *comparacoes);
        void salvarCodigos(No* raiz, int array[], int topo);
        void imprimirCodificado(No* raiz, int array[], int topo);
        void salvarArray(int *array, int N, bool* codigo);
        void imprimirArray(int *array, int N);
        bool* comprimir(char *letras, long *frequencias, string review_text);
        void salvarTamanhos(char *letras, long *frequencias);
        string descomprimir(bool *comprimido);

    private:

        bool** codigos;
        int* tamanhos;
        double tamanhoComprimido;
        double tamanhoOriginal;
        No *raiz;
        Heap *heapMinima;
};

#endif // HUFFMAN_H_INCLUDED
