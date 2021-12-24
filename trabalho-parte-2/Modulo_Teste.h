/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/
#ifndef MODULO_TESTE_H_INCLUDED
#define MODULO_TESTE_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

#include "Data.h"
#include "Processamento.h"

using namespace std;
using namespace std::chrono;

class Modulo_Teste
{
    public:

    // CONSTRUTOR
    Modulo_Teste(){}

    // DESTRUTOR
    ~Modulo_Teste(){}

    // FUNÇÃO PARA INÍCIO AO MÓDULO DE TESTE
    void moduloTesteOrdenacao(ofstream& saidaTeste, char *argv[], int execucoes)
    {
        Processamento processamento;

        // VETOR DE DADOS

        vector<Data> dados;

        // VETOR DE DADOS AUXILIAR

        vector<Data> dadosAux;

        // ORDENAÇÃO

        int auxExecucoes = 0, indiceLeitura = 0;
        long total_comparacoes_quicksort = 0, total_comparacoes_heapsort = 0, total_comparacoes_combsort = 0, 
        total_movimentacoes_quicksort = 0, total_movimentacoes_heapsort = 0, total_movimentacoes_combsort = 0, 
        media_comparacoes_quicksort = 0, media_comparacoes_heapsort = 0, media_comparacoes_combsort = 0,
        media_movimentacoes_quicksort = 0, media_movimentacoes_heapsort = 0, media_movimentacoes_combsort = 0;
        double total_tempo_quicksort = 0, total_tempo_heapsort = 0, total_tempo_combsort = 0, tempo = 0, 
        media_tempo_quicksort = 0, media_tempo_heapsort = 0, media_tempo_combsort = 0, inicio, fim;

        fstream arquivoEntrada(argv[1], ios::in | ios::binary);

        Dados_Ordenacao ordenacao;

        while(auxExecucoes < execucoes)
        {
            Data data;

            cout << "EXECUCAO: " << auxExecucoes+1 << endl;
            saidaTeste << "EXECUCAO: " << auxExecucoes+1 << endl;
            saidaTeste << endl;

            // LEITURA DO ARQUIVO .BIN

            indiceLeitura = 1+rand()%3660628;

            cout << "Importando dados..." << endl;

            for(int i=0; i< 100; i++)
            {
                data = processamento.leituraBinIndividual(indiceLeitura, arquivoEntrada);
                dados.push_back(data);
                indiceLeitura = 1+rand()%3660628;
            }
            cout << "Dados importados" << endl;

            // UTILIZANDO VETOR AUXILIAR

            for(int i=0; i<100; i++)
            {
                dadosAux.push_back(dados.at(i));
            }

            // ORDENAÇÃO QUICKSORT -------------------------------------------

            cout << "Iniciando ordenacao quicksort..." << endl;
            saidaTeste << "Quicksort: " << endl;

            inicio = inicio = double(clock()) / CLOCKS_PER_SEC;

            ordenacao.clear();

            processamento.quickSort(&dadosAux, 0, dadosAux.size(), &ordenacao);
            total_comparacoes_quicksort += ordenacao.getTotalComparacoes();
            total_movimentacoes_quicksort += ordenacao.getTotalMovimentacoes();
            fim = double(clock()) / CLOCKS_PER_SEC;

            tempo = fim - inicio;

            total_tempo_quicksort += tempo;

            saidaTeste << "Total de comparacoes: " << ordenacao.getTotalComparacoes() << ", total de movimentacoes: " << ordenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   

            cout << "Ordenacao quicksort finalizada..." << endl;

            dadosAux.clear();

            // ORDENAÇÃO HEAPSORT --------------------------------------------

            for(int i=0; i<100; i++)
            {
                dadosAux.push_back(dados.at(i));
            }

            cout << "Iniciando ordenacao heapsort..." << endl;
            saidaTeste << "Heapsort: " << endl;

            inicio = double(clock()) / CLOCKS_PER_SEC;

            ordenacao.clear();

            processamento.heapSort(&dadosAux, dadosAux.size(), &ordenacao);
            total_comparacoes_heapsort += ordenacao.getTotalComparacoes();
            total_movimentacoes_heapsort += ordenacao.getTotalMovimentacoes();
            fim = double(clock()) / CLOCKS_PER_SEC;

            tempo = fim - inicio;

            total_tempo_heapsort += tempo;

            saidaTeste << "Total de comparacoes: " << ordenacao.getTotalComparacoes() << ", total de movimentacoes: " << ordenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   

            cout << "Ordenacao finalizada..." << endl;

            dadosAux.clear();

            // ORDENAÇÃO COMBSORT ----------------------------------------------

            for(int i=0; i<100; i++)
            {
                dadosAux.push_back(dados.at(i));
            }

            cout << "Iniciando ordenacao combsort..." << endl;
            saidaTeste << "Combsort: " << endl;

            inicio = double(clock()) / CLOCKS_PER_SEC;

            ordenacao.clear();

            processamento.combSort(&dadosAux, dadosAux.size(), &ordenacao);
            total_comparacoes_combsort += ordenacao.getTotalComparacoes();
            total_movimentacoes_combsort += ordenacao.getTotalMovimentacoes();
            fim = double(clock()) / CLOCKS_PER_SEC;

            tempo = fim - inicio;

            total_tempo_combsort += tempo;

            saidaTeste << "Total de comparacoes: " << ordenacao.getTotalComparacoes() << ", total de movimentacoes: " << ordenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   

            cout << "Ordenacao finalizada..." << endl;

            dadosAux.clear();

            // ------------------------------------------------------

            indiceLeitura = 0;
            dados.clear();
            auxExecucoes++;

            saidaTeste << endl;
        }
            media_comparacoes_quicksort = total_comparacoes_quicksort / execucoes;
            media_comparacoes_heapsort = total_comparacoes_heapsort / execucoes;
            media_comparacoes_combsort = total_comparacoes_combsort / execucoes;

            media_movimentacoes_quicksort = total_movimentacoes_quicksort / execucoes;
            media_movimentacoes_heapsort = total_movimentacoes_heapsort / execucoes;
            media_movimentacoes_combsort = total_movimentacoes_combsort / execucoes;

            media_tempo_quicksort = total_tempo_quicksort / execucoes;
            media_tempo_heapsort = total_tempo_heapsort / execucoes;
            media_tempo_combsort = total_tempo_combsort / execucoes;

            saidaTeste << "MEDIAS: " << endl;
            saidaTeste << endl;

            saidaTeste << "Media comparacoes quicksort: " << media_comparacoes_quicksort << ", media movimentacoes quicksort: " << media_movimentacoes_quicksort << ", media tempo quicksort: " << media_tempo_quicksort << endl;
            saidaTeste << endl;

            saidaTeste << "Media comparacoes heapsort: " << media_comparacoes_heapsort << ", media movimentacoes heapsort: " << media_movimentacoes_heapsort << ", media tempo heapsort: " << media_tempo_heapsort << endl;
            saidaTeste << endl;

            saidaTeste << "Media comparacoes combsort: " << media_comparacoes_combsort << ", media movimentacoes combsort: " << media_movimentacoes_combsort << ", media tempo combsort: " << media_tempo_combsort << endl;
            saidaTeste << endl;
    }

    void moduloTesteHash()
    {}
};

#endif //MODULO_TESTE_H_INCLUDED