#include "addArest.h"

void InseraAresta_matr(Vertice V1, Vertice V2, Aresta.peso Peso, Grafo grafo)
{
  grafo.MAT[V1, V2] = Peso;
}

void Add_aresta(Vertice V1, Vertice V2, Aresta.peso Peso, Grafo1 grafo)
{
  int Pos;
  Pos = grafo.ProxDisponivel;
  if(grafo.ProxDisponivel = MaxTam)
  {
      cout << "nao ha espaco disponivel para a aresta" << endl;
  }
  else
  {
      grafo.ProxDisponivel = grafo.ProxDisponivel + 1;
      grafo.Prox[grafo.Cab[V1]] = Pos;
      grafo.Cab[Pos] = V2;
      grafo.Cab[V1] = Pos;
      grafo.Prox[Pos] = 0;
      grafo.Peso[Pos] = Peso;
  }
}
