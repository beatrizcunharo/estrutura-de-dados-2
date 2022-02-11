#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED

#include "No.h"

class Lista_Encadeada
{
    public:

        // CONSTRUTOR

        Lista_Encadeada()
        {
            primeiro = NULL;
        }

        // DESTRUTOR

        ~Lista_Encadeada()
        {
            No* p = primeiro;
            while(p != NULL)
            {
                No* t = p->getProx();
                delete p;
                p = t;
            }
        }

        // OUTRAS FUNÇÕES

        No* insereInicio(Data* val)
        {
            No* p = new No(); 
            p->setInfo(val); 
            p->setProx(primeiro); 
            primeiro = p; 
            return p;
        }

        No* busca(Data* val)
        {
            No* p;
            for(p = primeiro; p != NULL; p = p->getProx())
            {
                if(p->getInfo() == val){
                    return p;
                }
            }
            return NULL;
        }

        bool listaVazia()
        {
            if(primeiro == NULL) {
                    return true;
            }
                
            return false;
        }


    private:

        No* primeiro;
};
#endif // LISTA_ENCADEADA_H_INCLUDED