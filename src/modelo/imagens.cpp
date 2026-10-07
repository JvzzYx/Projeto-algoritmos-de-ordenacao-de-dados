#include <iostream>
#include <string>

class Imagem {
private:
    std::string nome;
    double tamanho;
    int largura;
    int altura;
public:
    // Construtor
    Imagem(std::string nome, double tamanho, int largura, int altura)
        : nome(nome), tamanho(tamanho), largura(largura), altura(altura) {}
    // Gets
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