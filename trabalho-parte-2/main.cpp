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
#include "Modulo_Teste.h"
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

void ordenacao(char *argv[], int execucoes, ofstream& saida, vector<int> N)
{
    Processamento processamento;

    string arquivoBin = "tiktok_app_reviews.bin";

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

    // ARQUIVO ENTRADA .CSV

    ifstream arquivoEntradaCSV(argv[1]);

    // LEITURA DO ARQUIVO .CSV

    cout << "Lendo arquivo .csv..." << endl;

    processamento.leituraArquivoCSV(&dados, arquivoEntradaCSV);

    cout << "Leitura finalizada." << endl;

    // CRIAÇÃO DO ARQUIVO .BIN

    cout << "Criando arquivo tiktok_app_reviews.bin..." << endl;

    processamento.escritaArquivo(dados);
    dados.clear();

    cout << "Arquivo .bin criado." << endl;

    // ARQUIVO ENTRADA .BIN

    fstream arquivoEntradaBIN(arquivoBin, ios::in | ios::binary);
    
    for(int i=0;i<N.size();i++)
    {
        int auxN = N.at(i);
        cout << "TAMANHO: " << auxN << endl;
        saida << "------------------------------------------------" << endl;
        saida << "TAMANHO: " << auxN << endl;
        saida << endl;

        Dados_Ordenacao ordenacao;
        auxExecucoes = 0;

        while(auxExecucoes < execucoes)
        {
            Data data;

            cout << "EXECUCAO: " << auxExecucoes+1 << endl;
            saida << "EXECUCAO: " << auxExecucoes+1 << endl;
            saida << endl;

            // LEITURA DO ARQUIVO .BIN

            indiceLeitura = 1+rand()%3660628;

            cout << "Importando dados..." << endl;

            for(int i=0; i< auxN; i++)
            {
                data = processamento.leituraBinIndividual(indiceLeitura, arquivoEntradaBIN);
                dados.push_back(data);
                indiceLeitura = 1+rand()%3660628;
            }
            
            cout << "Dados importados" << endl;

            // UTILIZANDO VETOR AUXILIAR

            for(int i=0; i< auxN; i++)
            {
                dadosAux.push_back(dados.at(i));
            }

            // ORDENAÇÃO QUICKSORT -------------------------------------------

            cout << "Iniciando ordenacao quicksort..." << endl;
            saida << "Quicksort: " << endl;

            inicio = inicio = double(clock()) / CLOCKS_PER_SEC;

            ordenacao.clear();

            processamento.quickSort(&dadosAux, 0, dadosAux.size(), &ordenacao);
            total_comparacoes_quicksort += ordenacao.getTotalComparacoes();
            total_movimentacoes_quicksort += ordenacao.getTotalMovimentacoes();
            fim = double(clock()) / CLOCKS_PER_SEC;

            tempo = fim - inicio;

            total_tempo_quicksort += tempo;

            saida << "Total de comparacoes: " << ordenacao.getTotalComparacoes() << ", total de movimentacoes: " << ordenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   

            cout << "Ordenacao quicksort finalizada..." << endl;

            dadosAux.clear();

            // ORDENAÇÃO HEAPSORT --------------------------------------------

            for(int i=0; i<auxN; i++)
            {
                dadosAux.push_back(dados.at(i));
            }

            cout << "Iniciando ordenacao heapsort..." << endl;
            saida << "Heapsort: " << endl;

            inicio = double(clock()) / CLOCKS_PER_SEC;

            ordenacao.clear();

            processamento.heapSort(&dadosAux, dadosAux.size(), &ordenacao);
            total_comparacoes_heapsort += ordenacao.getTotalComparacoes();
            total_movimentacoes_heapsort += ordenacao.getTotalMovimentacoes();
            fim = double(clock()) / CLOCKS_PER_SEC;

            tempo = fim - inicio;

            total_tempo_heapsort += tempo;

            saida << "Total de comparacoes: " << ordenacao.getTotalComparacoes() << ", total de movimentacoes: " << ordenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   

            cout << "Ordenacao finalizada..." << endl;

            dadosAux.clear();

            // ORDENAÇÃO COMBSORT ----------------------------------------------

            for(int i=0; i<auxN; i++)
            {
                dadosAux.push_back(dados.at(i));
            }

            cout << "Iniciando ordenacao combsort..." << endl;
            saida << "Combsort: " << endl;

            inicio = double(clock()) / CLOCKS_PER_SEC;

            ordenacao.clear();

            processamento.combSort(&dadosAux, dadosAux.size(), &ordenacao);
            total_comparacoes_combsort += ordenacao.getTotalComparacoes();
            total_movimentacoes_combsort += ordenacao.getTotalMovimentacoes();
            fim = double(clock()) / CLOCKS_PER_SEC;

            tempo = fim - inicio;

            total_tempo_combsort += tempo;

            saida << "Total de comparacoes: " << ordenacao.getTotalComparacoes() << ", total de movimentacoes: " << ordenacao.getTotalMovimentacoes() << ", tempo de execucao: " << tempo << endl;   

            cout << "Ordenacao finalizada..." << endl;

            dadosAux.clear();

            // ------------------------------------------------------

            indiceLeitura = 0;
            dados.clear();
            auxExecucoes++;

            saida << endl;
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

        saida << "MEDIAS: " << endl;
        saida << endl;

        saida << "Media comparacoes quicksort: " << media_comparacoes_quicksort << ", media movimentacoes quicksort: " << media_movimentacoes_quicksort << ", media tempo quicksort: " << media_tempo_quicksort << endl;
        saida << endl;

        saida << "Media comparacoes heapsort: " << media_comparacoes_heapsort << ", media movimentacoes heapsort: " << media_movimentacoes_heapsort << ", media tempo heapsort: " << media_tempo_heapsort << endl;
        saida << endl;

        saida << "Media comparacoes combsort: " << media_comparacoes_combsort << ", media movimentacoes combsort: " << media_movimentacoes_combsort << ", media tempo combsort: " << media_tempo_combsort << endl;
        saida << endl;
    }
}


// PROCESSAMENTO DO PROJETO

void processamento(char * argv[], ofstream& saida, ofstream& saidaTeste, ofstream& saidaHash)
{
    Processamento processamento;
    Modulo_Teste modulo;

    string saidaBin = "tiktok_app_reviews.bin";

    // LEITURA DO ARQUIVO .DAT

    vector<int> N = processamento.leituraDAT();
  
    int opcao = 0;
    while(opcao != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Ordenacao;" << endl;
        cout << "2 - Hash;" << endl;
        cout << "3 - Modulo de teste;" << endl;
        cout << "-1 - Sair;" << endl;
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

                int execucoes;

                cout << "Ordenacao: " << endl;
                
                cout << "Entre com o numero de execucoes: " << endl;
                cin >> execucoes;

                if(execucoes < 3)
                {
                    cout << "Numero de execucoes invalida. Eh necessario ser maior ou igual a 3." << endl;
                }else 
                {
                    ordenacao(argv, execucoes, saida, N);
                }
                break;
            }
            case 2: 
            {
                // HASH

                vector<Data> dados;

                fstream arquivoEntrada(argv[1], ios::in | ios::binary);

                // ARQUIVO ENTRADA .CSV

                ifstream arquivoEntradaCSV(argv[1]);

                // LEITURA DO ARQUIVO .CSV

                cout << "Lendo arquivo .csv..." << endl;

                processamento.leituraArquivoCSV(&dados, arquivoEntradaCSV);

                cout << "Leitura finalizada." << endl;

                // CRIAÇÃO DO ARQUIVO .BIN

                cout << "Criando arquivo tiktok_app_reviews.bin..." << endl;

                processamento.escritaArquivo(dados);
                dados.clear();

                cout << "Arquivo .bin criado." << endl;

                // ARQUIVO ENTRADA .BIN

                fstream arquivoEntradaBIN("tiktok_app_reviews.bin", ios::in | ios::binary);

                int M; 
                long long int tamanho;

                cout << "Hash: " << endl;

                cout << "Entre com o numero de dados que sera lido: " << endl;
                cin >> tamanho;

                cout << "Entre com o numero de versoes mais recentes do app a ser impresso: " << endl;
                cin >> M;

                Data data;

                int indiceLeitura = 0;

                for(int i=0; i < tamanho; i++)
                {
                    data = processamento.leituraBinIndividual(indiceLeitura, arquivoEntradaBIN);
                    dados.push_back(data);
                    indiceLeitura = 1+rand()%3660628;
                }
                processamento.processamentoHash(dados, tamanho, M);
                break;
   
            }
            case 3: 
            {
                
                // MODULO TESTE

                int execucoes;

                cout << "Modulo de teste..." << endl;

                cout << "Entre com o numero de execucoes: " << endl;
                cin >> execucoes;

                if(execucoes < 3)
                {
                    cout << "Numero de execucoes invalida. Eh necessario ser maior ou igual a 3." << endl;
                }else 
                {
                    modulo.moduloTesteOrdenacao(saidaTeste, argv, execucoes);
                }
                break;
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
    ofstream saida ("saida.txt");
    ofstream saidaTeste ("teste.txt");
    ofstream saidaHash ("saidaHash.txt");

    processamento(argv, saida, saidaTeste, saidaHash);
}