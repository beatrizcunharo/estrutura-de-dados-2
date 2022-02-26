/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Data.h"
#include "Processamento.h"
#include "Huffman.h"
#include <chrono>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

string arquivoCSV = "tiktok_app_reviews.csv";
string arquivoBIN = "tiktok_app_reviews.bin";
string arquivoPosicoes = "posicoes_reviews.bin";
string arquivoComprimido = "reviewsComp.bin";
string arquivoDescomprimido = "reviewsOrig.bin";
string arquivoSaida = "saida.txt";

typedef Data *PonteiroData;

void processamento(ifstream &arquivoProcessado, ifstream &posicoesSalvas, string diretorio, PonteiroData *maioresDados, int *posicoesData, int quantidadeDados)
{
    int opcao = 0;

    while (opcao != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Comprimir e descomprimir;" << endl;
        cout << "2 - Analise;" << endl;
        cout << "-1 - Sair;" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case -1:
        {
            // OPÇÃO DE SAÍDA

            cout << "Saindo..." << endl;
            arquivoProcessado.close();
            posicoesSalvas.close();
            delete[] posicoesData;
            Processamento::desalocarVetor(maioresDados, quantidadeDados);
            exit(0);
        }
        case 1:
        {

            // COMPRESSÃO E DESCOMPRESSÃO

            int n;
            cout << "Compressao e descompressao..." << endl;
            cout << "Entre com o valor de N: " << endl;
            cin >> n;
            PonteiroData *menores_dados = Processamento::getDadosAleatoriosDoVetor(maioresDados, quantidadeDados, n);
            string review_text = "", str = "";
            for (int i = 0; i < n; i++)
            {
                str = " ";
                for (int j = 0; j < menores_dados[i]->getReviewText().length(); j++)
                {
                    str += menores_dados[i]->getReviewText()[j];
                    if (j == 50)
                    {
                        break;
                    }
                }
                review_text += str;
            }

            int qntMaxLetras = 300;
            char *letras = new char[qntMaxLetras];
            long *frequencias = new long[qntMaxLetras];
            for (int i = 0; i < qntMaxLetras; i++)
            {
                letras[i] = '$';
                frequencias[i] = 0;
            }

            long qntChars = review_text.length();
            char letraAtual;
            for (long i = 0; i < qntChars; i++)
            {
                letraAtual = review_text[i];
                for (int j = 0; j < qntMaxLetras; j++)
                {
                    if (letras[j] == '$' && letraAtual == '$' && frequencias[j] > 0)
                    {
                        frequencias[j] += 1;
                    }
                    else if (letras[j] == '$')
                    {
                        letras[j] = letraAtual;
                        frequencias[j] += 1;
                        break;
                    }
                    else if (letraAtual == letras[j])
                    {
                        frequencias[j] += 1;
                        break;
                    }
                }
            }

            int qntLetrasEncontradas = 0;
            for (int i = 0; i < qntMaxLetras; i++)
            {
                if (frequencias[i] > 0)
                {
                    qntLetrasEncontradas++;
                }
            }

            int comparacoes = 0;
            Huffman *arvore = new Huffman(review_text.length());
            arvore->codificar(letras, frequencias, qntLetrasEncontradas, &comparacoes);
            bool *review_text_comprimido = arvore->comprimirHuffman(letras, frequencias, review_text);
            ofstream comprimidoBin;
            comprimidoBin.open(arquivoComprimido, ios::trunc);
            for (int i = 0; i < arvore->getTamanhoComprimido(); i++)
            {
                comprimidoBin << review_text_comprimido[i];
            }
            comprimidoBin.close();

            delete[] letras;
            delete[] frequencias;

            cout << "Comprimido com sucesso..." << endl;
            cout << "1 - Descomprimir" << endl;
            cout << "-1 - Sair" << endl;

            int descomprimir;
            cin >> descomprimir;
            if (descomprimir)
            {
                string descomprimido = arvore->descomprimirHuffman(review_text_comprimido);
                ofstream descomprimidoBin;

                descomprimidoBin.open(arquivoDescomprimido, ios::trunc);
                descomprimidoBin << descomprimido;
                descomprimidoBin.close();

                cout << "Descomprimido com sucesso..." << endl;
            }

            delete[] menores_dados;
            delete arvore;

            break;
        }
        case 2:
        {

            // ANALISE

            int m = 0, n = 0;
            int ns[] = {10000, 100000, 1000000, 10000, 100000, 1000000, 10000, 100000, 1000000};
            int nAtualIdx = 0;

            cout << "Analise..." << endl;

            ofstream arquivo_saida;
            arquivo_saida.open(arquivoSaida, ios::out | ios::trunc);

            arquivo_saida << "Analise..." << endl;

            double mediaComparacoes1 = 0;
            double mediaComparacoes2 = 0;
            double mediaComparacoes3 = 0;

            int taxaCompressao1 = 0;
            int taxaCompressao2 = 0;
            int taxaCompressao3 = 0;

            while (m < 9)
            {
                n = ns[nAtualIdx];

                PonteiroData *menores_dados = Processamento::getDadosAleatoriosDoVetor(maioresDados, quantidadeDados, n);

                string review_text = "", str = "";
                for (int i = 0; i < n; i++)
                {
                    str = " ";
                    for (int j = 0; j < menores_dados[i]->getReviewText().length(); j++)
                    {
                        str += menores_dados[i]->getReviewText()[j];
                        if (j == 50)
                        {
                            break;
                        }
                    }
                    review_text += str;
                }

                int qntMaxLetras = 300;
                char *letras = new char[qntMaxLetras];
                long *frequencias = new long[qntMaxLetras];
                for (int i = 0; i < qntMaxLetras; i++)
                {
                    letras[i] = '$';
                    frequencias[i] = 0;
                }

                long qntChars = review_text.length();
                char letraAtual;
                for (long i = 0; i < qntChars; i++)
                {
                    letraAtual = review_text[i];
                    for (int j = 0; j < qntMaxLetras; j++)
                    {
                        if (letras[j] == '$' && letraAtual == '$' && frequencias[j] > 0)
                        {
                            frequencias[j] += 1;
                        }
                        else if (letras[j] == '$')
                        {
                            letras[j] = letraAtual;
                            frequencias[j] += 1;
                            break;
                        }
                        else if (letraAtual == letras[j])
                        {
                            frequencias[j] += 1;
                            break;
                        }
                    }
                }

                int qntLetrasEncontradas = 0;
                for (int i = 0; i < qntMaxLetras; i++)
                {
                    if (frequencias[i] > 0)
                    {
                        qntLetrasEncontradas++;
                    }
                }

                int comparacoes = 0;
                Huffman *arvore = new Huffman(review_text.length());
                arvore->codificar(letras, frequencias, qntLetrasEncontradas, &comparacoes);

                if (n == ns[0] || n == ns[3] || n == ns[6])
                {
                    mediaComparacoes1 += comparacoes / 3;
                    taxaCompressao1 = taxaCompressao1 = ((arquivoBIN.size() * 8) - arquivoComprimido.size()) / arquivoBIN.size() * 8;
                }
                else if (n == ns[1] || n == ns[4] || n == ns[7])
                {
                    mediaComparacoes2 += comparacoes / 3;
                    taxaCompressao2 = ((n * 8) - arquivoComprimido.length()) / n * 8;
                }
                else if (n == ns[2] || n == ns[5] || n == ns[8])
                {
                    mediaComparacoes3 += comparacoes / 3;
                    taxaCompressao3 = ((n * 8) - arquivoComprimido.length()) / n * 8;
                }
                arquivo_saida << "Teste para n=" << n << " comparacoes: " << comparacoes << endl;

                delete[] letras;
                delete[] frequencias;
                delete[] menores_dados;
                delete arvore;
                m++;
                nAtualIdx++;
            }
            cout << "Analise finalizada e arquivo gerado. " << endl;
            arquivo_saida << "Dados: 10000" << endl;
            arquivo_saida << "Media de comparacoes: " << to_string(mediaComparacoes1) << " comparacoes." << endl;
            arquivo_saida << "Taxa compressao: " << to_string(taxaCompressao1) << "%" << endl;
            arquivo_saida << "Dados: 100000" << endl;
            arquivo_saida << "Media de comparacoes: " << to_string(mediaComparacoes2) << " comparacoes." << endl;
            arquivo_saida << "Taxa compressao: " << to_string(taxaCompressao2) << "%" << endl;
            arquivo_saida << "Dados: 1000000" << endl;
            arquivo_saida << "Media de comparacoes: " << to_string(mediaComparacoes3) << " comparacoes." << endl;
            arquivo_saida << "Taxa compressao: " << to_string(taxaCompressao3) << "%" << endl;

            break;
        }
        default:
            cout << "Entre com uma opcao valida." << endl;
        }
    }
}

void mainMenu(ifstream &arquivoProcessado, ifstream &posicoesSalvas, string diretorio, PonteiroData *maioresDados, int *posicoesData, int quantidadeDados)
{

    processamento(arquivoProcessado, posicoesSalvas, diretorio, maioresDados, posicoesData, quantidadeDados);
    arquivoProcessado.close();
    posicoesSalvas.close();
    delete[] posicoesData;
    Processamento::desalocarVetor(maioresDados, quantidadeDados);
}

int main(int argc, char const *argv[])
{

    // Verificando os parâmetro de input
    srand((unsigned)time(NULL));
    if (argc != 2)
    {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    // Abrindo o arquivo binario e o de posições
    ifstream arquivo_bin;
    arquivo_bin.open(arquivoBIN, ios::binary);
    ifstream posicoesSalvas;
    posicoesSalvas.open(arquivoPosicoes, ios::binary);

    // Verificando se abriu os arquivos
    if (arquivo_bin.is_open() && posicoesSalvas.is_open())
    {

        // Importando os binarios para vetor
        int quantidadeDados = Processamento::getQuantidadeData(posicoesSalvas);
        cout << "Foi encontrado um arquivo bin com " << quantidadeDados << " reviews." << endl;
        PonteiroData *maioresDados = Processamento::getTodosOsDados(arquivo_bin, posicoesSalvas);
        int *posicoesData = Processamento::getTodasAsPosicoes(posicoesSalvas);

        mainMenu(arquivo_bin, posicoesSalvas, argv[1], maioresDados, posicoesData, quantidadeDados);
    }
    else
    {
        arquivo_bin.close();

        // Abrindo o arquivo csv
        ifstream arquivo_csv;
        arquivo_csv.open(arquivoCSV);

        // Checando a abertura do arquivo
        if (arquivo_csv.is_open())
        {

            // Abrindo o arquivo bin
            ofstream arquivo_bin;
            arquivo_bin.open(arquivoBIN, ios::binary | ios::trunc);

            // Abrindo arquivo salvar as posições
            ofstream arquivo_posicoes;
            arquivo_posicoes.open(arquivoPosicoes, ios::binary | ios::trunc);

            // Função para processamento o arquivo
            Processamento::processamento(arquivo_csv, arquivo_bin, arquivo_posicoes);

            // Fechando os arquivos abertos
            arquivo_csv.close();
            arquivo_bin.close();
            arquivo_posicoes.close();

            // Abrindo para o modo leitura
            ifstream arquivoProcessado;
            arquivoProcessado.open(arquivoBIN, ios::binary);

            // Abrindo para o modo leitura o arquivo das posicoes tambem
            ifstream posicoesSalvas;
            posicoesSalvas.open(arquivoPosicoes, ios::binary);

            // Checando se o arquivo foi aberto com sucesso
            if (arquivoProcessado.is_open() && posicoesSalvas.is_open())
            {

                // Importando binários para vetor
                int quantidadeDados = Processamento::getQuantidadeData(posicoesSalvas);
                PonteiroData *maioresDados = Processamento::getTodosOsDados(arquivoProcessado, posicoesSalvas);
                int *posicoesData = Processamento::getTodasAsPosicoes(posicoesSalvas);

                mainMenu(arquivoProcessado, posicoesSalvas, argv[1], maioresDados, posicoesData, quantidadeDados);
            }
            else
            {
                cout << "Erro: Nao foi possivel abrir o arquivo bin '" << arquivoBIN << "'" << endl;
                exit(1);
            }
        }
    }

    return 0;
}