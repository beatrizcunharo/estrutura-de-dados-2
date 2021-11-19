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

    void leituraArquivoBIN(vector<Data> *dados, fstream& arquivoEntrada)
    {        
        // FAZER

        /*if(arquivoEntrada.is_open())
        {
            Data dadosLeitura;
            int contador = 0;
            while(!arquivoEntrada.eof())
            {
                string review_id;
                string review_text;
                int upvotes;
                string app_version;
                string posted_data;

                arquivoEntrada.read(reinterpret_cast<char*>(&dados), sizeof(string));
                cout << dados->at(0).getReviewId() << endl;
            }
        }*/
    }

    void escritaArquivo(vector<Data> dados)
    {
        fstream arquivoSaida("arquivos/tiktok_app_reviews.bin", ios::out | ios::binary);
        string virgula = ",";
        string espaco = "\n";

        // VERIFICA SE O ARQUIVO ESTÁ ABERTO

        if(arquivoSaida.is_open())
        {
            for(int i=0;i < dados.size(); i++) 
            {
                string upvotes = to_string(dados[i].getUpvotes());
                arquivoSaida.write(reinterpret_cast<const char*>(dados[i].getReviewId().c_str()), dados[i].getReviewId().length());
                arquivoSaida.write(reinterpret_cast<const char*>(virgula.c_str()), virgula.length());
                arquivoSaida.write(reinterpret_cast<const char*>(dados[i].getReviewText().c_str()), dados[i].getReviewText().length());
                arquivoSaida.write(reinterpret_cast<const char*>(virgula.c_str()), virgula.length());
                arquivoSaida.write(reinterpret_cast<const char*>(upvotes.c_str()), upvotes.length());
                arquivoSaida.write(reinterpret_cast<const char*>(virgula.c_str()), virgula.length());
                arquivoSaida.write(reinterpret_cast<const char*>(dados[i].getAppVersion().c_str()), dados[i].getAppVersion().length());
                arquivoSaida.write(reinterpret_cast<const char*>(virgula.c_str()), virgula.length());
                arquivoSaida.write(reinterpret_cast<const char*>(dados[i].getPostedDate().c_str()), dados[i].getPostedDate().length());
                arquivoSaida.write(reinterpret_cast<const char*>(espaco.c_str()), espaco.length());
            }
        }
    }

    void acessaRegistro(int indice, vector<Data> dados)
    {
        cout << "Review id: " << dados[indice].getReviewId() << endl;
        cout << "Review text: " << dados[indice].getReviewText() << endl;
        cout << "Upvotes: " << dados[indice].getUpvotes() << endl;
        cout << "App version: " << dados[indice].getAppVersion() << endl;
        cout << "Posted date: " << dados[indice].getPostedDate() << endl;
    }

    void testeImportacaoConsole(vector<Data> dados)
    {
        int indice = 1+rand()%3660628;

        for(int i=0;i<10;i++)
        {
            cout << "Review id: " << dados[indice].getReviewId() << endl;
            cout << "Review text: " << dados[indice].getReviewText() << endl;
            cout << "Upvotes: " << dados[indice].getUpvotes() << endl;
            cout << "App version: " << dados[indice].getAppVersion() << endl;
            cout << "Posted date: " << dados[indice].getPostedDate() << endl;
            indice = 1+rand()%3660628;
        }
        
    }

    void testeImportacaoArquivo(vector<Data> dados)
    {
        ofstream arquivoTeste("arquivos/arquivoTeste.txt");
        int indice = 1+rand()%3660628;
        cout << "Escrevendo arquivo..." << endl;
        for(int i=0;i<100;i++)
        {
            arquivoTeste << "Review id: " << dados[indice].getReviewId() << endl;
            arquivoTeste << "Review text: " << dados[indice].getReviewText() << endl;
            arquivoTeste << "Upvotes: " << dados[indice].getUpvotes() << endl;
            arquivoTeste << "App version: " << dados[indice].getAppVersion() << endl;
            arquivoTeste << "Posted date: " << dados[indice].getPostedDate() << endl;
            indice = 1+rand()%3660628;
        }
        cout << "Escrita finalizada." << endl;
    }

};

#endif // PROCESSAMENTO_H_INCLUDED