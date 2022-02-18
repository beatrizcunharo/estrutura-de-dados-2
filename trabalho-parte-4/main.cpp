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

void compressao(char * argv[], int N, ofstream& reviewsComp)
{
    Processamento processamento;

    // VETOR DE DADOS

    vector<Data> dados;

    ifstream arquivoEntrada(argv[1]);

    // VETOR AUXILIAR DE DADOS

    vector<Data> dadosAux;

    // LEITURA DO ARQUIVO .CSV

    cout << "Lendo arquivo .csv..." << endl;

    processamento.leituraArquivoCSV(&dados, arquivoEntrada);

    cout << "Leitura finalizada." << endl;

    // ARMAZENAMENTO DE N DADOS

    int indice = 0;

    for(int i=0;i<N;i++)
    {
        indice = 1+rand()%3660628;
        dadosAux.push_back(dados.at(indice));
    }
    
}

// PROCESSAMENTO DO PROJETO

void processamento(char * argv[], ofstream& reviewsComp, ofstream& reviewsOrig, ofstream& saida)
{
    Processamento processamento;
  
    int opcao = 0;
    while(opcao != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Comprimir um conjunto N;" << endl;
        cout << "2 - Descomprimir;" << endl;
        cout << "3 - Executar sequencia de compressoes;" << endl;
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
                // COMPRIMIR

                int N;

                cout << "Entre com o valor de N para a leitura do arquivo: " << endl;
                cin >> N;

                compressao(argv, N, reviewsComp);

                break;
            }
            case 2: 
            {
                // DESCOMPRIMIR

                break;
   
            }
            case 3: 
            {
                
                // EXECUTAR SEQUENCIA DE COMPRESSÕES

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
    ofstream reviewsComp ("reviewsComp.bin");
    ofstream reviewsOrig ("reviewsOrig.bin");
    ofstream saida ("saida.txt");
    processamento(argv, reviewsComp, reviewsOrig, saida);
}