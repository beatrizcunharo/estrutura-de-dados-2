/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "No.h"

// CONSTRUTOR

No::No(char info, int frequencia)
{
    this->info = info;
    this->frequencia = frequencia;
    this->esquerda = nullptr;
    this->direita = nullptr;
}

// DESTRUTOR
No::~No()
{
    // DESTRUTOR
}

// GETS

char No::getInfo()
{
    return this->info;
}

int No::getFrequencia()
{
    return this->frequencia;
}

No *No::getEsquerda()
{
    return this->esquerda;
}

No *No::getDireita()
{
    return this->direita;
}

// SETS

void No::setInfo(char info)
{
    this->info = info;
}

void No::setFrequencia(int frequencia)
{
    this->frequencia = frequencia;
}

void No::setEsquerda(No *esquerda)
{
    this->esquerda = esquerda;
}

void No::setDireita(No *direita)
{
    this->direita = direita;
}

// OUTRAS FUNÇÕES

bool No::ehFolha()
{
    return this->esquerda == nullptr && this->direita == nullptr;
}