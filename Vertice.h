#ifndef _VERTICE_H_
#define _VERTICE_H_

struct Vertice {


	int id; // Identifica��o do vertice
    int grau; // Grau de prioridade do vertice
    int status; // Status do vertice (J� visitada ou n�o)

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
