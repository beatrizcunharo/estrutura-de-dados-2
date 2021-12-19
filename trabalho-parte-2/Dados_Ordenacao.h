/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/
#ifndef DADOS_ORDENACAO_H_INCLUDED
#define DADOS_ORDENACAO_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Dados_Ordenacao {

    public:
        
        // CONSTRUTOR
        Dados_Ordenacao()
        {
            total_comparacoes = 0;
            total_movimentacoes = 0;
        }

        // DESTRUTOR
        ~Dados_Ordenacao()
        {
            total_comparacoes = 0;
            total_movimentacoes = 0;
        }

        // GETS

        int getTotalComparacoes()
        {
            return this->total_comparacoes;
        }

        int getTotalMovimentacoes()
        {
            return this->total_movimentacoes;
        }

        // SETS

        void setTotalComparacoes(int total_comparacoes)
        {
            this->total_comparacoes = total_comparacoes;
        }

        void setTotalMovimentacoes(int total_movimentacoes)
        {
            this->total_movimentacoes = total_movimentacoes;
        }

        // OUTRAS FUNÇÕES

        void incrementaComparacoes()
        {
            this->total_comparacoes++;
        }

        void incrementaMovimentacoes()
        {
            this->total_movimentacoes++;
        }

        void clear()
        {
            total_comparacoes = 0;
            total_movimentacoes = 0;
        }

    private:

        int total_comparacoes;
        int total_movimentacoes;

};
#endif //DADOS_ORDENACAO_H_INCLUDED