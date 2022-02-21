/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef RECUPERAR_H_INCLUDED
#define RECUPERAR_H_INCLUDED

#include "Data.h"
#include <fstream>
#include <iostream>
#include <chrono>

typedef Data* DataPonteiro;

class Recuperar
{
    public:
        
        static void processamento(ifstream &arquivoCSV, ofstream &arquivoBIN, ofstream &arquivoPosicoes);
        static bool buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual);
        static void salvarString(ofstream &arquivoBIN, string valor);
        static string getString(ifstream &arquivoProcessado);
        static int getQuantidadeDados(ifstream &posicoes_salvas);
        static int getPosicaoDadosPeloId(ifstream &posicoes_salvas, int id);
        static Data* getDadosPeloId(ifstream &arquivoProcessado, ifstream &posicoes_salvas, int id);
        static DataPonteiro* getDadosAleatorios(ifstream &arquivoProcessado, ifstream &posicoes_salvas, int n);
        static DataPonteiro* getTodosDados(ifstream &arquivoProcessado, ifstream &posicoes_salvas);
        static int* getTodasPosicoes(ifstream &posicoes_salvas);
        static DataPonteiro* getDadosAleatoriosDoVetor(DataPonteiro *dados_review, int quantidade, int n);
        static DataPonteiro* getDadosAleatoriosDoVetorComPosicao(DataPonteiro *dados_review, int *posicoes, int *posicoesDados, int quantidade, int n);
};

#endif // RECUPERAR_H_INCLUDED
