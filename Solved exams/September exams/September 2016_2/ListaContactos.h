// Marcos Herrero

#ifndef CONTACTOS_H
#define CONTACTOS_H

#include "Contacto.h"

const int MAXCONTACTOS = 50;

struct tListaContactos {
	tContacto* v[MAXCONTACTOS];
	int cont;
};

void crear(tListaContactos & lista);
void destruir(tListaContactos & lista);
void cargar(tListaContactos & lista, std::istream & flujo);

#endif