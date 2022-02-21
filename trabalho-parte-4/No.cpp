/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "No.h"

No::No(char dado, int frequencia) {
    this->dado = dado;
    this->frequencia = frequencia;
    this->esquerda = nullptr;
    this->direita = nullptr;
}

No::~No()
{
    // DESTRUTOR VAZIO
}

char No::getDado() {
    return this->dado;
}

void No::setDado(char dado) {
    this->dado = dado;
}

int No::getFrequencia() {
    return this->frequencia;
}

void No::setFrequencia(int frequencia) {
    this->frequencia = frequencia;
}

No *No::getEsquerda() {
    return this->esquerda;
}

void No::setEsquerda(No *esquerda) {
    this->esquerda = esquerda;
}

No *No::getDireita() {
    return this->direita;
}

void No::setDireita(No *direita) {
    this->direita = direita;
}

bool No::ehFolha() {
    return this->esquerda == nullptr && this->direita == nullptr;
}