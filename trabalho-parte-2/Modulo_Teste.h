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
#include "Dados_Ordenacao.h"

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
    void moduloTesteOrdenacao(ofstream& saidaTeste, int opcao, char *argv[], int execucoes)
    {
        Processamento processamento;

        // VETOR DE DADOS
        vector<Data> dados;

        // LEITURA DO ARQUIVO .BIN

        cout << "Importando dados..." << endl;
        processamento.leituraBIN(&dados, argv, 100);
        cout << "Dados importados" << endl;

        // ORDENAÇÃO

        switch(opcao)
        {
            case 1:
            {
                // ORDENAÇÃO QUICKSORT

                Dados_Ordenacao dadosOrdenacao;
                cout << "Iniciando ordenacao quicksort..." << endl;
                int auxExecucoes = 0;
                long comparacoes = 0;
                long movimentacoes = 0;
                long tempo = 0;
                
                saidaTeste << "Quicksort: " << endl;

                while(auxExecucoes < execucoes)
                {
                    high_resolution_clock::time_point inicio = high_resolution_clock::now();
                    processamento.quickSort(&dados, 0, dados.size(), &dadosOrdenacao);
                    comparacoes = comparacoes + dadosOrdenacao.getTotalComparacoes();
                    movimentacoes = movimentacoes + dadosOrdenacao.getTotalMovimentacoes();
                    high_resolution_clock::time_point fim = high_resolution_clock::now();

                    long temp = duration_cast<duration<double>>(fim - inicio).count();

                    tempo = tempo + temp;

                    saidaTeste << "Total de comparacoes: " << dadosOrdenacao.getTotalComparacoes() << ", total de movimentacoes: " << dadosOrdenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   
                    auxExecucoes++;
                }

                long media_comparacoes = comparacoes / execucoes;
                long media_movimentacoes = movimentacoes / execucoes;
                long media_tempo = tempo / execucoes;

                saidaTeste << "Media comparacoes: " << media_comparacoes << ", media movimentacoes: " << media_movimentacoes << ", media tempo: " << media_tempo << endl;
                saidaTeste << endl;

                cout << "Ordenacao finalizada..." << endl;
                break;
            }
            case 2:
            {            
                // ORDENAÇÃO HEAPSORT

                Dados_Ordenacao dadosOrdenacao;
                cout << "Iniciando ordenacao heapsort..." << endl;
                int auxExecucoes = 0;
                long comparacoes = 0;
                long movimentacoes = 0;
                long tempo = 0;

                saidaTeste << "Heapsort: " << endl;

                while(auxExecucoes < execucoes)
                {
                    high_resolution_clock::time_point inicio = high_resolution_clock::now();
                    processamento.heapSort(&dados, dados.size(), &dadosOrdenacao);
                    comparacoes = comparacoes + dadosOrdenacao.getTotalComparacoes();
                    movimentacoes = movimentacoes + dadosOrdenacao.getTotalMovimentacoes();
                    high_resolution_clock::time_point fim = high_resolution_clock::now();

                    long temp = duration_cast<duration<double>>(fim - inicio).count();

                    tempo = tempo + temp;

                    saidaTeste << "Total de comparacoes: " << dadosOrdenacao.getTotalComparacoes() << ", total de movimentacoes: " << dadosOrdenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   
                    auxExecucoes++;
                }

                long media_comparacoes = comparacoes / execucoes;
                long media_movimentacoes = movimentacoes / execucoes;
                long media_tempo = tempo / execucoes;

                saidaTeste << "Media comparacoes: " << media_comparacoes << ", media movimentacoes: " << media_movimentacoes << ", media tempo: " << media_tempo << endl;
                saidaTeste << endl;

                cout << "Ordenacao finalizada..." << endl;
                break;
            }
            case 3:
            {
                // ORDENAÇÃO COMBSORT

                Dados_Ordenacao dadosOrdenacao;
                cout << "Iniciando ordenacao combsort..." << endl;
                int auxExecucoes = 0;
                long comparacoes = 0;
                long movimentacoes = 0;
                long tempo = 0;

                saidaTeste << "Combsort: " << endl;
                
                while(auxExecucoes < execucoes)
                {
                    high_resolution_clock::time_point inicio = high_resolution_clock::now();
                    processamento.combSort(&dados, dados.size(), &dadosOrdenacao);
                    comparacoes = comparacoes + dadosOrdenacao.getTotalComparacoes();
                    movimentacoes = movimentacoes + dadosOrdenacao.getTotalMovimentacoes();
                    high_resolution_clock::time_point fim = high_resolution_clock::now();

                    long temp = duration_cast<duration<double>>(fim - inicio).count();

                    tempo = tempo + temp;

                    saidaTeste << "Total de comparacoes: " << dadosOrdenacao.getTotalComparacoes() << ", total de movimentacoes: " << dadosOrdenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   
                    auxExecucoes++;
                }

                long media_comparacoes = comparacoes / execucoes;
                long media_movimentacoes = movimentacoes / execucoes;
                long media_tempo = tempo / execucoes;

                saidaTeste << "Media comparacoes: " << media_comparacoes << ", media movimentacoes: " << media_movimentacoes << ", media tempo: " << media_tempo << endl;
                saidaTeste << endl;

                cout << "Ordenacao finalizada..." << endl;
                break;
            }
        }
        dados.clear();
    }
};

#endif //MODULO_TESTE_H_INCLUDED