#ifndef _VERTICE_H_
#define _VERTICE_H_

struct Vertice {

	int id; // Identifica��o do vertice
    int grau; // Grau de prioridade do vertice
    bool status; // Status do vertice (J� visitada ou n�o)
    bool tipo;  // Indica qual vertice � o restaurante

	// Sobrecarga do operador '=='
	void marcar(){ status = true;}
	bool operator==(const Vertice &V) {
		if (id == V.id && status == V.status && grau == V.grau && tipo == V.tipo){
                return true;
		}
		return false;
	}
};
#endif
