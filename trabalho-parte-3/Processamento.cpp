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
    cout << "Lendo arquivo .csv e transformando em binario..." << endl;
    int quantidadeLinhas = 0;
    string linha = "";
    int colunaAtual;
    string *colunas;
    bool entreAspas;
    bool resposta;

    getline(arquivoCSV, linha, '\n');

    while (getline(arquivoCSV, linha, '\n'))
    {
        if (linha.size() > 0)
        {
            colunas = new string[5];
            entreAspas = false;
            colunaAtual = 0;

            resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);

            if (!resposta)
            {
                do
                {
                    getline(arquivoCSV, linha, '\n');
                    resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
                } while (!resposta);
            }

            Data *data = new Data(colunas[0], colunas[1], stoi(colunas[2]), colunas[3], colunas[4]);

            data->setData(arquivoBinario, arquivoPosicoes);

            quantidadeLinhas++;

            delete[] colunas;
            delete data;
        }
    }
    arquivoBinario.close();
    arquivoPosicoes.close();
    cout << "Processo finalizado." << endl;
}
bool Processamento::buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual)
{
    string dado = "";
    for (int i = 0; i < linha.size(); i++)
    {
        if (linha[i] == '"' && !entreAspas)
        {
            entreAspas = true;
        }
        else if (linha[i] == '"' && entreAspas)
        {
            entreAspas = false;
        }
        if (linha[i] == ',' && !entreAspas)
        {
            colunas[colunaAtual] += dado;
            dado = "";
            colunaAtual++;
        }
        else
        {
            dado += linha[i];
        }
        if (colunaAtual == 4)
        {
            dado = "";
            for (int j = linha.size(); j > 0; j--)
            {
                if (linha[j] == ',')
                {
                    colunas[colunaAtual] += dado;
                    return true;
                }
                dado = linha[j] + dado;
            }
            break;
        }
        if (i == linha.size() - 1)
        {
            colunas[colunaAtual] += dado;
            break;
        }
    }
    return false;
}

void Processamento::setString(ofstream &arquivoBinario, string valor)
{
    size_t tamanho = valor.size();
    arquivoBinario.write((char *)&tamanho, sizeof(tamanho));
    arquivoBinario.write(valor.c_str(), tamanho);
}

string Processamento::getString(ifstream &arquivoProcessado)
{
    string texto;
    string::size_type tamanho;
    arquivoProcessado.read((char *)&tamanho, sizeof(tamanho));
    texto.resize(tamanho);
    arquivoProcessado.read(&texto[0], tamanho);

    return texto;
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

int Processamento::getPosicaoDataPeloId(ifstream &posicoesSalvas, int id)
{
    int posicoesData = -1;
    int posicaoCursor = (id - 1) * sizeof(int);

    posicoesSalvas.clear();
    posicoesSalvas.seekg(posicaoCursor, posicoesSalvas.beg);

    posicoesSalvas.read((char *)&posicoesData, sizeof(int));

    return posicoesData;
}

Data *Processamento::getDataPeloId(ifstream &arquivoProcessado, ifstream &posicoesSalvas, int id)
{
    int intAux;
    Data *data = new Data();

    int total = Processamento::getQuantidadeData(posicoesSalvas);

    if (id <= 0 || id > total)
    {
        return nullptr;
    }

    int posicao = Processamento::getPosicaoDataPeloId(posicoesSalvas, id);

    if (posicao == -1)
    {
        return nullptr;
    }

    arquivoProcessado.clear();
    arquivoProcessado.seekg(posicao, arquivoProcessado.beg);

    while (arquivoProcessado.good())
    {
        data->setReviewId(Processamento::getString(arquivoProcessado));
        data->setReviewText(Processamento::getString(arquivoProcessado));
        arquivoProcessado.read((char *)&intAux, sizeof(int));
        data->setUpvotes(intAux);
        data->setAppVersion(Processamento::getString(arquivoProcessado));
        data->setPostedDate(Processamento::getString(arquivoProcessado));

        return data;
    }

    return nullptr;
}

PonteiroData *Processamento::getDadosAleatorios(ifstream &arquivoProcessado, ifstream &posicoesSalvas, int n)
{
    int quantidadeDados = Processamento::getQuantidadeData(posicoesSalvas);
    int intAleatorio;
    if (n <= quantidadeDados)
    {
        cout << "Importando dados do arquivo .bin..." << endl;
        PonteiroData *dados = new PonteiroData[n];
        for (int i = 0; i < n; i++)
        {
            intAleatorio = rand() % (quantidadeDados) + 1;
            dados[i] = Processamento::getDataPeloId(arquivoProcessado, posicoesSalvas, intAleatorio);
        }

        cout << "Dados importados." << endl;

        return dados;
    }
}

void Processamento::desalocarVetor(PonteiroData *dados, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete dados[i];
    }
    delete[] dados;
}

PonteiroData *Processamento::getTodosOsDados(ifstream &arquivoProcessado, ifstream &posicoesSalvas)
{
    cout << "Importando todo o arquivo binario..." << endl;
    int tamanho = Processamento::getQuantidadeData(posicoesSalvas);

    PonteiroData *dados = new PonteiroData[tamanho];

    arquivoProcessado.clear();
    arquivoProcessado.seekg(0, arquivoProcessado.beg);

    int intAux = 0, idAtual = 0;

    while (arquivoProcessado.good() && idAtual < tamanho)
    {
        Data *data = new Data();
        data->setReviewId(Processamento::getString(arquivoProcessado));
        data->setReviewText(Processamento::getString(arquivoProcessado));
        arquivoProcessado.read((char *)&intAux, sizeof(int));
        data->setUpvotes(intAux);
        data->setAppVersion(Processamento::getString(arquivoProcessado));
        data->setPostedDate(Processamento::getString(arquivoProcessado));

        dados[idAtual] = data;

        idAtual++;
    }
    cout << "Importado com sucesso!" << endl;

    return dados;
}

int *Processamento::getTodasAsPosicoes(ifstream &posicoesSalvas)
{
    int tamanho = Processamento::getQuantidadeData(posicoesSalvas);

    int *posicoes = new int[tamanho];

    posicoesSalvas.clear();
    posicoesSalvas.seekg(0, posicoesSalvas.beg);

    int posicoesData = 0, idAtual = 0;

    while (posicoesSalvas.good() && idAtual < tamanho)
    {
        posicoesSalvas.read((char *)&posicoesData, sizeof(int));
        posicoes[idAtual] = posicoesData;
        idAtual++;
    }

    return posicoes;
}

PonteiroData *Processamento::getDadosAleatoriosDoVetor(PonteiroData *dados, int quantidade, int n)
{
    cout << "Importando dados do vetor maior para um menor..." << endl;

    PonteiroData *maioresDados = new PonteiroData[n];

    int intAleatorio;
    for (int i = 0; i < n; i++)
    {
        intAleatorio = rand() % (quantidade) + 1;
        maioresDados[i] = dados[intAleatorio];
    }
    cout << "Dados importados." << endl;

    return maioresDados;
}

PonteiroData *Processamento::getDadosAleatoriosDoVetorComPosicao(PonteiroData *dados, int *posicoes, int *posicoesDados, int quantidade, int n)
{
    cout << "Importando dados aleatorios do vetor maior para um menor..." << endl;

    PonteiroData *menoresDados = new PonteiroData[n];

    int intAleatorio;
    for (int i = 0; i < n; i++)
    {
        intAleatorio = rand() % (quantidade) + 1;
        menoresDados[i] = dados[intAleatorio];
        posicoes[i] = posicoesDados[intAleatorio];
    }
    cout << "Dados importados." << endl;

    return menoresDados;
}
