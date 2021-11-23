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

void processamentoInicial(bool imprimir,char *argv[])
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

    // LEITURA DO ARQUIVO .CSV

    if(imprimir)
    {
        // IMPRESSAO DOS DADOS DO ARQUIVO

        processamento.impressaoArquivo(&dados, arquivoEntrada);
        arquivoEntrada.close();
    }else 
    {
        // LEITURA DO ARQUIVO .CSV

        cout << "Lendo o arquivo..." << endl;
        processamento.leituraArquivoCSV(&dados, arquivoEntrada);
        cout << "Arquivo Lido" << endl;
        arquivoEntrada.close();

        // CRIAÇÃO DO ARQUIVO .BIN  

        cout << "Criando arquivo .bin" << endl;
        processamento.escritaArquivo(dados);
        cout << "Arquivo criado." << endl;  

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
        cout << "1 - Pre-processamento dos dados;" << endl;
        cout << "2 - Acessar Registro;" << endl;
        cout << "3 - Teste de importacao de registro;" << endl;
        cout << "4 - Importacao de N registros;" << endl;
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
                // PRÉ - PROCESSAMENTO

                cout << "Iniciando pre-processamento de dados: " << endl;
                processamentoInicial(false, argv);
                break;
            }
            case 2: 
            {
                // ACESSO AO REGISTRO
                fstream arquivoEntrada("tiktok_app_reviews.bin", ios::in | ios::binary);
                int indice;
                cout << "Entre com o indice que deseja acessar: ";
                cin >> indice;
                processamento.acessaRegistro(indice,arquivoEntrada);
                arquivoEntrada.close();
                break;
            }
            case 3:
            {
                // TESTE DE IMPORTAÇÃO COM SAÍDA EM ARQUIVO OU EM CONSOLE

                int opTeste;
                cout << "Deseja exibir a saida no console ou salvar em um arquivo texto? (1 - console | 2 - arquivo) ";
                cin >> opTeste;

                fstream arquivoEntrada("tiktok_app_reviews.bin", ios::in | ios::binary);

                switch (opTeste)
                {
                    case 1:
                    {
                        processamento.testeImportacaoConsole(arquivoEntrada);
                        break;
                    }
                    case 2:
                    {
                        processamento.testeImportacaoArquivo(arquivoEntrada);
                        break;
                    }
                    default:
                    {
                        cout << "Opcao invalida. Escolha opcao 1 ou 2.";
                        break;
                    }
                }

                arquivoEntrada.close();
                break;
            }
            case 4: 
            {
                // IMPORTACAO DE N REGISTROS

                int opTeste;
                int n;

                cout << "Deseja exibir a saida no console ou salvar em um arquivo texto? (1 - console | 2 - arquivo) ";
                cin >> opTeste;
                cout << "Insira o numero de registros: ";
                cin >> n;

                fstream arquivoEntrada("tiktok_app_reviews.bin", ios::in | ios::binary);

                switch (opTeste)
                {
                    case 1:
                    {
                        processamento.testeImportacaoConsoleN(arquivoEntrada,n);
                        break;
                    }
                    case 2:
                    {
                        processamento.testeImportacaoArquivoN(arquivoEntrada,n);
                        break;
                    }
                    default:
                    {
                        cout << "Opcao invalida. Escolha opcao 1 ou 2.";
                        break;
                    }
                }
                arquivoEntrada.close();
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
    processamento(argv);
}