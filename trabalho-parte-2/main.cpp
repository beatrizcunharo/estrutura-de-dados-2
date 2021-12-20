/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042

*/

#include <fstream>
#include <vector>
#include<bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <cstring>
#include <algorithm>
#include <random>

#include "Data.h"
#include "Dados_Ordenacao.h"
#include "Processamento.h"

using namespace std;
using namespace std::chrono;

void prefacio()
{
    cout << "Trabalho de estrutura de dados 2 - 2021/3" << endl;
    cout << "Grupo: " << endl;
    cout << "Beatriz Cunha Rodrigues - 201776038" << endl;
    cout << "Daniel Ribeiro Lavra - 201735042" << endl;
}

void processamentoInicial(char *argv[], int opcao, int execucoes)
{
    Processamento processamento;

    // VETOR DE DADOS

    vector<Data> dados;

    // LEITURA DO ARQUIVO .DAT

    int n = processamento.leituraDAT();

    // LEITURA DO ARQUIVO .BIN

    cout << "Importando dados..." << endl;
    processamento.leituraBIN(&dados, argv, n);
    cout << "Dados importados" << endl;

    // ORDENAÇÃO

    Dados_Ordenacao dadosOrdenacao;
    ofstream saida ("saida.txt");

    switch(opcao)
    {
        case 1:
        {
            // ORDENAÇÃO QUICKSORT

            cout << "Iniciando ordenacao quicksort..." << endl;
            int auxExecucoes = 0;
            long comparacoes = 0;
            long movimentacoes = 0;
            long tempo = 0;
            
            saida << "Quicksort: " << endl;

            while(auxExecucoes < execucoes)
            {
                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                processamento.quickSort(&dados, 0, dados.size(), &dadosOrdenacao);
                comparacoes = comparacoes + dadosOrdenacao.getTotalComparacoes();
                movimentacoes = movimentacoes + dadosOrdenacao.getTotalMovimentacoes();
                high_resolution_clock::time_point fim = high_resolution_clock::now();

                long temp = duration_cast<duration<double>>(fim - inicio).count();

                tempo = tempo + temp;

                saida << "Total de comparacoes: " << dadosOrdenacao.getTotalComparacoes() << ", total de movimentacoes: " << dadosOrdenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   
                auxExecucoes++;
            }

            long media_comparacoes = comparacoes / execucoes;
            long media_movimentacoes = movimentacoes / execucoes;
            long media_tempo = tempo / execucoes;

            saida << "Media comparacoes: " << media_comparacoes << ", media movimentacoes: " << media_movimentacoes << ", media tempo: " << media_tempo << endl;
            saida << endl;

            cout << "Ordenacao finalizada..." << endl;
            break;
        }
        case 2:
        {
            // ORDENAÇÃO HEAPSORT

            cout << "Iniciando ordenacao heapsort..." << endl;
            int auxExecucoes = 0;
            long comparacoes = 0;
            long movimentacoes = 0;
            long tempo = 0;

            saida << "Heapsort: " << endl;

            while(auxExecucoes < execucoes)
            {
                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                processamento.heapSort(&dados, dados.size(), &dadosOrdenacao);
                comparacoes = comparacoes + dadosOrdenacao.getTotalComparacoes();
                movimentacoes = movimentacoes + dadosOrdenacao.getTotalMovimentacoes();
                high_resolution_clock::time_point fim = high_resolution_clock::now();

                long temp = duration_cast<duration<double>>(fim - inicio).count();

                tempo = tempo + temp;

                saida << "Total de comparacoes: " << dadosOrdenacao.getTotalComparacoes() << ", total de movimentacoes: " << dadosOrdenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   
                auxExecucoes++;
            }

            long media_comparacoes = comparacoes / execucoes;
            long media_movimentacoes = movimentacoes / execucoes;
            long media_tempo = tempo / execucoes;

            saida << "Media comparacoes: " << media_comparacoes << ", media movimentacoes: " << media_movimentacoes << ", media tempo: " << media_tempo << endl;
            saida << endl;

            cout << "Ordenacao finalizada..." << endl;
            break;
        }
        case 3:
        {
            // ORDENAÇÃO COMBSORT
            
            cout << "Iniciando ordenacao..." << endl;
            processamento.combSort(&dados, execucoes);
            cout << "Ordenacao finalizada..." << endl;
            break;
        }
    }

    dados.clear();
}

// PROCESSAMENTO DO PROJETO

void processamento(char * argv[])
{
    Processamento processamento;

    int opcao = 0;
    while(opcao != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Ordenacao;" << endl;
        cout << "2 - Arrumar;" << endl;
        cout << "-1 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch(opcao) 
        {
            case -1:
            {
                // OPÇÃO DE SAÍDA

                cout << "Saindo..." << endl;
                exit(0);
            }                
            case 1:
            {
                // ORDENAÇÃO

                int opcao, execucoes;

                cout << "Ordenacao: " << endl;
                cout << "Entre com a ordenacao que deseja executar: " << endl;
                cout << "1 - Quicksort;" << endl;
                cout << "2 - Heapsort;" << endl;
                cout << "3 - Combsort" << endl;
                cin >> opcao;

                if(opcao!=1 && opcao!=2 && opcao!=3)
                {
                    cout << "Opcao invalida. Escolha uma opcao valida." << endl;    
                }else
                {
                    cout << "Entre com o numero de execucoes: " << endl;
                    cin >> execucoes;

                    if(execucoes < 3)
                    {
                        cout << "Numero de execucoes invalida. Eh necessario ser maior ou igual a 3." << endl;
                    }else 
                    {
                        processamentoInicial(argv, opcao, execucoes);
                    }
                }
                break;
            }
            case 2: 
            {
                // ARRUMAR
                exit(1);
            }
            default:
                cout << "Opcao invalida. Escolha uma opcao valida." << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    // VERIFICA ENTRADA DO ARQUIVO PARA EXECUÇÃO

    if (argc != 2)
    {
        cout << "ERROR: Expecting: ./<nomePrograma> <arquivoEntrada> " << endl;
        return 0;
    }
    system("clear");
    prefacio();
    processamento(argv);
}