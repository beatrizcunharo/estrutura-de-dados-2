/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "Huffman.h"

// CONSTRUTOR

Huffman::Huffman(long tamanhoOriginal) 
{
    this->codigos = new bool*[TAMANHO];
    this->tamanhos = new int[TAMANHO];
    this->tamanhoComprimido = 0;
    this->tamanhoOriginal = tamanhoOriginal;
    this->raiz = nullptr;
    this->heapMinima = nullptr;
}

// DESTRUTOR

Huffman::~Huffman() 
{
    delete this->heapMinima;
}

// GETS

double Huffman::getTamanhoComprimido() 
{
    return this->tamanhoComprimido;
}

// OUTRAS FUNÇÕES

Heap* Huffman::criarHeapMinima(char *dados, long *frequencia, long tamanho, int *comparacoes) 
{
    Heap *heapMinima = new Heap(tamanho);

    for (int i = 0; i < tamanho; ++i) {
        heapMinima->setNoArrayNos(new No(dados[i], frequencia[i]), i);
    }

    heapMinima->setTamanho(tamanho);
    heapMinima->constroiHeapMinima(comparacoes);

    return heapMinima;
}

No* Huffman::construirArvore(char *dados, long *frequencia, long tamanho, int *comparacoes) 
{
    No *esquerda, *direita, *topo;
    Heap *heapMinima = criarHeapMinima(dados, frequencia, tamanho, comparacoes);
    
    this->heapMinima = heapMinima;

    while (!heapMinima->ehRaiz()) {

        esquerda = heapMinima->recuperaHeapMinima(comparacoes);
        direita = heapMinima->recuperaHeapMinima(comparacoes);

        topo = new No('$', esquerda->getFrequencia() + direita->getFrequencia());

        topo->setEsquerda(esquerda);
        topo->setDireita(direita);

        heapMinima->insereHeapMinima(topo, comparacoes);
    }

    return heapMinima->recuperaHeapMinima(comparacoes);
}

void Huffman::codificar(char *dados, long *frequencia, long tamanho, int *comparacoes) 
{
    No *raiz = construirArvore(dados, frequencia, tamanho, comparacoes);
    this->raiz = raiz;

    int array[this->heapMinima->getCapacidade()], topo = 0;

    salvarCodigos(raiz, array, topo);
}

void Huffman::salvarCodigos(No* raiz, int array[], int topo) 
{
    if (raiz->getEsquerda()) {
        array[topo] = 0;
        salvarCodigos(raiz->getEsquerda(), array, topo + 1);
    }
    if (raiz->getDireita()) {
        array[topo] = 1;
        salvarCodigos(raiz->getDireita(), array, topo + 1);
    }
    if (raiz->ehFolha()) {
        int char_int = raiz->getInfo() + METADE;
        this->codigos[char_int] = new bool[topo];
        this->tamanhos[char_int] = topo;
        this->salvarArray(array, topo, this->codigos[char_int]);
    }
}

void Huffman::imprimirCodificado(No* raiz, int array[], int topo) 
{
    if (raiz->getEsquerda()) {
        array[topo] = 0;
        imprimirCodificado(raiz->getEsquerda(), array, topo + 1);
    }

    if (raiz->getDireita()) {
        array[topo] = 1;
        imprimirCodificado(raiz->getDireita(), array, topo + 1);
    }

    if (raiz->ehFolha()) {
        cout<< raiz->getInfo() << ": ";
        imprimirArray(array, topo);
    }
}

void Huffman::salvarArray(int *array, int N, bool* codigo) 
{
    for (int i = 0; i < N; ++i)
        codigo[i] = array[i];
}

void Huffman::imprimirArray(int *array, int N) 
{
    for (int i = 0; i < N; ++i)
        cout<< array[i];

    cout<<"\n";
}

void Huffman::salvarTamanhos(char *letras, long *frequencias) 
{
    this->tamanhoComprimido = 1;
    for(int i = 0; i < heapMinima->getCapacidade(); i++) {
        if(frequencias[i] > 0) {
            int char_int = letras[i] + METADE;
            this->tamanhoComprimido += (this->tamanhos[char_int] * frequencias[i]);
        }
    }
}

bool* Huffman::comprimir(char *letras, long *frequencias, string review_text) 
{
    this->salvarTamanhos(letras, frequencias);
    
    bool* stringComprimida = new bool[(int)this->tamanhoComprimido];

    int charAtual = 0;
    for(int i = 0; i < this->tamanhoOriginal; i++){
        int char_int = review_text[i] + METADE;
        for(int j = 0; j < this->tamanhos[char_int]; j++) {
            stringComprimida[charAtual] = this->codigos[char_int][j];
            charAtual++;
        }
    }

    return stringComprimida;
}

string Huffman::descomprimir(bool *comprimido) 
{
    No* noAtual = this->raiz;

    string descomprimido = "";

    for (int i = 0; i < ((int)this->tamanhoComprimido); i++) {
        
        if (noAtual->ehFolha()) 
        {
            descomprimido += noAtual->getInfo();
            noAtual = this->raiz;
        }
        if (comprimido[i])
        {
            noAtual = noAtual->getDireita();
        } else
        { 
            noAtual = noAtual->getEsquerda();
        }
    }
    
    return descomprimido + ' ';
}
