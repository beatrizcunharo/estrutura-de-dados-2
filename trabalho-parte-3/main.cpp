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

// BOOL ARVORE: 0 - arvore vermelho-preto / 1 - arvore b
// BOOL MODO: 0 - modo analise / 1 - modo teste

void processamentoInicial(char *argv[], ofstream& saida, bool modo, int N, int M)
{
    Processamento processamento;

    ifstream arquivoEntrada(argv[1]);

    // CONFERE SE O ARQUIVO ESTÁ ABERTO

    if(!arquivoEntrada.is_open())
    {
        cout << "Erro. Arquivo não pode ser aberto." << endl;
        exit(1);
    }

    // VETOR DE DADOS

    vector<Data> dados;

    int indiceLeitura = 0;

    // LEITURA DO ARQUIVO .BIN

    for(int i=0; i<N; i++)
    {
        processamento.leituraBIN(&dados, argv, N);
        indiceLeitura = 1+rand()%3660628;
    }


    if(M == -1)
    {
        // PROCESSAMENTO ARVORE VERMELHO-PRETO

        switch (modo)
        {
            case 0:
                // MODO ANÁLISE
                //processamento.modoAnalise();
                break;
            default:
                // MODO TESTE
                //processamento.modoAnalise();
                break;
        }
    } else 
    {
        // PROCESSAMENTO ARVORE B

        switch (modo)
        {
            case 0:
                // MODO ANÁLISE
                //processamento.modoAnalise();
                break;
            default:
                // MODO TESTE
                //processamento.modoAnalise();
                break;
        }
    }
}

// PROCESSAMENTO DO PROJETO

void processamento(char * argv[], ofstream& saida)
{
    Processamento processamento;

    int opcao = 0;
    while(opcao != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Arvore Vermelho-Preto;" << endl;
        cout << "2 - Arvore B;" << endl;
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
                // ÁRVORE VERMELHA E PRETA

                int op = 0, N;
                cout << "Escolha uma opcao: " << endl;
                cout << "1 - Modo de analise;" << endl;
                cout << "2 - Modo de teste;" << endl;
                cout << "-1 - Sair;" << endl;
                cout << "Opcao: ";
                cin >> op;

                switch (op)
                {
                    case 1:
                        
                        // MODO DE ANÁLISE
                        cout << "MODO DE ANALISE" << endl;
                        cout << "Entre com o numero de registros para a leitura: " << endl;
                        cin >> N;

                        processamentoInicial(argv, saida, 0, N, -1);

                        break;
                    case 2:

                        // MODO DE TESTE

                        cout << "MODO DE TESTE" << endl;
                        cout << "Entre com o numero de registros para a leitura: " << endl;
                        cin >> N;

                        processamentoInicial(argv, saida, 1, N, -1);

                        break;
                    default:

                        // OPÇÃO DE SAÍDA

                        cout << "Saindo..." << endl;
                        exit(0);

                        break;
                }
                break;
            }
            case 2: 
            {
                // ARVORE B

                int op = 0, N, M;
                cout << "Escolha uma opcao: " << endl;
                cout << "1 - Modo de analise;" << endl;
                cout << "2 - Modo de teste;" << endl;
                cout << "-1 - Sair;" << endl;
                cout << "Opcao: ";
                cin >> op;

                switch (op)
                {
                    case 1:
                        
                        // MODO DE ANÁLISE
                        cout << "MODO DE ANALISE" << endl;
                        cout << "Entre com o numero de registros para a leitura: " << endl;
                        cin >> N;
                        cout << "Ordem da arvore: " << endl;
                        cin >> M;

                        processamentoInicial(argv, saida, 0, N, M);

                        break;
                    case 2:

                        // MODO DE TESTE

                        cout << "MODO DE TESTE" << endl;
                        cout << "Entre com o numero de registros para a leitura: " << endl;
                        cin >> N;
                        cout << "Ordem da arvore: " << endl;
                        cin >> M;

                        processamentoInicial(argv, saida, 1, N, M);

                        break;
                    default:

                        // OPÇÃO DE SAÍDA

                        cout << "Saindo..." << endl;
                        exit(0);

                        break;
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

    processamento(argv, saida);
}