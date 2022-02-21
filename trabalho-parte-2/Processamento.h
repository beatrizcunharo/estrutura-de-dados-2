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
#include "Dados_Hash.h"
#include "Hash.h"

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

    // LEITURA ARQUIVO .DAT

    vector<int> leituraDAT()
    {
        ifstream arquivoEntrada("input.dat");

        vector<int> valores;

        int valor = 0;

        string linha;

        if(!arquivoEntrada.is_open())
        {
            cout << "Erro. Recuperar não pode ser aberto." << endl;
            exit(1);
        }

        while(!arquivoEntrada.eof())
        {
            getline(arquivoEntrada, linha, '\n');
            valor = stoi (linha);
            linha.clear();

            valores.push_back(valor);
        }

        return valores;
    }

    // FUNÇÃO DE TROCA
    template <typename T>
    void troca(T& a, T& b)
    {
        T aux = a;
        a = b;
        b = aux;
    }

    // LEITURA BINÁRIA INDIVIDUAL

    Data leituraBinIndividual(int indice, fstream& arquivoEntrada)
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

    void quickSort(vector<Data> *dados, int esquerda, int direita, Dados_Ordenacao *ordenacao)
    {
        int i,j;
        Data pivo, aux;
        i = esquerda;
        j = direita - 1;
        pivo = dados->at((esquerda + direita)/2);

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
            int indice = 2 * i + 1;
            if(indice < n)
            {
                ordenacao->incrementaComparacoes();
                if(indice+1 < n && dados->at(indice+1).getUpvotes() > dados->at(indice).getUpvotes())
                    indice++;
                
                ordenacao->incrementaComparacoes();
                if(dados->at(indice).getUpvotes() > dados->at(i).getUpvotes())
                {
                    troca(dados->at(i), dados->at(indice));
                    ordenacao->incrementaMovimentacoes();
                }
            }

            i = indice;
        }

    }

    void heapSort(vector<Data> *dados, int n, Dados_Ordenacao *ordenacao)
    {
        for(int i = n/2-1; i >= 0; i--)
            heapify(dados, i, n, ordenacao);
        while(n > 0)
        {
            troca(dados->at(0), dados->at(n-1));
            ordenacao->incrementaMovimentacoes();
            heapify(dados, 0, n-1, ordenacao);
            n--;
        }
    }

    // ORDENAÇÃO HEAPSORT HASH

    void heapifyHash(vector<Dados_Hash> *dados, int i, int n)
    {
        while(i < n)
        {
            int indice = 2 * i + 1;
            if(indice < n)
            {
                if(indice+1 < n && dados->at(indice+1).getContagem() > dados->at(indice).getContagem())
                    indice++;
                
                if(dados->at(indice).getContagem() > dados->at(i).getContagem())
                {
                    troca(dados->at(i), dados->at(indice));
                }
            }

            i = indice;
        }

    }

    void heapSortHash(vector<Dados_Hash> *dados, int n)
    {
        for(int i = n/2-1; i >= 0; i--)
            heapifyHash(dados, i, n);
        while(n > 0)
        {
            troca(dados->at(0), dados->at(n-1));
            heapifyHash(dados, 0, n-1);
            n--;
        }
    }


    // ORDENAÇÃO COMBSORT

    int acharGap(int gap)
    {
        gap = (gap*10)/13;
    
        if (gap < 1)
            return 1;
        return gap;
    }
    
    void combSort(vector<Data> *dados, int n, Dados_Ordenacao *ordenacao)
    {
        int gap = n;

        bool trocado = true;

        while (gap != 1 || trocado == true)
        {
            gap = acharGap(gap);
        
            trocado = false;
        
            for (int i=0; i<n-gap; i++)
            {
                ordenacao->incrementaComparacoes();
                if (dados->at(i).getUpvotes() > dados->at(i+gap).getUpvotes())
                {
                    troca(dados->at(i), dados->at(i+gap));
                    trocado = true;
                    ordenacao->incrementaMovimentacoes();
                }
            }
        }
    }

    void imprimirOrdenacao(vector<Data> dados)
    {
        for(int i=0; i < dados.size(); i++)
        {
            cout << "Review id: " << dados.at(i).getReviewId() << endl;
            cout << "Review text: " << dados.at(i).getReviewText() << endl;
            cout << "Upvotes: " << dados.at(i).getUpvotes() << endl;
            cout << "App version: " << dados.at(i).getAppVersion() << endl;
            cout << "Posted date: " << dados.at(i).getPostedDate() << endl;
        }
    }

    // ORDENAÇÃO COMBSORT HASH

    // ORDENAÇÃO COMBSORT
    
    void combSortHash(int vetor[], int n)
    {
        int gap;
        bool trocar;
        int comparar, qnt_troca, troque;

        gap = n;

        trocar = true;
        comparar = 0;
        qnt_troca = 0;

        while (gap != 1 || trocar == true)
        {
            gap = acharGap(gap);

            trocar = false;
            troque = 0;

            for (int i = 0; i < n - gap; i++)
            {
                if (vetor[i] > vetor[i + gap])
                {
                    comparar += 1;
                    swap(vetor[i], vetor[i + gap]);
                    trocar = true;
                    troque = 1;
                    qnt_troca += troque;
                }
            }
        } 
    }

    // PROCESSAMENTO HASH

    void processamentoHash(vector<Data> &dados, int tamanho, int M)
    {
        Hash hash(tamanho);

        int posicao = rand() % 3660628;

        for (int i = 0; i < tamanho; i++)
        {
            hash.insere(&dados[posicao]);
            posicao = rand() % 3660628;
        }
    }
    
};

#endif // PROCESSAMENTO_H_INCLUDED