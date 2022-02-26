/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "Heap.h"

// CONSTRUTOR

Heap::Heap(long capacidade) {
    this->capacidade = capacidade;
    this->tamanho = 0;
    this->raiz = nullptr;
    this->arrayNos = new No*[capacidade];
}

// DESTRUTOR

Heap::~Heap() {
    for(int i = 0; i < this->tamanho; i++) {
        if(this->arrayNos[i] != nullptr) {
            delete arrayNos[i];
        }
    }
    delete [] arrayNos;
}

// GETS

long Heap::getTamanho()
{
    return this->tamanho;
}

long Heap::getCapacidade() 
{
    return this->capacidade;
}

No *Heap::getRaiz()
{
    return this->raiz;
}

No **Heap::getArrayNos()
{
    return this->arrayNos;
}

// SETS

void Heap::setTamanho(long tamanho) 
{
    this->tamanho = tamanho;
}

void Heap::setCapacidade(long capacidade) {
    this->capacidade = capacidade;
}

void Heap::setRaiz(No *raiz) {
    this->raiz = raiz;
}

void Heap::setArrayNos(No **arrayNos) {
    this->arrayNos = arrayNos;
}

void Heap::setNoArrayNos(No *no, int indice) {
    this->arrayNos[indice] = no;
}

// OUTRAS FUNÇÕES

void Heap::insereHeapMinima(No* noHeapMinima, int *comparacoes) 
{
    ++this->tamanho;
    int i = this->tamanho - 1;

    (*comparacoes) += 2;
    while (i && noHeapMinima->getFrequencia() < this->arrayNos[(i - 1) / 2]->getFrequencia()) {
        (*comparacoes) += 2;
        this->arrayNos[i] = this->arrayNos[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->arrayNos[i] = noHeapMinima;
}

No* Heap::recuperaHeapMinima(int *comparacoes) 
{
    No* temp = this->arrayNos[0];
    this->arrayNos[0] = this->arrayNos[this->tamanho - 1];

    --this->tamanho;
    heapifyMinima(0, comparacoes);

    return temp;
}

bool Heap::ehRaiz() 
{
    if(this->tamanho == 1)
        return true;
    return false;
}

void Heap::troca(No** a, No** b) 
{
    No *t = *a;
    *a = *b;
    *b = t;
}

void Heap::heapifyMinima(int indice, int *comparacoes) {
    int menor = indice;
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;

    (*comparacoes) += 2;
    if (esquerda < this->tamanho && this->arrayNos[esquerda]->getFrequencia() < this->arrayNos[menor]->getFrequencia())
        menor = esquerda;

    (*comparacoes) += 2;
    if (direita < this->tamanho && this->arrayNos[direita]->getFrequencia() < this->arrayNos[menor]->getFrequencia())
        menor = direita;

    (*comparacoes) += 1;
    if (menor != indice) {
        troca(&this->arrayNos[menor], &this->arrayNos[indice]);
        heapifyMinima(menor, comparacoes);
    }
}

void Heap::constroiHeapMinima(int *comparacoes) {
    int n = this->tamanho - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        heapifyMinima(i, comparacoes);
}