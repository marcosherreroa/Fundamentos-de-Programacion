//Marcos Herrero

#ifndef LISTACOMPRADORES_H
#define LISTACOMPRADORES_H

#include <iostream>
#include <iomanip>

const int CAPINICIAL = 1;

struct tComprador {
	long long int num;
	float importe;
};

struct tListaComprador {
	tComprador* punt;
	int cont;
	int capacidad;
};

std::ostream &operator<<(std::ostream & flujo, tComprador const & comprador);
void inicializar(tListaComprador & lista);
void redimensionar(tListaComprador & lista);
void insertar(tListaComprador & lista, tComprador const & insertado);
bool buscar(tListaComprador const & lista, int num, int & pos);
void mostrar(tListaComprador const & lista);
void liberar(tListaComprador & lista);

#endif