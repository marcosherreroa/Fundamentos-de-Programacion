#ifndef LISTAESTUDIANTES_H
#define LISTAESTUDIANTES_H

#include "estudiante.h"

struct tListaEstudiantes{
	tEstudiante* ptr;
	int cont;
	int capacidad;
};

const int TAM_LISTAESTUDIANTES = 30;

void inicializarListaEstudiantes(tListaEstudiantes & lista);
bool buscar(tListaEstudiantes const & lista, std::string const & NIF, int & pos);
void insertar(tListaEstudiantes & lista, tEstudiante const & estudiante);
void ampliar(tListaEstudiantes & lista);
void mostrar(std::ostream & flujo, tListaEstudiantes const & lista);
void liberar(tListaEstudiantes & lista);

#endif