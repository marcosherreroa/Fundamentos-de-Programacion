//Marcos Herrero

#ifndef TABLERO_H
#define TABLERO_H

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


const int DIMENSION = 8; //dimension del tablero

//vectores auxiliares:
const std::vector<int> incF { -1, 0, 1, 0 }; // incremento fila
const std::vector<int> incC { 0, 1, 0, -1 }; // incremento columna
const std::vector<int> PALETA = { 1,11,7,4,12,5,13,9,10,3 }; // colores

enum tEstadoCasilla{ VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA, NUMESTADOS }; 
enum tDir { UP, RIGHT, DOWN, LEFT, NUM_DIRECCIONES }; 


struct tTortuga{
	int id;   //el id de la tortuga, por ir asociado al numero del jugador, ira de 0 a 3 en el codigo y se mostrara por pantalla, si es 
	tDir dir; // necesario, de 1 a 4( sumandole 1). Las casillas sin tortuga tienen 0 en el campo id ( igual que la primera tortuga).
};            

struct tCasilla{
	tEstadoCasilla estado;
	tTortuga tortuga; // solo se utiliza cuando el estado es TORTUGA
};

struct tCoordenada{
	int x;
	int y;
};

using tTablero = std::vector<std::vector<tCasilla>>;

void colorFondo(int color); //cambia el color del fondo. Se utiliza junto con el vector PALETA
void chartoCasilla(tCasilla & casilla, char caracter, int idtort = -1);
void casillatoString(std::string & cadena, tCasilla const & casilla);
std::ostream &operator<<(std::ostream & flujo, tCasilla const & casilla);
std::ostream &operator<<(std::ostream & flujo, tTablero const & tablero);
tDir operator++(tDir & dir);    //modifica la direccion 90 grados en sentido horario
tDir operator++(tDir & dir, int);
tDir operator--(tDir & dir);    // modifica la direccion 90 grados en sentido antihorario
tDir operator--(tDir & dir, int);
bool comprobarCoord(tCoordenada const & coord);//comprueba si las coordenadas pertenecen al tablero
void avanzar(tTablero & tablero, tCoordenada const & coord, tDir const & direccion); // se utiliza para tortugas y para cajas. No comprueba nada
bool comprobarMovimiento(tTablero const & tablero, tCoordenada const & coordtort, tDir dirtort); // comprueba si el movimiento es posible ( no lo ejecuta)
void cargarTablero(tTablero & tablero, std::vector<tCoordenada> & coordstorts, std::istream & flujo, int numJugadores);
void laser(tTablero & tablero, tCoordenada const & coordtort, tDir dirtort); // modifica el tablero en función de la trayectoria del laser

#endif