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

using namespace std;

class Dados_Arvore
{
    public:

        // CONSTRUTOR
        Dados_Arvore()
        {
            // CONSTRUTOR VAZIO
        }

        Dados_Arvore(string review_id, double localizacao)
        {
            this->review_id = review_id;
            this->localizacao = localizacao;
        }

        // DESTRUTOR
        ~Dados_Arvore()
        {
            // DESTRUTOR VAZIO
        }

        // GETS

        string getReview_Id()
        {
            return this->review_id;
        }

        double getLocalizacao()
        {
            return this->localizacao;
        }

        // SETS

        void setReview_Id(string review_id)
        {
            this->review_id = review_id;
        }

        void setLocalizacao(long localizacao)
        {
            this->localizacao = localizacao;
        }

    private:

        string review_id;
        long localizacao;
};
#endif // DADOS_ARVORE_H_INCLUDED