#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "../modelo/imagens.cpp"

using namespace std;

vector<Imagem> lerArquivoInterno() {

    vector<Imagem> dados;

    string caminho =
        "src/dados/dados.txt";
    ifstream arquivo(caminho);

    if (!arquivo.is_open()) {

        cout << "Erro ao abrir arquivo interno:" << endl;
        cout << caminho << endl;
        return dados;
    }
    string linha;

    while (getline(arquivo, linha)) {

        stringstream ss(linha);
        string strId;
        string nome;
        string strTamanho;
        string strAltura;
        string strLargura;

        if (
            !getline(ss, strId, ';') ||
            !getline(ss, nome, ';') ||
            !getline(ss, strTamanho, ';') ||
            !getline(ss, strAltura, ';') ||
            !getline(ss, strLargura, ';')
        ) {
            continue;
        }
        try {
            int id =
                stoi(strId);
            double tamanho =
                stod(strTamanho);
            int altura =
                stoi(strAltura);
            int largura =
                stoi(strLargura);
            dados.push_back(
                Imagem(
                    id,
                    nome,
                    tamanho,
                    largura,
                    altura
                )
            );
        }
        catch (...) {
            // Ignora cabecalho ou linha invalida
        }
    }
    arquivo.close();
    cout << "\n"
         << dados.size()
         << " dados internos carregados."
         << endl;
    return dados;
}