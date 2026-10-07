#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Chamando os 3 algoritmos de ordenacao
void bubbleSort(vector<int>& dados);
void insertionSort(vector<int>& dados);
void quickSort(vector<int>& dados);

// LeitorTXT.cpp
vector<int> lerTXT(const string& caminhoArquivo);

int main() {

    // Lendo arquivo de dados txt e armazenando os dados em um vetor
    vector<int> dados = lerTXT("../dados/dados.txt");

    // Verifica se os dados foram carregados
    if (dados.empty()) {
        cout << "Nenhum dado foi carregado." << endl;
        return 0;
    }

    cout << "Quantidade de dados carregados: "
         << dados.size()
         << endl;

    int opcao;

    do {

        cout << "\n==============================" << endl;
        cout << "   ALGORITMOS DE ORDENACAO" << endl;
        cout << "==============================" << endl;

        cout << "1 - Bubble Sort" << endl;
        cout << "2 - Insertion Sort" << endl;
        cout << "3 - Quick Sort" << endl;
        cout << "0 - Sair" << endl;

        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        // Faz uma copia dos dados originais
        vector<int> dadosOrdenados = dados;

        switch (opcao) {

            case 1:

                cout << "\nExecutando Bubble Sort..." << endl;

                bubbleSort(dadosOrdenados);

                break;

            case 2:

                cout << "\nExecutando Insertion Sort..." << endl;

                insertionSort(dadosOrdenados);

                break;

            case 3:

                cout << "\nExecutando Quick Sort..." << endl;

                quickSort(dadosOrdenados);

                break;

            case 0:

                cout << "\nPrograma encerrado." << endl;

                break;

            default:

                cout << "\nOpcao invalida!" << endl;

                continue;
        }

        if (opcao != 0) {

            cout << "\nPrimeiros 20 dados ordenados:" << endl;

            int quantidadeMostrar = 20;

            if (dadosOrdenados.size() < 20) {
                quantidadeMostrar = dadosOrdenados.size();
            }

            for (int i = 0; i < quantidadeMostrar; i++) {

                cout << dadosOrdenados[i] << " ";

            }

            cout << endl;
        }

    } while (opcao != 0);

    return 0;
}