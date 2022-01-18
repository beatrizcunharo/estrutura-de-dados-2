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
#include "Arvore_B.h"

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

void processamentoInicial(char *argv[], ofstream& saida, bool modo, int N, int m)
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

    // ARVORE B

    Arvore_B *arvore = new Arvore_B(m);

    // ARVORE VERMELHO-PRETO

    //RBTree *arvoreVP = new RBTree();


    // CLASSE DE DADOS A SEREM SALVOS NA ÁRVORE

    Dados_Arvore *dadosArvore = new Dados_Arvore();

    int indiceLeitura = 0;

    if(m == -1)
    {
        // PROCESSAMENTO ARVORE VERMELHO-PRETO

        // LEITURA DO ARQUIVO .BIN

        for(int i=0; i<N; i++)
        {
            indiceLeitura = 1+rand()%3660628;
            processamento.leituraBIN(&dados, argv, N);
            dadosArvore->setReviewId(dados.at(i).getReviewId());
            dadosArvore->setLocalizacao(indiceLeitura);
            cout << dadosArvore->getReviewId() << endl;
            //arvoreVP->insert(*&dadosArvore->getReviewId(), dadosArvore->getLocalizacao());
            indiceLeitura = 1+rand()%3660628;
        }

        switch (modo)
        {
            case 0:
                // MODO ANÁLISE
                //arvoreVermelha.modoAnalise();
                break;
            default:
                // MODO TESTE

                string id_avaliacao;
                cout << "Insira o id que deseja buscar: " << endl;
                cin >> id_avaliacao;

                /*bool existe = arvoreVP->busca(id_avaliacao);

                if(existe)
                    cout << "Indice encontrado na arvore." << endl;
                else
                    cout << "Nada encontrado. " << endl;*/
        }
        dados.clear();
    } else 
    {
        // PROCESSAMENTO ARVORE B

        // LEITURA DO ARQUIVO .BIN

        for(int i=0; i<N; i++)
        {
            indiceLeitura = 1+rand()%3660628;
            processamento.leituraBIN(&dados, argv, N);
            dadosArvore->setReviewId(dados.at(i).getReviewId());
            dadosArvore->setLocalizacao(indiceLeitura);
            cout << dadosArvore->getReviewId() << endl;
            arvore->inserir(*dadosArvore);
            indiceLeitura = 1+rand()%3660628;
        }

        switch (modo)
        {
            case 0:
                // MODO ANÁLISE
                //arvoreB.modoAnalise();
                break;
            default:

                // MODO TESTE

                string id_avaliacao;
                cout << "Insira o id que deseja buscar: " << endl;
                cin >> id_avaliacao;

                if(arvore->busca(id_avaliacao) != NULL)
                    cout << "Indice encontrado na arvore." << endl;
                else
                    cout << "Nada encontrado. " << endl;
                               
        }
    }
    dados.clear();
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

                int op = 0, N, m;
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
                        cin >> m;

                        processamentoInicial(argv, saida, 0, N, m);

                        break;
                    case 2:

                        // MODO DE TESTE

                        cout << "MODO DE TESTE" << endl;
                        cout << "Entre com o numero de registros para a leitura: " << endl;
                        cin >> N;
                        cout << "Ordem da arvore: " << endl;
                        cin >> m;

                        processamentoInicial(argv, saida, 1, N, m);

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