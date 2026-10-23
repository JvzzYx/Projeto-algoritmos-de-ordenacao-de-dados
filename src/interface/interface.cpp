#include <windows.h>
#include <commdlg.h>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "../modelo/imagens.cpp"

using namespace std;

string caminhoArquivoExterno = "";

// =======================================================
// DECLARACOES DAS FUNCOES EXTERNAS DO PROJETO
// =======================================================

vector<Imagem> lerArquivoInterno();
vector<Imagem> lerArquivoExterno();
vector<Imagem> selecionarAleatorios(const vector<Imagem> &dados,
                                    int quantidade);
double medirBubble(vector<Imagem> &dados, int criterio);
double medirInsertion(vector<Imagem> &dados, int criterio);
double medirQuick(vector<Imagem> &dados, int criterio);

// =======================================================
// IDENTIFICADORES (IDS) DOS COMPONENTES VISUAIS
// =======================================================

// Origem dos Dados
#define ID_ORIGEM_0 101
#define ID_ORIGEM_1 102
#define ID_ORIGEM_2 103
#define ID_BTN_PROCURAR 104
#define ID_LABEL_ARQUIVO 105

// Quantidade e Atalhos (Presets)
#define ID_QUANTIDADE 201
#define ID_PRESET_1000 202
#define ID_PRESET_5000 203
#define ID_PRESET_10000 204
#define ID_PRESET_50000 205

// Criterios de Ordenacao
#define ID_CRIT_0 301
#define ID_CRIT_1 302
#define ID_CRIT_2 303
#define ID_CRIT_3 304
#define ID_CRIT_4 305

// Algoritmos de Ordenacao
#define ID_ALGO_0 401
#define ID_ALGO_1 402
#define ID_ALGO_2 403
#define ID_ALGO_3 404

// Botoes de Acao e Terminal
#define ID_EXECUTAR 501
#define ID_BTN_LIMPAR 502
#define ID_RESULTADO 503

// =======================================================
// ATIVAR MODO ESCURO NA BARRA DE TITULO (WINDOWS 10 E 11)
// =======================================================

void ativarBarraTituloEscura(HWND janela) {
  HMODULE hDwmapi = LoadLibraryA("dwmapi.dll");
  if (hDwmapi) {
    typedef HRESULT(WINAPI * DwmFunc)(HWND, DWORD, LPCVOID, DWORD);
    DwmFunc setAttr = (DwmFunc)GetProcAddress(hDwmapi, "DwmSetWindowAttribute");
    if (setAttr) {
      BOOL modoEscuro = TRUE;
      if (FAILED(setAttr(janela, 20, &modoEscuro, sizeof(modoEscuro)))) {
        setAttr(janela, 19, &modoEscuro, sizeof(modoEscuro));
      }
    }
    FreeLibrary(hDwmapi);
  }
}

// =======================================================
// CLASSE PRINCIPAL DA INTERFACE
// =======================================================

class Interface {
private:
  // Estado atual das escolhas do usuario
  int origemSelecionada;    // 0 = Interno, 1 = Externo, 2 = Aleatorios
  int criterioSelecionado;  // 0 = ID, 1 = Nome, 2 = Tamanho, 3 = Largura, 4 =
                            // Altura
  int algoritmoSelecionado; // 0 = Bubble, 1 = Insertion, 2 = Quick, 3 =
                            // Comparar Todos

  // Controles da janela (HWND)
  HWND labelTitulo;
  HWND labelSubtitulo;

  HWND labelSecaoOrigem;
  HWND btnOrigem[3];
  HWND btnProcurar;
  HWND labelArquivo;

  HWND labelSecaoQtd;
  HWND campoQuantidade;
  HWND btnPresets[4];

  HWND labelSecaoCrit;
  HWND btnCriterio[5];

  HWND labelSecaoAlgo;
  HWND btnAlgoritmo[4];

  HWND btnExecutar;
  HWND btnLimpar;

  HWND labelSecaoResultado;
  HWND campoResultado;

  // Fontes visuais
  HFONT hFontTitulo;
  HFONT hFontSubtitulo;
  HFONT hFontSecao;
  HFONT hFontPadrao;
  HFONT hFontBotao;
  HFONT hFontBotaoExecutar;
  HFONT hFontTerminal;

  // Cores de fundo (Brushes)
  HBRUSH hBrushFundo;
  HBRUSH hBrushCampo;
  HBRUSH hBrushTerminal;

  static Interface *instancia;

  // Metodos auxiliares
  void criarComponentes(HWND janela);
  void redimensionar(int largura, int altura);
  void executarPrograma(HWND janela);
  void selecionarArquivoExterno(HWND janela);
  void atualizarBotoes();

  static LRESULT CALLBACK WindowProcedure(HWND janela, UINT mensagem,
                                          WPARAM wParam, LPARAM lParam);

public:
  Interface();
  ~Interface();

  int iniciar(HINSTANCE hInstance, int nCmdShow);
};

// Instancia estatica para a funcao de callback da janela
Interface *Interface::instancia = nullptr;

// =======================================================
// CONSTRUTOR - CONFIGURA CORES E FONTES
// =======================================================

Interface::Interface() {
  origemSelecionada = 0;
  criterioSelecionado = 0;
  algoritmoSelecionado = 3; // Padrao: Comparar todos

  // Inicializacao dos ponteiros de controles
  labelTitulo = NULL;
  labelSubtitulo = NULL;
  labelSecaoOrigem = NULL;
  labelSecaoQtd = NULL;
  labelSecaoCrit = NULL;
  labelSecaoAlgo = NULL;
  labelSecaoResultado = NULL;

  for (int i = 0; i < 3; ++i)
    btnOrigem[i] = NULL;
  btnProcurar = NULL;
  labelArquivo = NULL;

  campoQuantidade = NULL;
  for (int i = 0; i < 4; ++i)
    btnPresets[i] = NULL;
  for (int i = 0; i < 5; ++i)
    btnCriterio[i] = NULL;
  for (int i = 0; i < 4; ++i)
    btnAlgoritmo[i] = NULL;

  btnExecutar = NULL;
  btnLimpar = NULL;
  campoResultado = NULL;

  // Paleta de Cores Moderna (Dark Theme)
  hBrushFundo =
      CreateSolidBrush(RGB(15, 23, 42)); // Fundo geral escuro (Slate-900)
  hBrushCampo = CreateSolidBrush(
      RGB(30, 41, 59)); // Fundo dos campos de entrada (Slate-800)
  hBrushTerminal = CreateSolidBrush(RGB(8, 12, 20)); // Fundo do console escuro

  // 1. Titulo principal em destaque (28px Negrito)
  hFontTitulo =
      CreateFontA(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                  DEFAULT_PITCH | FF_SWISS, "Segoe UI");

  // 2. Subtitulo legivel (16px)
  hFontSubtitulo =
      CreateFontA(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                  DEFAULT_PITCH | FF_SWISS, "Segoe UI");

  // 3. Titulos de secao (15px Negrito)
  hFontSecao =
      CreateFontA(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                  DEFAULT_PITCH | FF_SWISS, "Segoe UI");

  // 4. Texto padrao dos campos (16px)
  hFontPadrao =
      CreateFontA(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                  DEFAULT_PITCH | FF_SWISS, "Segoe UI");

  // 5. Botoes seletores normais (16px Negrito)
  hFontBotao =
      CreateFontA(16, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
                  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                  CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");

  // 6. Botao principal Executar (18px Negrito)
  hFontBotaoExecutar =
      CreateFontA(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                  DEFAULT_PITCH | FF_SWISS, "Segoe UI");

  // 7. Terminal de Resultados (16px Consolas Monospace - facil de ler)
  hFontTerminal =
      CreateFontA(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                  FIXED_PITCH | FF_MODERN, "Consolas");
}

// =======================================================
// DESTRUTOR - LIBERA OS RECURSOS CRIADOS
// =======================================================

Interface::~Interface() {
  if (hFontTitulo)
    DeleteObject(hFontTitulo);
  if (hFontSubtitulo)
    DeleteObject(hFontSubtitulo);
  if (hFontSecao)
    DeleteObject(hFontSecao);
  if (hFontPadrao)
    DeleteObject(hFontPadrao);
  if (hFontBotao)
    DeleteObject(hFontBotao);
  if (hFontBotaoExecutar)
    DeleteObject(hFontBotaoExecutar);
  if (hFontTerminal)
    DeleteObject(hFontTerminal);

  if (hBrushFundo)
    DeleteObject(hBrushFundo);
  if (hBrushCampo)
    DeleteObject(hBrushCampo);
  if (hBrushTerminal)
    DeleteObject(hBrushTerminal);
}

// =======================================================
// FUNCOES DE AJUDA
// =======================================================

void Interface::atualizarBotoes() {
  for (int i = 0; i < 3; ++i)
    if (btnOrigem[i])
      InvalidateRect(btnOrigem[i], NULL, TRUE);
  for (int i = 0; i < 5; ++i)
    if (btnCriterio[i])
      InvalidateRect(btnCriterio[i], NULL, TRUE);
  for (int i = 0; i < 4; ++i)
    if (btnAlgoritmo[i])
      InvalidateRect(btnAlgoritmo[i], NULL, TRUE);
}

vector<Imagem> pegarPrimeiros(const vector<Imagem> &dados, int quantidade) {
  if (quantidade > static_cast<int>(dados.size())) {
    quantidade = static_cast<int>(dados.size());
  }
  return vector<Imagem>(dados.begin(), dados.begin() + quantidade);
}

string nomeCriterio(int criterio) {
  if (criterio == 1)
    return "ID";
  if (criterio == 2)
    return "Nome";
  if (criterio == 3)
    return "Tamanho";
  if (criterio == 4)
    return "Largura";
  if (criterio == 5)
    return "Altura";
  return "";
}

// =======================================================
// SELECAO DE ARQUIVO EXTERNO COM CAIXA DE DIALOGO
// =======================================================

void Interface::selecionarArquivoExterno(HWND janela) {
  char filename[MAX_PATH] = "";
  OPENFILENAMEA ofn;
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = janela;
  ofn.lpstrFilter = "Arquivos de Dados (*.csv;*.txt)\0*.csv;*.txt\0Todos os "
                    "Arquivos (*.*)\0*.*\0";
  ofn.lpstrFile = filename;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if (GetOpenFileNameA(&ofn)) {
    caminhoArquivoExterno = filename;

    string nomeExibicao = caminhoArquivoExterno;
    size_t lastSlash = nomeExibicao.find_last_of("\\/");
    if (lastSlash != string::npos) {
      nomeExibicao = nomeExibicao.substr(lastSlash + 1);
    }
    SetWindowTextA(labelArquivo,
                   ("Arquivo selecionado: " + nomeExibicao).c_str());
    origemSelecionada = 1;
    atualizarBotoes();
  }
}

// =======================================================
// EXECUTA OS ALGORITMOS E EXIBE NO TERMINAL
// =======================================================

void Interface::executarPrograma(HWND janela) {
  vector<Imagem> todosDados;
  vector<Imagem> dadosTeste;

  // 1. Carrega os dados de acordo com a origem
  if (origemSelecionada == 0) {
    todosDados = lerArquivoInterno();
  } else if (origemSelecionada == 1) {
    if (caminhoArquivoExterno.empty()) {
      MessageBoxA(janela,
                  "Por favor, clique em 'Escolher arquivo...' para selecionar "
                  "o arquivo externo.",
                  "Aviso", MB_OK | MB_ICONWARNING);
      return;
    }
    todosDados = lerArquivoExterno();
  } else if (origemSelecionada == 2) {
    todosDados = lerArquivoInterno();
  }

  if (todosDados.empty()) {
    MessageBoxA(janela, "Nenhum dado foi carregado com sucesso.", "Erro",
                MB_OK | MB_ICONERROR);
    return;
  }

  // 2. Le a quantidade digitada
  char textoQuantidade[20];
  GetWindowTextA(campoQuantidade, textoQuantidade, 20);
  int quantidade = atoi(textoQuantidade);

  if (quantidade <= 0) {
    MessageBoxA(janela, "Digite uma quantidade valida de registros (ex: 5000).",
                "Aviso", MB_OK | MB_ICONWARNING);
    return;
  }

  if (quantidade > static_cast<int>(todosDados.size())) {
    quantidade = static_cast<int>(todosDados.size());
  }

  // 3. Prepara a amostra de dados
  if (origemSelecionada == 2) {
    dadosTeste = selecionarAleatorios(todosDados, quantidade);
  } else {
    dadosTeste = pegarPrimeiros(todosDados, quantidade);
  }

  int criterio = criterioSelecionado + 1;
  int algoritmo = algoritmoSelecionado;

  // 4. Mede os tempos de execucao
  stringstream relatorio;
  relatorio << fixed << setprecision(6);
  relatorio << "  "
               "==============================================================="
               "=========\r\n";
  relatorio << "                        RELATORIO DE DESEMPENHO E BENCHMARK    "
               "           \r\n";
  relatorio << "  "
               "==============================================================="
               "=========\r\n";
  relatorio << "   * Quantidade de itens testados : " << dadosTeste.size()
            << " registros\r\n";
  relatorio << "   * Criterio de ordenacao        : " << nomeCriterio(criterio)
            << "\r\n";
  relatorio << "  "
               "---------------------------------------------------------------"
               "---------\r\n\r\n";

  if (algoritmo == 0) {
    vector<Imagem> dadosOrdenados = dadosTeste;
    double tempo = medirBubble(dadosOrdenados, criterio);
    relatorio << "   [Bubble Sort]\r\n";
    relatorio << "   Tempo decorrido: " << tempo << " segundos\r\n";
  } else if (algoritmo == 1) {
    vector<Imagem> dadosOrdenados = dadosTeste;
    double tempo = medirInsertion(dadosOrdenados, criterio);
    relatorio << "   [Insertion Sort]\r\n";
    relatorio << "   Tempo decorrido: " << tempo << " segundos\r\n";
  } else if (algoritmo == 2) {
    vector<Imagem> dadosOrdenados = dadosTeste;
    double tempo = medirQuick(dadosOrdenados, criterio);
    relatorio << "   [Quick Sort]\r\n";
    relatorio << "   Tempo decorrido: " << tempo << " segundos\r\n";
  } else if (algoritmo == 3) {
    vector<Imagem> dadosBubble = dadosTeste;
    vector<Imagem> dadosInsertion = dadosTeste;
    vector<Imagem> dadosQuick = dadosTeste;

    double tempoBubble = medirBubble(dadosBubble, criterio);
    double tempoInsertion = medirInsertion(dadosInsertion, criterio);
    double tempoQuick = medirQuick(dadosQuick, criterio);

    relatorio << "   COMPARATIVO DOS ALGORITMOS:\r\n\r\n";
    relatorio << "     - Bubble Sort:    " << tempoBubble << " s\r\n";
    relatorio << "     - Insertion Sort: " << tempoInsertion << " s\r\n";
    relatorio << "     - Quick Sort:     " << tempoQuick << " s\r\n\r\n";
    relatorio << "  "
                 "-------------------------------------------------------------"
                 "-----------\r\n";

    double menorTempo = tempoBubble;
    string maisRapido = "Bubble Sort";

    if (tempoInsertion < menorTempo) {
      menorTempo = tempoInsertion;
      maisRapido = "Insertion Sort";
    }
    if (tempoQuick < menorTempo) {
      menorTempo = tempoQuick;
      maisRapido = "Quick Sort";
    }

    relatorio << "   [Vencedor mais rapido] : " << maisRapido << "\r\n";
    relatorio << "   [Menor tempo alcancado]: " << menorTempo
              << " segundos\r\n";
  }

  SetWindowTextA(campoResultado, relatorio.str().c_str());
}

// =======================================================
// CRIACAO DOS COMPONENTES VISUAIS DA JANELA
// =======================================================

void Interface::criarComponentes(HWND janela) {
  auto criar = [&](const char *classe, const char *texto, DWORD estilo,
                   HMENU id, HFONT fonte) {
    HWND h = CreateWindowA(classe, texto, WS_VISIBLE | WS_CHILD | estilo, 0, 0,
                           0, 0, janela, id, NULL, NULL);
    if (h && fonte) {
      SendMessage(h, WM_SETFONT, (WPARAM)fonte, TRUE);
    }
    return h;
  };

  // Cabecalho
  labelTitulo = criar("STATIC", "GERENCIADOR DE ORDENACAO DE DADOS", SS_LEFT,
                      NULL, hFontTitulo);
  labelSubtitulo =
      criar("STATIC",
            "Comparativos de algoritmos em C++",
            SS_LEFT, NULL, hFontSubtitulo);

  // Secao 1: Origem dos Dados
  labelSecaoOrigem =
      criar("STATIC", "1. ORIGEM DOS DADOS", SS_LEFT, NULL, hFontSecao);
  btnOrigem[0] = criar("BUTTON", "Arquivo Interno", BS_OWNERDRAW | WS_TABSTOP,
                       (HMENU)ID_ORIGEM_0, hFontBotao);
  btnOrigem[1] =
      criar("BUTTON", "Arquivo Externo (.csv)", BS_OWNERDRAW | WS_TABSTOP,
            (HMENU)ID_ORIGEM_1, hFontBotao);
  btnOrigem[2] = criar("BUTTON", "Dados Aleatorios", BS_OWNERDRAW | WS_TABSTOP,
                       (HMENU)ID_ORIGEM_2, hFontBotao);

  btnProcurar =
      criar("BUTTON", "Escolher arquivo...", BS_OWNERDRAW | WS_TABSTOP,
            (HMENU)ID_BTN_PROCURAR, hFontBotao);
  labelArquivo = criar(
      "STATIC", "Nenhum arquivo externo selecionado (usando dados padrao)",
      SS_LEFT | SS_CENTERIMAGE, (HMENU)ID_LABEL_ARQUIVO, hFontPadrao);

  // Secao 2: Quantidade de Registros
  labelSecaoQtd =
      criar("STATIC", "2. QUANTIDADE DE REGISTROS", SS_LEFT, NULL, hFontSecao);
  campoQuantidade = criar("EDIT", "5000", WS_BORDER | ES_NUMBER | WS_TABSTOP,
                          (HMENU)ID_QUANTIDADE, hFontPadrao);
  SendMessage(campoQuantidade, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN,
              MAKELPARAM(10, 10));

  btnPresets[0] = criar("BUTTON", "1.000", BS_OWNERDRAW | WS_TABSTOP,
                        (HMENU)ID_PRESET_1000, hFontBotao);
  btnPresets[1] = criar("BUTTON", "5.000", BS_OWNERDRAW | WS_TABSTOP,
                        (HMENU)ID_PRESET_5000, hFontBotao);
  btnPresets[2] = criar("BUTTON", "10.000", BS_OWNERDRAW | WS_TABSTOP,
                        (HMENU)ID_PRESET_10000, hFontBotao);
  btnPresets[3] = criar("BUTTON", "50.000", BS_OWNERDRAW | WS_TABSTOP,
                        (HMENU)ID_PRESET_50000, hFontBotao);

  // Secao 3: Criterio de Ordenacao
  labelSecaoCrit =
      criar("STATIC", "3. CRITERIO DE ORDENACAO", SS_LEFT, NULL, hFontSecao);
  btnCriterio[0] = criar("BUTTON", "ID", BS_OWNERDRAW | WS_TABSTOP,
                         (HMENU)ID_CRIT_0, hFontBotao);
  btnCriterio[1] = criar("BUTTON", "Nome", BS_OWNERDRAW | WS_TABSTOP,
                         (HMENU)ID_CRIT_1, hFontBotao);
  btnCriterio[2] = criar("BUTTON", "Tamanho", BS_OWNERDRAW | WS_TABSTOP,
                         (HMENU)ID_CRIT_2, hFontBotao);
  btnCriterio[3] = criar("BUTTON", "Largura", BS_OWNERDRAW | WS_TABSTOP,
                         (HMENU)ID_CRIT_3, hFontBotao);
  btnCriterio[4] = criar("BUTTON", "Altura", BS_OWNERDRAW | WS_TABSTOP,
                         (HMENU)ID_CRIT_4, hFontBotao);

  // Secao 4: Algoritmos de Ordenacao
  labelSecaoAlgo =
      criar("STATIC", "4. ALGORITMO DE ORDENACAO", SS_LEFT, NULL, hFontSecao);
  btnAlgoritmo[0] = criar("BUTTON", "Bubble Sort", BS_OWNERDRAW | WS_TABSTOP,
                          (HMENU)ID_ALGO_0, hFontBotao);
  btnAlgoritmo[1] = criar("BUTTON", "Insertion Sort", BS_OWNERDRAW | WS_TABSTOP,
                          (HMENU)ID_ALGO_1, hFontBotao);
  btnAlgoritmo[2] = criar("BUTTON", "Quick Sort", BS_OWNERDRAW | WS_TABSTOP,
                          (HMENU)ID_ALGO_2, hFontBotao);
  btnAlgoritmo[3] = criar("BUTTON", "Comparar Todos", BS_OWNERDRAW | WS_TABSTOP,
                          (HMENU)ID_ALGO_3, hFontBotao);

  // Botoes de Acao Principais
  btnExecutar = criar("BUTTON", "EXECUTAR",
                      BS_OWNERDRAW | BS_DEFPUSHBUTTON | WS_TABSTOP,
                      (HMENU)ID_EXECUTAR, hFontBotaoExecutar);
  btnLimpar = criar("BUTTON", "Limpar Terminal", BS_OWNERDRAW | WS_TABSTOP,
                    (HMENU)ID_BTN_LIMPAR, hFontBotao);

  // Terminal de Resultados
  labelSecaoResultado =
      criar("STATIC", "5. TERMINAL DE RESULTADOS", SS_LEFT, NULL, hFontSecao);
  campoResultado = criar(
      "EDIT",
      "  "
      "========================================================================"
      "\r\n"
      "                     TERMINAL PRONTO PARA EXECUCAO                      "
      "  \r\n"
      "  "
      "========================================================================"
      "\r\n"
      "  Selecione os parametros acima e clique em 'EXECUTAR'.\r\n",
      WS_BORDER | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | WS_VSCROLL |
          WS_TABSTOP,
      (HMENU)ID_RESULTADO, hFontTerminal);
  SendMessage(campoResultado, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN,
              MAKELPARAM(12, 12));
}

// =======================================================
// REDIMENSIONA E CENTRALIZA COMPONENTES EM TELA CHEIA
// =======================================================

void Interface::redimensionar(int larguraJanela, int alturaJanela) {
  // Mantem o conteudo elegante e centralizado em telas largas (Full HD / 4K)
  int conteudoLargura = larguraJanela - 80;
  int margemX = 40;

  if (conteudoLargura > 1150) {
    conteudoLargura = 1150;
    margemX = (larguraJanela - conteudoLargura) / 2;
  }

  // Cabecalho
  MoveWindow(labelTitulo, margemX, 20, conteudoLargura, 34, TRUE);
  MoveWindow(labelSubtitulo, margemX, 58, conteudoLargura, 24, TRUE);

  // Secao 1: Origem dos Dados (3 botoes lado a lado)
  MoveWindow(labelSecaoOrigem, margemX, 94, conteudoLargura, 22, TRUE);
  int wBtn3 = (conteudoLargura - 24) / 3;
  MoveWindow(btnOrigem[0], margemX, 120, wBtn3, 46, TRUE);
  MoveWindow(btnOrigem[1], margemX + wBtn3 + 12, 120, wBtn3, 46, TRUE);
  MoveWindow(btnOrigem[2], margemX + (wBtn3 + 12) * 2, 120, wBtn3, 46, TRUE);

  // Linha de Arquivo Externo
  MoveWindow(btnProcurar, margemX, 176, 220, 38, TRUE);
  MoveWindow(labelArquivo, margemX + 234, 176, conteudoLargura - 234, 38, TRUE);

  // Secao 2 e 3 em Duas Colunas
  int colLargura = (conteudoLargura - 30) / 2;

  // Coluna 1: Quantidade de Registros + Presets
  MoveWindow(labelSecaoQtd, margemX, 228, colLargura, 22, TRUE);
  int wInputQtd = colLargura - 260;
  if (wInputQtd < 120)
    wInputQtd = 120;
  MoveWindow(campoQuantidade, margemX, 254, wInputQtd, 38, TRUE);

  int posXPreset = margemX + wInputQtd + 10;
  int wPreset = (colLargura - wInputQtd - 25) / 4;
  for (int i = 0; i < 4; ++i) {
    MoveWindow(btnPresets[i], posXPreset + i * (wPreset + 5), 254, wPreset, 38,
               TRUE);
  }

  // Coluna 2: Criterio de Ordenacao (5 botoes tipo pill)
  int col2X = margemX + colLargura + 30;
  MoveWindow(labelSecaoCrit, col2X, 228, colLargura, 22, TRUE);
  int wCrit = (colLargura - 20) / 5;
  for (int i = 0; i < 5; ++i) {
    MoveWindow(btnCriterio[i], col2X + i * (wCrit + 5), 254, wCrit, 38, TRUE);
  }

  // Secao 4: Algoritmos de Ordenacao (4 cartoes largos)
  MoveWindow(labelSecaoAlgo, margemX, 306, conteudoLargura, 22, TRUE);
  int wAlgo = (conteudoLargura - 36) / 4;
  for (int i = 0; i < 4; ++i) {
    MoveWindow(btnAlgoritmo[i], margemX + i * (wAlgo + 12), 332, wAlgo, 46,
               TRUE);
  }

  // Botoes Principais de Acao
  int wLimpar = 190;
  int wExecutar = conteudoLargura - wLimpar - 16;
  MoveWindow(btnExecutar, margemX, 392, wExecutar, 54, TRUE);
  MoveWindow(btnLimpar, margemX + wExecutar + 16, 392, wLimpar, 54, TRUE);

  // Secao 5: Terminal de Resultados (Ocupa todo o espaco vertical restante)
  MoveWindow(labelSecaoResultado, margemX, 460, conteudoLargura, 22, TRUE);
  int alturaTerminal = alturaJanela - 490 - 35;
  if (alturaTerminal < 180)
    alturaTerminal = 180;
  MoveWindow(campoResultado, margemX, 486, conteudoLargura, alturaTerminal,
             TRUE);
}

// =======================================================
// CONTROLE DE EVENTOS DA JANELA (WINDOW PROCEDURE)
// =======================================================

LRESULT CALLBACK Interface::WindowProcedure(HWND janela, UINT mensagem,
                                            WPARAM wParam, LPARAM lParam) {
  switch (mensagem) {
  case WM_CREATE:
    if (instancia != nullptr) {
      instancia->criarComponentes(janela);
    }
    break;

  case WM_SIZE: {
    int largura = LOWORD(lParam);
    int altura = HIWORD(lParam);
    if (instancia != nullptr && largura > 0 && altura > 0) {
      instancia->redimensionar(largura, altura);
    }
    break;
  }

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(janela, &ps);

    // Linha superior decorativa moderna em azul ciano
    RECT rcTop = {0, 0, 4000, 4};
    HBRUSH hBrushAccent = CreateSolidBrush(RGB(14, 165, 233));
    FillRect(hdc, &rcTop, hBrushAccent);
    DeleteObject(hBrushAccent);

    EndPaint(janela, &ps);
    return 0;
  }

  case WM_CTLCOLORSTATIC: {
    HDC dc = (HDC)wParam;
    HWND hStatic = (HWND)lParam;
    if (instancia != nullptr) {
      // Estilo especial para o campo do Terminal de Resultados
      if (hStatic == instancia->campoResultado) {
        SetTextColor(dc, RGB(56, 189, 248)); // Texto em ciano brilhante
        SetBkColor(dc, RGB(8, 12, 20));      // Fundo escuro do console
        return (INT_PTR)instancia->hBrushTerminal;
      }
      // Titulo principal em branco
      if (hStatic == instancia->labelTitulo) {
        SetTextColor(dc, RGB(255, 255, 255));
        SetBkMode(dc, TRANSPARENT);
        return (INT_PTR)instancia->hBrushFundo;
      }
      // Subtitulo em cinza suave
      if (hStatic == instancia->labelSubtitulo) {
        SetTextColor(dc, RGB(148, 163, 184));
        SetBkMode(dc, TRANSPARENT);
        return (INT_PTR)instancia->hBrushFundo;
      }
      // Titulos de secao em ciano
      if (hStatic == instancia->labelSecaoOrigem ||
          hStatic == instancia->labelSecaoQtd ||
          hStatic == instancia->labelSecaoCrit ||
          hStatic == instancia->labelSecaoAlgo ||
          hStatic == instancia->labelSecaoResultado) {
        SetTextColor(dc, RGB(56, 189, 248));
        SetBkMode(dc, TRANSPARENT);
        return (INT_PTR)instancia->hBrushFundo;
      }
    }
    SetTextColor(dc, RGB(226, 232, 240));
    SetBkMode(dc, TRANSPARENT);
    return (INT_PTR)instancia->hBrushFundo;
  }

  case WM_CTLCOLOREDIT: {
    HDC dc = (HDC)wParam;
    SetTextColor(dc, RGB(241, 245, 249));
    SetBkColor(dc, RGB(30, 41, 59));
    return (INT_PTR)instancia->hBrushCampo;
  }

  // Desenho moderno e personalizado de todos os botoes
  case WM_DRAWITEM: {
    LPDRAWITEMSTRUCT item = (LPDRAWITEMSTRUCT)lParam;
    if (item && item->CtlType == ODT_BUTTON) {
      bool principal = (item->CtlID == ID_EXECUTAR);
      bool limpar = (item->CtlID == ID_BTN_LIMPAR);
      bool procurar = (item->CtlID == ID_BTN_PROCURAR);
      bool pressionado = (item->itemState & ODS_SELECTED);

      COLORREF fundo;
      COLORREF borda;
      COLORREF texto;
      HFONT fonteUsada = instancia->hFontBotao;
      const char *textoBotao = "";
      int radius = 8;

      // 1. Botoes de Origem dos Dados
      if (item->CtlID >= ID_ORIGEM_0 && item->CtlID <= ID_ORIGEM_2) {
        int idx = item->CtlID - ID_ORIGEM_0;
        bool ativo = (idx == instancia->origemSelecionada);
        if (ativo) {
          fundo = RGB(14, 165, 233); // Azul em destaque
          borda = RGB(56, 189, 248);
          texto = RGB(255, 255, 255);
        } else {
          fundo = pressionado ? RGB(51, 65, 85) : RGB(30, 41, 59);
          borda = RGB(51, 65, 85);
          texto = RGB(203, 213, 225);
        }
        if (idx == 0)
          textoBotao = "Arquivo Interno";
        else if (idx == 1)
          textoBotao = "Arquivo Externo (.csv)";
        else
          textoBotao = "Dados Aleatorios";
      }
      // 2. Atalhos de Quantidade
      else if (item->CtlID >= ID_PRESET_1000 &&
               item->CtlID <= ID_PRESET_50000) {
        fundo = pressionado ? RGB(14, 165, 233) : RGB(30, 41, 59);
        borda = pressionado ? RGB(56, 189, 248) : RGB(51, 65, 85);
        texto = pressionado ? RGB(255, 255, 255) : RGB(148, 163, 184);
        if (item->CtlID == ID_PRESET_1000)
          textoBotao = "1k";
        else if (item->CtlID == ID_PRESET_5000)
          textoBotao = "5k";
        else if (item->CtlID == ID_PRESET_10000)
          textoBotao = "10k";
        else
          textoBotao = "50k";
      }
      // 3. Criterios de Ordenacao
      else if (item->CtlID >= ID_CRIT_0 && item->CtlID <= ID_CRIT_4) {
        int idx = item->CtlID - ID_CRIT_0;
        bool ativo = (idx == instancia->criterioSelecionado);
        if (ativo) {
          fundo = RGB(14, 165, 233);
          borda = RGB(56, 189, 248);
          texto = RGB(255, 255, 255);
        } else {
          fundo = pressionado ? RGB(51, 65, 85) : RGB(30, 41, 59);
          borda = RGB(51, 65, 85);
          texto = RGB(203, 213, 225);
        }
        if (idx == 0)
          textoBotao = "ID";
        else if (idx == 1)
          textoBotao = "Nome";
        else if (idx == 2)
          textoBotao = "Tamanho";
        else if (idx == 3)
          textoBotao = "Largura";
        else
          textoBotao = "Altura";
      }
      // 4. Algoritmos de Ordenacao
      else if (item->CtlID >= ID_ALGO_0 && item->CtlID <= ID_ALGO_3) {
        int idx = item->CtlID - ID_ALGO_0;
        bool ativo = (idx == instancia->algoritmoSelecionado);
        if (ativo) {
          fundo = RGB(14, 165, 233);
          borda = RGB(56, 189, 248);
          texto = RGB(255, 255, 255);
        } else {
          fundo = pressionado ? RGB(51, 65, 85) : RGB(30, 41, 59);
          borda = RGB(51, 65, 85);
          texto = RGB(203, 213, 225);
        }
        if (idx == 0)
          textoBotao = "Bubble Sort";
        else if (idx == 1)
          textoBotao = "Insertion Sort";
        else if (idx == 2)
          textoBotao = "Quick Sort";
        else
          textoBotao = "Comparar Todos";
      }
      // 5. Botao Procurar Arquivo
      else if (procurar) {
        fundo = pressionado ? RGB(51, 65, 85) : RGB(30, 41, 59);
        borda = RGB(14, 165, 233);
        texto = RGB(241, 245, 249);
        textoBotao = "Escolher arquivo...";
      }
      // 6. Botao Principal Executar
      else if (principal) {
        fundo = pressionado ? RGB(2, 132, 199) : RGB(14, 165, 233);
        borda = RGB(56, 189, 248);
        texto = RGB(255, 255, 255);
        fonteUsada = instancia->hFontBotaoExecutar;
        textoBotao = "EXECUTAR";
        radius = 12;
      }
      // 7. Botao Limpar
      else if (limpar) {
        fundo = pressionado ? RGB(51, 65, 85) : RGB(30, 41, 59);
        borda = RGB(71, 85, 105);
        texto = pressionado ? RGB(241, 245, 249) : RGB(148, 163, 184);
        textoBotao = "Limpar Terminal";
        radius = 10;
      }

      // Limpa o fundo do botao antes de arredondar (elimina artefatos)
      FillRect(item->hDC, &item->rcItem, instancia->hBrushFundo);

      // Desenha a forma arredondada com borda
      HBRUSH brush = CreateSolidBrush(fundo);
      HPEN pen = CreatePen(PS_SOLID, 1, borda);
      HGDIOBJ oldBrush = SelectObject(item->hDC, brush);
      HGDIOBJ oldPen = SelectObject(item->hDC, pen);

      RoundRect(item->hDC, item->rcItem.left, item->rcItem.top,
                item->rcItem.right, item->rcItem.bottom, radius, radius);

      SelectObject(item->hDC, oldBrush);
      SelectObject(item->hDC, oldPen);
      DeleteObject(brush);
      DeleteObject(pen);

      // Desenha o texto centralizado
      SetBkMode(item->hDC, TRANSPARENT);
      SetTextColor(item->hDC, texto);
      SelectObject(item->hDC, fonteUsada);

      RECT rc = item->rcItem;
      if (pressionado) {
        OffsetRect(&rc, 0, 1);
      }
      DrawTextA(item->hDC, textoBotao, -1, &rc,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE);

      return TRUE;
    }
    break;
  }

  // Trata os cliques dos botoes
  case WM_COMMAND: {
    WORD id = LOWORD(wParam);

    // Botoes de Origem
    if (id >= ID_ORIGEM_0 && id <= ID_ORIGEM_2) {
      if (instancia != nullptr) {
        instancia->origemSelecionada = id - ID_ORIGEM_0;
        instancia->atualizarBotoes();
        if (instancia->origemSelecionada == 1) {
          instancia->selecionarArquivoExterno(janela);
        }
      }
    }
    // Atalhos rapidos de quantidade
    else if (id == ID_PRESET_1000 && instancia)
      SetWindowTextA(instancia->campoQuantidade, "1000");
    else if (id == ID_PRESET_5000 && instancia)
      SetWindowTextA(instancia->campoQuantidade, "5000");
    else if (id == ID_PRESET_10000 && instancia)
      SetWindowTextA(instancia->campoQuantidade, "10000");
    else if (id == ID_PRESET_50000 && instancia)
      SetWindowTextA(instancia->campoQuantidade, "50000");

    // Botoes de Criterio
    else if (id >= ID_CRIT_0 && id <= ID_CRIT_4) {
      if (instancia != nullptr) {
        instancia->criterioSelecionado = id - ID_CRIT_0;
        instancia->atualizarBotoes();
      }
    }
    // Botoes de Algoritmo
    else if (id >= ID_ALGO_0 && id <= ID_ALGO_3) {
      if (instancia != nullptr) {
        instancia->algoritmoSelecionado = id - ID_ALGO_0;
        instancia->atualizarBotoes();
      }
    }
    // Botao Procurar Arquivo
    else if (id == ID_BTN_PROCURAR) {
      if (instancia != nullptr) {
        instancia->origemSelecionada = 1;
        instancia->atualizarBotoes();
        instancia->selecionarArquivoExterno(janela);
      }
    }
    // Botao Executar
    else if (id == ID_EXECUTAR) {
      if (instancia != nullptr) {
        instancia->executarPrograma(janela);
      }
    }
    // Botao Limpar
    else if (id == ID_BTN_LIMPAR) {
      if (instancia != nullptr) {
        SetWindowTextA(
            instancia->campoResultado,
            "  ========================================================================\r\n"
            "                     TERMINAL PRONTO PARA EXECUCAO                        \r\n"
            "  ========================================================================\r\n"
            "  Selecione os parametros acima e clique em 'EXECUTAR'.\r\n");
      }
    }
    break;
  }

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProcA(janela, mensagem, wParam, lParam);
  }
  return 0;
}

// =======================================================
// INICIALIZACAO DA APLICACAO (CONFIGURA E ABRE TELA CHEIA)
// =======================================================

int Interface::iniciar(HINSTANCE hInstance, int nCmdShow) {
  instancia = this;

  const char NOME_CLASSE[] = "InterfaceOrdenacaoAcademicaV3";

  WNDCLASSA wc = {};
  wc.lpfnWndProc = WindowProcedure;
  wc.hInstance = hInstance;
  wc.lpszClassName = NOME_CLASSE;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = instancia->hBrushFundo;

  RegisterClassA(&wc);

  // Janela com estilo padrao completo (WS_OVERLAPPEDWINDOW permite
  // maximizar/tela cheia)
  HWND janela = CreateWindowExA(
      0, NOME_CLASSE, "Gerenciador de Ordenacao de Dados - Benchmark Academico",
      WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800, NULL, NULL,
      hInstance, NULL);

  if (janela == NULL) {
    MessageBoxA(NULL, "Erro ao criar a janela do programa.", "Erro",
                MB_OK | MB_ICONERROR);
    return 0;
  }

  // Aplica o tema escuro na barra de titulo
  ativarBarraTituloEscura(janela);

  // ABRE DIRETAMENTE EM TELA CHEIA (MAXIMIZADO)
  ShowWindow(janela, SW_SHOWMAXIMIZED);
  UpdateWindow(janela);

  // Loop de mensagens do Windows
  MSG mensagem = {};
  while (GetMessage(&mensagem, NULL, 0, 0)) {
    TranslateMessage(&mensagem);
    DispatchMessage(&mensagem);
  }

  return 0;
}

// =======================================================
// PONTO DE ENTRADA CHAMADO PELA MAIN
// =======================================================

int iniciarInterface(HINSTANCE hInstance, int nCmdShow) {
  Interface interfacePrograma;
  return interfacePrograma.iniciar(hInstance, nCmdShow);
}