/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED

#include <string>

using namespace std;

class NoVP
{
public:
    // CONSTRUTOR

    NoVP(string review_id, int localizacao);

    // DESTRUTOR

    ~NoVP();

    // GETS

    string getReviewId();
    int getLocalizacao();
    NoVP *getPai();
    NoVP *getEsquerda();
    NoVP *getDireita();

    // SETS

    void setReviewId(string id);
    void setLocalizacao(int localizacao);
    void setVermelho();
    void setPreto();
    void setCor(bool cor);
    void setPai(NoVP *pai);
    void setEsquerda(NoVP *esquerdo);
    void setDireita(NoVP *direito);

    // OUTRAS FUNÇÕES

    bool isVermelho();
    bool isPreto();
    void trocarCor();

private:
    string review_id;
    int localizacao;
    bool cor;
    NoVP *pai;
    NoVP *esquerda;
    NoVP *direita;
};

#endif // NOVP_H_INCLUDED
