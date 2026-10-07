#include <iostream>
#include <vector> 
#include <utility> 
using namespace std;

int particionar(vector<int>& dados, int inicio, int fim) {
    int pivo = dados[fim]; // Ultimo elemento como pivô
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (dados[j] <= pivo) {
            i++;
            swap(dados[i], dados[j]);
        }
    }
    swap(dados[i + 1], dados[fim]);
    return i + 1;
}
void quickSortAuxiliar(vector<int>& dados, int inicio, int fim) {
    if (inicio < fim) {
        int pivoIndice = particionar(dados, inicio, fim);

        // Ordena as duas parte
        quickSortAuxiliar(dados, inicio, pivoIndice - 1);
        quickSortAuxiliar(dados, pivoIndice + 1, fim);
    }
}
void quickSort(vector<int>& dados) {
    if (!dados.empty()) {
        quickSortAuxiliar(dados, 0, dados.size() - 1);
    }
}