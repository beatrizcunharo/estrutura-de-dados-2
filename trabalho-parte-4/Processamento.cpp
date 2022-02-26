/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "Processamento.h"

void Processamento::processamento(ifstream &arquivoCSV, ofstream &arquivoBinario, ofstream &arquivoPosicoes) 
{
    cout << "Lendo arquivo csv e criando arquivo bin..." << endl;
    int qnt_linhas = 0;
    string linha = "";
    int colunaAtual;
    string *colunas;
    bool aspas;
    bool resposta;

    getline(arquivoCSV, linha, '\n');

    while (getline(arquivoCSV, linha, '\n')) {
        if (linha.size() > 0) {
            colunas = new string[5];
            aspas = false;
            colunaAtual = 0;

            resposta = buscarColunas(linha, colunas, aspas, colunaAtual);
            
            if (!resposta) {
                do {
                    getline(arquivoCSV, linha, '\n');
                    resposta = buscarColunas(linha, colunas, aspas, colunaAtual);
                } while (!resposta);
            }
            
            Data *dados = new Data(colunas[0], colunas[1], stoi(colunas[2]), colunas[3], colunas[4]);
            
            dados->escreveBinario(arquivoBinario, arquivoPosicoes);

            qnt_linhas++;

            delete [] colunas;
            delete dados;
        }
    }
    
    arquivoBinario.close();
    arquivoPosicoes.close();

    cout << "Processamento finalizado!" << endl;
}

bool Processamento::buscarColunas(string linha, string *colunas, bool &aspas, int &colunaAtual) 
{
    string dado = "";
    
    for (int i = 0; i < linha.size(); i++) {
        
        if (linha[i] == '"' && !aspas) {
            aspas = true;
        } else if (linha[i] == '"' && aspas) {
            aspas = false;
        }
       
        if (linha[i] == ',' && !aspas) {
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

void Processamento::setString(ofstream &arquivoBinario, string valor) 
{
    size_t tamanho = valor.size();
    arquivoBinario.write((char *) &tamanho, sizeof(tamanho));
    arquivoBinario.write(valor.c_str(), tamanho);
}

string Processamento::getString(ifstream &arquivoProcessado) 
{
    string review_text;
    string::size_type tamanho;
    
    arquivoProcessado.read((char *) &tamanho, sizeof(tamanho));
    review_text.resize(tamanho);
    arquivoProcessado.read(&review_text[0], tamanho);

    return review_text;
}

int Processamento::getQuantidadeData(ifstream &posicoesSalvas) 
{
    int quantidade = 0;
    posicoesSalvas.clear();
    posicoesSalvas.seekg(0, posicoesSalvas.end);
    int posicaoFinal = posicoesSalvas.tellg();
    quantidade = posicaoFinal / sizeof(int);

    return quantidade;
}

int Processamento::getPosicaoDataPeloReviewId(ifstream &posicoesSalvas, int id) 
{
    int posicaoData = -1;
    int posicaoCursor = (id - 1) * sizeof(int);

    posicoesSalvas.clear();
    posicoesSalvas.seekg(posicaoCursor, posicoesSalvas.beg);

    posicoesSalvas.read((char *) &posicaoData, sizeof(int));

    return posicaoData;
}

Data* Processamento::getDataPeloReviewId(ifstream &arquivoProcessado, ifstream &posicoesSalvas, int id) 
{
    int intAux;
    Data *data = new Data();
    int total = Processamento::getQuantidadeData(posicoesSalvas);

    if(id <= 0 || id > total) {
        return nullptr;
    }

    int posicao = Processamento::getPosicaoDataPeloReviewId(posicoesSalvas, id);

    if(posicao == -1) {
        return nullptr;
    }

    arquivoProcessado.clear();
    arquivoProcessado.seekg(posicao, arquivoProcessado.beg);

    while(arquivoProcessado.good()) {
        data->setReviewId(Processamento::getString(arquivoProcessado));
        data->setReviewText(Processamento::getString(arquivoProcessado));
        arquivoProcessado.read((char *) &intAux, sizeof(int));
        data->setUpvotes(intAux);
        data->setAppVersion(Processamento::getString(arquivoProcessado));
        data->setPostedDate(Processamento::getString(arquivoProcessado));

        return data;
    }

    return nullptr;
}

PonteiroData* Processamento::getData(ifstream &arquivo_processado, ifstream &posicoes_salvas, int n) {
    
    int quantidadeDados = Processamento::getQuantidadeData(posicoes_salvas);
    int intAleatorio;
    
    if(n <= quantidadeDados) {
        cout << "Importando dados..." << endl;
        
        PonteiroData* dados = new PonteiroData[n];
        
        for(int i = 0; i < n; i++) {
            
            intAleatorio = rand()%(quantidadeDados) + 1;
            dados[i] = Processamento::getDataPeloReviewId(arquivo_processado, posicoes_salvas, intAleatorio);
        }

        cout << "Importado com sucesso!" << endl;
        
        return dados;
    }
}

void Processamento::desalocarVetor(PonteiroData *reviews, int n) 
{
    for(int i = 0; i < n; i++) {
        delete reviews[i];
    }
    delete [] reviews;
}

PonteiroData* Processamento::getTodosOsDados(ifstream &arquivoProcessado, ifstream &posicoesSalvas) 
{
    cout << "Importando dados..." << endl;
    int tamanho = Processamento::getQuantidadeData(posicoesSalvas);

    PonteiroData* dados = new PonteiroData[tamanho];

    arquivoProcessado.clear();
    arquivoProcessado.seekg(0, arquivoProcessado.beg);

    int intAux = 0, idAtual = 0;

    while (arquivoProcessado.good() && idAtual < tamanho) {
        Data *data = new Data();
        data->setReviewId(Processamento::getString(arquivoProcessado));
        data->setReviewText(Processamento::getString(arquivoProcessado));
        arquivoProcessado.read((char *) &intAux, sizeof(int));
        data->setUpvotes(intAux);
        data->setAppVersion(Processamento::getString(arquivoProcessado));
        data->setPostedDate(Processamento::getString(arquivoProcessado));

        dados[idAtual] = data;

        idAtual++;
    }
    cout << "Importado com sucesso!" << endl;
    
    return dados;
}

int* Processamento::getTodasAsPosicoes(ifstream &posicoesSalvas) {
    int tamanho = Processamento::getQuantidadeData(posicoesSalvas);
    int* posicoes = new int[tamanho];

    posicoesSalvas.clear();
    posicoesSalvas.seekg(0, posicoesSalvas.beg);

    int posicaoDados = 0, idAtual = 0;

    while (posicoesSalvas.good() && idAtual < tamanho) {
        posicoesSalvas.read((char *) &posicaoDados, sizeof(int));
        posicoes[idAtual] = posicaoDados;
        idAtual++;
    }

    return posicoes;
}

PonteiroData* Processamento::getDadosAleatorios(PonteiroData *dados, int quantidade, int n) 
{
    cout << "Importando dados..." << endl;
    PonteiroData* menoresDados = new PonteiroData[n];

    int intAleatorio;
    for(int i = 0; i < n; i++) {
        intAleatorio = rand()%(quantidade) + 1;
        menoresDados[i] = dados[intAleatorio];
    }
    cout << "Importado com sucesso!" << endl;
   
    return menoresDados;
}

PonteiroData* Processamento::getDadosAleatoriosComPosicao(PonteiroData *dados, int *posicoes, int *posicoesData, int quantidade, int n) {
    cout << "Importando dados..." << endl;
    PonteiroData* menoresDados = new PonteiroData[n];

    int intAleatorio;
    for(int i = 0; i < n; i++) {
        intAleatorio = rand()%(quantidade) + 1;
        menoresDados[i] = dados[intAleatorio];
        posicoes[i] = posicoesData[intAleatorio];
    }
    cout << "Importado com sucesso!" << endl;
    return menoresDados;
}
