package principal;
#include <iostream>
#include <vector>
#include "/data/LeitorCSV.cpp"

int main() {
    // 1. Onde o algoritmo de leitura é executado:
    std::string caminho = "src/dados/imagens.csv";
    std::vector<Imagem> dados = LeitorCSV::ler(caminho);

    std::cout << "Foram lidos " << dados.size() << " registos do CSV.\n";

    // 2. A partir daqui fazes as cópias do vector e medes o tempo dos algoritmos
    // ...

    return 0;
}
