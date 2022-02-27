#include <iostream>
#include <fstream>
#include <string>
#include "Data.h"
#include "Processamento.h"
#include "ArvoreVP.h"
#include "ArvoreB.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef Data *PonteiroData;

const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_posicoes = "posicoes_reviews.bin";
const string nome_txt = "export_reviews.txt";
const string nome_input = "input.txt";
const string nome_saida = "saida.txt";
const string nome_testes = "teste.txt";

int menu()
{
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] Arvore Vermelho-Preto" << endl;
    cout << "[2] Arvore B" << endl;
    cout << "[0] Sair" << endl;
    cin >> selecao;

    return selecao;
}

void testarArvoreB(int b, int n, int m, int p, PonteiroData *reviewsMaior, int *posicoesReviews, int quantidadeReviews, ofstream &arquivo_saida)
{
    int intAleatorio = 0;

    double insercao_media = 0;
    double comparacoes_insercao_media = 0;
    double busca_media = 0;
    double comparacoes_busca_media = 0;

    for (int k = 0; k < m; k++)
    {

        double insercao = 0;
        int comparacoes_insercao = 0;
        double busca = 0;
        int comparacoes_busca = 0;

        ArvoreB *arvoreB = new ArvoreB((int)(b + 1) / 2, b);
        int *posicoes = new int[n];
        PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

        auto start = std::chrono::high_resolution_clock::now();
        cout << "Inserindo " << n << " reviews..." << endl;
        for (int i = 0; i < n; i++)
        {
            arvoreB->insereNoArvore(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        insercao = int_m.count() / 1000;
        cout << "Tempo Insercao: " << to_string(insercao) << " segundos     Comparacoes: " << comparacoes_insercao << endl;

        auto start2 = std::chrono::high_resolution_clock::now();
        cout << "Buscando " << p << " reviews..." << endl;
        for (int i = 0; i < p; i++)
        {
            intAleatorio = rand() % (n) + 1;
            arvoreB->buscaNo(reviews[intAleatorio]->getReviewId(), &comparacoes_busca);
        }
        auto end2 = std::chrono::high_resolution_clock::now();
        auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
        busca = int_m2.count();
        cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

        insercao_media += insercao / m;
        comparacoes_insercao_media += comparacoes_insercao / m;
        busca_media += busca / m;
        comparacoes_busca_media += comparacoes_busca / m;

        delete arvoreB;
        delete[] reviews;
        delete[] posicoes;
    }

    arquivo_saida << "===================== ArvoreB (Ordem = " << b << ") =====================" << endl;
    arquivo_saida << "Tempo de insercao de " << n << " reviews: " << insercao_media << " segundos" << endl;
    arquivo_saida << "Quantidade de comparacoes na insercao: " << comparacoes_insercao_media << endl;
    arquivo_saida << "Tempo de busca de " << p << " reviews: " << busca_media << " milisegundos" << endl;
    arquivo_saida << "Quantidade de comparacoes na busca: " << comparacoes_busca_media << endl;
}

void selecionar(int selecao, ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, PonteiroData *reviewsMaior, int *posicoesReviews, int quantidadeReviews, ofstream &arquivo_saida)
{

    switch (selecao)
    {
    case 0:
    {

        cout << "Programa finalizado!" << endl;
        arquivo_processado.close();
        posicoes_salvas.close();
        arquivo_saida.close();
        delete[] posicoesReviews;
        Processamento::desalocarVetor(reviewsMaior, quantidadeReviews);
        exit(0);
        break;
    }
    case 1:
    {
        int opcao;
        cout << "---------- Arvore Vermelho-Preto ----------" << endl;
        cout << "[1] Analises" << endl;
        cout << "[2] Buscar pelo ID" << endl;
        cout << "[0] Sair" << endl;
        cin >> opcao;

        if (opcao == 1)
        {
            int m = 3, n = 1000000, b = 100, intAleatorio = 0;

            double insercao_media = 0;
            double comparacoes_insercao_media = 0;
            double busca_media = 0;
            double comparacoes_busca_media = 0;

            for (int j = 0; j < m; j++)
            {

                double insercao = 0;
                int comparacoes_insercao = 0;
                double busca = 0;
                int comparacoes_busca = 0;

                ArvoreVP *arvoreVp = new ArvoreVP();
                int *posicoes = new int[n];
                PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

                auto start = std::chrono::high_resolution_clock::now();
                cout << "Inserindo " << n << " reviews..." << endl;
                for (int i = 0; i < n; i++)
                {
                    arvoreVp->inserir(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                insercao = int_m.count() / 1000;
                cout << "Tempo Insercao: " << to_string(insercao) << " segundos     Comparacoes: " << comparacoes_insercao << endl;

                auto start2 = std::chrono::high_resolution_clock::now();
                cout << "Buscando " << b << " reviews..." << endl;
                for (int i = 0; i < b; i++)
                {
                    intAleatorio = rand() % (n) + 1;
                    arvoreVp->buscar(reviews[intAleatorio]->getReviewId(), &comparacoes_busca);
                }
                auto end2 = std::chrono::high_resolution_clock::now();
                auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
                busca = int_m2.count();
                cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

                insercao_media += insercao / m;
                comparacoes_insercao_media += comparacoes_insercao / m;
                busca_media += busca / m;
                comparacoes_busca_media += comparacoes_busca / m;

                delete arvoreVp;
                delete[] reviews;
                delete[] posicoes;
            }

            arquivo_saida << "============== Arvore Vermelho-Preto ==============" << endl;
            arquivo_saida << "Tempo de insercao de " << n << " reviews: " << insercao_media << " segundos" << endl;
            arquivo_saida << "Quantidade de comparacoes na insercao: " << comparacoes_insercao_media << endl;
            arquivo_saida << "Tempo de busca de " << b << " reviews: " << busca_media << " milisegundos" << endl;
            arquivo_saida << "Quantidade de comparacoes na busca: " << comparacoes_busca_media << endl;
        }
        else if (opcao == 2)
        {
            int n = 0;
            double insercao = 0, busca = 0;
            int comparacoes_insercao = 0, comparacoes_busca = 0;

            cout << "Deseja importar quantos Reviews para a Arvore?" << endl;
            cin >> n;

            ArvoreVP *arvoreVp = new ArvoreVP();
            int *posicoes = new int[n];
            PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

            auto start = std::chrono::high_resolution_clock::now();
            cout << "Inserindo " << n << " reviews..." << endl;
            for (int i = 0; i < n; i++)
            {
                arvoreVp->inserir(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            insercao = int_m.count() / 1000;
            cout << "Tempo Insercao: " << to_string(insercao) << " segundos     Comparacoes: " << comparacoes_insercao << endl;

            string id_busca;
            cout << "Qual ID deseja buscar na Arvore?" << endl;
            cin >> id_busca;

            auto start2 = std::chrono::high_resolution_clock::now();
            cout << "Buscando o review..." << endl;
            NoVP *no = arvoreVp->buscar(id_busca, &comparacoes_busca);
            auto end2 = std::chrono::high_resolution_clock::now();
            auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
            busca = int_m2.count();
            cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

            if (no != nullptr)
            {
                cout << "ID encontrado:" << endl;
                cout << "ID: " << no->getReviewId() << endl;
                cout << "Localizacao: " << no->getLocalizacao() << endl;
            }
            else
            {
                cout << "ID nao encontrado!" << endl;
            }

            cout << "Voltando para o menu..." << endl;

            delete arvoreVp;
            delete[] reviews;
            delete[] posicoes;
        }
        break;
    }
    case 2:
    {
        int opcao;
        cout << "---------------- Arvore B -----------------" << endl;
        cout << "[1] Analises" << endl;
        cout << "[2] Buscar pelo ID" << endl;
        cout << "[0] Sair" << endl;
        cin >> opcao;

        if (opcao == 1)
        {
            cout << "Voce selecionou o modulo Analises. Aguarde o resultado..." << endl;
            int n = 1000000;
            int b1 = 20;
            int b2 = 200;
            int m = 3;
            int p = 100;

            testarArvoreB(b1, n, m, p, reviewsMaior, posicoesReviews, quantidadeReviews, arquivo_saida);
            testarArvoreB(b2, n, m, p, reviewsMaior, posicoesReviews, quantidadeReviews, arquivo_saida);
        }
        else if (opcao == 2)
        {
            cout << "Voce selecionou o modulo de busca pelo id..." << endl;
            int n = 0, ordem = 0;
            double insercao = 0, busca = 0;
            int comparacoes_insercao = 0, comparacoes_busca = 0;

            cout << "Deseja importar quantos Reviews para a Arvore?" << endl;
            cin >> n;

            cout << "Qual a ordem da Arvore?" << endl;
            cin >> ordem;

            if (ordem < 0)
            {
                cout << "Valor invalido para Ordem!" << endl;
                return;
            }

            ArvoreB *arvoreB = new ArvoreB((int)(ordem + 1) / 2, ordem);
            int *posicoes = new int[n];
            PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

            auto start = std::chrono::high_resolution_clock::now();
            cout << "Inserindo " << n << " reviews..." << endl;
            for (int i = 0; i < n; i++)
            {

                arvoreB->insereNoArvore(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            insercao = int_m.count() / 1000;
            cout << "Tempo Insercao: " << to_string(insercao) << " segundos     Comparacoes: " << comparacoes_insercao << endl;

            string id_busca;
            cout << "Qual ID deseja buscar na Arvore?" << endl;
            cin >> id_busca;

            auto start2 = std::chrono::high_resolution_clock::now();
            cout << "Buscando o review..." << endl;
            NoB *noB = arvoreB->buscaNo(id_busca, &comparacoes_busca);
            auto end2 = std::chrono::high_resolution_clock::now();
            auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
            busca = int_m2.count();
            cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

            if (noB != nullptr)
            {
                cout << "ID encontrado:" << endl;
                cout << "ID: " << noB->getChaves()->review_id << endl;
                cout << "Localizacao: " << noB->getChaves()->localizacao << endl;
            }
            else
            {
                cout << "ID nao encontrado!" << endl;
            }

            delete arvoreB;
            delete[] reviews;
            delete[] posicoes;
        }
        break;
    }
    default:
    {
        cout << "Erro: Opcao invalida!" << endl;
    }
    }
}

void mainMenu(ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, PonteiroData *reviewsMaior, int *posicoesReviews, int quantidadeReviews)
{

    ofstream arquivo_saida;
    arquivo_saida.open(diretorio + nome_saida, ios::trunc);
    int selecao = 1;
    while (selecao != 0)
    {
        selecao = menu();
        selecionar(selecao, arquivo_processado, posicoes_salvas, diretorio, reviewsMaior, posicoesReviews, quantidadeReviews, arquivo_saida);
    }
    delete[] posicoesReviews;
    Processamento::desalocarVetor(reviewsMaior, quantidadeReviews);
}

int main(int argc, char const *argv[])
{

    srand((unsigned)time(NULL));
    if (argc != 2)
    {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    ifstream arquivo_bin;
    arquivo_bin.open(nome_bin, ios::binary);
    ifstream posicoes_salvas;
    posicoes_salvas.open(nome_posicoes, ios::binary);

    if (arquivo_bin.is_open() && posicoes_salvas.is_open())
    {

        int quantidadeReviews = Processamento::getQuantidadeData(posicoes_salvas);
        cout << "Foi encontrado um arquivo bin com " << quantidadeReviews << " reviews." << endl;
        PonteiroData *reviewsMaior = Processamento::getTodosOsDados(arquivo_bin, posicoes_salvas);
        int *posicoesReviews = Processamento::getTodasAsPosicoes(posicoes_salvas);

        mainMenu(arquivo_bin, posicoes_salvas, argv[1], reviewsMaior, posicoesReviews, quantidadeReviews);
    }
    else
    {
        arquivo_bin.close();

        ifstream arquivo_csv;
        arquivo_csv.open(nome_csv);

        if (arquivo_csv.is_open())
        {

            ofstream arquivo_bin;
            arquivo_bin.open(nome_bin, ios::binary | ios::trunc);

            ofstream arquivo_posicoes;
            arquivo_posicoes.open(nome_posicoes, ios::binary | ios::trunc);

            Processamento::processamento(arquivo_csv, arquivo_bin, arquivo_posicoes);

            arquivo_csv.close();
            arquivo_bin.close();
            arquivo_posicoes.close();

            ifstream arquivo_processado;
            arquivo_processado.open(nome_bin, ios::binary);

            ifstream posicoes_salvas;
            posicoes_salvas.open(nome_posicoes, ios::binary);

            if (arquivo_processado.is_open() && posicoes_salvas.is_open())
            {

                int quantidadeReviews = Processamento::getQuantidadeData(posicoes_salvas);
                PonteiroData *reviewsMaior = Processamento::getTodosOsDados(arquivo_processado, posicoes_salvas);
                int *posicoesReviews = Processamento::getTodasAsPosicoes(posicoes_salvas);

                mainMenu(arquivo_processado, posicoes_salvas, argv[1], reviewsMaior, posicoesReviews, quantidadeReviews);
            }
            else
            {
                cout << "Erro: Nao foi possivel abrir o arquivo bin '" << nome_bin << "'" << endl;
                exit(1);
            }
        }
    }

    return 0;
}