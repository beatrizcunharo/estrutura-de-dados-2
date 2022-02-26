/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef PROCESSAMENTO_H_INCLUDED
#define PROCESSAMENTO_H_INCLUDED

#include "Data.h"
#include <fstream>
#include <iostream>
#include <chrono>

typedef Data *PonteiroData;

class Processamento
{
public:
    // GETS

    static string getString(ifstream &arquivoProcessado);
    static int getQuantidadeData(ifstream &posicoesSalvas);
    static int getPosicaoDataPeloId(ifstream &posicoesSalvas, int id);
    static Data *getDataPeloId(ifstream &arquivoProcessado, ifstream &posicoesSalvas, int id);
    static PonteiroData *getDadosAleatorios(ifstream &arquivoProcessado, ifstream &posicoesSalvas, int n);
    static PonteiroData *getTodosOsDados(ifstream &arquivoProcessado, ifstream &posicoesSalvas);
    static int *getTodasAsPosicoes(ifstream &posicoesSalvas);
    static PonteiroData *getDadosAleatoriosDoVetor(PonteiroData *data, int quantidade, int n);
    static PonteiroData *getDadosAleatoriosDoVetorComPosicao(PonteiroData *data, int *posicoes, int *posicoesData, int quantidade, int n);

    // SETS

    static void setString(ofstream &arquivoBinario, string valor);

    // OUTRAS FUNÇÕES

    static void processamento(ifstream &arquivo_csv, ofstream &arquivoBinario, ofstream &arquivoPosicoes);
    static bool buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual);
    static void desalocarVetor(PonteiroData *data, int n);
};

#endif // PROCESSAMENTO_H_INCLUDED
