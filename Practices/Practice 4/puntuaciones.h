//Marcos Herrero

#ifndef PUNTUACIONES_H
#define PUNTUACIONES_H

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

struct tpuntosJugador{
	std::string nombre;
	int puntos;
 };

template <typename T>  // permite implementar algunas funciones para vectores dinámicos genericos
struct vDinam {
	T* ptr;
	int cont;
	int capacidad;
};

using tPuntuaciones = vDinam<tpuntosJugador*>;

struct Comppordefecto {  // orden por defecto: decreciente por puntos y, si coinciden, alfabeticamente
	bool operator()(tpuntosJugador* jugador1, tpuntosJugador* jugador2) {
		if (jugador1->puntos > jugador2->puntos) return true;
		else if (jugador1->puntos == jugador2->puntos && jugador1->nombre < jugador2->nombre) return true;
		else return false;
	}
};

struct Compalfab { // orden alfabetico
	bool operator()(tpuntosJugador* jugador1, tpuntosJugador* jugador2) {
		if (jugador1->nombre < jugador2->nombre) return true;
		else return false;
	}
};

enum tOrden{PORDEFECTO, ALFAB};

const std::string FICHERO_PUNTUACIONES = "Puntuaciones.txt";
const int TAM_INICIAL = 4;  // tamaño inicial del array dinamico de puntuaciones
const int AUM_REDIMENSION = 4; // aumento del array de puntuaciones en cada redimension


std::istream &operator>>(std::istream & flujo, tpuntosJugador & puntosJugador);
std::ostream &operator<<(std::ostream & flujo, tpuntosJugador const & puntosJugador);

template <typename T>
void crearvDinam(vDinam<T> & v, int tam); // crea un array dinamico (con capacidad=tam y cont = 0)

template <typename T>
void redimensionar(vDinam<T> & v, int aum); // aumenta la capacidad de un array dinámico en aum

void liberarPuntuaciones(tPuntuaciones & puntuaciones); //libera la memoria dinamica reservada por las puntuaciones

template <typename T, typename Comp = Comppordefecto> 
void ordenarInsercion(std::vector<T> & v, Comp ord = Comp()); // ordena por el metodo de insercion( vale para cualquier vector)

template<typename T, typename Comp = Comppordefecto> 
bool buscarBinaria(vDinam<T> const & v, T buscado, int & pos, Comp ord = Comp()); // busca un elemento por el metodo binario (vale para cualquier array dinámico)

template<typename T, typename Comp = Comppordefecto> 
bool insertarSinRep(vDinam<T> & v, T insertado, int aum, Comp ord = Comp()); // inserta ordenadamente y sin repeticion un elemento, redimensionando en el proceso si es necesario

bool cargarPuntuaciones(tPuntuaciones & puntuaciones);
bool guardarPuntuaciones(tPuntuaciones const & puntuaciones);
void mostrarPuntuaciones(tPuntuaciones const & puntuaciones, tOrden comp);
bool actualizarPuntuacion(tPuntuaciones & puntuaciones, std::string const & nombre, int nuevos);

#endif