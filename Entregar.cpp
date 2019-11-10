#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


void carregar_grafo(const string &arquivo);
string imprimir();

string imprimir() {

	string s = to_string(v) + "\n"; // Acrescentando quantidade de vértices
	//for que acrescenta as linhas no padrao desejao
	for (int k = 1; k <= v; k++)
		s += to_string(aresta[k].i) + " " + to_string(aresta[k].j) + " " + to_string(aresta[k].peso) + "\n";
	return s;
}

void carregar_grafo(const string &arquivo) {

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
