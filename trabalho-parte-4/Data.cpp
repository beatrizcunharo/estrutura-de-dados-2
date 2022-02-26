/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include <iostream>
#include <fstream>
#include "Data.h"
#include "Processamento.h"
#include <chrono>

using namespace std;

// CONSTRUTOR

Data::Data(string review_id, string review_text, int upvotes, string app_version, string posted_date) 
{
    this->review_id = review_id;
    this->review_text = review_text;
    this->upvotes = upvotes;
    this->app_version = app_version;
    this->posted_date = posted_date;
}

Data::Data() 
{
    // CONSTRUTOR VAZIO
}

// DESTRUTOR

Data::~Data() 
{
    this->review_id.clear();
    this->review_text.clear();
    this->app_version.clear();
    this->posted_date.clear();
}

// GETS

string Data::getReviewId() 
{
    return this->review_id;
}

string Data::getReviewText() 
{
    return this->review_text;
}

int Data::getUpvotes() 
{
    return this->upvotes;
}

string Data::getAppVersion() 
{
    return this->app_version;
}

string Data::getPostedDate() 
{
    return this->posted_date;
}

// SETS

void Data::setReviewId(string review_id) 
{
    this->review_id = review_id;
}

void Data::setReviewText(string review_text) 
{
    this->review_text = review_text;
}

void Data::setUpvotes(int upvotes) 
{
    this->upvotes = upvotes;
}

void Data::setAppVersion(string app_version) 
{
    this->app_version = app_version;
}

void Data::setPostedDate(string posted_date) 
{
    this->posted_date = posted_date;
}

void Data::escreveBinario(ofstream &arquivoBinario, ofstream &arquivoPosicoes) 
{
    cout << "Escrevendo arquivo binario..." << endl;
    int posicaoReview = arquivoBinario.tellp();
    Processamento::setString(arquivoBinario, this->review_id);
    Processamento::setString(arquivoBinario, this->review_text);
    arquivoBinario.write((char *) &this->upvotes, sizeof(int));
    Processamento::setString(arquivoBinario, this->app_version);
    Processamento::setString(arquivoBinario, this->posted_date);
    arquivoPosicoes.write((char *) &posicaoReview, sizeof(int));

    cout << "Escrita finalizada." << endl;
}
