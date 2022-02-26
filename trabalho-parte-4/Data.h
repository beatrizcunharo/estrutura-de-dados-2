/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <string>

using namespace std;

class Data 
{

    public:
        
        // CONSTRUTOR

        Data(string review_id, string review_text, int upvotes, string app_version, string posted_date);
        
        // CONSTRUTOR SEM INICIALIZAÇÃO

        Data();
        
        // DESTRUTOR

        ~Data();

        // GETS

        string getReviewId();
        string getReviewText();
        int getUpvotes();
        string getAppVersion();
        string getPostedDate();

        // SETS

        void setReviewId(string review_id);
        void setReviewText(string review_text);
        void setUpvotes(int upvotes);
        void setAppVersion(string app_version);
        void setPostedDate(string posted_date);
        
        // OUTRAS FUNÇÕES

        void escreveBinario(ofstream &arquivoBinario, ofstream &arquivoPosicoes);

    private:
        
        string review_id;
        string review_text;
        int upvotes;
        string app_version;
        string posted_date;
};

#endif // DATA_H_INCLUDED