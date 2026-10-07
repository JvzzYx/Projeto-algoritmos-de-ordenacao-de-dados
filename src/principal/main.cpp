#include <iostream>
#include <vector>
#include <string>

// Inclusão das classes
#include "../modelo/imagens.h"
#include "../data/LeitorTXT.h"
#include "../algoritmos/BubbleSort.h"
#include "../algoritmos/InsertionSort.h"
#include "../algoritmos/QuickSort.h"
#include "../desempenho/desempenho.h"
#include "interface.h"

using namespace std;

int main() {
    // Caminho para o ficheiro CSV
    string caminhoTXT = "../dados/imagens.txt";

    vector<Imagem> listaImagens = LeitorTXT::ler(caminhoTXT);

    if (listaImagens.empty()) {
        cout << "Nenhum dado carregado." << endl;
        return 1;
    }

    cout << "Foram carregadas " << listaImagens.size() << " imagens do ficheiro TXT." << endl;

    // Cópias algoritmos separadamente
    vector<Imagem> dadosBubble = listaImagens;
    vector<Imagem> dadosInsertion = listaImagens;
    vector<Imagem> dadosQuick = listaImagens;

    // Execução e medição do Bubble Sort
    cout << "A executar Bubble Sort..." << endl;
    bubbleSort(dadosBubble);

    // Execução e medição do Insertion Sort
    cout << "A executar Insertion Sort..." << endl;
    insertionSort(dadosInsertion);

    // Execução e medição do Quick Sort
    cout << "A executar Quick Sort..." << endl;
    quickSort(dadosQuick);

    return 0;
}