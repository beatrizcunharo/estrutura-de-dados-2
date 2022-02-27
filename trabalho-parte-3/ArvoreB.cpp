/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "ArvoreB.h"
#include "NoB.h"
#include <iostream>

using namespace std;

// CONSTRUTOR

ArvoreB::ArvoreB(int grau, int nfilhos)
{
    this->raiz = nullptr;
    this->grau = grau;
    this->nfilhos = nfilhos;
}

// DESTRUTOR

ArvoreB::~ArvoreB()
{
    ArvoreB::destrutorAux(this->raiz);
    delete this->raiz;
}

// GETS

NoB *ArvoreB::getRaiz()
{
    return this->raiz;
}

int ArvoreB::getGrau()
{
    return this->grau;
}

// SETS

void ArvoreB::setGrau(int grau)
{
    this->grau = grau;
}

void ArvoreB::setRaiz(NoB *raiz)
{
    this->raiz = raiz;
}

// OUTRAS FUNÇÕES

void ArvoreB::destrutorAux(NoB *no)
{
    if (no != nullptr)
    {
        if (!no->isFolha())
        {
            for (int i = 0; i < no->getN(); i++)
            {
                destrutorAux(no->filhos[i]);
                delete no->filhos[i];
            }
        }
    }
}

void ArvoreB::percorreNos()
{
    if (raiz != nullptr)
        raiz->percorreNos();
}

NoB *ArvoreB::buscaNo(string indice, int *comparacoes)
{

    if (this->raiz == nullptr)
        return nullptr;
    else
        return this->raiz->buscaNo(indice, comparacoes);
}

void ArvoreB::insereNoArvore(string k, int localizacao, int *comparacoes)
{
    if (raiz == nullptr)
    {
        raiz = new NoB(this->grau, true, nfilhos);
        raiz->chaves[0].review_id = k;
        raiz->chaves[0].localizacao = localizacao;
        raiz->n = 1;
    }
    else
    {
        if (raiz->getN() == nfilhos)
        {
            NoB *s = new NoB(grau, false, nfilhos);
            s->filhos[0] = raiz;
            s->particionaNoFilho(0, raiz);
            int i = 0;
            if (s->chaves[0].review_id < k)
            {
                (*comparacoes)++;
                i++;
            }
            s->filhos[i]->insereNoComEspaco(k, localizacao, comparacoes);
            raiz = s;
        }
        else
        {
            raiz->insereNoComEspaco(k, localizacao, comparacoes);
        }
    }
}
