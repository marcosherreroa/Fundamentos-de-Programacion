//Marcos Herrero

#ifndef LISTATEMAS_H
#define LISTATEMAS_H

#include "Tema.h"

const int MAXTEMAS = 50;

struct tListaTemas {
	tTema* v[MAXTEMAS];
	int cont;
};

void crear(tListaTemas & lista);
void destruir(tListaTemas & lista);
bool cargar(tListaTemas & lista);

#endif
