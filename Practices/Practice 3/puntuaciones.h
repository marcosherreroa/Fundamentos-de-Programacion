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

const std::string FICHERO_PUNTUACIONES = "Puntuaciones.txt";
using tPuntuaciones = std::vector<tpuntosJugador>;

std::istream &operator>>(std::istream & flujo, tpuntosJugador & puntosJugador);
std::ostream &operator<<(std::ostream & flujo, tpuntosJugador const & puntosJugador);
bool cargarPuntuaciones(tPuntuaciones & puntuaciones);
bool guardarPuntuaciones(tPuntuaciones const & puntuaciones);
void mostrarPuntuaciones(tPuntuaciones const & puntuaciones);
bool actualizarPuntuacion(tPuntuaciones & puntuaciones, std::string const & nombre, int nuevos);

#endif