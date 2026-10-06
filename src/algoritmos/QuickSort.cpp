#include <iostream>
using namespace std;

void quickSort(int vetor[], int inicio, int fim)
{
    int i = inicio;
    int j = fim;

    int pivo = vetor[(inicio + fim) / 2];

    while (i <= j)
    {
        while (vetor[i] < pivo)
        {
            i++;
        }

        while (vetor[j] > pivo)
        {
            j--;
        }

        if (i <= j)
        {
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;

            i++;
            j--;
        }
    }

    if (inicio < j)
    {
        quickSort(vetor, inicio, j);
    }

    if (i < fim)
    {
        quickSort(vetor, i, fim);
    }
}

int main()
{
    int vetor[] = {8, 3, 7, 4, 2, 9, 1, 5};

    int tamanho = 8;

    quickSort(vetor, 0, tamanho - 1);

    for (int i = 0; i < tamanho; i++)
    {
        cout << vetor[i] << " ";
    }

    return 0;
}