/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef NO_VP_H_INCLUDED
#define NO_VP_H_INCLUDED
#include <bits/stdc++.h>
#include "Dados_Arvore.h"
#include "Arvore_VP.h"

using namespace std;

enum Cor {RED, BLACK};

class No_VP
{
    string review_id;
    long long int localizacao;
    bool cor;
    No_VP *esquerda;
    No_VP *direita;
    No_VP *parente;

    // CONSTRUTOR

    No_VP(string review_id, long long int localizacao)
    {
       this->review_id = review_id;
       this->localizacao = localizacao;
       esquerda = direita = parente = NULL;
       this->cor = RED;
    }

    // DESTRUTOR

    ~No_VP()
    {
        // DESTRUTOR VAZIO
    }

    // GETS

    string getReviewId()
    {
        return this->review_id;
    }

    long long int getLocalizacao()
    {
        return this->localizacao;
    }

    bool getCor()
    {
        return this->cor;
    }

    No_VP* getEsquerda()
    {
        return this->esquerda;
    }

    No_VP* getDireita()
    {
        return this->direita;
    }

    No_VP *getParente()
    {
        return this->parente;
    }

    // SETS

    void setReviewId(string review_id)
    {
        this->review_id = review_id;
    }

    void setLocalizacao(long long int localizacao)
    {
        this->localizacao = localizacao;
    }

    void setCor(bool cor)
    {
        this->cor = cor;
    }

    void setEsquerda(No_VP *esquerda)
    {
        this->esquerda = esquerda;
    }

    void setDireita(No_VP *direita)
    {
        this->direita = direita;
    }

    void setParente(No_VP *parente)
    {
        this->parente = parente;
    }

    friend class Arvore_VP;
};
#endif // NO_VP_H_INCLUDED