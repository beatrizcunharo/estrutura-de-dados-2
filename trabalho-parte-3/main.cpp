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

void testarArvoreB(int b, int n, int m, int p, PonteiroData *maioresDados, int *posicoesData, int quantidadeDados, ofstream &arquivo_saida)
{
    int intAleatorio = 0;

    double insercao_media = 0;
    double comparacoes_insercao_media = 0;
    double busca_media = 0;
    double comparacoes_busca_media = 0;

    double inicio, fim, tempo1, tempo2;

    for (int k = 0; k < m; k++)
    {

        cout << "Execucao: " << k + 1 << endl;

        inicio = 0;
        fim = 0;
        tempo1 = 0;
        tempo2 = 0;

        double insercao = 0;
        int comparacoes_insercao = 0;
        double busca = 0;
        int comparacoes_busca = 0;

        ArvoreB *arvoreB = new ArvoreB((int)(b + 1) / 2, b);
        int *posicoes = new int[n];
        PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(maioresDados, posicoes, posicoesData, quantidadeDados, n);

        inicio = double(clock()) / CLOCKS_PER_SEC;
        cout << "Inserindo..." << endl;
        for (int i = 0; i < n; i++)
        {
            arvoreB->insereNoArvore(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
        }
        fim = double(clock()) / CLOCKS_PER_SEC;
        tempo1 = fim - inicio;
        cout << "Tempo Insercao: " << to_string(tempo1) << " segundos." << endl;
        cout << "Comparacoes: " << comparacoes_insercao << endl;

        inicio = 0;
        fim = 0;

        inicio = double(clock()) / CLOCKS_PER_SEC;
        cout << "Buscando " << p << " reviews..." << endl;
        for (int i = 0; i < p; i++)
        {
            intAleatorio = rand() % (n) + 1;
            arvoreB->buscaNo(reviews[intAleatorio]->getReviewId(), &comparacoes_busca);
        }
        fim = double(clock()) / CLOCKS_PER_SEC;
        tempo2 = fim - inicio;
        cout << "Tempo Busca: " << to_string(tempo2) << " segundos." << endl;
        cout << "Comparacoes: " << comparacoes_busca << endl;

        insercao_media += tempo1 / m;
        comparacoes_insercao_media += comparacoes_insercao / m;
        busca_media += tempo2 / m;
        comparacoes_busca_media += comparacoes_busca / m;

        delete arvoreB;
        delete[] reviews;
        delete[] posicoes;
    }

    arquivo_saida << "------------------------------ ArvoreB ordem " << b << "-----------------------------" << endl;
    arquivo_saida << "Tempo de insercao: " << insercao_media << " segundos" << endl;
    arquivo_saida << "Quantidade de comparacoes na insercao: " << comparacoes_insercao_media << endl;
    arquivo_saida << "Tempo de busca: " << busca_media << " segundos" << endl;
    arquivo_saida << "Quantidade de comparacoes na busca: " << comparacoes_busca_media << endl;
}

void selecionar(ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, PonteiroData *maioresDados, int *posicoesData, int quantidadeDados, ofstream &arquivo_saida)
{

    int op = 0;
    while (!op == -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Comprimir e descomprimir;" << endl;
        cout << "2 - Analise;" << endl;
        cout << "-1 - Sair;" << endl;
        cout << "op: ";
        cin >> op;

        switch (op)
        {
        case -1:
        {

            cout << "Saindo..." << endl;
            arquivo_processado.close();
            posicoes_salvas.close();
            arquivo_saida.close();
            delete[] posicoesData;
            Processamento::desalocarVetor(maioresDados, quantidadeDados);
            exit(0);
            break;
        }
        case 1:
        {
            int opcao;
            cout << "Arvore vermelha e preta..." << endl;
            cout << "1 - Analises" << endl;
            cout << "2 - Buscar pelo ID" << endl;
            cout << "-1 - Sair" << endl;
            cin >> opcao;

            switch (opcao)
            {
            case -1:
            {
                cout << "Saindo..." << endl;
                exit(0);
                break;
            }
            case 1:
            {
                int m = 3, n = 1000000, b = 100, intAleatorio = 0;

                double inicio, fim, tempo1, tempo2;

                double insercao_media = 0;
                double comparacoes_insercao_media = 0;
                double busca_media = 0;
                double comparacoes_busca_media = 0;

                cout << "Analise..." << endl;
                arquivo_saida << "Analise..." << endl;

                for (int j = 0; j < m; j++)
                {

                    inicio = 0;
                    fim = 0;
                    tempo1 = 0;
                    tempo2 = 0;

                    arquivo_saida << "Execucao: " << j + 1 << endl;

                    double insercao = 0;
                    int comparacoes_insercao = 0;
                    double busca = 0;
                    int comparacoes_busca = 0;

                    ArvoreVP *arvoreVp = new ArvoreVP();
                    int *posicoes = new int[n];
                    PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(maioresDados, posicoes, posicoesData, quantidadeDados, n);

                    inicio = double(clock()) / CLOCKS_PER_SEC;
                    cout << "Inserindo..." << endl;
                    for (int i = 0; i < n; i++)
                    {
                        arvoreVp->inserir(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
                    }
                    fim = double(clock()) / CLOCKS_PER_SEC;
                    tempo1 = fim - inicio;
                    cout << "Tempo Insercao: " << to_string(tempo1) << " segundos." << endl;
                    cout << "Comparacoes: " << comparacoes_insercao << endl;

                    inicio = 0;
                    fim = 0;

                    inicio = double(clock()) / CLOCKS_PER_SEC;
                    cout << "Buscando..." << endl;
                    for (int i = 0; i < b; i++)
                    {
                        intAleatorio = rand() % (n) + 1;
                        arvoreVp->buscar(reviews[intAleatorio]->getReviewId(), &comparacoes_busca);
                    }
                    fim = double(clock()) / CLOCKS_PER_SEC;
                    tempo2 = fim - inicio;
                    cout << "Tempo Busca: " << to_string(tempo2) << " segundos." << endl;
                    cout << "Comparacoes: " << comparacoes_busca << endl;

                    insercao_media += tempo1 / m;
                    comparacoes_insercao_media += comparacoes_insercao / m;
                    busca_media += tempo2 / m;
                    comparacoes_busca_media += comparacoes_busca / m;

                    delete arvoreVp;
                    delete[] reviews;
                    delete[] posicoes;
                }

                arquivo_saida << "-------------------------------- Arvore Vermelho-Preto -----------------------------" << endl;
                arquivo_saida << "Tempo de insercao: " << insercao_media << " segundos." << endl;
                arquivo_saida << "Quantidade de comparacoes na insercao: " << comparacoes_insercao_media << endl;
                arquivo_saida << "Tempo de busca: " << busca_media << " segundos." << endl;
                arquivo_saida << "Quantidade de comparacoes na busca: " << comparacoes_busca_media << endl;
                break;
            }
            case 2:
            {
                int n = 0;
                double insercao = 0, busca = 0;
                int comparacoes_insercao = 0, comparacoes_busca = 0;

                double inicio, fim, tempo1, tempo2;

                inicio = 0;
                fim = 0;
                tempo1 = 0;
                tempo2 = 0;

                cout << "Entre com o valor de n: " << endl;
                cin >> n;

                ArvoreVP *arvoreVp = new ArvoreVP();
                int *posicoes = new int[n];
                PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(maioresDados, posicoes, posicoesData, quantidadeDados, n);

                inicio = double(clock()) / CLOCKS_PER_SEC;
                cout << "Inserindo " << n << " reviews..." << endl;
                for (int i = 0; i < n; i++)
                {
                    arvoreVp->inserir(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
                }
                fim = double(clock()) / CLOCKS_PER_SEC;
                tempo1 = fim - inicio;
                cout << "Tempo Insercao: " << to_string(tempo1) << " segundos. " << endl;
                cout << "Comparacoes: " << comparacoes_insercao << endl;

                string id_busca;
                cout << "Qual ID deseja buscar na Arvore?" << endl;
                cin >> id_busca;

                inicio = 0;
                fim = 0;

                inicio = double(clock()) / CLOCKS_PER_SEC;
                cout << "Buscando o review..." << endl;
                NoVP *no = arvoreVp->buscar(id_busca, &comparacoes_busca);
                fim = double(clock()) / CLOCKS_PER_SEC;
                tempo2 = fim - inicio;
                cout << "Tempo Busca: " << to_string(tempo2) << " segundos." << endl;
                cout << "Comparacoes: " << comparacoes_busca << endl;

                if (no != nullptr)
                {
                    cout << "Encontrado na árvore." << endl;
                    cout << "ID: " << no->getReviewId() << endl;
                    cout << "Localizacao: " << no->getLocalizacao() << endl;
                }
                else
                {
                    cout << "Nada encontrado." << endl;
                }

                cout << "Voltando para o menu..." << endl;

                delete arvoreVp;
                delete[] reviews;
                delete[] posicoes;

                break;
            }
            default:
                cout << "Entre com uma opcao valida." << endl;
                break;
            }
        }
        case 2:
        {
            int opcao;
            cout << "ArvoreB..." << endl;
            cout << "1 - Analises" << endl;
            cout << "2 - Buscar pelo ID" << endl;
            cout << "-1 - Sair" << endl;
            cin >> opcao;

            switch (opcao)
            {
            case 1:
            {
                cout << "Analise..." << endl;
                int n = 1000000;
                int b1 = 20;
                int b2 = 200;
                int m = 3;
                int p = 100;

                testarArvoreB(b1, n, m, p, maioresDados, posicoesData, quantidadeDados, arquivo_saida);
                testarArvoreB(b2, n, m, p, maioresDados, posicoesData, quantidadeDados, arquivo_saida);
            }
            case 2:
            {
                cout << "Busca..." << endl;
                int n = 0, ordem = 0;
                double insercao = 0, busca = 0;
                int comparacoes_insercao = 0, comparacoes_busca = 0;

                double inicio, fim, tempo1, tempo2;

                inicio = 0;
                fim = 0;
                tempo1 = 0;
                tempo2 = 0;

                cout << "Entre com o valor de n: " << endl;
                cin >> n;

                cout << "Entre com a ordem da arvore: " << endl;
                cin >> ordem;

                if (ordem < 0)
                {
                    cout << "A ordem tem que ser maior que 0." << endl;
                    return;
                }

                ArvoreB *arvoreB = new ArvoreB((int)(ordem + 1) / 2, ordem);
                int *posicoes = new int[n];
                PonteiroData *reviews = Processamento::getDadosAleatoriosDoVetorComPosicao(maioresDados, posicoes, posicoesData, quantidadeDados, n);

                inicio = double(clock()) / CLOCKS_PER_SEC;
                cout << "Inserindo..." << endl;
                for (int i = 0; i < n; i++)
                {
                    arvoreB->insereNoArvore(reviews[i]->getReviewId(), posicoes[i], &comparacoes_insercao);
                }
                fim = double(clock()) / CLOCKS_PER_SEC;
                tempo1 = fim - inicio;
                cout << "Tempo Insercao: " << to_string(tempo1) << " segundos." << endl;
                cout << "Comparacoes: " << comparacoes_insercao << endl;

                string id_busca;
                cout << "Id que deseja buscar: " << endl;
                cin >> id_busca;

                inicio = 0;
                fim = 0;

                inicio = double(clock()) / CLOCKS_PER_SEC;
                cout << "Buscando o review..." << endl;
                NoB *noB = arvoreB->buscaNo(id_busca, &comparacoes_busca);
                fim = double(clock()) / CLOCKS_PER_SEC;
                tempo2 = fim - inicio;
                cout << "Tempo Busca: " << to_string(tempo2) << " segundos." << endl;
                cout << "Comparacoes: " << comparacoes_busca << endl;

                if (noB != nullptr)
                {
                    cout << "Encontrado na arvore." << endl;
                    cout << "ID: " << noB->getChaves()->review_id << endl;
                    cout << "Localizacao: " << noB->getChaves()->localizacao << endl;
                }
                else
                {
                    cout << "Nada encontrado." << endl;
                }

                delete arvoreB;
                delete[] reviews;
                delete[] posicoes;
            }
            }

            break;
        }
        default:
        {
            cout << "Erro: Opcao invalida!" << endl;
        }
        }
    }
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

        int quantidadeDados = Processamento::getQuantidadeData(posicoes_salvas);
        cout << "Foi encontrado um arquivo bin com " << quantidadeDados << " reviews." << endl;
        PonteiroData *maioresDados = Processamento::getTodosOsDados(arquivo_bin, posicoes_salvas);
        int *posicoesData = Processamento::getTodasAsPosicoes(posicoes_salvas);

        ofstream arquivo_saida;
        arquivo_saida.open(nome_saida, ios::trunc);
        selecionar(arquivo_bin, posicoes_salvas, argv[1], maioresDados, posicoesData, quantidadeDados, arquivo_saida);
        delete[] posicoesData;
        Processamento::desalocarVetor(maioresDados, quantidadeDados);
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

                int quantidadeDados = Processamento::getQuantidadeData(posicoes_salvas);
                PonteiroData *maioresDados = Processamento::getTodosOsDados(arquivo_processado, posicoes_salvas);
                int *posicoesData = Processamento::getTodasAsPosicoes(posicoes_salvas);

                ofstream arquivo_saida;
                arquivo_saida.open(nome_saida, ios::trunc);
                selecionar(arquivo_processado, posicoes_salvas, argv[1], maioresDados, posicoesData, quantidadeDados, arquivo_saida);
                delete[] posicoesData;
                Processamento::desalocarVetor(maioresDados, quantidadeDados);
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