#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "Dados_Hash.h"
#include "Data.h"
#include "Processamento.h"
#include "Lista_Encadeada.h"

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

using namespace std;

class Hash
{

    public:

        // CONSTRUTOR

        Hash(long long int tamanho)
        {
            this->tamanho = tamanho;
            registros = new Lista_Encadeada* [tamanho];
            for(int i=0; i < tamanho; i++){
                registros[i] = new Lista_Encadeada();
            }
        }

        // DESTRUTOR

        virtual ~Hash()
        {
            for(int i=0; i < tamanho; i++){
                delete registros[i];
            }
            delete [] registros;
        }

        // OUTRAS FUNÇÕES

        string substituirPontos(std::string string, const std::string& atual, const std::string& proximo) {
        
            size_t posicaoInicial = 0;
                
            while((posicaoInicial = string.find(atual, posicaoInicial)) != std::string::npos) { // o algoritmo procura o char atual de acordo com a posição 
                // quando encontrado, ele substitui para o próximo (o char a ser substituido)
                
                string.replace(posicaoInicial, atual.length(), proximo);
                // incrementa para a próxima posição
                posicaoInicial += proximo.length();
            }
            return string;
        }

        int funcaoHash(string app_review)
        {
            string versao_app = substituirPontos(app_review, ".", "");
            int app_convertido = stol(versao_app);
            int chave = app_convertido % this->tamanho; 
            return chave;
        }


        void insere(Data* data)
        {
            int index = funcaoHash(data->getAppVersion());
            No* elemento;
            elemento = registros[index]->busca(data);

            if(elemento == NULL) {
                elemento = registros[index]->insereInicio(data);
            }
        }

        No* busca(Data* data)
        {
            No* elemento;
            int index = funcaoHash(data->getAppVersion());

            elemento = registros[index]->busca(data);
            return elemento;
        }


    private:
        long long int tamanho;
        Lista_Encadeada** registros;
        
};

#endif // HASH_H_INCLUDED