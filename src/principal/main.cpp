#include <iostream>
#include <vector>
#include <iomanip>
#include "../modelo/imagens.cpp"
using namespace std;

// =====================================
// LEITORES
// =====================================
vector<Imagem> lerArquivoInterno();
vector<Imagem> lerArquivoExterno();
// =====================================
// AMOSTRADOR
// =====================================
vector<Imagem> selecionarAleatorios(
    const vector<Imagem>& dados,
    int quantidade
);
// =====================================
// DESEMPENHO
// =====================================
double medirBubble(
    vector<Imagem>& dados,
    int criterio
);
double medirInsertion(
    vector<Imagem>& dados,
    int criterio
);
double medirQuick(
    vector<Imagem>& dados,
    int criterio
);
void compararDesempenho(
    const vector<Imagem>& dados,
    int criterio
);
// =====================================
// PEGA OS PRIMEIROS REGISTROS
// =====================================
vector<Imagem> pegarPrimeiros(
    const vector<Imagem>& dados,
    int quantidade
) {
    if (
        quantidade >
        static_cast<int>(dados.size())
    ) {
        quantidade =
            static_cast<int>(dados.size());
    }
    return vector<Imagem>(
        dados.begin(),
        dados.begin() + quantidade
    );
}
// =====================================
// MOSTRA OS PRIMEIROS REGISTROS
// =====================================
void mostrarDados(
    const vector<Imagem>& dados
) {
    int limite =
        static_cast<int>(dados.size()); 
    if (limite > 20) {
        limite = 20;
    }
    cout << "\n========================================" << endl;
    cout << "      PRIMEIROS REGISTROS" << endl;
    cout << "========================================" << endl;
    for (
        int i = 0;
        i < limite;
        i++
    ) {
        cout << "ID: "
             << dados[i].getId();
        cout << " | Nome: "
             << dados[i].getNome();
        cout << " | Tamanho: "
             << dados[i].getTamanho();
        cout << " | Largura: "
             << dados[i].getLargura();
        cout << " | Altura: "
             << dados[i].getAltura();
        cout << endl;
    }
}
// =====================================
// MAIN
// =====================================
int main() {
    vector<Imagem> todosDados;
    vector<Imagem> dadosTeste;

    // =====================================
    // ORIGEM
    // =====================================
    int origem;
    cout << "========================================" << endl;
    cout << "          ORIGEM DOS DADOS" << endl;
    cout << "========================================" << endl;
    cout << "1 - Arquivo interno" << endl;
    cout << "2 - Arquivo externo" << endl;
    cout << "3 - Amostrador aleatorio" << endl;
    cout << "0 - Sair" << endl;
    cout << "\nEscolha: ";
    cin >> origem;

    // INTERNO
    if (origem == 1) {
        cout << "\nCarregando arquivo interno..." << endl;
        todosDados =
            lerArquivoInterno();
    }
    // EXTERNO
    else if (origem == 2) {

        todosDados =
            lerArquivoExterno();
    }
    // AMOSTRADOR
    else if (origem == 3) {
        cout << "\nCarregando arquivo interno para amostragem..."
             << endl;
        todosDados =
            lerArquivoInterno();
    }
    // SAIR
    else if (origem == 0) {
        cout << "\nPrograma encerrado." << endl;
        return 0;
    }
    else {
        cout << "\nOpcao invalida." << endl;
        return 0;
    }
    // =====================================
    // VERIFICA LEITURA
    // =====================================
    if (todosDados.empty()) {
        cout << "\nNenhum dado foi carregado." << endl;
        return 0;
    }
    cout << "\nTotal disponivel: "
         << todosDados.size()
         << " registros"
         << endl;
    // =====================================
    // QUANTIDADE
    // =====================================
    int quantidade;
    cout << "\nQuantidade de registros para testar: ";
    cin >> quantidade;

    if (quantidade <= 0) {
        cout << "\nQuantidade invalida." << endl;
        return 0;
    }
    if (
        quantidade >
        static_cast<int>(todosDados.size())
    ) {
        cout << "\nQuantidade maior que o total disponivel."
             << endl;
        quantidade =
            static_cast<int>(todosDados.size());
        cout << "Usando "
             << quantidade
             << " registros."
             << endl;
    }
    // =====================================
    // ESCOLHE OS REGISTROS
    // =====================================
    if (origem == 3) {
        // Amostra aleatoria
        dadosTeste =
            selecionarAleatorios(
                todosDados,
                quantidade
            );
    }
    else {
        // Interno ou externo
        // pega os primeiros registros
        dadosTeste =
            pegarPrimeiros(
                todosDados,
                quantidade
            );
    }
    cout << "\nRegistros selecionados: "
         << dadosTeste.size()
         << endl;
    // =====================================
    // CRITERIO
    // =====================================
    int criterio;
    cout << "\n========================================" << endl;
    cout << "        CRITERIO DE ORDENACAO" << endl;
    cout << "========================================" << endl;
    cout << "1 - ID" << endl;
    cout << "2 - Nome" << endl;
    cout << "3 - Tamanho" << endl;
    cout << "4 - Largura" << endl;
    cout << "5 - Altura" << endl;
    cout << "\nEscolha: ";
    cin >> criterio;
    if (
        criterio < 1 ||
        criterio > 5
    ) {
        cout << "\nCriterio invalido." << endl;

        return 0;
    }
    // =====================================
    // ALGORITMO
    // =====================================
    int algoritmo;
    cout << "\n========================================" << endl;
    cout << "       ALGORITMO DE ORDENACAO" << endl;
    cout << "========================================" << endl;
    cout << "1 - Bubble Sort" << endl;
    cout << "2 - Insertion Sort" << endl;
    cout << "3 - Quick Sort" << endl;
    cout << "4 - Comparar todos" << endl;
    cout << "0 - Sair" << endl;
    cout << "\nEscolha: ";
    cin >> algoritmo;
    cout << fixed
         << setprecision(6);
    // =====================================
    // BUBBLE SORT
    // =====================================
    if (algoritmo == 1) {
        vector<Imagem> dadosOrdenados =
            dadosTeste;
        cout << "\nExecutando Bubble Sort..."
             << endl;
        double tempo =
            medirBubble(
                dadosOrdenados,
                criterio
            );
        cout << "\nTempo Bubble Sort: "
             << tempo
             << " segundos"
             << endl;
        mostrarDados(
            dadosOrdenados
        );
    }
    // =====================================
    // INSERTION SORT
    // =====================================
    else if (algoritmo == 2) {
        vector<Imagem> dadosOrdenados =
            dadosTeste;
        cout << "\nExecutando Insertion Sort..."
             << endl;
        double tempo =
            medirInsertion(
                dadosOrdenados,
                criterio
            );
        cout << "\nTempo Insertion Sort: "
             << tempo
             << " segundos"
             << endl;
        mostrarDados(
            dadosOrdenados
        );
    }
    // =====================================
    // QUICK SORT
    // =====================================
    else if (algoritmo == 3) {
        vector<Imagem> dadosOrdenados =
            dadosTeste;
        cout << "\nExecutando Quick Sort..."
             << endl;
        double tempo =
            medirQuick(
                dadosOrdenados,
                criterio
            );
        cout << "\nTempo Quick Sort: "
             << tempo
             << " segundos"
             << endl;
        mostrarDados(
            dadosOrdenados
        );
    }
    // =====================================
    // COMPARAR TODOS
    // =====================================
    else if (algoritmo == 4) {
        compararDesempenho(
            dadosTeste,
            criterio
        );
    }
    // ======+==============================
    // SAIR
    // =====================================
    else if (algoritmo == 0) {
        cout << "\nPrograma encerrado." << endl;
        return 0;
    }
    else {
        cout << "\nOpcao invalida." << endl;
        return 0;
    }
    cout << "\nPrograma finalizado." << endl;
    return 0;
}