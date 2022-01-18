#include "ListaGrupos.h"

void inicializarListaGrupos(tListaGrupos & lista){
	lista.cont = 0;
}

bool buscar(tListaGrupos const & lista, std::string const & identificador, int & pos){
	bool encontrado = false;
	for (int i = 0; !encontrado && i < lista.cont; ++i){
		if (lista.v[i]->identificador == identificador){
			pos = i;
			encontrado = true;
		}
	}

	return encontrado;
}

void insertar(tListaGrupos & listaG, std::string const & identificador, tListaEstudiantes const & listaE){
	listaG.v[listaG.cont] = new tGrupo;
	listaG.v[listaG.cont]->identificador = identificador;
	listaG.v[listaG.cont]->lista = listaE;
	++listaG.cont;
}

void mostrarNotas(tListaGrupos const & lista, std::string const & NIF){
	
	std::cout << "Alumno " << NIF << " Grupos\n";
	int pos;

	for (int i = 0; i < lista.cont; ++i){
		pos = 0;
		if (buscar(lista.v[i]->lista, NIF, pos)){
			std::cout << lista.v[i]->identificador <<" - "<< lista.v[i]->lista.ptr[pos].nota<<'\n';
		}
	}
}

void mostrarSuspensos(tListaGrupos const & lista, std::string const & identificador){
	int pos = 0;
	bool OK = buscar(lista, identificador, pos);
	if (!OK) std::cout << "No se encuentra el grupo\n";
	else {
		std::cout << "Estudiantes suspensos en el grupo " << identificador<<'\n';
		for (int i = 0; i < lista.v[pos]->lista.cont; ++i){
			if (lista.v[pos]->lista.ptr[i].nota < 5) std::cout << lista.v[pos]->lista.ptr[i];
		}
	}
}

void liberar(tListaGrupos & lista){
	for (int i = 0; i < lista.cont; ++i){
		liberar(lista.v[i]->lista);
		delete lista.v[i];
		lista.v[i] = nullptr;
	}

	lista.cont = 0;
}