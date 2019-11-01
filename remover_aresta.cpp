#include "remover_aresta.h"

#include <iostream>

using namespace std;

void remover_aresta_matr(Vertice V1, Vertice V2, Aresta.peso Peso, Grafo grafo)
{
  if(grafo.MAT[V1, V2] = 0)
  {
    cout << "Aresta não existe" << endl;
  }
  else
  {
      Peso = grafo.Mat[V1, V2] = 0;
      Peso = grafo.Mat[V1, V2] = 0;
  }
}

void remover_aresta(Vertice V1, Vertice V2, Aresta.peso Peso, Grafo grafo)
      {
         bool Aux, AuxAnterio, Apontador, EncontrouAresta;
         AuxAnterio =  V1;
         aux = grafo.Prox[V1];
         EncontrouAresta = true;
         while (Aux != 0 && EncontrouAresta = false) {
             if(V2 = grafo.Cab[Aux])
             {
                 EncontrouAresta = true;

             }
             else
             {
                 AuxAnterio = Aux;
                 Aux = grafo.Prox[Aux];
             }
         }
         if(EncontrouAresta)
         {
             grafo.Cab[Aux] = MaxNumVertices+2*MaxNumArestas;
             cout << "marca como retirado" << endl;
         }
         else
            {
             cout << "Aresta não existe" << endl;
         }
      }


