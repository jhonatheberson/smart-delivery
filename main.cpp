#include <iostream>
#include"Grafo.h"
#include <string>

using namespace std;

int main()
{
    Grafo Atual;

    gerarGrafoCompleto(718);

    Atual.carregar_grafo("Completo.txt"); // Carrega um grafo do arquivo de nome passado como parametro
    Atual.Set_restaurante(1); // Coloca o vertice de Id == 1 do grafo como restaurante
    Atual.imprimir(); // Imprimi o grafo Atual no arquivo Resultado.txt
    Atual.melhoresRotas(); // Escreve as melhores rotas no arquivo "melhoresRotas.txt";

    return 0;
}
