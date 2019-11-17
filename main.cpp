#include <iostream>
#include"Grafo.h"
#include <string>


using namespace std;

int main()
{
    Grafo Atual;

    char a[] = {'R','e','s','u','l','t','a','d','o','.','t','x','t','\0'};

    Atual.carregar_grafo(a); // Carrega um grafo do arquivo de nome "Resultado.txt"
    Atual.Ordenar_vertice(0, 6); // Ordena o vetor de vertices do grafo de acordo com os graus, em ordem decrescente
    Atual.Set_restaurante(1); // Coloca o vertice de Id == 1 do grafo como restaurante

    Atual.melhoresRotas(); // Escreve as melhores rotas no arquivo "melhoresRotas.txt";

    return 0;
}
