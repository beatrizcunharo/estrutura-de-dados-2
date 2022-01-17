/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef NO_B_H_INCLUDED
#define NO_B_H_INCLUDED

#include <iostream>
#include "Dados_B.h"
#include "Arvore_B.h"

using namespace std;

class No_B
{
	public:

		// CONSTRUTOR
		No_B(int t, bool _folha)
		{
			grau_minimo = t;
			folha = _folha;

			chaves = new Dados_B[2 * grau_minimo - 1];
			filhos = new No_B *[2 * grau_minimo];
			nos = 0;
		}

		// DESTRUTOR
		~No_B()
		{

			delete[] chaves;
			delete[] filhos;
		}

		void divideFilho(int i, No_B *no)
		{

			No_B *aux = new No_B(no->grau_minimo, no->folha);
			aux->nos = grau_minimo - 1;

			for (int j = 0; j < grau_minimo - 1; j++)
			{
				aux->chaves[j] = no->chaves[j + grau_minimo];
			}

			if (no->folha == false)
			{
				for (int j = 0; j < grau_minimo; j++)
					aux->filhos[j] = no->filhos[j + grau_minimo];
			}

			no->nos = grau_minimo - 1;

			for (int j = nos; j >= i + 1; j--)
			{
				filhos[j + 1] = filhos[j];
			}

			filhos[i + 1] = aux;

			for (int j = nos - 1; j >= i; j--)
			{
				chaves[j + 1] = chaves[j];
			}

			chaves[i] = no->chaves[grau_minimo - 1];

			nos = nos + 1;
		}

		void inserirNaoCheio(Dados_B no)
		{
			int i = nos - 1;

			if (folha == true)
			{
				while (i >= 0 && chaves[i].getReviewId() > no.getReviewId())
				{
					chaves[i + 1] = chaves[i];
					i--;
				}

				chaves[i + 1] = no;
				nos = nos + 1;
			}
			else
			{
				while (i >= 0 && chaves[i].getReviewId() > no.getReviewId())
				{
					i--;
				}

				if (filhos[i + 1]->nos == 2 * grau_minimo - 1)
				{
					divideFilho(i + 1, filhos[i + 1]);

					if (chaves[i + 1].getReviewId() < no.getReviewId())
					{
						i++;
					}
				}
				filhos[i + 1]->inserirNaoCheio(no);
			}
		}

		No_B *busca(string review_id)
		{
			int i = 0;
			while (i < nos && review_id > chaves[i].getReviewId()){
				i++;
			}

			if (chaves[i].getReviewId() == review_id)
				return this;

			if (folha == true)
				return NULL;

			return filhos[i]->busca(review_id);
		}
		
	friend class Arvore_B;

	private:
		int grau_minimo;
		No_B **filhos;
		int nos;
		bool folha;
		Dados_B *chaves;
};

#endif // NO_B_H_INCLUDED