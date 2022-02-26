/*
    TRABALHO DE ESTRUTURA DE DADOS - 2021/3
    PROF MARCELO CANIATO RENHE
    GRUPO:
    Beatriz Cunha Rodrigues - 201776038
    Daniel Ribeiro Lavra - 201735042
*/

#include "Huffman.h"

// CONSTRUTOR

Huffman::Huffman(long tamanhoOriginal)
{
    this->codigos = new bool *[TAMANHO_MAXIMO];
    this->tamanhos = new int[TAMANHO_MAXIMO];
    this->tamanhoComprimido = 0;
    this->tamanhoOriginal = tamanhoOriginal;
    this->raiz = nullptr;
    this->heapMinima = nullptr;
}

// DESTRUTOR

Huffman::~Huffman()
{
    delete this->heapMinima;
}

Heap *Huffman::criarHeapMinima(char *dados, long *frequencia, long tamanho, int *comparacoes)
{
    Heap *heapMinima = new Heap(tamanho);
    for (int i = 0; i < tamanho; ++i)
    {
        heapMinima->setNoArrayNos(new No(dados[i], frequencia[i]), i);
    }
    heapMinima->setTamanho(tamanho);
    heapMinima->construirHeapMinima(comparacoes);

    return heapMinima;
}

No *Huffman::construirHuffman(char *dados, long *frequencia, long tamanho, int *comparacoes)
{
    No *left, *right, *top;
    Heap *heapMinima = criarHeapMinima(dados, frequencia, tamanho, comparacoes);
    this->heapMinima = heapMinima;
    while (!heapMinima->ehRaiz())
    {
        left = heapMinima->retirarMinima(comparacoes);
        right = heapMinima->retirarMinima(comparacoes);
        top = new No('$', left->getFrequencia() + right->getFrequencia());

        top->setEsquerda(left);
        top->setDireita(right);

        heapMinima->inserirHeapMinima(top, comparacoes);
    }

    return heapMinima->retirarMinima(comparacoes);
}

void Huffman::codificar(char *dados, long *frequencia, long tamanho, int *comparacoes)
{
    No *root = construirHuffman(dados, frequencia, tamanho, comparacoes);
    this->raiz = root;

    int arr[this->heapMinima->getCapacidade()], top = 0;

    setCodigos(root, arr, top);
}

void Huffman::setCodigos(No *root, int arr[], int top)
{
    if (root->getEsquerda())
    {
        arr[top] = 0;
        setCodigos(root->getEsquerda(), arr, top + 1);
    }
    if (root->getDireita())
    {
        arr[top] = 1;
        setCodigos(root->getDireita(), arr, top + 1);
    }
    if (root->ehFolha())
    {
        int char_int = root->getInfo() + METADE_MAXIMO;
        this->codigos[char_int] = new bool[top];
        this->tamanhos[char_int] = top;
        this->setArray(arr, top, this->codigos[char_int]);
    }
}

void Huffman::imprimirCodificado(No *root, int arr[], int top)
{
    if (root->getEsquerda())
    {
        arr[top] = 0;
        imprimirCodificado(root->getEsquerda(), arr, top + 1);
    }

    if (root->getDireita())
    {
        arr[top] = 1;
        imprimirCodificado(root->getDireita(), arr, top + 1);
    }

    if (root->ehFolha())
    {
        cout << root->getInfo() << ": ";
        imprimirArray(arr, top);
    }
}

void Huffman::setArray(int *arr, int n, bool *codigo)
{
    int i;

    for (i = 0; i < n; ++i)
        codigo[i] = arr[i];
}

void Huffman::imprimirArray(int *arr, int n)
{
    int i;

    for (i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}

void Huffman::setTamanhos(char *letras, long *frequencias)
{
    this->tamanhoComprimido = 1;
    for (int i = 0; i < heapMinima->getCapacidade(); i++)
    {
        if (frequencias[i] > 0)
        {
            int char_int = letras[i] + METADE_MAXIMO;
            this->tamanhoComprimido += (this->tamanhos[char_int] * frequencias[i]);
        }
    }
}

bool *Huffman::comprimirHuffman(char *letras, long *frequencias, string review_text)
{
    this->setTamanhos(letras, frequencias);
    bool *stringComprimida = new bool[(int)this->tamanhoComprimido];

    int charAtual = 0;
    for (int i = 0; i < this->tamanhoOriginal; i++)
    {
        int char_int = review_text[i] + METADE_MAXIMO;
        for (int j = 0; j < this->tamanhos[char_int]; j++)
        {
            stringComprimida[charAtual] = this->codigos[char_int][j];
            charAtual++;
        }
    }

    return stringComprimida;
}

double Huffman::getTamanhoComprimido()
{
    return this->tamanhoComprimido;
}

string Huffman::descomprimirHuffman(bool *comprimido)
{
    No *noAtual = this->raiz;

    string descomprimido = "";

    for (int i = 0; i < ((int)this->tamanhoComprimido); i++)
    {
        if (noAtual->ehFolha())
        {
            descomprimido += noAtual->getInfo();
            noAtual = this->raiz;
        }
        if (comprimido[i])
        {
            noAtual = noAtual->getDireita();
        }
        else
        {
            noAtual = noAtual->getEsquerda();
        }
    }
    return descomprimido + ' ';
}
