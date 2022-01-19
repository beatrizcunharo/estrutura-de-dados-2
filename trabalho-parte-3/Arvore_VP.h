/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef ARVORE_VP_H_INCLUDED
#define ARVORE_VP_H_INCLUDED
#include <bits/stdc++.h>
#include "No_VP.h"

class Arvore_VP
{
    protected:

        void girarEsquerda(No_VP *&raiz, No_VP *&ponteiro)
        {
            No_VP *ponteiroDireita = ponteiro->direita;
 
            ponteiro->direita = ponteiroDireita->esquerda;
        
            if (ponteiro->direita != NULL)
                ponteiro->direita->parente = ponteiro;
        
            ponteiroDireita->parente = ponteiro->parente;
        
            if (ponteiro->parente == NULL)
                raiz = ponteiroDireita;
        
            else if (ponteiro == ponteiro->parente->esquerda)
                ponteiro->parente->esquerda = ponteiroDireita;
        
            else
                ponteiro->parente->direita = ponteiroDireita;
        
            ponteiroDireita->esquerda = ponteiro;
            ponteiro->parente = ponteiroDireita;
        }

        void girarDireita(No_VP *&raiz, No_VP *&ponteiro)
        {
            No_VP *ponteiroEsquerda = ponteiro->esquerda;
 
            ponteiro->esquerda = ponteiroEsquerda->direita;
        
            if (ponteiro->esquerda != NULL)
                ponteiro->esquerda->parente = ponteiro;
        
            ponteiroEsquerda->parente = ponteiro->parente;
        
            if (ponteiro->parente == NULL)
                raiz = ponteiroEsquerda;
        
            else if (ponteiro == ponteiro->parente->esquerda)
                ponteiro->parente->esquerda = ponteiroEsquerda;
        
            else
                ponteiro->parente->direita = ponteiroEsquerda;
        
            ponteiroEsquerda->direita = ponteiro;
            ponteiro->parente = ponteiroEsquerda;
        }

        void arrumaArvore(No_VP *&raiz, No_VP *&ponteiro)
        {
            No_VP *ponteiroParente = NULL;
            No_VP *ponteiroAvo = NULL;
        
            while ((ponteiro != raiz) && (ponteiro->cor != BLACK) && (ponteiro->parente->cor == RED))
            {
                ponteiroParente = ponteiro->parente;
                ponteiroAvo = ponteiro->parente->parente;
        
                if (ponteiroParente == ponteiroAvo->esquerda)
                {
                    No_VP *ponteiroTio = ponteiroAvo->direita;
       
                    if (ponteiroTio != NULL && ponteiroTio->cor == RED)
                    {
                        ponteiroAvo->cor = RED;
                        ponteiroParente->cor = BLACK;
                        ponteiroTio->cor = BLACK;
                        ponteiro = ponteiroAvo;
                    }
        
                    else
                    {
                        if (ponteiro == ponteiroParente->direita)
                        {
                            girarEsquerda(raiz, ponteiroParente);
                            ponteiro = ponteiroParente;
                            ponteiroParente = ponteiro->parente;
                        }
        
                        girarDireita(raiz, ponteiroAvo);
                        swap(ponteiroParente->cor, ponteiroAvo->cor);
                        ponteiro = ponteiroParente;
                    }
                }
                else
                {
                    No_VP *ponteiroTio = ponteiroAvo->esquerda;
        
                    if ((ponteiroTio != NULL) && (ponteiroTio->cor == RED))
                    {
                        ponteiroAvo->cor = RED;
                        ponteiroParente->cor = BLACK;
                        ponteiroTio->cor = BLACK;
                        ponteiro = ponteiroAvo;
                    }
                    else
                    {
                        if (ponteiro == ponteiroParente->esquerda)
                        {
                            girarDireita(raiz, ponteiroParente);
                            ponteiro = ponteiroParente;
                            ponteiroParente = ponteiro->parente;
                        }
        
                        girarEsquerda(raiz, ponteiroAvo);
                        swap(ponteiroParente->cor,
                                ponteiroAvo->cor);
                        ponteiro = ponteiroParente;
                    }
                }
            }
        
            raiz->cor = BLACK;
        }

    public:

        // CONSTRUTOR

        Arvore_VP()
        { 
            raiz = NULL;
        }

        // DESTRUTOR
        
        ~Arvore_VP()
        {
            // DESTRUTOR VAZIO
        }

        void inserir(string review_id, long long int localizacao)
        {
            No_VP *ponteiro = new No_VP(review_id, localizacao);
        
            raiz = auxInserir(raiz, ponteiro);
        
            arrumaArvore(raiz, ponteiro);
        }

        No_VP* auxInserir(No_VP* raiz, No_VP *ponteiro)
        {
            if (raiz == NULL)
                return ponteiro;
        
            if (ponteiro->review_id < raiz->review_id)
            {
                raiz->esquerda  = auxInserir(raiz->esquerda, ponteiro);
                raiz->esquerda->parente = raiz;
            }
            else if (ponteiro->review_id > raiz->review_id)
            {
                raiz->direita = auxInserir(raiz->direita, ponteiro);
                raiz->direita->parente = raiz;
            }
        
            return raiz;
        }

        No_VP *busca(string chave)
        {
            return auxBusca(this->raiz, chave);
        }

        No_VP *auxBusca(No_VP *n, string chave)
        {
        if (n == NULL || chave == n->review_id) {
                return n;
            }
            if (chave < n->review_id) {
                return auxBusca(n->esquerda, chave);
            } 
            return auxBusca(n->direita, chave);
        }
        
    private:

        No_VP *raiz;

};
#endif // ARVORE_VP_H_INCLUDED