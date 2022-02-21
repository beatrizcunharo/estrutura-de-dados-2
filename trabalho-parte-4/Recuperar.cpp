/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "Recuperar.h"

void Recuperar::processamento(ifstream &arquivoCSV, ofstream &arquivoBIN, ofstream &arquivoPosicoes) {
    
    cout << "Importando dados e criando arquivo .bin" << endl;

    int qnt_linhas = 0;
    string linha = "";
    int colunaAtual;
    string *colunas;
    bool entreAspas;
    bool resposta;

    getline(arquivoCSV, linha, '\n');

    while (getline(arquivoCSV, linha, '\n')) {

        if (linha.size() > 0) {
            colunas = new string[5];
            entreAspas = false;
            colunaAtual = 0;

            resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
            
            if (!resposta) {
                do {
                    getline(arquivoCSV, linha, '\n');
                    resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
                } while (!resposta);
            }
            
            Data *dados_review = new Data(colunas[0], colunas[1], stoi(colunas[2]), colunas[3], colunas[4]);

            dados_review->salvarData(arquivoBIN, arquivoPosicoes);

            qnt_linhas++;

            delete [] colunas;
            delete dados_review;
        }
    }
    
    arquivoBIN.close();
    arquivoPosicoes.close();

    cout << "Processamento finalizado!" << endl;
}

bool Recuperar::buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual) {
    
    string dado = "";
    
    for (int i = 0; i < linha.size(); i++) {
        
        if (linha[i] == '"' && !entreAspas) {
            entreAspas = true;
        } else if (linha[i] == '"' && entreAspas) {
            
            entreAspas = false;
        }
        
        if (linha[i] == ',' && !entreAspas) {
            
            colunas[colunaAtual] += dado;
            
            dado = "";
            
            colunaAtual++;
        } else {
            
            dado += linha[i];
        }
        
        if (colunaAtual == 4) {
            
            dado = "";
            
            for (int j = linha.size(); j > 0; j--) {
                
                if (linha[j] == ',') {
                    colunas[colunaAtual] += dado;
                    
                    return true;
                }
                
                dado = linha[j] + dado;
            }
            break;
        }
        
        if (i == linha.size() - 1) {
            colunas[colunaAtual] += dado;
            break;
        }
    }
    return false;
}

void Recuperar::salvarString(ofstream &arquivoBIN, string valor) {
    
    size_t tamanho = valor.size();
    
    arquivoBIN.write((char *) &tamanho, sizeof(tamanho));
    
    arquivoBIN.write(valor.c_str(), tamanho);
}

string Recuperar::getString(ifstream &arquivoProcessado) {
    
    string texto;
    string::size_type tamanho;
    
    arquivoProcessado.read((char *) &tamanho, sizeof(tamanho));
    
    texto.resize(tamanho);
    arquivoProcessado.read(&texto[0], tamanho);

    return texto;
}

int Recuperar::getQuantidadeDados(ifstream &posicoes_salvas) {
   
    int quantidade = 0;
   
    posicoes_salvas.clear();
    posicoes_salvas.seekg(0, posicoes_salvas.end);
 
    int posicaoFinal = posicoes_salvas.tellg();

    quantidade = posicaoFinal / sizeof(int);

    return quantidade;
}

int Recuperar::getPosicaoDadosPeloId(ifstream &posicoes_salvas, int id) {
   
    int posicaoDados = -1;
    int posicaoCursor = (id - 1) * sizeof(int);
    
    posicoes_salvas.clear();
    posicoes_salvas.seekg(posicaoCursor, posicoes_salvas.beg);

    posicoes_salvas.read((char *) &posicaoDados, sizeof(int));

    return posicaoDados;
}

Data* Recuperar::getDadosPeloId(ifstream &arquivoProcessado, ifstream &posicoes_salvas, int id) {
    int intAux;
    Data *dados_review = new Data();

    int total = Recuperar::getQuantidadeDados(posicoes_salvas);

    if(id <= 0 || id > total) {
        return nullptr;
    }

    int posicao = Recuperar::getPosicaoDadosPeloId(posicoes_salvas, id);

    if(posicao == -1) {
        return nullptr;
    }

    arquivoProcessado.clear();
    arquivoProcessado.seekg(posicao, arquivoProcessado.beg);

    while(arquivoProcessado.good()) {

        dados_review->setReviewId(Recuperar::getString(arquivoProcessado));
        dados_review->setReviewText(Recuperar::getString(arquivoProcessado));
        arquivoProcessado.read((char *) &intAux, sizeof(int));
        dados_review->setUpvotes(intAux);
        dados_review->setAppVersion(Recuperar::getString(arquivoProcessado));
        dados_review->setPostedDate(Recuperar::getString(arquivoProcessado));

        return dados_review;
    }

    return nullptr;
}

DataPonteiro* Recuperar::getDadosAleatorios(ifstream &arquivoProcessado, ifstream &posicoes_salvas, int n) {
    
    int qntDados = Recuperar::getQuantidadeDados(posicoes_salvas);
    
    int intAleatorio;

    if(n <= qntDados) {
        cout << "Importando dados do arquivo .bin..." << endl;
        
        DataPonteiro* dados_review = new DataPonteiro[n];
        
        for(int i = 0; i < n; i++) {
            
            intAleatorio = rand()%(qntDados) + 1;
            
            dados_review[i] = Recuperar::getDadosPeloId(arquivoProcessado, posicoes_salvas, intAleatorio);
        }

        return dados_review;
    }
}

DataPonteiro* Recuperar::getTodosDados(ifstream &arquivoProcessado, ifstream &posicoes_salvas) {
    
    int tamanho = Recuperar::getQuantidadeDados(posicoes_salvas);

    DataPonteiro* dados_review = new DataPonteiro[tamanho];

    arquivoProcessado.clear();
    arquivoProcessado.seekg(0, arquivoProcessado.beg);

    int intAux = 0, idAtual = 0;

    while (arquivoProcessado.good() && idAtual < tamanho) {
        
        Data *dados = new Data();
        dados->setReviewId(Recuperar::getString(arquivoProcessado));
        dados->setReviewText(Recuperar::getString(arquivoProcessado));
        arquivoProcessado.read((char *) &intAux, sizeof(int));
        dados->setUpvotes(intAux);
        dados->setAppVersion(Recuperar::getString(arquivoProcessado));
        dados->setPostedDate(Recuperar::getString(arquivoProcessado));

        dados_review[idAtual] = dados;

        idAtual++;
    }
    
    return dados_review;
}

int* Recuperar::getTodasPosicoes(ifstream &posicoes_salvas) {
    int tamanho = Recuperar::getQuantidadeDados(posicoes_salvas);

    int* posicoes = new int[tamanho];

    posicoes_salvas.clear();
    posicoes_salvas.seekg(0, posicoes_salvas.beg);

    int posicaoDados = 0, idAtual = 0;

    while (posicoes_salvas.good() && idAtual < tamanho) {
        posicoes_salvas.read((char *) &posicaoDados, sizeof(int));
        posicoes[idAtual] = posicaoDados;
        idAtual++;
    }

    return posicoes;
}

DataPonteiro* Recuperar::getDadosAleatoriosDoVetor(DataPonteiro *dados_review, int quantidade, int n) {
    
    DataPonteiro* dadosMenor = new DataPonteiro[n];

    int intAleatorio;
    for(int i = 0; i < n; i++) {
        intAleatorio = rand()%(quantidade) + 1;
        dadosMenor[i] = dados_review[intAleatorio];
    }
    return dadosMenor;
}

DataPonteiro* Recuperar::getDadosAleatoriosDoVetorComPosicao(DataPonteiro *dados_review, int *posicoes, int *posicoesReviews, int quantidade, int n) {
    
    DataPonteiro* dadosMenor = new DataPonteiro[n];

    int intAleatorio;
    for(int i = 0; i < n; i++) {
        intAleatorio = rand()%(quantidade) + 1;
        dadosMenor[i] = dados_review[intAleatorio];
        posicoes[i] = posicoesReviews[intAleatorio];
    }
    
    return dadosMenor;
}
