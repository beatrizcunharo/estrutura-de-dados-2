#ifndef DADOS_HASH_H_INCLUDED
#define DADOS_HASH_H_INCLUDED

#include <string>

using namespace std;

class Dados_Hash 
{
    public:

        Dados_Hash()
        {
            app_version = "";
            contagem = 0;
        }

        ~Dados_Hash()
        {
            // DESTRUTOR VAZIO
        }

        // GETS E SETS

        void setAppVersion(string app_version)
        {
            this->app_version = app_version;
        }

        void setContagem(int contagem)
        {
            this->contagem = contagem;
        }

        string getAppVersion()
        {
            return app_version;
        }

        int getContagem()
        {
            return getContagem();
        }

    private:

        string app_version;
        int contagem;
};

#endif // DADOS_HASH_H_INCLUDED