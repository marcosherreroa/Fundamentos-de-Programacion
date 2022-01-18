#ifndef LISTAGRUPOS_H
#define LISTAGRUPOS_H

#include "listaEstudiantes.h";

const int TAMMAX_LISTAGRUPOS = 10;

struct tGrupo{
	std::string identificador;
	tListaEstudiantes lista;
};

struct tListaGrupos{
	tGrupo* v [TAMMAX_LISTAGRUPOS];
	int cont;
};

void inicializarListaGrupos(tListaGrupos & lista);
bool buscar(tListaGrupos const & lista, std::string const & identificador, int & pos);
void insertar(tListaGrupos & listaG, std::string const & identificador, tListaEstudiantes const & listaE);
void mostrarNotas(tListaGrupos const & lista, std::string const & NIF);
void mostrarSuspensos(tListaGrupos const & lista, std::string const & identificador);
void liberar(tListaGrupos & lista);



#endif