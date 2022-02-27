/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "ArvoreVP.h"
#include <iostream>

using namespace std;

// CONSTRUTOR

ArvoreVP::ArvoreVP()
{
    this->raiz = nullptr;
}

// DESTRUTOR

ArvoreVP::~ArvoreVP()
{
    this->raiz = ArvoreVP::destrutorAux(this->raiz);
}

// GETS

NoVP *ArvoreVP::getRaiz()
{
    return this->raiz;
}

// SETS

void ArvoreVP::setRaiz(NoVP *raiz)
{
    this->raiz = raiz;
}

// OUTRAS FUNÇÕES

NoVP *ArvoreVP::destrutorAux(NoVP *no)
{
    if (no != nullptr)
    {
        no->setEsquerda(ArvoreVP::destrutorAux(no->getEsquerda()));
        no->setDireita(ArvoreVP::destrutorAux(no->getDireita()));
        delete no;
    }
    return nullptr;
}

NoVP *ArvoreVP::rotacionarEsquerda(NoVP *no)
{
    NoVP *no_dir = no->getDireita();
    no->setDireita(no_dir->getEsquerda());
    no_dir->setEsquerda(no);
    no_dir->setCor(no->isVermelho());
    no->setVermelho();

    return no_dir;
}

NoVP *ArvoreVP::rotacionarDireita(NoVP *no)
{
    NoVP *no_esq = no->getEsquerda();
    no->setEsquerda(no_esq->getDireita());
    no_esq->setDireita(no);
    no_esq->setCor(no->isVermelho());
    no->setVermelho();

    return no_esq;
}

void ArvoreVP::trocarCor(NoVP *no)
{
    no->trocarCor();
    if (no->getEsquerda() != nullptr)
    {
        no->getEsquerda()->trocarCor();
    }
    if (no->getDireita() != nullptr)
    {
        no->getDireita()->trocarCor();
    }
}

bool ArvoreVP::inserir(string review_id, int localizacao, int *comparacoes)
{
    bool resposta = false;

    NoVP *novo_no = new NoVP(review_id, localizacao);

    this->raiz = ArvoreVP::inserirAux(this->raiz, novo_no, &resposta, comparacoes);

    if (resposta)
    {
        this->raiz->setCor(false);
    }
    else
    {
        delete novo_no;
    }

    return resposta;
}

NoVP *ArvoreVP::inserirAux(NoVP *raiz, NoVP *novo_no, bool *resposta, int *comparacoes)
{
    (*comparacoes)++;
    if (raiz == nullptr)
    {
        (*resposta) = true;
        return novo_no;
    }
    (*comparacoes)++;
    if (novo_no->getReviewId() == raiz->getReviewId())
    {
        (*resposta) = false;
    }
    else
    {
        (*comparacoes)++;
        if (novo_no->getReviewId() < raiz->getReviewId())
        {
            raiz->setEsquerda(ArvoreVP::inserirAux(raiz->getEsquerda(), novo_no, resposta, comparacoes));
            raiz->getEsquerda()->setPai(raiz);
        }
        else
        {
            raiz->setDireita(ArvoreVP::inserirAux(raiz->getDireita(), novo_no, resposta, comparacoes));
            raiz->getDireita()->setPai(raiz);
        }
    }
    if (raiz->getDireita()->isVermelho() && raiz->getEsquerda()->isPreto())
    {
        raiz = ArvoreVP::rotacionarEsquerda(raiz);
    }
    if (raiz->getEsquerda()->isVermelho() && raiz->getEsquerda()->getEsquerda()->isVermelho())
    {
        raiz = ArvoreVP::rotacionarDireita(raiz);
    }
    if (raiz->getEsquerda()->isVermelho() && raiz->getDireita()->isVermelho())
    {
        ArvoreVP::trocarCor(raiz);
    }

    return raiz;
}

NoVP *ArvoreVP::buscar(string review_id, int *comparacoes)
{
    if (this->raiz != nullptr)
    {
        NoVP *no = ArvoreVP::buscarAux(this->raiz, review_id, comparacoes);
        if (no != nullptr)
        {
            return no;
        }
        else
        {
            cout << "Erro: review_id não encontrado." << endl;
            return nullptr;
        }
    }
    else
    {
        cout << "Erro: Arvore Vazia!" << endl;
        return nullptr;
    }
}

NoVP *ArvoreVP::buscarAux(NoVP *no, string review_id, int *comparacoes)
{
    if (no != nullptr)
    {
        (*comparacoes)++;
        if (review_id == no->getReviewId())
        {
            return no;
        }
        (*comparacoes)++;
        if (review_id > no->getReviewId())
        {
            return ArvoreVP::buscarAux(no->getDireita(), review_id, comparacoes);
        }
        return ArvoreVP::buscarAux(no->getEsquerda(), review_id, comparacoes);
    }
    else
    {
        return nullptr;
    }
}