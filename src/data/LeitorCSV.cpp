#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Imagem> LeitorCSV::ler(const std::string& caminhoFicheiro) {
    std::vector<Imagem> lista;
    std::ifstream ficheiro(caminhoFicheiro);

    if (!ficheiro.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro: " << caminhoFicheiro << std::endl;
        return lista;
    }

    std::string linha;
    // Ignorar a primeira linha (cabeçalho do CSV) se existir
    std::getline(ficheiro, linha);

    while (std::getline(ficheiro, linha)) {
        std::stringstream ss(linha);
        std::string nome, strTamanho, strLargura, strAltura;

        // Assumindo formato CSV: nome,tamanho,largura,altura
        if (std::getline(ss, nome, ',') &&
            std::getline(ss, strTamanho, ',') &&
            std::getline(ss, strLargura, ',') &&
            std::getline(ss, strAltura, ',')) {

            double tamanho = std::stod(strTamanho);
            int largura = std::stoi(strLargura);
            int altura = std::stoi(strAltura);

            lista.push_back(Imagem(nome, tamanho, largura, altura));
        }
    }

    ficheiro.close();
    return lista;
}