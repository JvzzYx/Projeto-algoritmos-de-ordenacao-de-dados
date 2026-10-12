#include <vector>
#include <utility>
#include "../modelo/imagens.cpp"
using namespace std;

bool menorQue(
    const Imagem& a,
    const Imagem& b,
    int criterio
) {
    if (criterio == 1) {
        return a.getId() < b.getId();
    }
    if (criterio == 2) {
        return a.getNome() < b.getNome();
    }
    if (criterio == 3) {
        return a.getTamanho() < b.getTamanho();
    }
    if (criterio == 4) {
        return a.getLargura() < b.getLargura();
    }
    if (criterio == 5) {
        return a.getAltura() < b.getAltura();
    }
    return false;
}
bool maiorQue(
    const Imagem& a,
    const Imagem& b,
    int criterio
) {
    if (criterio == 1) {
        return a.getId() > b.getId();
    }
    if (criterio == 2) {
        return a.getNome() > b.getNome();
    }
    if (criterio == 3) {
        return a.getTamanho() > b.getTamanho();
    }
    if (criterio == 4) {
        return a.getLargura() > b.getLargura();
    }
    if (criterio == 5) {
        return a.getAltura() > b.getAltura();
    }
    return false;
}
void quickSortAuxiliar(
    vector<Imagem>& dados,
    int esquerda,
    int direita,
    int criterio
) {
    int i = esquerda;
    int j = direita;

    Imagem pivo =
        dados[
            (esquerda + direita) / 2
        ];
    while (i <= j) {
        while (
            menorQue(
                dados[i],
                pivo,
                criterio
            )
        ) {
            i++;
        }
        while (
            maiorQue(
                dados[j],
                pivo,
                criterio
            )
        ) {
            j--;
        }
        if (i <= j) {
            swap(
                dados[i],
                dados[j]
            );
            i++;
            j--;
        }
    }
    if (esquerda < j) {

        quickSortAuxiliar(
            dados,
            esquerda,
            j,
            criterio
        );
    }
    if (i < direita) {
        quickSortAuxiliar(
            dados,
            i,
            direita,
            criterio
        );
    }
}
void quickSort(
    vector<Imagem>& dados,
    int criterio
) {
    if (dados.empty()) {
        return;
    }
    quickSortAuxiliar(
        dados,
        0,
        static_cast<int>(dados.size()) - 1,
        criterio
    );
}