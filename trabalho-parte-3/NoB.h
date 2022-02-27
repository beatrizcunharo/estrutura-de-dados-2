/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef NOB_H_INCLUDED
#define NOB_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

struct InfoB
{
    string review_id;
    int localizacao;
};

class NoB
{

public:
    // CONSTRUTOR

    NoB(int grau, bool folha, int nfilhos);

    // DESTRUTOR

    ~NoB();

    // GETS

    InfoB *getChaves();
    int getGrau();
    int getN();
    NoB **getFilhos();
    int getNfilhos();

    // SETS

    void setChaves(InfoB *chaves);
    void setGrau(int grau);
    void setN(int n);
    void setNfilhos(int nfilhos);
    void setFolha(bool folha);
    void setFilhos(NoB **filhos);

    // OUTRAS FUNÇÕES

    bool isFolha();
    void insereNoComEspaco(string k, int localizacao, int *comparacoes);
    void particionaNoFilho(int i, NoB *y);
    void percorreNos();
    NoB *buscaNo(string k, int *comparacoes);

    friend class ArvoreB;

private:
    InfoB *chaves;
    int grau;
    int n;
    bool folha;
    NoB **filhos;
    int nfilhos;
};

#endif // NOB_H_INCLUDED