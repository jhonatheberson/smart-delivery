#ifndef _VERTICE_H_
#define _VERTICE_H_

struct Vertice {


	int id; // Identificação do vertice
    int grau; // Grau de prioridade do vertice
    int status; // Status do vertice (Já visitada ou não)

	// Sobrecarga do operador '=='
	void marcar(){ status = true;}
	bool operator==(const Vertice &V) {
		if (id == V.id && status == V.status && grau == A.grau){
                return true;
		}
		return false;
	}
};
#endif
