#include "listaEstudiantes.h"

void inicializarListaEstudiantes(tListaEstudiantes & lista){
	lista.ptr = new tEstudiante[TAM_LISTAESTUDIANTES];
	lista.cont = 0;
	lista.capacidad = TAM_LISTAESTUDIANTES;
}

bool buscar(tListaEstudiantes const & lista, std::string const & NIF, int & pos ){
	bool encontrado = false;
	int ini = 0, fin = lista.cont, mitad;

	while (!encontrado && ini < fin){
		mitad = (ini + fin - 1) / 2;
		if ( NIF < lista.ptr[mitad].NIF) fin = mitad;
		else if (lista.ptr[mitad].NIF < NIF) ini = mitad + 1;
		else encontrado = true;
	}
	if (encontrado) pos = mitad;
	else pos = ini;

	return encontrado;
}

void insertar(tListaEstudiantes & lista, tEstudiante const & estudiante){
	int pos = 0;
	if (!buscar(lista, estudiante.NIF, pos)){
		if (lista.cont == lista.capacidad) ampliar(lista);
		for (int i = lista.cont; i > pos; --i) lista.ptr[i] = lista.ptr[i - 1];
		lista.ptr[pos] = estudiante;
		++lista.cont;
	}
}

void ampliar(tListaEstudiantes & lista){}

void mostrar(std::ostream & flujo, tListaEstudiantes const & lista){
	for (int i = 0; i < lista.cont; ++i) flujo << lista.ptr[i];
}

void liberar(tListaEstudiantes & lista){
	delete[] lista.ptr;
	lista.ptr = nullptr;
	lista.cont = 0;
	lista.capacidad = 0;
}