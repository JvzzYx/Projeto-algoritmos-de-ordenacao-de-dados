#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include "../modelo/imagens.cpp"

using namespace std;
// ALGORITMOS DE ORDENACAO
void bubbleSort(
    vector<Imagem>& dados,
    int criterio
);
void insertionSort(
    vector<Imagem>& dados,
    int criterio
);
void quickSort(
    vector<Imagem>& dados,
    int criterio
);
double medirBubble(
    vector<Imagem>& dados,
    int criterio
) {
    auto inicio =
        chrono::high_resolution_clock::now();
    bubbleSort(
        dados,
        criterio
    );
    auto fim =
        chrono::high_resolution_clock::now();
    chrono::duration<double> tempo =
        fim - inicio;
    return tempo.count();
}
double medirInsertion(
    vector<Imagem>& dados,
    int criterio
) {
    auto inicio =
        chrono::high_resolution_clock::now();
    insertionSort(
        dados,
        criterio
    );
    auto fim =
        chrono::high_resolution_clock::now();
    chrono::duration<double> tempo =
        fim - inicio;
    return tempo.count();
}
double medirQuick(
    vector<Imagem>& dados,
    int criterio
) {
    auto inicio =
        chrono::high_resolution_clock::now();
    quickSort(
        dados,
        criterio
    );
    auto fim =
        chrono::high_resolution_clock::now();
    chrono::duration<double> tempo =
        fim - inicio;
    return tempo.count();
}
void compararDesempenho(
    const vector<Imagem>& dados,
    int criterio
) {
    // Os tres recebem os mesmos dados
    vector<Imagem> dadosBubble =
        dados;
    vector<Imagem> dadosInsertion =
        dados;
    vector<Imagem> dadosQuick =
        dados;
    cout << "\n========================================" << endl;
    cout << "       COMPARACAO DE DESEMPENHO" << endl;
    cout << "========================================" << endl;

    cout << "Quantidade: "
         << dados.size()
         << " registros"
         << endl;
    cout << "\nExecutando Bubble Sort..." << endl;

    double bubble =
        medirBubble(
            dadosBubble,
            criterio
        );
    cout << "Executando Insertion Sort..." << endl;

    double insertion =
        medirInsertion(
            dadosInsertion,
            criterio
        );
    cout << "Executando Quick Sort..." << endl;

    double quick =
        medirQuick(
            dadosQuick,
            criterio
        );
    cout << fixed
         << setprecision(6);

    cout << "\n========================================" << endl;
    cout << "               RESULTADOS" << endl;
    cout << "========================================" << endl;

    cout << "Bubble Sort:    "
         << bubble
         << " segundos"
         << endl;
    cout << "Insertion Sort: "
         << insertion
         << " segundos"
         << endl;
    cout << "Quick Sort:     "
         << quick
         << " segundos"
         << endl;

    double menor =
        bubble;

    string maisRapido =
        "Bubble Sort";
    if (insertion < menor) {
        menor =
            insertion;
        maisRapido =
            "Insertion Sort";
    }
    if (quick < menor) {
        menor =
            quick;
        maisRapido =
            "Quick Sort";
    }
    cout << "\nMais rapido: "
         << maisRapido
         << endl;
    cout << "Tempo: "
         << menor
         << " segundos"
         << endl;
    cout << "========================================" << endl;
}