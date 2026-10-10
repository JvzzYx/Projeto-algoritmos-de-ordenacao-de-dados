#include <vector>
#include "../modelo/imagens.cpp"
using namespace std;

void insertionSort(
    vector<Imagem>& dados,
    int criterio
) {
    int quantidade =
        static_cast<int>(dados.size());
    for (
        int i = 1;
        i < quantidade;
        i++
    ) {
        Imagem chave =
            dados[i];
        int j =
            i - 1;

        while (j >= 0) {
            bool maior = false;
            // ID
            if (criterio == 1) {
                maior =
                    dados[j].getId() >
                    chave.getId();
            }
            // NOME
            else if (criterio == 2) {
                maior =
                    dados[j].getNome() >
                    chave.getNome();
            }
            // TAMANHO
            else if (criterio == 3) {
                maior =
                    dados[j].getTamanho() >
                    chave.getTamanho();
            }
            // LARGURA
            else if (criterio == 4) {
                maior =
                    dados[j].getLargura() >
                    chave.getLargura();
            }
            // ALTURA
            else if (criterio == 5) {
                maior =
                    dados[j].getAltura() >
                    chave.getAltura();
            }
            if (!maior) {
                break;
            }
            dados[j + 1] =
                dados[j];
            j--;
        }
        dados[j + 1] =
            chave;
    }
}