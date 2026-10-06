#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& dados) {
    int quantidade = dados.size();
      bool trocou;

    for (int i = 0; i < quantidade - 1; i++) {
        trocou = false;
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (dados[j] > dados[j + 1]) {
                int temp = dados[j];
                dados[j] = dados[j + 1];
                dados[j + 1] = temp;
                trocou = true;         
            }
        }
        if (!trocou) {
            break;
        }
    }
}
