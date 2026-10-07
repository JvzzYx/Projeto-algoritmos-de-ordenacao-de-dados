#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<int> lerTXT(const string& caminhoArquivo) {

    vector<int> dados;

    ifstream arquivo(caminhoArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: "
             << caminhoArquivo << endl;

        return dados;
    }

    string linha;

    // Ignora o cabeçalho
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {

        stringstream ss(linha);

        string strId;
        string nome;
        string strTamanho;
        string strAltura;
        string strLargura;

        getline(ss, strId, ';');
        getline(ss, nome, ';');
        getline(ss, strTamanho, ';');
        getline(ss, strAltura, ';');
        getline(ss, strLargura, ';');

        try {

            int id = stoi(strId);
            // Por enquanto envia o ID
            // para os algoritmos de ordenacao
            dados.push_back(id);

        }
        catch (...) {

            cout << "Erro ao ler linha: "
                 << linha << endl;
        }
    }

    arquivo.close();

    return dados;
}