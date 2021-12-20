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
#include "Dados_Ordenacao.h"
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

    // FUNÇÃO DE TROCA
    template <typename T>
    void troca(T& a, T& b)
    {
        T aux = a;
        a = b;
        b = aux;
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

    // ORDENAÇÃO QUICKSORT

    void quickSort(vector<Data> *dados, int esquerda, int direita, Dados_Ordenacao* ordenacao)
    {
        int i,j;
        Data pivo, aux;
        i = esquerda;
        j = direita - 1;
        pivo = dados->at((esquerda + direita)/2);

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        while(i<=j)
        {
            ordenacao->incrementaComparacoes();
            while(dados->at(i).getUpvotes() < pivo.getUpvotes() && i < direita)
            {
                i++;
            }
            ordenacao->incrementaComparacoes();
            while(dados->at(j).getUpvotes() > pivo.getUpvotes() && j > esquerda)
            {
                j--;
            }
            if(i <= j)
            {
                aux = dados->at(i);
                dados->at(i) = dados->at(j);
                dados->at(j) = aux;
                i++;
                j--;
                ordenacao->incrementaMovimentacoes();
            }
        }

        if(j > esquerda)
        {
            quickSort(dados,esquerda,j+1, ordenacao);
        }
        if(i < direita)
        {
            quickSort(dados,i,direita, ordenacao);
        }
    }

    // ORDENAÇÃO HEAPSORT

    void heapify(vector<Data> *dados, int i, int n, Dados_Ordenacao *ordenacao)
    {
        while(i < n)
        {
            int filho = 2*i + 1;
            if(filho < n)
            {
                ordenacao->incrementaComparacoes();
                if(filho+1 < n && dados->at(filho+1).getUpvotes() > dados->at(filho).getUpvotes())
                    filho++;
                
                ordenacao->incrementaComparacoes();
                if(dados->at(filho).getUpvotes() > dados->at(i).getUpvotes())
                {
                    troca(dados->at(i), dados->at(filho));
                    ordenacao->incrementaMovimentacoes();
                }
            }

            i = filho;
        }

    }

    void constroiHeap(vector<Data> *dados, int n, Dados_Ordenacao *ordenacao)
    {
        for(int i = n/2-1; i >= 0; i--)
            heapify(dados, i, n, ordenacao);
    }

    void heapSortRec(vector<Data> *dados, int n, Dados_Ordenacao *ordenacao)
    {
        constroiHeap(dados, n, ordenacao);
        while(n > 0)
        {
            troca(dados->at(0), dados->at(n-1));
            ordenacao->incrementaMovimentacoes();
            heapify(dados, 0, n-1, ordenacao);
            n--;
        }
    }

    void heapSort(vector<Data> *dados, int n, Dados_Ordenacao *ordenacao)
    {
        heapSortRec(dados, n, ordenacao);
    }


    // ORDENAÇÃO COMBSORT
    
    void combSort(vector<Data> *dados, int execucoes)
    {
        // ARRUMAR
    }
    
};

#endif // PROCESSAMENTO_H_INCLUDED