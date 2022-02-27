/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef ARVOREVP_H_INCLUDED
#define ARVOREVP_H_INCLUDED

#include "NoVP.h"

class ArvoreVP
{

public:
    // CONSTRUTOR

    ArvoreVP();

    // DESTRUTOR

    ~ArvoreVP();

    // GETS

    NoVP *getRaiz();

    // SETS

    void setRaiz(NoVP *raiz);

    // OUTRAS FUNÇÕES

    bool inserir(string review_id, int localizacao, int *comparacoes);
    NoVP *buscar(string review_id, int *comparacoes);

private:
    NoVP *raiz;
    NoVP *rotacionarEsquerda(NoVP *no);
    NoVP *rotacionarDireita(NoVP *no);
    NoVP *inserirAux(NoVP *raiz, NoVP *novo_no, bool *resposta, int *comparacoes);
    NoVP *buscarAux(NoVP *no, string id, int *comparacoes);
    NoVP *destrutorAux(NoVP *no);
    void trocarCor(NoVP *no);
};

#endif // ARVOREVP_H_INCLUDED
