/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include <iostream>
#include "NoB.h"

using namespace std;

// CONSTRUTOR

NoB::NoB(int grau, bool folha, int nfilhos)
{
    this->grau = grau;
    this->folha = folha;
    this->chaves = new InfoB[nfilhos];
    this->filhos = new NoB *[nfilhos + 1];
    this->n = 0;
    this->nfilhos = nfilhos;
}

// DESTRUTOR

NoB::~NoB()
{
    delete[] this->chaves;
    delete[] this->filhos;
}

// GETS

InfoB *NoB::getChaves()
{
    return this->chaves;
}

NoB **NoB::getFilhos()
{
    return this->filhos;
}

int NoB::getGrau()
{
    return this->grau;
}

int NoB::getN()
{
    return this->n;
}

int NoB::getNfilhos()
{
    return this->nfilhos;
}

// SETS

void NoB::setFolha(bool folha)
{
    this->folha = folha;
}

void NoB::setFilhos(NoB **filhos)
{
    this->filhos = filhos;
}

void NoB::setNfilhos(int nfilhos)
{
    this->nfilhos = nfilhos;
}

void NoB::setChaves(InfoB *chaves)
{
    this->chaves = chaves;
}

void NoB::setGrau(int grau)
{
    this->grau = grau;
}

void NoB::setN(int n)
{
    this->n = n;
}

// OUTRAS FUNÇÕES

void NoB::percorreNos()
{

    int i;
    for (i = 0; i < n; i++)
    {

        if (!folha)
        {
            filhos[i]->percorreNos();
        }
        cout << " " << chaves[i].review_id;
    }

    if (!folha)
        filhos[i]->percorreNos();
}

NoB *NoB::buscaNo(string k, int *comparacoes)
{

    int i = 0;
    while (i < n && k > chaves[i].review_id)
    {
        (*comparacoes)++;
        i++;
    }

    if (chaves[i].review_id == k)
    {
        (*comparacoes)++;
        return this;
    }

    if (folha)
        return nullptr;

    return filhos[i]->buscaNo(k, comparacoes);
}

void NoB::insereNoComEspaco(string k, int localizacao, int *comparacoes)
{
    int i = n - 1;
    if (folha)
    {

        while (i >= 0 && chaves[i].review_id > k)
        {
            (*comparacoes)++;
            chaves[i + 1] = chaves[i];
            i--;
        }
        chaves[i + 1].review_id = k;
        chaves[i + 1].localizacao = localizacao;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && chaves[i].review_id > k)
        {
            (*comparacoes)++;
            i--;
        }

        if (filhos[i + 1]->getN() == nfilhos)
        {
            (*comparacoes)++;
            particionaNoFilho(i + 1, filhos[i + 1]);

            if (chaves[i + 1].review_id < k)
                (*comparacoes)++;
            i++;
        }
        filhos[i + 1]->insereNoComEspaco(k, localizacao, comparacoes);
    }
}

void NoB::particionaNoFilho(int i, NoB *y)
{

    NoB *z = new NoB(y->grau, y->folha, y->nfilhos);
    z->n = grau - 1;
    for (int j = 0; j < grau - 1; j++)
        z->chaves[j] = y->chaves[j + grau];
    if (!y->folha)
    {
        for (int j = 0; j < grau; j++)
            z->filhos[j] = y->filhos[j + grau];
    }
    y->n = grau - 1;

    for (int j = n; j >= i + 1; j--)
    {
        filhos[j + 1] = filhos[j];
    }

    filhos[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        chaves[j + 1] = chaves[j];

    chaves[i] = y->chaves[grau - 1];

    n = n + 1;
}

bool NoB::isFolha()
{
    return this->folha;
}
