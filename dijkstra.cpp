#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <iostream>

#define MAX 100

using namespace std;

struct HeapMinNo {
	int v;
	int dist;
};

struct HeapMin {
	int n;
	int tam;
	int* indice;
	struct HeapMinNo** lista;
};

struct HeapMinNo* newHeapMinNo(int v, int dist) {
	struct HeapMinNo* heapMinNo = (struct HeapMinNo*) malloc(sizeof(struct HeapMinNo));
	heapMinNo->v = v;
	heapMinNo->dist = dist;
	return heapMinNo;
}

struct Grafo {
	int V;
	struct ListaAdj* lista;
};

struct ListaAdjNo {
	int d;
	int peso;
	struct ListaAdjNo* prox;
};

struct ListaAdj {
	struct ListaAdjNo* cabeca;
};

struct ListaAdjNo* criarListaAdjNo(int d, int peso) {
	struct ListaAdjNo* novoNo = (struct ListaAdjNo*) malloc(sizeof(struct ListaAdjNo));
	novoNo->d = d;
	novoNo->peso = peso;
	novoNo->prox = NULL;
	return novoNo;
}

struct Grafo* criaGrafo(int V) {
	struct Grafo* grafo = (struct Grafo*) malloc(sizeof(struct Grafo));
	grafo->V = V;

	grafo->lista = (struct ListaAdj*) malloc(V * sizeof(struct ListaAdj));

	for (int i = 0; i < V; ++i) {
		grafo->lista[i].cabeca = NULL;
	}

	return grafo;
}

void adicionaAresta(struct Grafo* grafo, int origem, int d, int peso) {


	struct ListaAdjNo* newNode = criarListaAdjNo(d, peso);
	newNode->prox = grafo->lista[origem].cabeca;
	grafo->lista[origem].cabeca = newNode;

	newNode = criarListaAdjNo(origem, peso);
	newNode->prox = grafo->lista[d].cabeca;
	grafo->lista[d].cabeca = newNode;
}

struct HeapMin* criaHeapMin(int tam) {
	struct HeapMin* heapMin = (struct HeapMin*) malloc(sizeof(struct HeapMin));
	heapMin->indice = (int*)malloc(tam * sizeof(int));
	heapMin->n = 0;
	heapMin->tam = tam;
	heapMin->lista = (struct HeapMinNo**) malloc(tam * sizeof(struct HeapMinNo*));
	return heapMin;
}

void trocaHeapMinNo(struct HeapMinNo** a, struct HeapMinNo** b) {
	struct HeapMinNo* aux = *a;
	*a = *b;
	*b = aux;
}

void constroiHeapMin(struct HeapMin* heapMin, int indice) {
	int menor, esq, dir;
	menor = indice;
	esq = 2 * indice + 1;
	dir = 2 * indice + 2;

	if (esq < heapMin->n &&
		heapMin->lista[esq]->dist < heapMin->lista[menor]->dist)
		menor = esq;

	if (dir < heapMin->n &&
		heapMin->lista[dir]->dist < heapMin->lista[menor]->dist)
		menor = dir;

	if (menor != indice) {

		HeapMinNo* noMenor = heapMin->lista[menor];
		HeapMinNo* indiceNode = heapMin->lista[indice];

		// troca posicoes
		heapMin->indice[noMenor->v] = indice;
		heapMin->indice[indiceNode->v] = menor;

		// troca no
		trocaHeapMinNo(&heapMin->lista[menor], &heapMin->lista[indice]);

		constroiHeapMin(heapMin, menor);
	}
}

int vazia(struct HeapMin* heapMin) {
	return heapMin->n == 0;
}

struct HeapMinNo* pegarMenor(struct HeapMin* heapMin) {
	if (vazia(heapMin))
		return NULL;

	struct HeapMinNo* raiz = heapMin->lista[0];

	struct HeapMinNo* ultimo = heapMin->lista[heapMin->n - 1];
	heapMin->lista[0] = ultimo;

	heapMin->indice[raiz->v] = heapMin->n - 1;
	heapMin->indice[ultimo->v] = 0;

	--heapMin->n;
	constroiHeapMin(heapMin, 0);

	return raiz;
}

void alteraDist(struct HeapMin* heapMin, int v, int dist) {

	int i = heapMin->indice[v];

	heapMin->lista[i]->dist = dist;

	while (i && heapMin->lista[i]->dist < heapMin->lista[(i - 1) / 2]->dist) {
		heapMin->indice[heapMin->lista[i]->v] = (i - 1) / 2;
		heapMin->indice[heapMin->lista[(i - 1) / 2]->v] = i;
		trocaHeapMinNo(&heapMin->lista[i], &heapMin->lista[(i - 1) / 2]);

		i = (i - 1) / 2;
	}
}

bool inseridoNaHeap(struct HeapMin* heapMin, int v)
{
	if (heapMin->indice[v] < heapMin->n)
		return true;
	return false;
}

void imprime(int dist[], int n) {
	cout << "Vertex Distance from Source\n";
	for (int i = 0; i < n; ++i) {
		cout << i << "     " << dist[i] << endl;
	}
}

void dijkstra(struct Grafo* grafo, int origem) {
	int V = grafo->V;
	int dist[MAX]; 

	struct HeapMin* heapMin = criaHeapMin(V);

	// inicia a heap com todos os vertices
	for (int v = 0; v < V; ++v) {
		dist[v] = INT_MAX;
		heapMin->lista[v] = newHeapMinNo(v, dist[v]);
		heapMin->indice[v] = v;
	}

	heapMin->lista[origem] = newHeapMinNo(origem, dist[origem]);
	heapMin->indice[origem] = origem;
	dist[origem] = 0;
	alteraDist(heapMin, origem, dist[origem]);

	// inicialmente a heap possui a quantidade de vertices do grafo
	heapMin->n = V;

	while (!vazia(heapMin)) {

		struct HeapMinNo* minHeapNode = pegarMenor(heapMin);
		int u = minHeapNode->v;

		struct ListaAdjNo* listaAux = grafo->lista[u].cabeca;
		while (listaAux != NULL) {
			int v = listaAux->d;

			if (inseridoNaHeap(heapMin, v) && dist[u] != INT_MAX && listaAux->peso + dist[u] < dist[v]) {
				dist[v] = dist[u] + listaAux->peso;

				// atualiza com a distancia minima
				alteraDist(heapMin, v, dist[v]);
			}
			listaAux = listaAux->prox;
		}
	}

	imprime(dist, V);
}
