#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "../modelo/imagens.cpp"
using namespace std;
// =====================================
// FUNCOES DOS OUTROS ARQUIVOS
// =====================================
vector<Imagem> lerArquivoInterno();
vector<Imagem> lerArquivoExterno();
vector<Imagem> selecionarAleatorios(
    const vector<Imagem>& dados,
    int quantidade
);
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
// =====================================
// IDs DOS COMPONENTES
// =====================================
#define ID_ORIGEM       101
#define ID_QUANTIDADE   102
#define ID_CRITERIO     103
#define ID_ALGORITMO    104
#define ID_EXECUTAR     105
#define ID_RESULTADO    106
// =====================================
// CLASSE INTERFACE
// =====================================
class Interface {
private:
    HWND comboOrigem;
    HWND campoQuantidade;
    HWND comboCriterio;
    HWND comboAlgoritmo;
    HWND campoResultado;
    static Interface* instancia;
    static LRESULT CALLBACK WindowProcedure(
        HWND janela,
        UINT mensagem,
        WPARAM wParam,
        LPARAM lParam
    );
    void criarComponentes(
        HWND janela
    );
    void executarPrograma(
        HWND janela
    );
public:
    Interface();

    int iniciar(
        HINSTANCE hInstance,
        int nCmdShow
    );
};
// =====================================
// INSTANCIA DA INTERFACE
// =====================================
Interface* Interface::instancia = nullptr;
// =====================================
// CONSTRUTOR
// =====================================
Interface::Interface() {
    comboOrigem = NULL;
    campoQuantidade = NULL;
    comboCriterio = NULL;
    comboAlgoritmo = NULL;
    campoResultado = NULL;
}
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
// NOME DO CRITERIO
// =====================================

string nomeCriterio(
    int criterio
) {
    if (criterio == 1) {
        return "ID";
    }

    if (criterio == 2) {
        return "Nome";
    }

    if (criterio == 3) {
        return "Tamanho";
    }

    if (criterio == 4) {
        return "Largura";
    }

    if (criterio == 5) {
        return "Altura";
    }

    return "";
}

// =====================================
// EXECUTA O PROGRAMA
// =====================================

void Interface::executarPrograma(
    HWND janela
) {
    vector<Imagem> todosDados;
    vector<Imagem> dadosTeste;

    // =====================================
    // ORIGEM
    // =====================================

    int origem =
        SendMessage(
            comboOrigem,
            CB_GETCURSEL,
            0,
            0
        );

    if (origem == CB_ERR) {
        MessageBoxA(
            janela,
            "Escolha a origem dos dados.",
            "Aviso",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    // Arquivo interno
    if (origem == 0) {
        todosDados =
            lerArquivoInterno();
    }

    // Arquivo externo
    else if (origem == 1) {
        todosDados =
            lerArquivoExterno();
    }

    // Dados aleatorios
    else if (origem == 2) {
        todosDados =
            lerArquivoInterno();
    }

    // =====================================
    // VERIFICA LEITURA
    // =====================================

    if (todosDados.empty()) {
        MessageBoxA(
            janela,
            "Nenhum dado foi carregado.",
            "Erro",
            MB_OK | MB_ICONERROR
        );

        return;
    }

    // =====================================
    // QUANTIDADE
    // =====================================

    char textoQuantidade[20];

    GetWindowTextA(
        campoQuantidade,
        textoQuantidade,
        20
    );

    int quantidade =
        atoi(textoQuantidade);

    if (quantidade <= 0) {
        MessageBoxA(
            janela,
            "Digite uma quantidade valida.",
            "Aviso",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    if (
        quantidade >
        static_cast<int>(todosDados.size())
    ) {
        quantidade =
            static_cast<int>(todosDados.size());
    }

    // =====================================
    // ESCOLHE OS REGISTROS
    // =====================================

    if (origem == 2) {
        dadosTeste =
            selecionarAleatorios(
                todosDados,
                quantidade
            );
    }
    else {
        dadosTeste =
            pegarPrimeiros(
                todosDados,
                quantidade
            );
    }

    // =====================================
    // CRITERIO
    // =====================================

    int criterio =
        SendMessage(
            comboCriterio,
            CB_GETCURSEL,
            0,
            0
        );

    if (criterio == CB_ERR) {
        MessageBoxA(
            janela,
            "Escolha um criterio.",
            "Aviso",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    // ComboBox começa em 0
    // Algoritmos usam 1 ate 5
    criterio =
        criterio + 1;

    // =====================================
    // ALGORITMO
    // =====================================

    int algoritmo =
        SendMessage(
            comboAlgoritmo,
            CB_GETCURSEL,
            0,
            0
        );

    if (algoritmo == CB_ERR) {
        MessageBoxA(
            janela,
            "Escolha um algoritmo.",
            "Aviso",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    // =====================================
    // RESULTADO
    // =====================================

    stringstream resultado;

    resultado
        << fixed
        << setprecision(6);

    resultado
        << "Quantidade: "
        << dadosTeste.size()
        << "\r\n";

    resultado
        << "Criterio: "
        << nomeCriterio(criterio)
        << "\r\n\r\n";

    // =====================================
    // BUBBLE SORT
    // =====================================

    if (algoritmo == 0) {
        vector<Imagem> dadosOrdenados =
            dadosTeste;

        double tempo =
            medirBubble(
                dadosOrdenados,
                criterio
            );

        resultado
            << "Bubble Sort"
            << "\r\n";

        resultado
            << "Tempo: "
            << tempo
            << " segundos";
    }

    // =====================================
    // INSERTION SORT
    // =====================================

    else if (algoritmo == 1) {
        vector<Imagem> dadosOrdenados =
            dadosTeste;

        double tempo =
            medirInsertion(
                dadosOrdenados,
                criterio
            );

        resultado
            << "Insertion Sort"
            << "\r\n";

        resultado
            << "Tempo: "
            << tempo
            << " segundos";
    }

    // =====================================
    // QUICK SORT
    // =====================================

    else if (algoritmo == 2) {
        vector<Imagem> dadosOrdenados =
            dadosTeste;

        double tempo =
            medirQuick(
                dadosOrdenados,
                criterio
            );

        resultado
            << "Quick Sort"
            << "\r\n";

        resultado
            << "Tempo: "
            << tempo
            << " segundos";
    }

    // =====================================
    // COMPARAR TODOS
    // =====================================

    else if (algoritmo == 3) {
        vector<Imagem> dadosBubble =
            dadosTeste;

        vector<Imagem> dadosInsertion =
            dadosTeste;

        vector<Imagem> dadosQuick =
            dadosTeste;

        double tempoBubble =
            medirBubble(
                dadosBubble,
                criterio
            );

        double tempoInsertion =
            medirInsertion(
                dadosInsertion,
                criterio
            );

        double tempoQuick =
            medirQuick(
                dadosQuick,
                criterio
            );

        resultado
            << "COMPARACAO"
            << "\r\n\r\n";

        resultado
            << "Bubble Sort: "
            << tempoBubble
            << " s"
            << "\r\n";

        resultado
            << "Insertion Sort: "
            << tempoInsertion
            << " s"
            << "\r\n";

        resultado
            << "Quick Sort: "
            << tempoQuick
            << " s"
            << "\r\n\r\n";

        double menorTempo =
            tempoBubble;

        string maisRapido =
            "Bubble Sort";

        if (
            tempoInsertion <
            menorTempo
        ) {
            menorTempo =
                tempoInsertion;

            maisRapido =
                "Insertion Sort";
        }

        if (
            tempoQuick <
            menorTempo
        ) {
            menorTempo =
                tempoQuick;

            maisRapido =
                "Quick Sort";
        }

        resultado
            << "Mais rapido: "
            << maisRapido
            << "\r\n";

        resultado
            << "Tempo: "
            << menorTempo
            << " segundos";
    }

    // =====================================
    // MOSTRA RESULTADO
    // =====================================

    string texto =
        resultado.str();

    SetWindowTextA(
        campoResultado,
        texto.c_str()
    );
}

// =====================================
// CRIA OS COMPONENTES DA INTERFACE
// =====================================

void Interface::criarComponentes(
    HWND janela
) {
    // TITULO

    CreateWindowA(
        "STATIC",
        "ALGORITMOS DE ORDENACAO",
        WS_VISIBLE | WS_CHILD,
        150,
        20,
        250,
        25,
        janela,
        NULL,
        NULL,
        NULL
    );

    // =====================================
    // ORIGEM
    // =====================================

    CreateWindowA(
        "STATIC",
        "Origem:",
        WS_VISIBLE | WS_CHILD,
        40,
        80,
        100,
        25,
        janela,
        NULL,
        NULL,
        NULL
    );

    comboOrigem =
        CreateWindowA(
            "COMBOBOX",
            "",
            WS_VISIBLE |
            WS_CHILD |
            CBS_DROPDOWNLIST,
            150,
            75,
            250,
            150,
            janela,
            (HMENU) ID_ORIGEM,
            NULL,
            NULL
        );

    SendMessageA(
        comboOrigem,
        CB_ADDSTRING,
        0,
        (LPARAM) "Arquivo interno"
    );

    SendMessageA(
        comboOrigem,
        CB_ADDSTRING,
        0,
        (LPARAM) "Arquivo externo"
    );

    SendMessageA(
        comboOrigem,
        CB_ADDSTRING,
        0,
        (LPARAM) "Dados aleatorios"
    );

    SendMessage(
        comboOrigem,
        CB_SETCURSEL,
        0,
        0
    );

    // =====================================
    // QUANTIDADE
    // =====================================

    CreateWindowA(
        "STATIC",
        "Quantidade:",
        WS_VISIBLE | WS_CHILD,
        40,
        130,
        100,
        25,
        janela,
        NULL,
        NULL,
        NULL
    );

    campoQuantidade =
        CreateWindowA(
            "EDIT",
            "10000",
            WS_VISIBLE |
            WS_CHILD |
            WS_BORDER |
            ES_NUMBER,
            150,
            125,
            250,
            25,
            janela,
            (HMENU) ID_QUANTIDADE,
            NULL,
            NULL
        );

    // =====================================
    // CRITERIO
    // =====================================

    CreateWindowA(
        "STATIC",
        "Criterio:",
        WS_VISIBLE | WS_CHILD,
        40,
        180,
        100,
        25,
        janela,
        NULL,
        NULL,
        NULL
    );

    comboCriterio =
        CreateWindowA(
            "COMBOBOX",
            "",
            WS_VISIBLE |
            WS_CHILD |
            CBS_DROPDOWNLIST,
            150,
            175,
            250,
            180,
            janela,
            (HMENU) ID_CRITERIO,
            NULL,
            NULL
        );

    SendMessageA(
        comboCriterio,
        CB_ADDSTRING,
        0,
        (LPARAM) "ID"
    );

    SendMessageA(
        comboCriterio,
        CB_ADDSTRING,
        0,
        (LPARAM) "Nome"
    );

    SendMessageA(
        comboCriterio,
        CB_ADDSTRING,
        0,
        (LPARAM) "Tamanho"
    );

    SendMessageA(
        comboCriterio,
        CB_ADDSTRING,
        0,
        (LPARAM) "Largura"
    );

    SendMessageA(
        comboCriterio,
        CB_ADDSTRING,
        0,
        (LPARAM) "Altura"
    );

    SendMessage(
        comboCriterio,
        CB_SETCURSEL,
        0,
        0
    );

    // =====================================
    // ALGORITMO
    // =====================================

    CreateWindowA(
        "STATIC",
        "Algoritmo:",
        WS_VISIBLE | WS_CHILD,
        40,
        230,
        100,
        25,
        janela,
        NULL,
        NULL,
        NULL
    );

    comboAlgoritmo =
        CreateWindowA(
            "COMBOBOX",
            "",
            WS_VISIBLE |
            WS_CHILD |
            CBS_DROPDOWNLIST,
            150,
            225,
            250,
            180,
            janela,
            (HMENU) ID_ALGORITMO,
            NULL,
            NULL
        );

    SendMessageA(
        comboAlgoritmo,
        CB_ADDSTRING,
        0,
        (LPARAM) "Bubble Sort"
    );

    SendMessageA(
        comboAlgoritmo,
        CB_ADDSTRING,
        0,
        (LPARAM) "Insertion Sort"
    );

    SendMessageA(
        comboAlgoritmo,
        CB_ADDSTRING,
        0,
        (LPARAM) "Quick Sort"
    );

    SendMessageA(
        comboAlgoritmo,
        CB_ADDSTRING,
        0,
        (LPARAM) "Comparar todos"
    );

    SendMessage(
        comboAlgoritmo,
        CB_SETCURSEL,
        2,
        0
    );

    // =====================================
    // BOTAO EXECUTAR
    // =====================================

    CreateWindowA(
        "BUTTON",
        "EXECUTAR",
        WS_VISIBLE |
        WS_CHILD |
        BS_PUSHBUTTON,
        150,
        290,
        250,
        40,
        janela,
        (HMENU) ID_EXECUTAR,
        NULL,
        NULL
    );

    // =====================================
    // RESULTADO
    // =====================================

    CreateWindowA(
        "STATIC",
        "Resultado:",
        WS_VISIBLE | WS_CHILD,
        40,
        360,
        100,
        25,
        janela,
        NULL,
        NULL,
        NULL
    );

    campoResultado =
        CreateWindowA(
            "EDIT",
            "Aguardando execucao...",
            WS_VISIBLE |
            WS_CHILD |
            WS_BORDER |
            ES_MULTILINE |
            ES_READONLY |
            ES_AUTOVSCROLL |
            WS_VSCROLL,
            40,
            390,
            440,
            140,
            janela,
            (HMENU) ID_RESULTADO,
            NULL,
            NULL
        );
}

// =====================================
// CONTROLA OS EVENTOS DA JANELA
// =====================================

LRESULT CALLBACK Interface::WindowProcedure(
    HWND janela,
    UINT mensagem,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (mensagem) {
        case WM_CREATE:
        {
            if (
                instancia != nullptr
            ) {
                instancia->criarComponentes(
                    janela
                );
            }

            break;
        }

        case WM_COMMAND:
        {
            if (
                LOWORD(wParam) ==
                ID_EXECUTAR
            ) {
                if (
                    instancia != nullptr
                ) {
                    instancia->executarPrograma(
                        janela
                    );
                }
            }

            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);

            break;
        }

        default:
        {
            return DefWindowProcA(
                janela,
                mensagem,
                wParam,
                lParam
            );
        }
    }

    return 0;
}

// =====================================
// INICIA A INTERFACE
// =====================================

int Interface::iniciar(
    HINSTANCE hInstance,
    int nCmdShow
) {
    instancia = this;

    const char NOME_CLASSE[] =
        "InterfaceOrdenacao";

    WNDCLASSA wc = {};

    wc.lpfnWndProc =
        WindowProcedure;

    wc.hInstance =
        hInstance;

    wc.lpszClassName =
        NOME_CLASSE;

    wc.hCursor =
        LoadCursor(
            NULL,
            IDC_ARROW
        );

    wc.hbrBackground =
        (HBRUSH)(
            COLOR_WINDOW + 1
        );

    RegisterClassA(
        &wc
    );

    HWND janela =
        CreateWindowExA(
            0,
            NOME_CLASSE,
            "Projeto de Ordenacao",
            WS_OVERLAPPED |
            WS_CAPTION |
            WS_SYSMENU |
            WS_MINIMIZEBOX,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            540,
            600,
            NULL,
            NULL,
            hInstance,
            NULL
        );

    if (
        janela == NULL
    ) {
        MessageBoxA(
            NULL,
            "Erro ao criar a interface.",
            "Erro",
            MB_OK | MB_ICONERROR
        );

        return 0;
    }

    ShowWindow(
        janela,
        nCmdShow
    );

    UpdateWindow(
        janela
    );

    MSG mensagem = {};

    while (
        GetMessage(
            &mensagem,
            NULL,
            0,
            0
        )
    ) {
        TranslateMessage(
            &mensagem
        );

        DispatchMessage(
            &mensagem
        );
    }

    return 0;
}

// =====================================
// FUNCAO QUE A MAIN CHAMA
// =====================================

int iniciarInterface(
    HINSTANCE hInstance,
    int nCmdShow
) {
    Interface interfacePrograma;

    return interfacePrograma.iniciar(
        hInstance,
        nCmdShow
    );
}