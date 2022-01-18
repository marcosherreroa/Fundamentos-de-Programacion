#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "carta.h"
#include "puntuaciones.h"

const int MAXJUGADORES= 4;
const int MINJUGADORES = 1;

const int MAXLETRAS = 12;// numero de caracteres maximo y
const int MINLETRAS = 2;// minimo que se permite como nombre de jugador ( no se permiten espacios)

using tMano = std::vector<int>;
const int CARTASMANO_INICIAL = 3;

const int MODOEJECSEC = 1; //Modo 1: comprueba si las jugadas son posibles conforme el  jugador las introduce y no permite
                         // cancelar la secuencia ( porque va restando las cartas conforme se introducen)
                         //Modo 2: comprueba si las jugadas son posibles una vez introducida la secuencia entera. Además permite
	                     // cancelar una secuencia

enum tTecla{ ARRIBA, ABAJO, IZQUIERDA, DERECHA, ESPACIO, ENTER, OTRA}; // usado para leer teclas especiales

struct tJugador{
	tMano mano;
	tMazo mazo;
	std::string nombre;
	tCoordenada coord;
};

struct tJuego{
	tTablero tablero;
	int numJugadores;
	int turno;  // indica el numero del jugador que tiene el turno (numerando de 0 a 3)
	std::vector<tJugador> jugadores; // se ha elegido numerar a los jugadores de 0 a 3 en el codigo por coherencia con este vector	                                 //
};                                   // No obstante, de cara al jugador aparecen numerados de 1 a 4, como se pedia

void incluirCarta(tMano & mano, tCarta carta); // añade una carta a la mano de un jugador
bool cargarJuego(tJuego & juego);  // da configuracion a todos los aspectos necesarios para la partida. Llama a cargarTablero()
void mostrarJuego(tJuego const & juego); // muestra el tablero y la lista de jugadores con sus correspondientes manos
bool realizarMovimiento(tTablero & tablero, tCoordenada const & coord, tVCartas const & vcartas); // se vale de avanzar() para modificar el tablero
bool ejecutarTurno(tJuego &juego); // permite a los jugadores robar cartas y ejecutar secuencias
bool ejecutarSecuenciaModo1(tJuego & juego, bool & joya);// vease constante MODOEJECSEC
bool ejecutarSecuenciaModo2(tJuego & juego, bool & joya);
bool jugar(tPuntuaciones & puntuaciones); // funcion principal del modulo, que llama a las demas

#endif


