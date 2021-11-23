# estrutura-de-dados-2
Repositório para o trabalho de estrutura de dados 2.

Instruções para rodar o projeto:

WINDOWS:  Abra o cmd na pasta **trabalho-parte-1** e execute o comando: g++ main.cpp -o nomeDoExecutavel. O mesmo irá criar um executável com o nome que foi colocado (normalmente é main). Feito isso, digite .\nomeDoExecutavel no cmd, dê espaço e digite o endereço onde está o arquivo .csv.

Deste modo:

g++ main.cpp -o nomeDoExecutavel <br />
.\nomeDoExecutavel caminhoParaOArquivo <br />

Exemplo:

g++ main.cpp -o main
.\main .\tiktok_app_reviews.csv

LINUX: Abra o cmd na pasta **trabalho-parte-1** e execute o comando: clear && g++ -std=c++11 *.h *.cpp  -o nomeDoExecutavel && ./nomeDoExecutavel caminhoDoArquivo. O mesmo irá criar um executável com o nome que foi colocado (normalmente é main) e irá executar o programa automaticamente.

Deste modo:

clear && g++ -std=c++11 *.h *.cpp  -o nomeDoExecutavel && ./nomeDoExecutavel caminhoParaOArquivo

Exemplo:

clear && g++ -std=c++11 *.h *.cpp  -o main && ./main ./tiktok_app_reviews.csv

**Observação**: os arquivos gerados pelo programa como o .bin e o .txt, estarão dentro da pasta **trabalho-parte-1**.
