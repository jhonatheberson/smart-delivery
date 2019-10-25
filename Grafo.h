#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <iostream> // Saída padrão
#include <fstream> // Manipulação de arquivos
#include <cstdlib> // Funções padrão
#include <string> // Manipulação de strings
#include "Aresta.h" // Inclusão do tipo Aresta
#include "Vertice.h" // Inclusão do tipo Aresta


using namespace std;

#define MAX_V 31 // Quantidade maxima de vértices
#define MAX_E 450 // Quantidade maxima de arestas (calculado para suportar grafos completos 30 vértices)

class Grafo {
public:

    int v; // Quantidade de vértices
	int e; // Quantidade de arestas
	Aresta aresta[MAX_E]; // Vetor de arestas
	Vertice vertice[MAX_V]; // Vetor de vertices
	Vertice vertice[MAX_V];

	inline Grafo() {v = 0; e = 0;} // Construtor default
	Grafo(Grafo G); // Construtor por copia


    void  Adjunta(); // mostra a matriz adjunta  --  falta fazer
	void carregar_grafo(const string &arquivo); // -- falta fazer
	string imprimir() // -- falta fazer
	Aresta busca_caminho(Vertice A, Vertice B); // -- falta fazer
	void Ordenar_vertice(){/*MergeSort*/}; // falta fazer
	Aresta return_k_best_road(); // falta fazer -  ultima função
	bool add_aresta(); // falta fazer
    bool remover_aresta(); // falta fazer

};


Grafo::Grafo(Grafo G) {

	v = G.v;
	e = G.e;

	for (int i = 0; i < v; ++i){
            aresta[i] == G.aresta[i];
	}

	for (int i = 0; i < v; ++i){
            vertice[i] == G.vertice[i];
	}
}

 void  Grafo::Adjunta(){


 }



void Grafo::carregar_grafo(const string &arquivo) {
	ifstream fin; // Objeto de fluxo de entrada de arquivo
	fin.open(arquivo, ios::in); // Abrindo fluxo de leitura com o arquivo
	// Verificando se o arquivo foi aberto corretamente
	if (!fin.is_open()) {
		cerr << "Arquivo nao encontrado..." << endl;
		exit(0);
	}
	fin >> v; // Lendo quantidade de vértices que deve estar presenta na primeira linha do arquivo
	// Lendo vértices e peso de cada aresta e incrementando qtd de arestas do grafo
	e++; // Começar a armazenar as arestas a partir do indice 1 do vetor aresta[]
	for (e; !fin.eof(); e++) {
		fin >> aresta[e].i >> aresta[e].j >> aresta[e].peso;
		aresta[e].status = OPC; // Setando todas arestas inicialmente como opcionais
		custo_total += aresta[e].peso; // Calculando custo total de todas as arestas do grafo
	}
	e -= 2; // Correção na leitura
	// Fechando fluxo de leitura de arquivo
	fin.close();
}



string Grafo::imprimir() {
	string s = to_string(v) + "\n"; // Acrescentando quantidade de vértices
	// Acrescentando arestas no formato padrão ("vertice 1" "vertice 2" "peso")
	for (int k = 1; k <= e; k++)
		s += to_string(aresta[k].i) + " " + to_string(aresta[k].j) + " " + to_string(aresta[k].peso) + "\n";
	return s;
}

// Função para adicionar nova aresta em um grafo sem formar ciclos (baseada na proprosta das funções union e same_set)
// Verifica a formação de ciclos antes de realizar a adição da aresta
bool Grafo::add_aresta(const Aresta &h) {
	// Caso em que o grafo possui menos que 2 arestas: adiciona aresta diretamente
	// Caso em que o grafo não é nulo: verifica a formação de ciclos e, se não formar, adiciona o vértice
	if (((e < 2) || (grupos[h.i] != grupos[h.j])) && (h.status != PRB)) {
		e++;
		aresta[e].i = h.i; // Atualizando vertice final i da aresta[e]
		aresta[e].j = h.j; // Atualizando vertice final j da aresta[e]
		aresta[e].peso = h.peso;  // Atualizando peso da aresta[e]
		aresta[e].status = h.status; // Atualizando status da aresta[e]
		// Modificando grupo de todos os vértices que pertenciam ao mesmo grupo do segundo vertice final (h.j)
		// de modo que agora pertençam ao grupo do primeiro vertice final (h.i)
		int aux = grupos[h.j];
		for (int k = 1; k <= v; k++)
			if (grupos[k] == aux)
				grupos[k] = grupos[h.i];
		custo_total += h.peso;
		return true;
	}
	return false;
}

#endif
