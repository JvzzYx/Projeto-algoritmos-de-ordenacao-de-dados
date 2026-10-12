#include <vector>
#include "../modelo/imagens.cpp"
using namespace std;

void bubbleSort(
    vector<Imagem>& dados,
    int criterio
) {
    int quantidade =
        static_cast<int>(dados.size());
    bool trocou;
    for (
        int i = 0;
        i < quantidade - 1;
        i++
    ) {
        trocou = false;
        for (
            int j = 0;
            j < quantidade - i - 1;
            j++
        ) {
            bool precisaTrocar = false;
            // ID
            if (criterio == 1) {
                precisaTrocar =
                    dados[j].getId() >
                    dados[j + 1].getId();
            }
            // NOME
            else if (criterio == 2) {
                precisaTrocar =
                    dados[j].getNome() >
                    dados[j + 1].getNome();
            }
            // TAMANHO
            else if (criterio == 3) {
                precisaTrocar =
                    dados[j].getTamanho() >
                    dados[j + 1].getTamanho();
            }
            // LARGURA
            else if (criterio == 4) {
                precisaTrocar =
                    dados[j].getLargura() >
                    dados[j + 1].getLargura();
            }
            // ALTURA
            else if (criterio == 5) {
                precisaTrocar =
                    dados[j].getAltura() >
                    dados[j + 1].getAltura();
            }
            if (precisaTrocar) {
                Imagem temp =
                    dados[j];
                dados[j] =
                    dados[j + 1];
                dados[j + 1] =
                    temp;
                trocou = true;
            }
        }
        if (!trocou) {
            break;
        }
    }
}