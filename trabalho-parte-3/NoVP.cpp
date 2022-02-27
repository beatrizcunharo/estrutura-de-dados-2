/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "NoVP.h"

// CONSTRUTOR

NoVP::NoVP(string review_id, int localizacao)
{
    this->review_id = review_id;
    this->localizacao = localizacao;
    this->cor = true;
    this->pai = nullptr;
    this->esquerda = nullptr;
    this->direita = nullptr;
}

// DESTRUTOR

NoVP::~NoVP()
{
    this->review_id.clear();
}

// GETS

string NoVP::getReviewId()
{
    return this->review_id;
}

int NoVP::getLocalizacao()
{
    return this->localizacao;
}

NoVP *NoVP::getPai()
{
    return this->pai;
}

NoVP *NoVP::getEsquerda()
{
    return this->esquerda;
}

NoVP *NoVP::getDireita()
{
    return this->direita;
}

// SETS

void NoVP::setReviewId(string review_id)
{
    this->review_id = review_id;
}

void NoVP::setLocalizacao(int localizacao)
{
    this->localizacao = localizacao;
}

void NoVP::setVermelho()
{
    this->cor = true;
}

void NoVP::setPreto()
{
    this->cor = false;
}

void NoVP::setCor(bool cor)
{
    this->cor = cor;
}

void NoVP::setPai(NoVP *pai)
{
    this->pai = pai;
}

void NoVP::setEsquerda(NoVP *esquerda)
{
    this->esquerda = esquerda;
}

void NoVP::setDireita(NoVP *direita)
{
    this->direita = direita;
}

// OUTRAS FUNÇÕES

bool NoVP::isVermelho()
{
    return this != nullptr && this->cor;
}

bool NoVP::isPreto()
{
    if (this == nullptr)
        return true;
    return !this->cor;
}

void NoVP::trocarCor()
{
    this->cor = !this->isVermelho();
}