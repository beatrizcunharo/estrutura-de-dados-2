#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include "Data.h"
using namespace std;

class No
{
    public:

        // CONSTRUTOR

        No()
        {
            // CONSTRUTOR VAZIO
        }

        // DESTRUTOR

        ~No()
        {
            // DESTRUTOR VAZIO
        }

        // GETS

        Data* getInfo()
        {
            return this->info;
        }

        No* getProx()
        {
            return this->prox;
        }

        //SETS

        void setInfo(Data* val)
        {
            this->info = val;
        }

        void setProx(No* p)
        {
            this->prox = p;
        }

    private:

        Data *info;
        No* prox;
}; 
#endif // NO_H_INCLUDED