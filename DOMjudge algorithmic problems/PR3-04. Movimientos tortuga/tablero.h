#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

const int DIMENSION = 8;
const int NUM_DIRECCIONES = 4;
const std::vector<int> incF{ -1, 0, 1, 0 };
const std::vector<int> incC{ 0, 1, 0, -1 };

enum tEstadoCasilla{ VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA, NUMESTADOS };
enum tDir { UP, RIGHT, DOWN, LEFT };


struct tTortuga{
	int id;
	tDir dir;
};

struct tCasilla{
	tEstadoCasilla estado;
	tTortuga tortuga;
};

struct tCoordenada{
	int x;
	int y;
};

using tTablero = std::vector<std::vector<tCasilla>>;

void chartoCasilla(tCasilla & casilla, char caracter, int idtort = 0);
void casillatoString(std::string & cadena, tCasilla const & casilla);
std::ostream &operator<<(std::ostream & flujo, tCasilla const & casilla);
std::ostream &operator<<(std::ostream & flujo, tTablero const & tablero);
tDir operator++(tDir & dir);
tDir operator++(tDir & dir, int);
tDir operator--(tDir & dir);
tDir operator--(tDir & dir, int);
bool comprobarCoord(tCoordenada const & coord);
void avanzar(tTablero & tablero, tCoordenada const & coord, tDir const & direccion);
bool comprobarMovimiento(tTablero const & tablero, tCoordenada const & coordtort, tDir dirtort);
void cargar(tTablero & tablero, std::istream & flujo, int numJugadores);
void laser(tTablero & tablero, tCoordenada const & coordtort, tDir dirtort);

#endif