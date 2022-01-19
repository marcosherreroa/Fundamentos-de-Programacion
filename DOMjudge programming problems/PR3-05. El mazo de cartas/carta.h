// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11

#ifndef CARTA_H
#define CARTA_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

enum tCarta{AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER};
using tVCartas = std::vector<tCarta>;

struct tMazo {
	tVCartas baraja;
	int inicio;
	int fin;
	int ncartas;
};

std::ostream &operator<<(std::ostream & flujo, tCarta carta);
std::ostream &operator<<(std::ostream & flujo, tMazo const & mazo);
void crearMazo(tMazo & mazo, int nA, int nGI, int nGD, int nL);
bool cogerCarta(tMazo &  mazo, tCarta & carta);
void devolverCarta(tMazo & mazo, tVCartas & vcartas);
bool resuelveCaso();

#endif