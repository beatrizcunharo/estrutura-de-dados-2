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
        
        Data(string id, string text, int upvotes, string app_version, string posted_date);

        Data();

        // DESTRUTOR
  
        ~Data();

        // GETS E SETS

        string getReviewId();
        void setReviewId(string id);
        string getReviewText();
        void setReviewText(string text);
        int getUpvotes();
        void setUpvotes(int upvotes);
        string getAppVersion();
        void setAppVersion(string app_version);
        string getPostedDate();
        void setPostedDate(string posted_date);
        
        // OUTRAS FUNÇÕES
        
        void imprimir();

        void receberData(Data* data);

        void salvarData(ofstream &arquivoBIN, ofstream &arquivoPosicoes);

    private:

        string review_id;
        string review_text;
        int upvotes;
        string app_version;
        string posted_date;

};

#endif // DATA_H_INCLUDED