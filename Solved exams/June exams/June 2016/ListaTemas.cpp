//Marcos Herrero

#include"ListaTemas.h"
#include "checkML.h"

void crear(tListaTemas & lista) {
	lista.cont = 0;
}

void destruir(tListaTemas & lista) {
	for (int i = 0; i < lista.cont; ++i) delete lista.v[i];
	lista.cont = 0;
}

bool cargar(tListaTemas & lista) {
	crear(lista);

	std::ifstream entrada;
	entrada.open("temas.txt");
	if (!entrada.is_open()) return false;
	
	int numtemas;
	entrada >> numtemas;
	entrada.ignore(1);

	for (int i = 0; i < numtemas; ++i) {
		lista.v[i] = new tTema;
		entrada >> *lista.v[i];
	}
	lista.cont = numtemas;

	return true;
}
