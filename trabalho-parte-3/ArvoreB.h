/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED
#include <iostream>
#include "NoB.h"

class ArvoreB
{
public:
    // CONSTRUTOR

    ArvoreB(int grau, int nfilhos);

    // DESTRUTOR

    ~ArvoreB();

    // GETS

    NoB *getRaiz();
    int getGrau();

    // SETS

    void setRaiz(NoB *raiz);
    void setGrau(int grau);

    // OUTRAS FUNÇÕES

    void percorreNos();
    NoB *buscaNo(string k, int *comparacoes_busca);
    void insereNoArvore(string k, int localizacao, int *comparacoes);

private:
    NoB *raiz;
    int grau;
    int nfilhos;
    void destrutorAux(NoB *no);
};

#endif // ARVOREB_H_INCLUDED