/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include "Heap.h"
#include "No.h"

#define TAMANHO_MAXIMO 256
#define METADE_MAXIMO 128

class Huffman 
{

    public:

        // CONSTRUTOR

        Huffman(long tamanhoOriginal);

        // DESTRUTOR

        ~Huffman();

        // OUTRAS FUNÇÕES

        double getTamanhoComprimido();
        Heap* criarHeapMinima(char *dados, long *frequencia, long tamanho, int *comparacoes);
        No* construirHuffmanArvore(char *dados, long *frequencia, long tamanho, int *comparacoes);
        void codificar(char *dados, long *frequencia, long tamanho, int *comparacoes);
        void salvarCodigos(No* root, int arr[], int top);
        void imprimirCodificado(No* root, int arr[], int top);
        void salvarArray(int *arr, int n, bool* codigo);
        void imprimirArray(int *arr, int n);
        bool* comprimirHuffman(char *letras, long *frequencias, string review_text);
        void salvarTamanhos(char *letras, long *frequencias);
        string descomprimirHuffman(bool *comprimido);
    
    private:
        bool** codigosHuffman;
        int* tamanhosHuffman;
        double tamanhoComprimido;
        double tamanhoOriginal;
        No *raiz;
        Heap *minHeap;
};

#endif // HUFFMAN_H_INCLUDED
