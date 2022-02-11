#ifndef DADOS_HASH_H_INCLUDED
#define DADOS_HASH_H_INCLUDED

/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include <string>

using namespace std;

class Dados_Hash 
{
    public:

        // CONSTRUTOR

        Dados_Hash()
        {
            contagem = 0;
        }

        // DESTRUTOR

        ~Dados_Hash()
        {
            // DESTRUTOR VAZIO
        }

        // GETS

        string getAppVersion()
        {
            return app_version;
        }

        int getContagem()
        {
            return getContagem();
        }

        // SETS

        void setAppVersion(string app_version)
        {
            this->app_version = app_version;
        }

        void setContagem(int contagem)
        {
            this->contagem = contagem;
        }

        // OUTRAS FUNÇÕES

        void incrementa() 
        { 
            this->contagem++; 
        }

        void setDados(string app_version)
        {
            this->app_version = app_version;
            this->contagem = 0;
        }

    private:

        string app_version;
        int contagem;
};

#endif // DADOS_HASH_H_INCLUDED