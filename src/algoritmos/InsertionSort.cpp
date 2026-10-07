#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& dados) {
    int quantidade = dados.size();

    for (int i = 1; i < quantidade; i++) {
        int chave = dados[i];
        int j = i - 1;

        // Desloca os elementos maiores que a chave para a direita
        while (j >= 0 && dados[j] > chave) {
            dados[j + 1] = dados[j];
            j--;
        }
        
        // Insere a chave na posição correta
        dados[j + 1] = chave;
    }
}