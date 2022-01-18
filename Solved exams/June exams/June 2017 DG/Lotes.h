//Marcos Herrero

#ifndef LOTES_H
#define LOTES_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

struct tLotes{
	std::string id;
	std::string tipo;
	float peso;
	float precio;
	long long int idcomprador;
};

bool operator<(tLotes const & lote1, tLotes const & lote2);
bool operator==(tLotes const & lote1, tLotes const & lote2);
std::istream &operator>>(std::istream & flujo, tLotes & lote);
void mostrarLote(tLotes const & lote);
void mostrarPrecio(tLotes const & lote);
void modificarLote(tLotes & lote, long long int idcomprador, float precio);

#endif