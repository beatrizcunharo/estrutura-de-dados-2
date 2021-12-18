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

    // LEITURA ARQUIVO .DAT

    int leituraDAT()
    {
        ifstream arquivoEntrada("input.dat");
        string nString;
        if(arquivoEntrada.is_open())
        {
            getline(arquivoEntrada, nString);
        }
        int nInt = stoi (nString);
        return nInt;
    }


    // LEITURA BINÁRIA

    void leituraBIN(vector<Data> *dados, char *argv[], int n)
    {
        fstream arquivoEntrada(argv[1], ios::in | ios::binary);
        Data data;
        if(arquivoEntrada.is_open())
        {
            for(int i=0; i< n; i++)
            {
                arquivoEntrada.seekg((i)*(320+sizeof(int)));
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

                data.setReviewId(review_id);
                data.setReviewText(review_text);
                data.setUpvotes(upvotes);
                data.setAppVersion(app_version);
                data.setPostedDate(posted_data);

                dados->push_back(data);

            }
        }
        else
        {
            cout << "Erro. O arquivo não pode ser aberto." << endl;
            exit(1);
        }
        arquivoEntrada.close();
    }
};

#endif // PROCESSAMENTO_H_INCLUDED