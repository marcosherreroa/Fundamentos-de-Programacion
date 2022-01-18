//Marcos Herrero

#ifndef LISTALONJA_H
#define LISTALONJA_H

#include "Lotes.h"

const int MAXLOTES = 300;
const std::string FICHERO = "fichero.txt";

struct tListaLonja {
	tLotes* v[MAXLOTES];
	int cont;
};

void inicializar(tListaLonja & lista);
int numlotes(tListaLonja const & lista);
bool insertar(tListaLonja & lista, tLotes const & insertado);
bool cargar(tListaLonja & lista);
bool busqbinrecurs(tListaLonja const & lista, tLotes const & buscado, int ini, int fin, int & pos);
bool buscar(tListaLonja const & lista, std::string const & id, std::string const & tipo, int & pos);
tLotes obtenerLote(tListaLonja const & lista, int pos);
void mostrar(tListaLonja const & lista);
void liberar(tListaLonja & lista);

#endif