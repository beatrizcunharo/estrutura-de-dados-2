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
#include <vector>
#include <iostream>

using namespace std;

class Data 
{
    public:

    // CONSTRUTOR
        Data(){}

    // DESTRUTOR
        ~Data(){}

    // GETS

        string getReviewId()
        {
            return this->review_id;
        }
        string getReviewText()
        {
            return this->review_text;
        }
        int getUpvotes()
        {
            return this->upvotes;
        }
        string getAppVersion()
        {
            return this->app_version;
        }
        string getPostedDate()
        {
            return this->posted_date;
        }
    
    // SETS

        void setReviewId(string review_id)
        {
            this->review_id = review_id;
        }
        void setReviewText(string review_text)
        {
            this->review_text = review_text;
        }
        void setUpvotes(int upvotes)
        {
            this->upvotes = upvotes;
        }
        void setAppVersion(string app_version)
        {
            this->app_version = app_version;
        }
        void setPostedDate(string posted_date)
        {
            this->posted_date = posted_date;
        }

    // OUTRAS FUNÇÕES

        void impressao()
        {
            cout << review_id << ',';
            cout << review_text << ',';
            cout << upvotes << ',';
            cout << app_version << ',';
            cout << posted_date << ',';
        }
        
    private: 

        string review_id;
        string review_text;
        int upvotes;
        string app_version;
        string posted_date;
};

#endif //DATA_H_INCLUDED