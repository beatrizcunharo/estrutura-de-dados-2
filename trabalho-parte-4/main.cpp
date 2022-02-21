#include <iostream>
#include <fstream>
#include <string>
#include "Data.h"
#include "Arquivo.h"
#include "Huffman.h"
#include <chrono>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std::chrono;

using namespace std;

typedef Data *DataPonteiro;

void processamento(ifstream &arquivoProcessado, ifstream &posicoes_salvas, string saida, string comprimido, DataPonteiro *dadosMaior, int *posicaoDados, int quantidadeDados) {
    
    int op;

    while(op != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Comprimir e Descomprimir;" << endl;
        cout << "2 - Analise;" << endl;
        cout << "-1 - Sair;" << endl;
        cout << "Opcao: ";
        cin >> op;

        switch (op)
        {
            case -1:

                cout << "Saida..." << endl;
                exit(0);

            case 1:
            {
                // COMPRIMIR E DESCOMPRIMIR

                int n = 0;
                cout << "Compressao...." << endl;
                cout << "Entre com o valor de N: " << endl;
                cin >> n;

                DataPonteiro *dadosMenor = Arquivo::recuperarDadosAleatoriosDoVetor(dadosMaior, quantidadeDados, n);

                double inicioCompressao = double(clock()) / CLOCKS_PER_SEC;
                    
                string review_text = "", str = "";
                for(int i = 0; i < n; i++) {
                    str = " ";
                    for(int j = 0; j < dadosMenor[i]->getReviewText().length(); j++) {
                        str += dadosMenor[i]->getReviewText()[j];
                        if(j == 50) {
                            break;
                        }
                    }
                    review_text += str;
                }

                int qntMaxLetras = 300;
                char *letras = new char[qntMaxLetras];
                long *frequencias = new long[qntMaxLetras];
                for(int i = 0; i < qntMaxLetras; i++) {
                    letras[i] = '$';
                    frequencias[i] = 0;
                }

                long qntChars = review_text.length();
                char letraAtual;
                for(long i = 0; i < qntChars; i++) {
                    letraAtual = review_text[i];
                    for(int j = 0; j < qntMaxLetras; j++) {
                            
                        if(letras[j] == '$' && letraAtual == '$' && frequencias[j] > 0) {
                            frequencias[j] += 1;
                        }else if(letras[j] == '$') { 
                            letras[j] = letraAtual;
                            frequencias[j] += 1;
                            break;
                        }else if(letraAtual == letras[j]) { 
                            frequencias[j] += 1;
                            break;
                        }
                    }
                }

                int qntLetrasEncontradas = 0;
                for(int i = 0; i < qntMaxLetras; i++) {
                    if(frequencias[i] > 0) {
                        qntLetrasEncontradas++;                
                    }
                }

                int comparacoes = 0;
                Huffman *arvore = new Huffman(review_text.length());
                arvore->codificar(letras, frequencias, qntLetrasEncontradas, &comparacoes);
                bool *review_text_comprimido = arvore->comprimirHuffman(letras, frequencias, review_text);
                ofstream comprimidoBin;

                comprimidoBin.open(comprimido, ios::trunc);
                for(int i = 0; i < arvore->getTamanhoComprimido(); i++) {
                    comprimidoBin << review_text_comprimido[i];
                }

                comprimidoBin.close();

                double fimCompressao = double(clock()) / CLOCKS_PER_SEC;

                double tempoCompressao = fimCompressao - inicioCompressao;

                delete [] letras;
                delete [] frequencias;

                cout << "Arquivo comprimido com sucesso." << endl;
                cout << "Comparacoes: " << comparacoes << endl;
                cout << "Tempo: " << to_string(tempoCompressao) << " segundos" << endl;

                // DESCOMPRESSÃO
                
                cout << "Descomprimindo..." << endl;

                int descomprimir;
                cin >> descomprimir;
                if(descomprimir) {
                    double inicioDescompressao = double(clock()) / CLOCKS_PER_SEC;
                    Huffman *arvore = new Huffman(review_text.length());
                    string descomprimido = arvore->descomprimirHuffman(review_text_comprimido);
                    ofstream descomprimidoBin;

                    descomprimidoBin.open(descomprimido, ios::trunc);
                    descomprimidoBin << descomprimido;
                    descomprimidoBin.close();

                    double fimDescompressao = double(clock()) / CLOCKS_PER_SEC;
                    double tempoDescompressao = fimDescompressao - inicioDescompressao;

                    cout << "Arquivo descomprimido com sucesso." << endl;
                    cout << "Tempo: " << to_string(tempoDescompressao) << " segundos" << endl;
                }

                    delete [] dadosMenor;
                    delete arvore;
            }
            case 2:
            {
                // ANALISE

                int m = 0, n = 0;
                int ns[] = {10000, 100000, 1000000};
                int nAtualIdx = 0;

                cout << "Analise..." << saida << endl;

                ofstream arquivo_saida;
                arquivo_saida.open(saida, ios::out | ios::trunc);

                double mediaTempo1 = 0;
                double mediaComparacoes1 = 0;
                double mediaTempo2 = 0;
                double mediaComparacoes2 = 0;
                double mediaTempo3 = 0;
                double mediaComparacoes3 = 0;
                while(m < 9) {
                    n = ns[nAtualIdx];

                    DataPonteiro *dadosMenor = Arquivo::recuperarDadosAleatoriosDoVetor(dadosMaior, quantidadeDados, n);

                    double inicioAnalise = double(clock()) / CLOCKS_PER_SEC;
                    string reviews_texts = "", str = "";
                    for(int i = 0; i < n; i++) {
                        str = " ";
                        for(int j = 0; j < dadosMenor[i]->getReviewText().length(); j++) {
                            str += dadosMenor[i]->getReviewText()[j];
                            if(j == 50) {
                                break;
                            }
                        }
                        reviews_texts += str;
                    }

                    int qntMaxLetras = 300;
                    char *letras = new char[qntMaxLetras];
                    long *frequencias = new long[qntMaxLetras];
                    for(int i = 0; i < qntMaxLetras; i++) {
                        letras[i] = '$';
                        frequencias[i] = 0;
                    }

                    long qntChars = reviews_texts.length();
                    char letraAtual;
                    for(long i = 0; i < qntChars; i++) {
                        letraAtual = reviews_texts[i];
                        for(int j = 0; j < qntMaxLetras; j++) {
                            if(letras[j] == '$' && letraAtual == '$' && frequencias[j] > 0) {
                                frequencias[j] += 1;
                            }else if(letras[j] == '$') { 
                                letras[j] = letraAtual;
                                frequencias[j] += 1;
                                break;
                            }else if(letraAtual == letras[j]) { 
                                frequencias[j] += 1;
                                break;
                            }
                        }
                    }

                    int qntLetrasEncontradas = 0;
                    for(int i = 0; i < qntMaxLetras; i++) {
                        if(frequencias[i] > 0) {
                            qntLetrasEncontradas++;
                        }
                    }
                    int comparacoes = 0;
                    Huffman *arvore = new Huffman(reviews_texts.length());
                    arvore->codificar(letras, frequencias, qntLetrasEncontradas, &comparacoes);

                    double fimAnalise = double(clock()) / CLOCKS_PER_SEC;
                    double tempoAnalise = fimAnalise - inicioAnalise;

                    if(n == ns[0] || n == ns[3] || n == ns[6]) {
                        mediaTempo1 += tempoAnalise/3;
                        mediaComparacoes1 += comparacoes/3;
                    }else if(n == ns[1] || n == ns[4] || n == ns[7]){
                        mediaTempo2 += tempoAnalise/3;
                        mediaComparacoes2 += comparacoes/3;
                    }else if(n == ns[2] || n == ns[5] || n == ns[8]){
                        mediaTempo3 += tempoAnalise/3;
                        mediaComparacoes3 += comparacoes/3;
                    }
                    arquivo_saida << "Teste para n: " << n  << endl;
                    arquivo_saida << "Comparacoes: " << comparacoes << endl;
                    arquivo_saida << "Tempo: " << to_string(tempoAnalise) << endl;

                    delete [] letras;
                    delete [] frequencias;
                    delete [] dadosMenor;
                    delete arvore;
                    m++;
                    nAtualIdx++;
                }
                cout << "Analise finalizada."<< endl;
                arquivo_saida << "--------------------------------------------------------------------------------" << endl;
                arquivo_saida << "Media de tempo para 10000 reviews: " << to_string(mediaTempo1) << " milisegundos." << endl;
                arquivo_saida << "Media de comparacoes para 10000 reviews: " << to_string(mediaComparacoes1) << " comparacoes." << endl;
                arquivo_saida << "Media de tempo para 100000 reviews: " << to_string(mediaTempo2) << " milisegundos." << endl;
                arquivo_saida << "Media de comparacoes para 100000 reviews: " << to_string(mediaComparacoes2) << " comparacoes." << endl;
                arquivo_saida << "Media de tempo para 1000000 reviews: " << to_string(mediaTempo3) << " milisegundos." << endl;
                arquivo_saida << "Media de comparacoes para 1000000 reviews: " << to_string(mediaComparacoes3) << " comparacoes." << endl;

            }  
            default:
                cout << "Escolha uma opcao valida." << endl;
        }
    }

    arquivoProcessado.close();
    posicoes_salvas.close();
    delete [] posicaoDados;
    Arquivo::desalocarVetorDados(dadosMaior, quantidadeDados);
}

int main(int argc, char const *argv[]) {

    string csv = "tiktok_app_reviews.csv";
    string bin = "tiktok_app_reviews.bin";
    string posicoes = "posicoes.bin";
    string comprimido = "reviewsComp.bin";
    string descomprimido = "reviewsOrig.bin";
    string saida = "saida.txt";
    
    srand((unsigned) time(NULL));
    if (argc != 2)
    {
        cout << "ERROR: Expecting: ./<nomePrograma> <arquivoEntrada> " << endl;
        return 0;
    }
   
    ifstream arquivoBIN;
    arquivoBIN.open(bin, ios::binary);
    ifstream posicoes_salvas;
    posicoes_salvas.open(posicoes, ios::binary);

    if (arquivoBIN.is_open() && posicoes_salvas.is_open()) {

        int quantidadeDados = Arquivo::recuperarQuantidadeDados(posicoes_salvas);
        DataPonteiro *dadosMaior = Arquivo::recuperarTodosDados(arquivoBIN, posicoes_salvas);
        int *posicoesDados = Arquivo::recuperarTodasPosicoes(posicoes_salvas);

        processamento(arquivoBIN, posicoes_salvas, saida, comprimido, dadosMaior, posicoesDados, quantidadeDados);
    } else {
        arquivoBIN.close();

        // Iniciando leitura csv

        ifstream arquivoCSV;
        arquivoCSV.open(argv[1]);

        if (arquivoCSV.is_open()) {

            // Abrindo o arquivo .bin

            ofstream arquivoBIN;
            arquivoBIN.open(bin, ios::binary);

            // Abrindo arquivo posições
            ofstream arquivoPosicoes;
            arquivoPosicoes.open(posicoes, ios::binary);

            Arquivo::processar(arquivoCSV, arquivoBIN, arquivoPosicoes);

            arquivoCSV.close();
            arquivoBIN.close();
            arquivoPosicoes.close();

            ifstream arquivoProcessado;
            arquivoProcessado.open(bin, ios::binary);

            ifstream posicoes_salvas;
            posicoes_salvas.open(posicoes, ios::binary);

            if (arquivoProcessado.is_open() && posicoes_salvas.is_open()) {

                int quantidadeDados = Arquivo::recuperarQuantidadeDados(posicoes_salvas);
                DataPonteiro *dadosMaior = Arquivo::recuperarTodosDados(arquivoProcessado, posicoes_salvas);
                int *posicaoDados = Arquivo::recuperarTodasPosicoes(posicoes_salvas);

                processamento(arquivoProcessado, posicoes_salvas, saida, comprimido, dadosMaior, posicaoDados, quantidadeDados);
            } else {
                cout << "Erro: Nao foi possivel abrir o arquivo .bin." << endl;
                exit(1);
            }
        } 
    }

    return 0;
}