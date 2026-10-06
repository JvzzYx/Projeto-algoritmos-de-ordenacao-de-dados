#include <vector>
#include <utility> // Biblioteca

void ordenar(std::vector<Imagem>& lista) {
        int quantidade = lista.size();

        // Controla o número de passagens pela lista
        for (i = 0; i < quantidade - 1; i++) {
            
            // Compara os pares vizinhos
            for (j = 0; j < quantidade - 1 - i; j++) {
                
                // Troca-los
                if (lista[j].getTamanho() > lista[j + 1].getTamanho()) {
                    std::swap(lista[j], lista[j + 1]);
                }
            }
        }
    }
