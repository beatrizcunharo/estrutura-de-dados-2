/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE

    GRUPO:

    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/
#include "Data.h"

using namespace std;

void prefacio()
{
    cout << "Trabalho de estrutura de dados 2 - 2021/3" << endl;
    cout << "Grupo: " << endl;
    cout << "Beatriz Cunha Rodrigues - 201776038" << endl;
    cout << "Daniel Ribeiro Lavra - 201735042" << endl;
}

void processamento()
{
    int op = 0;
    while(op != -1)
    {
        cout << "Escolha uma opcao: " << endl;
        cout << "1 - Processamento dos dados;" << endl;
        cout << "2 - Acessar Registro;" << endl;
        cout << "3 - Funcao de teste;" << endl;
        cout << "-1 - Sair" << endl;
        cout << "Opcao: ";
        cin >> op;
        switch(op) 
        {
            case -1: 
                cout << "Saindo..." << endl;
                exit(0);
            case 1:
                // FAZER PROCESSAMENTO
                exit(0);
            case 2: 
                // FAZER ACESSO AO REGISTRO
                exit(0);
            case 3:
                // FAZER FUNÇÃO DE TESTE
                exit(0);
            default:
                cout << "Opcao invalida. Escolha uma opcao valida." << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    prefacio();
    processamento();
}