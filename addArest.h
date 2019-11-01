#ifndef _ADDAREST_H_
#define _ADDAREST_H_

#include "Aresta.h"
#include "Grafo.h"
#include "Vertice.h"

int MaxNumVertices = 100;

int MaxNumArestas = 4500;

int MaxTam  = MaxNumVertices+2*MaxNumArestas;

struct Grafo1 {
  int Cab[MaxTam];
  int prox[MaxTam];
  int peso[MaxTam];
  int ProxDisponivel ;
  int NumVertices;
  int NumArestas;
} ;


void InseraAresta_matr(Vertice V1, Vertice V2, Aresta.peso Peso, Grafo grafo);
/// Matriz de adjancentes

/// lista de adjancentes
void Add_aresta(Vertice V1, Vertice V2, Aresta.peso Peso, Grafo grafo);
/// lista de adjancentes
#endif
