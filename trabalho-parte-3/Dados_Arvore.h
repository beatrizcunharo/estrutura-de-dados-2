/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef DADOS_ARVORE_H_INCLUDED
#define DADOS_ARVORE_H_INCLUDED
#include <iostream>
#include "Arvore_B.h"

using namespace std;

class Dados_Arvore
{
    public:

        // CONSTRUTOR

        Dados_Arvore()
        {
            // CONSTRUTOR VAZIO
        };
   
        // DESTRUTOR
        
        ~Dados_Arvore()
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
#endif //DADOS_ARVORE_H_INCLUDED