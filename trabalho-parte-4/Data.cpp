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
#include "Recuperar.h"
#include <chrono>

using namespace std;

Data::Data(string review_id, string review_text, int upvotes, string app_version, string posted_date) {
    this->review_id = review_id;
    this->review_text = review_text;
    this->upvotes = upvotes;
    this->app_version = app_version;
    this->posted_date = posted_date;
}

Data::Data() {}

Data::~Data() {
    this->review_id.clear();
    this->review_text.clear();
    this->app_version.clear();
    this->posted_date.clear();
}

string Data::getReviewId() {
    return this->review_id;
}

void Data::setReviewId(string review_id) {
    this->review_id = review_id;
}

string Data::getReviewText() {
    return this->review_text;
}

void Data::setReviewText(string review_text) {
    this->review_text = review_text;
}

int Data::getUpvotes() {
    return this->upvotes;
}

void Data::setUpvotes(int upvotes) {
    this->upvotes = upvotes;
}

string Data::getAppVersion() {
    return this->app_version;
}

void Data::setAppVersion(string app_version) {
    this->app_version = app_version;
}

string Data::getPostedDate() {
    return this->posted_date;
}

void Data::setPostedDate(string posted_date) {
    this->posted_date = posted_date;
}

void Data::imprimir() {
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "Id: " << this->review_id << endl;
    cout << "Text: " << this->review_text << endl;
    cout << "Upvotes: " << to_string(this->upvotes) << endl;
    cout << "Version: " << this->app_version << endl;
    cout << "Date: " << this->posted_date << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

void Data::receberData(Data* data) {
    
    this->review_id = data->review_id;
    this->review_text = data->review_text;
    this->upvotes = data->upvotes;
    this->app_version = data->app_version;
    this->posted_date = data->posted_date;
}

void Data::salvarData(ofstream &arquivoBIN, ofstream &arquivoPosicoes) {
   
    int posicaoDados = arquivoBIN.tellp();
    
    Recuperar::salvarString(arquivoBIN, this->review_id);
    Recuperar::salvarString(arquivoBIN, this->review_text);
    arquivoBIN.write((char *) &this->upvotes, sizeof(int));
    Recuperar::salvarString(arquivoBIN, this->app_version);
    Recuperar::salvarString(arquivoBIN, this->posted_date);
    
    arquivoPosicoes.write((char *) &posicaoDados, sizeof(int));
}