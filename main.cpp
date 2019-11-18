#include <iostream>
#include"Grafo.h"
#include <string>

using namespace std;

int main()
{
    Grafo Atual;

    gerarGrafoGrid(5);

    Atual.carregar_grafo("Grid.txt"); // Carrega um grafo do arquivo de nome "Resultado.txt"
    Atual.Set_restaurante(1); // Coloca o vertice de Id == 1 do grafo como restaurante
    Atual.imprimir();
    Atual.melhoresRotas(); // Escreve as melhores rotas no arquivo "melhoresRotas.txt";

    return 0;
}
