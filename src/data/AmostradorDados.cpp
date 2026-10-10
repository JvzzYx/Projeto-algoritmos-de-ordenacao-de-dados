#include <vector>
#include <algorithm>
#include <random>
#include "../modelo/imagens.cpp"
using namespace std;

vector<Imagem> selecionarAleatorios(
    const vector<Imagem>& dados,
    int quantidade
) {
    vector<Imagem> amostra = dados;

    if (
        quantidade >
        static_cast<int>(amostra.size())
    ) {
        quantidade =
            static_cast<int>(amostra.size());
    }
    random_device rd;
    mt19937 gerador(rd());

    shuffle(
        amostra.begin(),
        amostra.end(),
        gerador
    );
    amostra.erase(
        amostra.begin() + quantidade,
        amostra.end()
    );
    return amostra;
}