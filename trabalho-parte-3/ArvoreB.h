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

using namespace std;

class ArvoreB
{
    public:

        // CONSTRUTOR

        ArvoreB(int grau_minimo, int nos)
        {
            this->raiz = nullptr;
            this->grau_minimo = grau_minimo;
            this->nos = nos;
        }

        ArvoreB();

        // DESTRUTOR

        ~ArvoreB();

        // GETS

        NoB* getRaiz()
        {
            return this->raiz;
        }

        int getGrauMinimo()
        {
            return this->grau_minimo;
        }

        // SETS

        void setRaiz(NoB *raiz)
        {
            this->raiz = raiz;
        }

        void setGrauMinimo(int grau_minimo)
        {
            this->grau_minimo = grau_minimo;
        }

        // OUTRAS FUNÇÕES

        void percorreNo()
        {
            if (raiz != NULL)
                raiz->percorreNo();
        }

        NoB* buscar(string review_id)
        {
            if(raiz == nullptr)
                return nullptr;
            else 
                return raiz->procura(review_id);
        }

        void insere(string review_id, long localizacao)
        {
            Dados_Arvore *dados = new Dados_Arvore();

            dados->setReview_Id(review_id);
            dados->setLocalizacao(localizacao);

            if (raiz == nullptr)
                {

                    raiz = new NoB(grau_minimo, true, nos);
                    raiz->chaves[0] = dados;
                    raiz->n = 1;
                }
                else
                {
                    if (raiz->n == 2 * grau_minimo - 1)
                    {
                        NoB *novoNo = new NoB(grau_minimo, false, nos);

                        novoNo->filhos[0] = raiz;

                        novoNo->divideFilho(0, raiz);

                        int i = 0;
                        if (novoNo->chaves[0]->getReview_Id() < review_id)
                        {
                            i++;
                        }
                        novoNo->filhos[i]->insereEspacado(review_id, localizacao);

                        raiz = novoNo;
                    }
                    else
                    {
                        raiz->insereEspacado(review_id, localizacao);
                    }
                }
        }

    private:

        NoB* raiz;
        int grau_minimo;
        int nos;
};
#endif // ARVOREB_H_INCLUDED