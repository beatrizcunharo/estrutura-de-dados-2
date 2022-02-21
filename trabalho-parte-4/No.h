/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include <iostream>

using namespace std;

class No 
{

    public:

        // CONSTRUTOR

        No(char dado, int frequencia);

        // DESTRUTOR

        ~No();

        // GETS E SETS

        char getDado();
        void setDado(char dado);
        int getFrequencia();
        void setFrequencia(int frequencia);
        No *getEsquerda();
        void setEsquerda(No *esquerda);
        No *getDireita();
        void setDireita(No *direita);

        // OUTRAS FUNÇÕES
        
        bool ehFolha();

    private:
    
        char dado;
        int frequencia;
        No *esquerda;
        No *direita;
};

#endif //NO_H_INCLUDED
