/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include "Data.h"
#include <fstream>
#include <iostream>
#include <chrono>

typedef Data* DataPonteiro;

class Arquivo
{
    public:
        
        static void processar(ifstream &arquivoCSV, ofstream &arquivoBIN, ofstream &arquivoPosicoes);
        
        static bool buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual);
        
        static void salvarString(ofstream &arquivoBIN, string valor);
        
        static string recuperarString(ifstream &arquivoProcessado);
        
        static int recuperarQuantidadeDados(ifstream &posicoes_salvas);
        
        static int recuperarPosicaoDadosPeloId(ifstream &posicoes_salvas, int id);
        
        static Data* recuperarDadosPeloId(ifstream &arquivoProcessado, ifstream &posicoes_salvas, int id);
        
        static DataPonteiro* recuperarDadosAleatorios(ifstream &arquivoProcessado, ifstream &posicoes_salvas, int n);
        
        static void desalocarVetorDados(DataPonteiro *dados_review, int n);
        
        static DataPonteiro* recuperarTodosDados(ifstream &arquivoProcessado, ifstream &posicoes_salvas);
        static int* recuperarTodasPosicoes(ifstream &posicoes_salvas);
        
        static DataPonteiro* recuperarDadosAleatoriosDoVetor(DataPonteiro *dados_review, int quantidade, int n);
        static DataPonteiro* recuperarDadosAleatoriosDoVetorComPosicao(DataPonteiro *dados_review, int *posicoes, int *posicoesDados, int quantidade, int n);
};

#endif // ARQUIVO_H_INCLUDED
