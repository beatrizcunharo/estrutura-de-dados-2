/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "Heap.h"

Heap::Heap(long capacidade)
{
    this->capacidade = capacidade;
    this->tamanho = 0;
    this->raiz = nullptr;
    this->arrayNos = new No*[capacidade];
}

Heap::~Heap() 
{
    for(int i = 0; i < this->tamanho; i++) {
        if(this->arrayNos[i] != nullptr) {
            delete arrayNos[i];
        }
    }
    delete [] arrayNos;
}

long Heap::getTamanho() {
    return this->tamanho;
}

void Heap::setTamanho(long tamanho) {
    this->tamanho = tamanho;
}

long Heap::getCapacidade() {
    return this->capacidade;
}

void Heap::setCapacidade(long capacidade) {
    this->capacidade = capacidade;
}

No *Heap::getRaiz() {
    return this->raiz;
}

void Heap::setRaiz(No *raiz) {
    this->raiz = raiz;
}

No **Heap::getArrayNos() {
    return this->arrayNos;
}

void Heap::setArrayNos(No **arrayNos) {
    this->arrayNos = arrayNos;
}

void Heap::setNoArrayNos(No *no, int indice) {
    this->arrayNos[indice] = no;
}

void Heap::insertMinHeap(No* minHeapNode, int *comparacoes) {
   
    ++this->tamanho;
    int i = this->tamanho - 1;

    (*comparacoes) += 2;
    while (i && minHeapNode->getFrequencia() < this->arrayNos[(i - 1) / 2]->getFrequencia()) {
        (*comparacoes) += 2;
        this->arrayNos[i] = this->arrayNos[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->arrayNos[i] = minHeapNode;
}

No* Heap::extractMin(int *comparacoes) {
    No* temp = this->arrayNos[0];
    this->arrayNos[0] = this->arrayNos[this->tamanho - 1];

    --this->tamanho;
    minHeapify(0, comparacoes);

    return temp;
}

bool Heap::isSizeOne() {
    return (this->tamanho == 1);
}

void Heap::swapMinHeapNode(No** a, No** b) {
   
    No *t = *a;
    *a = *b;
    *b = t;
}

void Heap::minHeapify(int idx, int *comparacoes) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    (*comparacoes) += 2;
    if (left < this->tamanho && this->arrayNos[left]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = left;

    (*comparacoes) += 2;
    if (right < this->tamanho && this->arrayNos[right]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = right;

    (*comparacoes) += 1;
    if (smallest != idx) {
        
        swapMinHeapNode(&this->arrayNos[smallest], &this->arrayNos[idx]);
        
        minHeapify(smallest, comparacoes);
    }
}

void Heap::buildMinHeap(int *comparacoes) {
    int n = this->tamanho - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(i, comparacoes);
}