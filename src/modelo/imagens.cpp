#include <string>

class Imagem {
private:
    int id;
    std::string nome;
    double tamanho;
    int largura;
    int altura;
public:
    Imagem(
        int id,
        std::string nome,
        double tamanho,
        int largura,
        int altura
    )
        : id(id),
          nome(nome),
          tamanho(tamanho),
          largura(largura),
          altura(altura) {
    }
    int getId() const {
        return id;
    }
    std::string getNome() const {
        return nome;
    }
    double getTamanho() const {
        return tamanho;
    }
    int getLargura() const {
        return largura;
    }
    int getAltura() const {
        return altura;
    }
};