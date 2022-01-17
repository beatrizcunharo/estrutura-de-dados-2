/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef ARVORE_B_H_INCLUDED
#define ARVORE_B_H_INCLUDED

#include <string.h>
#include <iostream>
#include "Dados_B.h"
#include "No_B.h"

using namespace std;


class Arvore_B
{

    public:

        // CONSTRUTOR
        Arvore_B(int t)
        {
            no = NULL;
            grau_minimo = t;
        }

        // DESTRUTOR
        ~Arvore_B()
        {
            delete no;
        }

        void inserir(Dados_B dados)
        {
            if (no == NULL)
            {
                no = new No_B(grau_minimo, true);
                no->chaves[0] = dados;
                no->nos = 1;
            }
            else
            {
                if (no->nos == 2 * grau_minimo - 1)
                {
                    No_B *noArvore = new No_B(grau_minimo, false);
                    noArvore->filhos[0] = no;

                    noArvore->divideFilho(0, no);
                    
                    int i = 0;
                    if (noArvore->chaves[0].getReviewId() < dados.getReviewId()){
                        i++;
                    }

                    noArvore->filhos[i]->inserirNaoCheio(dados);

                    no = noArvore;
                }
                else
                {
                    no->inserirNaoCheio(dados);
                }
            }
        }

        No_B *busca(string review_id)
        {
            return (no == NULL) ? NULL : no->busca(review_id);
        }

    private:
        No_B *no;
        int grau_minimo;
};

#endif // ARVORE_B_H_INCLUDED