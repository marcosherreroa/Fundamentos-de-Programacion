#include "tablero.h"

enum tCarta { AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER };
using tVCartas = std::vector<tCarta>;

tCarta string2carta(std::string const& s) {
	tCarta c;
	if (s == "AVANZAR") c = AVANZAR;
	else if (s == "GIRODERECHA")  c = GIRODERECHA;
	else if (s == "GIROIZQUIERDA") c = GIROIZQUIERDA;
	else c = LASER;
	return c;

}

bool realizarMovimiento(tTablero & tablero, tCoordenada const & coord, tVCartas const & vcartas){
	tCoordenada coordtort;
	coordtort.x = coord.x;
	coordtort.y = coord.y;
	tCoordenada coordCasillasig;
	tCasilla casillatort = tablero[coordtort.x][coordtort.y];
	bool joya = false;

	for (int i = 0; !joya && i < vcartas.size(); ++i){
		switch (vcartas[i]) {
		case AVANZAR: {
			if (comprobarMovimiento(tablero, coordtort, tablero[coordtort.x][coordtort.y].tortuga.dir)) {
				coordCasillasig.x = coordtort.x + incF[tablero[coordtort.x][coordtort.y].tortuga.dir];
				coordCasillasig.y = coordtort.y + incC[tablero[coordtort.x][coordtort.y].tortuga.dir];
				tCasilla casillasiguiente = tablero[coordCasillasig.x][coordCasillasig.y];

				if (casillasiguiente.estado == JOYA) {
					avanzar(tablero, coordtort, tablero[coordtort.x][coordtort.y].tortuga.dir);
					joya = true;
				}
				else if (casillasiguiente.estado == CAJA) {
					avanzar(tablero, coordCasillasig, tablero[coordtort.x][coordtort.y].tortuga.dir);
					avanzar(tablero, coordtort, tablero[coordtort.x][coordtort.y].tortuga.dir);
				}
				else avanzar(tablero, coordtort, tablero[coordtort.x][coordtort.y].tortuga.dir);
				
				coordtort = coordCasillasig;
				
			}
			break;
		}
		case GIROIZQUIERDA: {
			--tablero[coordtort.x][coordtort.y].tortuga.dir;
			break;
		}
		case GIRODERECHA: {
			++tablero[coordtort.x][coordtort.y].tortuga.dir;
			break;
		}
		case LASER: {
			laser(tablero, coordtort, tablero[coordtort.x][coordtort.y].tortuga.dir);
			break;
		}
		}
	}
	
	return joya;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	std::string linea;
	getline(std::cin, linea);
	std::stringstream ss; ss << linea;
	int numJugadores; ss >> numJugadores;
	if (numJugadores == 0) return false;
	int numTortuga; ss >> numTortuga;
	int numAcciones;  ss >> numAcciones;
	getline(std::cin, linea);
	ss.clear(); ss << linea;
	tVCartas vCartas(numAcciones);
	for (int i = 0; i < numAcciones; ++i){
		std::string aux; ss >> aux; vCartas[i] = string2carta(aux);
	}
	tTablero tablero(DIMENSION, std::vector<tCasilla>(DIMENSION));
	// Carga el tablero
	cargar(tablero, std::cin, numJugadores);
	tCoordenada coor;
	// Busca la tortuga a la que le toca jugar
	bool enc = false;
	int encontradas = 0;
	for (int i = 0; i < DIMENSION && !enc; ++i){
		for (int j = 0; j < DIMENSION && !enc; ++j){
			if (tablero[i][j].estado == TORTUGA) {
				encontradas++;
				if (numTortuga == encontradas){
					enc = true;
					coor.x = i;
					coor.y = j;
				}
			}
		}
	}
	// LLamada a la funcion que hace el movimiento
	bool ok = realizarMovimiento(tablero, coor, vCartas);
	// Mostrar tablero de salida
	if (ok) std::cout << "JOYA\n";
	else std::cout<< tablero;
	std::cout << '\n';
	// Para leer los tableros que no se han usado.
	// Son tableros del caso que se encuentran despues del tablero que se carga
	getline(std::cin, linea);
	while (std::cin && linea != "---") getline(std::cin, linea);
	return true;
}



int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	while (resuelveCaso());
	;


#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}