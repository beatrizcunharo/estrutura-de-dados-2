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

// VETOR DE DADOS
vector<Data> dados;

void leituraCSV(bool imprimir)
{
    Processamento processamento;

    ifstream arquivoEntrada("arquivos/tiktok_app_reviews.csv");

    // CONFERE SE O ARQUIVO ESTÁ ABERTO

    if(!arquivoEntrada.is_open())
    {
        cout << "Erro. Arquivo não pode ser aberto." << endl;
        exit(1);
    }

    // LEITURA DO ARQUIVO .CSV - VERIFICAR IMPLEMENTAÇÃO LEITURA EM BLOCO

    if(imprimir)
    {
        processamento.impressaoArquivo(&dados, arquivoEntrada);
        arquivoEntrada.close();
    }else 
    {
        cout << "Lendo o arquivo..." << endl;
        processamento.leituraArquivo(&dados, arquivoEntrada);
        cout << "Arquivo Lido" << endl;
        arquivoEntrada.close();    
    }
}

void escritaBIN()
{

    Processamento processamento;

    // ESCRITA DO ARQUIVO .BIN

    cout << "Criando arquivo .bin" << endl;
    processamento.escritaArquivo(dados);
    cout << "Arquivo criado." << endl;
}

void processamento()
{
    int opcao = 0;
    while(opcao != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Pre-processamento dos dados;" << endl;
        cout << "2 - Acessar Registro;" << endl;
        cout << "3 - Teste de importacao de registro;" << endl;
        cout << "-1 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        switch(opcao) 
        {
            case -1:
            {
                cout << "Saindo..." << endl;
                exit(0);
            }                
            case 1:
            {
                cout << "Iniciando pre-processamento de dados: " << endl;
                leituraCSV(true);
                break;
            }
            case 2: 
               {
                // FAZER ACESSO AO REGISTRO .BIN NO INDICE I
                exit(0);           
               }
            case 3:
                // FAZER FUNÇÃO DE TESTE
                exit(0);
            default:
                cout << "Opcao invalida. Escolha uma opcao valida." << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    // CONFERE SE HOUVE A ENTRADA DO ARQUIVO
    /*if (argc != 2) 
    {
        prefacio();
        cout << "ERROR: Expecting: ./<nomePrograma> <arquivo> " << endl;
        return 0;
    }*/
    leituraCSV(false);
    escritaBIN();
    prefacio();
    processamento();
}