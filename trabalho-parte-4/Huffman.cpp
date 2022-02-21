/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "Huffman.h"

Huffman::Huffman(long tamanhoOriginal) {
    this->codigosHuffman = new bool*[TAMANHO_MAXIMO];
    this->tamanhosHuffman = new int[TAMANHO_MAXIMO];
    this->tamanhoComprimido = 0;
    this->tamanhoOriginal = tamanhoOriginal;
    this->raiz = nullptr;
    this->minHeap = nullptr;
}

Huffman::~Huffman() {
    delete this->minHeap;
}

Heap* Huffman::criarHeapMinima(char *dados, long *frequencia, long tamanho, int *comparacoes) {
    
    Heap *minHeap = new Heap(tamanho);

    for (int i = 0; i < tamanho; ++i) {
        minHeap->setNoArrayNos(new No(dados[i], frequencia[i]), i);
    }

    minHeap->setTamanho(tamanho);

    minHeap->constroiHeap(comparacoes);

    return minHeap;
} 

No* Huffman::construirHuffmanArvore(char *dados, long *frequencia, long tamanho, int *comparacoes) {
    
    No *esquerda, *direita, *topo;

    Heap *minHeap = criarHeapMinima(dados, frequencia, tamanho, comparacoes);
    
    this->minHeap = minHeap;

    while (!minHeap->eRaiz()) {

        esquerda = minHeap->puxarMinima(comparacoes);
        direita = minHeap->puxarMinima(comparacoes);

        topo = new No('$', esquerda->getFrequencia() + direita->getFrequencia());

        topo->setEsquerda(esquerda);
        topo->setDireita(direita);

        minHeap->inserirHeapMinima(topo, comparacoes);
    }

    return minHeap->puxarMinima(comparacoes);
}

void Huffman::codificar(char *dados, long *frequencia, long tamanho, int *comparacoes) {
    
    No *root = construirHuffmanArvore(dados, frequencia, tamanho, comparacoes);
    this->raiz = root;

    int arr[this->minHeap->getCapacidade()], top = 0;

    salvarCodigos(root, arr, top);

}

void Huffman::salvarCodigos(No* root, int arr[], int top) {
    if (root->getEsquerda()) {
        arr[top] = 0;
        salvarCodigos(root->getEsquerda(), arr, top + 1);
    }
    if (root->getDireita()) {
        arr[top] = 1;
        salvarCodigos(root->getDireita(), arr, top + 1);
    }
    if (root->ehFolha()) {
        int char_int = root->getDado() + METADE_MAXIMO;
        this->codigosHuffman[char_int] = new bool[top];
        this->tamanhosHuffman[char_int] = top;
        this->salvarArray(arr, top, this->codigosHuffman[char_int]);
    }
}

void Huffman::imprimirCodificado(No* root, int arr[], int top) {

    if (root->getEsquerda()) {
        arr[top] = 0;
        imprimirCodificado(root->getEsquerda(), arr, top + 1);
    }

    if (root->getDireita()) {
        arr[top] = 1;
        imprimirCodificado(root->getDireita(), arr, top + 1);
    }

    if (root->ehFolha()) {
        cout<< root->getDado() << ": ";
        imprimirArray(arr, top);
    }
}

void Huffman::salvarArray(int *arr, int n, bool* codigo) {

    for (int i = 0; i < n; ++i)
        codigo[i] = arr[i];
}

void Huffman::imprimirArray(int *arr, int n) {

    for (int i = 0; i < n; ++i)
        cout<< arr[i] << endl;;

}

void Huffman::salvarTamanhos(char *letras, long *frequencias) {
    this->tamanhoComprimido = 1;
    for(int i = 0; i < minHeap->getCapacidade(); i++) {
        if(frequencias[i] > 0) {
            int char_int = letras[i] + METADE_MAXIMO;
            this->tamanhoComprimido += (this->tamanhosHuffman[char_int] * frequencias[i]);
        }
    }
}

bool* Huffman::comprimirHuffman(char *letras, long *frequencias, string review_text) {
    this->salvarTamanhos(letras, frequencias);
    
    bool* stringComprimida = new bool[(int)this->tamanhoComprimido];

    int charAtual = 0;

    for(int i = 0; i < this->tamanhoOriginal; i++){
        int char_int = review_text[i] + METADE_MAXIMO;
        for(int j = 0; j < this->tamanhosHuffman[char_int]; j++) {
            stringComprimida[charAtual] = this->codigosHuffman[char_int][j];
            charAtual++;
        }
    }

    return stringComprimida;
}

double Huffman::getTamanhoComprimido() {
    return this->tamanhoComprimido;
}

string Huffman::descomprimirHuffman(bool *comprimido) {
   
    No* noAtual = this->raiz;

    string descomprimido = "";

    for (int i = 0; i < ((int)this->tamanhoComprimido); i++) {
        
        if (noAtual->ehFolha()) {
            descomprimido += noAtual->getDado();
            noAtual = this->raiz;
        }

        if (comprimido[i]){
            noAtual = noAtual->getDireita();
        } else{ 
            noAtual = noAtual->getEsquerda();
        }
    }

    return descomprimido + ' ';
}
