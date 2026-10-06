#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../modelo/imagens.hpp" // Ajusta o nome do cabeçalho do modelo se necessário

class LeitorCSV {
public:
    static std::vector<Imagem> ler(const std::string& caminho) {
        std::vector<Imagem> imagens;
        std::ifstream ficheiro(caminho);

        if (!ficheiro.is_open()) {
            std::cerr << "Erro ao abrir o ficheiro CSV em: " << caminho << std::endl;
            return imagens;
        }

        std::string linha;
        // Ignora a primeira linha (cabeçalho: id,nome,tamanho,largura,altura)
        std::getline(ficheiro, linha);

        while (std::getline(ficheiro, linha)) {
            if (linha.empty()) continue;

            std::stringstream ss(linha);
            std::string strId, nome, strTamanho, strLargura, strAltura;

            // Separa os dados pela vírgula
            std::getline(ss, strId, ',');
            std::getline(ss, nome, ',');
            std::getline(ss, strTamanho, ',');
            std::getline(ss, strLargura, ',');
            std::getline(ss, strAltura, ',');

            int id = std::stoi(strId);
            double tamanho = std::stod(strTamanho);
            int largura = std::stoi(strLargura);
            int altura = std::stoi(strAltura);

            // Adiciona o objeto à lista
            imagens.emplace_back(id, nome, tamanho, largura, altura);
        }

        ficheiro.close();
        return imagens;
    }
};