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

        No(char info, int frequencia);
        
        // DESTRUTOR

        ~No();
        
        // GETS

        char getInfo();
        int getFrequencia();
        No *getEsquerda();
        No *getDireita();

        // SETS

        void setInfo(char info);
        void setFrequencia(int frequencia);
        void setEsquerda(No *esquerda);
        void setDireita(No *direita);
    
        // OUTRAS FUNCOES

        bool ehFolha();

    private:

        char info;
        int frequencia;
        No *esquerda;
        No *direita;
};

#endif // NO_H_INCLUDED
