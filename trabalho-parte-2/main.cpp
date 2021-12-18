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

void prefacio()
{
    cout << "Trabalho de estrutura de dados 2 - 2021/3" << endl;
    cout << "Grupo: " << endl;
    cout << "Beatriz Cunha Rodrigues - 201776038" << endl;
    cout << "Daniel Ribeiro Lavra - 201735042" << endl;
}

void processamentoInicial(char *argv[])
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

                cout << "Ordenacao: " << endl;
                processamentoInicial(argv);

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