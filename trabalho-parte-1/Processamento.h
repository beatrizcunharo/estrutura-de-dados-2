/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef PROCESSAMENTO_H_INCLUDED
#define PROCESSAMENTO_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

#include "Data.h"
using std::stringstream;
using std::string;
using namespace std;

class Processamento 
{
    public:

    // CONSTRUTOR
    Processamento()
    {
        // CONSTRUTOR VAZIO
    }

    // DESTRUTOR
    ~Processamento()
    {
        // DESTRUTOR VAZIO
    }

    // LEITURA DO ARQUIVO EM CSV

    void leituraArquivoCSV(vector<Data> *dados, ifstream& arquivoEntrada)
    {
        Data dadosLidos;
        string linha;

        // RETIRANDO A PRIMEIRA LINHA POIS É APENAS OS NOMES DOS CAMPOS
        getline(arquivoEntrada, linha, '\n');
        linha.clear();
        while(!arquivoEntrada.eof())
        {         
            // LENDO REVIEW_ID
            getline(arquivoEntrada, linha, ',');
            dadosLidos.setReviewId(linha);
            linha.clear();

            // LENDO REVIEW_TEXT
            if(arquivoEntrada.peek()=='"')
            {
                arquivoEntrada.get();
                getline(arquivoEntrada,linha,'"');
                dadosLidos.setReviewText(linha);
                arquivoEntrada.get();
                linha.clear();
            }
            else 
            {
                getline(arquivoEntrada,linha,',');
                dadosLidos.setReviewText(linha);
                linha.clear();
            }

            // LENDO UPVOTES
            getline(arquivoEntrada, linha,',');
            dadosLidos.setUpvotes(atoi(linha.c_str()));
            linha.clear();

            // LENDO APP_VERSION
            getline(arquivoEntrada, linha, ',');
            dadosLidos.setAppVersion(linha);
            linha.clear();

            // LENDO POSTED_DATE
            getline(arquivoEntrada, linha, '\n');
            dadosLidos.setPostedDate(linha);
            linha.clear();
            
            dados->push_back(dadosLidos);
        }
    }

    // IMPRESSAO DOS DADOS DO ARQUIVO

    void impressaoArquivo(vector<Data> *dados, ifstream& arquivoEntrada)
    {
        string linha;

        // RETIRANDO A PRIMEIRA LINHA POIS É APENAS OS NOMES DOS CAMPOS
        getline(arquivoEntrada, linha, '\n');
        linha.clear();

        while(!arquivoEntrada.eof())
        {         
            // IMPRIMINDO REVIEW_ID
            getline(arquivoEntrada, linha, ',');
            cout << linha << ',';
            linha.clear();

            // IMPRIMINDO REVIEW_TEXT
            if(arquivoEntrada.peek()=='"')
            {
                arquivoEntrada.get();
                getline(arquivoEntrada,linha,'"');
                cout << linha << ',';
                arquivoEntrada.get();
                linha.clear();
            }
            else 
            {
                getline(arquivoEntrada,linha,',');
                cout << linha << ',';
                linha.clear();
            }

            // IMPRIMINDO UPVOTES
            getline(arquivoEntrada, linha,',');
            cout << linha << ',';
            linha.clear();

            // IMPRIMINDO APP_VERSION
            getline(arquivoEntrada, linha, ',');
            cout << linha << ',';
            linha.clear();

            // IMPRIMINDO POSTED_DATE
            getline(arquivoEntrada, linha, '\n');
            cout << linha << endl;
            linha.clear();
        }
    }

    // ESCRITA DO ARQUIVO BINÁRIO

    void escritaArquivo(vector<Data> dados)
    {
        fstream arquivoSaida("tiktok_app_reviews.bin", ios::out | ios::binary);

        // VERIFICA SE O ARQUIVO ESTÁ ABERTO

        if(arquivoSaida.is_open())
        {
            for(int i=0;i < dados.size(); i++) 
            {
                int upvotes = dados[i].getUpvotes();

                arquivoSaida.write(dados[i].getReviewId().c_str(), sizeof(char)*90);
                arquivoSaida.write(dados[i].getReviewText().c_str(), sizeof(char)*200);
                arquivoSaida.write(reinterpret_cast<const char*>(&upvotes), sizeof(int));
                arquivoSaida.write(dados[i].getAppVersion().c_str(), sizeof(char)*10);
                arquivoSaida.write(dados[i].getPostedDate().c_str(), sizeof(char)*20);
            }
        }
    }

    // LEITURA BINÁRIA

    Data leituraBIN(int indice, fstream& arquivoEntrada)
    {
        Data dados;
        if(arquivoEntrada.is_open())
        {
            arquivoEntrada.seekg((indice-1)*(320+sizeof(int)));
            char review_id[90];
            char review_text[200];
            int upvotes;
            char app_version[10];
            char posted_data[20];

            arquivoEntrada.read(review_id, sizeof(char)*90);
            arquivoEntrada.read(review_text, sizeof(char)*200);
            arquivoEntrada.read(reinterpret_cast<char*>(&upvotes), sizeof(int));
            arquivoEntrada.read(app_version, sizeof(char)*10);
            arquivoEntrada.read(posted_data, sizeof(char)*20);

            dados.setReviewId(review_id);
            dados.setReviewText(review_text);
            dados.setUpvotes(upvotes);
            dados.setAppVersion(app_version);
            dados.setPostedDate(posted_data);

            return dados;
        }
    }
    
    // FUNÇÃO DE ACESSO AO REGISTRO

    void acessaRegistro(int indice, fstream& arquivoEntrada)
    {
        Data dados = leituraBIN(indice,arquivoEntrada);

        cout << "Review id: " << dados.getReviewId() << endl;
        cout << "Review text: " << dados.getReviewText() << endl;
        cout << "Upvotes: " << dados.getUpvotes() << endl;
        cout << "App version: " << dados.getAppVersion() << endl;
        cout << "Posted date: " << dados.getPostedDate() << endl;
        
    }

    // TESTE IMPORTAÇÃO - IMPRESSAO NO CONSOLE

    void testeImportacaoConsole(fstream& arquivoEntrada)
    {
        int indice = 1+rand()%3660628;

        for(int i=0;i<10;i++)
        {
            Data dados = leituraBIN(indice,arquivoEntrada);
            cout << "Review id: " << dados.getReviewId() << endl;
            cout << "Review text: " << dados.getReviewText() << endl;
            cout << "Upvotes: " << dados.getUpvotes() << endl;
            cout << "App version: " << dados.getAppVersion() << endl;
            cout << "Posted date: " << dados.getPostedDate() << endl;
            indice = 1+rand()%3660628;
        }
        
    }

    // TESTE IMPORTAÇÃO - SALVANDO EM ARQUIVO

    void testeImportacaoArquivo(fstream& arquivoEntrada)
    {
        ofstream arquivoTeste("arquivoTeste.txt");
        int indice = 1+rand()%3660628;
        cout << "Escrevendo arquivo..." << endl;
        for(int i=0;i<100;i++)
        {
            Data dados = leituraBIN(indice,arquivoEntrada);
            arquivoTeste << "Review id: " << dados.getReviewId() << endl;
            arquivoTeste << "Review text: " << dados.getReviewText() << endl;
            arquivoTeste << "Upvotes: " << dados.getUpvotes() << endl;
            arquivoTeste << "App version: " << dados.getAppVersion() << endl;
            arquivoTeste << "Posted date: " << dados.getPostedDate() << endl;
            indice = 1+rand()%3660628;
        }
        cout << "Escrita finalizada." << endl;
    }

    // TESTE IMPORTAÇÃO CONSOLE DE N

    void testeImportacaoConsoleN(fstream& arquivoEntrada, int n)
    {
        int indice = 1+rand()%3660628;

        for(int i=0;i<n;i++)
        {
            Data dados = leituraBIN(indice,arquivoEntrada);
            cout << "Review id: " << dados.getReviewId() << endl;
            cout << "Review text: " << dados.getReviewText() << endl;
            cout << "Upvotes: " << dados.getUpvotes() << endl;
            cout << "App version: " << dados.getAppVersion() << endl;
            cout << "Posted date: " << dados.getPostedDate() << endl;
            indice = 1+rand()%3660628;
        }
        
    }

    // TESTE IMPORTAÇÃO SALVANDO EM ARQUIVO COM N

    void testeImportacaoArquivoN(fstream& arquivoEntrada,int n)
    {
        ofstream arquivoTeste("arquivoTesteComN.txt");
        int indice = 1+rand()%3660628;
        cout << "Escrevendo arquivo..." << endl;
        for(int i=0;i<n;i++)
        {
            Data dados = leituraBIN(indice,arquivoEntrada);
            arquivoTeste << "Review id: " << dados.getReviewId() << endl;
            arquivoTeste << "Review text: " << dados.getReviewText() << endl;
            arquivoTeste << "Upvotes: " << dados.getUpvotes() << endl;
            arquivoTeste << "App version: " << dados.getAppVersion() << endl;
            arquivoTeste << "Posted date: " << dados.getPostedDate() << endl;
            indice = 1+rand()%3660628;
        }
        cout << "Escrita finalizada." << endl;
    }
};

#endif // PROCESSAMENTO_H_INCLUDED