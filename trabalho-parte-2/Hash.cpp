#include "Hash.h"

using namespace std;

string Hash::substituirPontos(std::string string, const std::string& atual, const std::string& proximo) {
        
    size_t posicaoInicial = 0;
        
    while((posicaoInicial = string.find(atual, posicaoInicial)) != std::string::npos) { // o algoritmo procura o char atual de acordo com a posição 
        // quando encontrado, ele substitui para o próximo (o char a ser substituido)
        
        string.replace(posicaoInicial, atual.length(), proximo);

        // incrementa para a próxima posição
        posicaoInicial += proximo.length();
    }
    return string;
}

int Hash::funcaoHash(string app_review)
{
    string versao_app = substituirPontos(app_review, ".", "");
    
    int app_convertido = stol(versao_app);

    int chave = app_convertido % this->tamanho; 

    return chave;
}

void Hash::inserir(Data data)
{
    long chave = funcaoHash(data.getAppVersion());
    long novaPosicao = 0;

    cout << chave << endl;

    // QUANTAS VEZES UMA VERSÃO DO APP SE REPETE
    long contagem = 0;

    // BOOLEANO PARA CONTROLAR A INSERÇÃO
    bool armazenado = false;

    // ENQUANTO NÃO FOR INSERIDO, É FEITA A OPERAÇÃO
    if(dados->size() == tamanho)    
    {
        cout << "Vetor cheio." << endl;
    }else
    {
        while(armazenado != true)
        {
            // SE FOR VAZIO, INSERE
            if(dados->at(chave).getAppVersion() == "")
            {
                dados->at(chave).setAppVersion(data.getAppVersion());
                contagem++;
                armazenado = true;
            }

            if(dados->at(chave).getAppVersion() == data.getAppVersion())
            {
                armazenado = true;
                contagem++;
            }
            else
            {
                novaPosicao++;
                chave = chave + novaPosicao;
            }
            
        }
    }
    dados->at(chave).setContagem(contagem);
}


