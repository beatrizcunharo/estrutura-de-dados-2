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

typedef Data* PonteiroData;

class Processamento 
{
    public:
        
        // GETS

        static string getString(ifstream &arquivoProcessado);
        static int getQuantidadeData(ifstream &posicoesSalvas);
        static int getPosicaoDataPeloReviewId(ifstream &posicoesSalvas, int id);
        static Data* getDataPeloReviewId(ifstream &arquivoProcessado, ifstream &posicoesSalvas, int id);
        static PonteiroData* getData(ifstream &arquivoProcessado, ifstream &posicoesSalvas, int n);
        static PonteiroData* getTodosOsDados(ifstream &arquivoProcessado, ifstream &posicoesSalvas);
        static int* getTodasAsPosicoes(ifstream &posicoesSalvas);
        static PonteiroData* getDadosAleatorios(PonteiroData *dados, int quantidade, int n);
        static PonteiroData* getDadosAleatoriosComPosicao(PonteiroData *dados, int *posicoes, int *posicoesDados, int quantidade, int n);

        // SETS

        static void setString(ofstream &arquivoBinario, string valor);

        // OUTRAS FUNÇÕES

        static void processamento(ifstream &arquivoCSV, ofstream &arquivoBinario, ofstream &arquivoPosicoes);
        static bool buscarColunas(string linha, string *colunas, bool &aspas, int &colunaAtual);    
        static void desalocarVetor(PonteiroData *dados, int n);
        
};

#endif // PROCESSAMENTO_H_INCLUDED
