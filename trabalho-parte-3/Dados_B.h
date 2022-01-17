/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef DADOS_B_H_INCLUDED
#define DADOS_B_H_INCLUDED
#include <iostream>
#include "Arvore_B.h"

using namespace std;

class Dados_B
{
    public:

        // CONSTRUTOR
        Dados_B()
        {
            // CONSTRUTOR VAZIO
        };
   
        // DESTRUTOR
        ~Dados_B()
        {
            // DESTRUTOR VAZIO
        };


        // GETS

        string getReviewId()
        {
            return review_id;
        };

        int getLocalizacao()
        {
            return localizacao;
        }

        // SETS

        void setReviewId(string review_id)
        {
            this->review_id = review_id;
        };

        void setLocalizacao(long long int localizacao)
        {
            this->localizacao = localizacao;
        }

    private:
        string review_id;
        long long int localizacao;
};
#endif //DADOS_B_H_INCLUDED