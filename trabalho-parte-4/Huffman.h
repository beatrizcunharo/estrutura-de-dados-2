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

    // GETS

    double getTamanhoComprimido();

    // SETS

    void setCodigos(No *root, int arr[], int top);
    void setArray(int *arr, int n, bool *codigo);
    void setTamanhos(char *letras, long *frequencias);

    // OUTRAS FUNÇÕES

    Heap *criarHeapMinima(char *dados, long *frequencia, long tamanho, int *comparacoes);
    No *construirHuffman(char *dados, long *frequencia, long tamanho, int *comparacoes);
    void codificar(char *dados, long *frequencia, long tamanho, int *comparacoes);
    void imprimirCodificado(No *root, int arr[], int top);
    void imprimirArray(int *arr, int n);
    bool *comprimirHuffman(char *letras, long *frequencias, string review_text);
    string descomprimirHuffman(bool *comprimido);

private:
    bool **codigos;
    int *tamanhos;
    double tamanhoComprimido;
    double tamanhoOriginal;
    No *raiz;
    Heap *heapMinima;
};

#endif // HUFFMAN_H_INCLUDED
