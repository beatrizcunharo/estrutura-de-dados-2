/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef NOB_H_INCLUDED
#define NOB_H_INCLUDED
#include <iostream>
#include <string>
#include "Dados_Arvore.h"

using namespace std;
class NoB
{
    public:

        // CONSTRUTOR

        NoB(int grau_minimo, bool folha, int nos)
        {
            this->chaves = new Dados_Arvore *[2 * grau_minimo - 1];
            this->grau_minimo = grau_minimo;
            this->filhos = new NoB * [ 2 * grau_minimo];
            this->nos = nos;
            this->folha = folha;
            this->n = 0;
        }

        NoB();
        
        // DESTRUTOR

        ~NoB();

        // GETS

        Dados_Arvore **getChaves()
        {
            return this->chaves;
        }

        int getGrauMinimo()
        {
            return this->grau_minimo;
        }

        int getNos()
        {
            return this->nos;
        }

        NoB **getFilhos()
        {
            return this->filhos;
        }

        bool isFolha()
        {
            return this->folha;
        }

        // SETS

        void setChaves(string review_id, long localizacao, int posicao)
        {
            this->chaves[posicao]->setReview_Id(review_id);
            this->chaves[posicao]->setLocalizacao(localizacao);
        }
        
        void setChaves(Dados_Arvore **chaves)
        {
            this->chaves = chaves;
        }

        void setGrauMinimo(int grau_minimo)
        {
            this->grau_minimo = grau_minimo;
        }

        void setNos(int nos)
        {
            this->nos = nos;
        }

        void setFolha(bool folha)
        {
            this->folha = folha;
        }

        void setFilhos(NoB **filhos)
        {
            this->filhos = filhos;
        }

        // OUTRAS FUNÇÕES

        void percorreNo()
        {
            int i=0;
            for(i=0;i<n;i++)
            {
                if(!folha)
                    filhos[i]->percorreNo();

                cout << " " << chaves[i];
            }

            if(!folha)
                filhos[i]->percorreNo();
        }
        
        NoB *procura(string review_id)
        {
            int i = 0;
            while (i < n && review_id > chaves[i]->getReview_Id())
                i++;

            if (chaves[i]->getReview_Id() == review_id)
            {
                return this;
            }

            if (folha == true)
                return nullptr;

            return filhos[i]->procura(chaves[i]->getReview_Id());
        }

        void divideFilho(int i, NoB *no)
        {
            NoB *novoNo = new NoB(no->grau_minimo, no->folha, no->nos);
            novoNo->n = grau_minimo - 1;
        
            for (int j = 0; j < grau_minimo - 1; j++)
                novoNo->chaves[j] = no->chaves[ j + grau_minimo];
        
            if (!no->folha) {
                for (int j = 0; j < grau_minimo; j++)
                    novoNo->filhos[j] = no->filhos[ j + grau_minimo];
            }

            no->n = grau_minimo - 1;

            for (int j = n; j >= i+1; j--)
                filhos[ j + 1 ] = filhos[j];
        
            filhos[i+1] = novoNo;
        
            for (int j = n-1; j >= i; j--)
                chaves[j+1] = chaves[j];
        
            chaves[i] = no->chaves[grau_minimo - 1];

            n = n + 1;
        }

        void insereEspacado(string review_id, long localizacao)
        {
            Dados_Arvore* dados = new Dados_Arvore();
            dados->setReview_Id(review_id);
            dados->setLocalizacao(localizacao);
            
            int i = n-1;

            if (folha) {

                while (i >= 0 && chaves[i]->getReview_Id() > review_id) {
                    chaves[i+1] = chaves[i];
                    i--;
                }
                chaves[i+1] = dados;
                n = n+1;
            }
            else 
            {
                while (i >= 0 && chaves[i]->getReview_Id() > review_id)
                    i--;
        
                if (filhos[i+1]->n == nos) {
                    divideFilho(i+1, filhos[i+1]);
        
                    if (chaves[i+1]->getReview_Id() < review_id)
                        i++;
                }
                filhos[i+1]->insereEspacado(review_id, localizacao);
            }
        }
        
        friend class ArvoreB;        

        private:

            Dados_Arvore **chaves; 

            int grau_minimo;     
            int n;             
            NoB **filhos;   
            int nos;
            bool folha; 
};
#endif // NOB_H_INCLUDED