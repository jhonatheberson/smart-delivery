#ifndef _ARESTA_H_
#define _ARESTA_H_

struct Aresta {

	int i; // Primeiro vértice terminal
	int j; // Segundo vértice terminal
	int peso; // Peso da aresta
	bool status; // Status do Aresta(Já visitada ou não)

    void marcar(){ status = true;}
	// Sobrecarga do operador '=='
	bool operator==(const Aresta &A) {
		if (i == A.i && j == A.j && peso == A.peso){
			return true;
		}
		return false;
	}
};
#endif
