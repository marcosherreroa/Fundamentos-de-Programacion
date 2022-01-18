//Marcos Herrero

#ifndef GRUPOCHAT_H
#define GRUPOCHAT_H

#include "ListaContactos.h"

struct tElemento {
	tContacto* punt;
	int nmensajes;
};

struct tGrupoChat {
	tElemento* v;
	int cont;
	int capacidad;
	std::string nombre;
};

bool operator<(tElemento const & el1, tElemento const & el2);
tGrupoChat nuevo(std::string const & nombre, int dim);
void destruir(tGrupoChat & grupo);
bool busqbinrecurs(tGrupoChat const & grupo, int ini, int fin, std::string const & idbuscado, int & pos);
bool buscar(tGrupoChat const & grupo, std::string const & idbuscado, int & pos);
bool insertar(tGrupoChat & grupo, tElemento const elemento);
void mostrar(tGrupoChat const & grupo);
tGrupoChat combinar(tGrupoChat const & A, tGrupoChat const & B);

#endif