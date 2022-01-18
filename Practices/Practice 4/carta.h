//Marcos Herrero

#ifndef CARTA_H
#define CARTA_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <functional>


enum tCarta{AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER, NUMMOVIMIENTOS}; //posibles movimientos de la tortuga

using tVCartas = std::vector<tCarta>;

//Cartas iniciales de cada mazo por tipo:
const int NA_INICIAL = 18; // cartas avanzar
const int NGI_INICIAL = 8; // cartas giro izquierda
const int NGD_INICIAL = 8; // cartas giro derecha
const int NL_INICIAL = 4;  // cartas laser
const int CARTASMAZO_INICIAL = NA_INICIAL + NGI_INICIAL + NGD_INICIAL + NL_INICIAL; // cartas totales

struct tMazo {   // vector circular. Cambiamos su tamaño moviendo inicio y fin
	tCarta* baraja [CARTASMAZO_INICIAL];
	int inicio; // posicion de la primera carta. Cuando esta lleno es 0
	int fin;    // posicion inmediatamente posterior a la ultima carta. Cuando esta lleno es 0
	int ncartas; // distingue el vector lleno del vector vacío
};

std::ostream &operator<<(std::ostream & flujo, tCarta carta);
std::ostream &operator<<(std::ostream & flujo, tMazo const & mazo);
void liberarMazo(tMazo & mazo); // libera la memoria dinamica reservada por el mazo
void crearMazoAleatorio(tMazo & mazo, int nA, int nGI, int nGD, int nL);
bool cogerCarta(tMazo &  mazo, tCarta & carta); // se obtiene la carta de la posicion inicio y se reduce el mazo
void devolverCarta(tMazo & mazo, tCarta carta); // se añade la carta en la posicion fin, aumentando el mazo
void devolverVector(tMazo & mazo, tVCartas & vcartas); // se devuelve un conjunto de cartas en orden

#endif