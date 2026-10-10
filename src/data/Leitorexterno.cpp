#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <windows.h>
#include <commdlg.h>

#include "../modelo/imagens.cpp"

using namespace std;


// Abre janela para escolher TXT
string selecionarArquivoTXT() {

    OPENFILENAMEA arquivo;

    char caminho[MAX_PATH] = "";

    ZeroMemory(
        &arquivo,
        sizeof(arquivo)
    );

    arquivo.lStructSize =
        sizeof(arquivo);

    arquivo.hwndOwner =
        NULL;

    arquivo.lpstrFile =
        caminho;

    arquivo.nMaxFile =
        MAX_PATH;

    arquivo.lpstrFilter =
        "Arquivos TXT\0*.txt\0"
        "Todos os Arquivos\0*.*\0";

    arquivo.nFilterIndex = 1;

    arquivo.Flags =
        OFN_PATHMUSTEXIST |
        OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&arquivo)) {

        return string(caminho);
    }

    return "";
}


// Le o arquivo escolhido
vector<Imagem> lerArquivoExterno() {

    vector<Imagem> dados;

    cout << "\nAbrindo seletor de arquivo..." << endl;

    string caminho =
        selecionarArquivoTXT();

    if (caminho.empty()) {

        cout << "Nenhum arquivo selecionado." << endl;

        return dados;
    }

    cout << "\nArquivo selecionado:" << endl;
    cout << caminho << endl;

    ifstream arquivo(caminho);

    if (!arquivo.is_open()) {

        cout << "Erro ao abrir arquivo." << endl;

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
         << " dados externos carregados."
         << endl;

    return dados;
}