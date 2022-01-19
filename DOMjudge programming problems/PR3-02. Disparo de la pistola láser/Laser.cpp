
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

const int DIMENSION = 8;
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

void chartoCasilla(tCasilla & casilla, char caracter, int idtort = 0){
	switch (caracter){
	case ' ': {casilla.estado = VACIA; break; }
	case '@': {casilla.estado = HIELO; break; }
	case'#':{casilla.estado = MURO; break; }
	case 'C':{casilla.estado = CAJA; break; }
	case '$':{casilla.estado = JOYA; break; }
	case 'U':{
		casilla.estado = TORTUGA;
		casilla.tortuga.id = idtort;
		casilla.tortuga.dir = UP;
		break;
	}
	case 'D':{
		casilla.estado = TORTUGA;
		casilla.tortuga.id = idtort;
		casilla.tortuga.dir = DOWN;
		break;
	}
	case 'R':{
		casilla.estado = TORTUGA;
		casilla.tortuga.id = idtort;
		casilla.tortuga.dir = RIGHT;
		break;
	}
	case 'L':{
		casilla.estado = TORTUGA;
		casilla.tortuga.id = idtort;
		casilla.tortuga.dir = LEFT;
		break;
	}
	}

}

void casillatoString(std::string & cadena, tCasilla const & casilla){

	switch (casilla.estado){
	case VACIA: {cadena = "  "; break; }
	case HIELO: {cadena = "**"; break; }
	case  MURO: {cadena = "||"; break; }
	case  CAJA: {cadena = "[]"; break; }
	case  JOYA: {cadena = "00"; break; }
	case  TORTUGA: {
		switch (casilla.tortuga.dir){
		case UP: {cadena = "^^"; break; }
		case DOWN: {cadena = "vv"; break; }
		case LEFT: {cadena = "<<"; break; }
		case RIGHT: {cadena = ">>"; break; }
		}
		break; }
	}
}


std::ostream &operator<<(std::ostream & flujo, tCasilla const & casilla){
	std::string cadena = "";
	casillatoString(cadena, casilla);
	flujo << cadena;
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tTablero const & tablero){
	for (int i = 0; i < DIMENSION; ++i) {
		for (int j = 0; j < DIMENSION; ++j) {
			flujo << tablero[i][j];
		}
		flujo << '\n';
	}
	return flujo;
}

bool comprobarCoord(tCoordenada const & coord) {
	return (coord.x >= 0 && coord.x < DIMENSION && coord.y >= 0 && coord.y < DIMENSION);
}

void cargar(tTablero & tablero, std::istream & flujo, int numJugadores) {
	std::string linea = "";
	getline(flujo, linea);
	std::stringstream ss; ss << linea;
	int numTortugas = 0;
	ss >> numTortugas;

	
	while (numTortugas != numJugadores) {
		for (int i = 0; i < DIMENSION; ++i) getline(flujo, linea);
		ss.clear();
		getline(flujo, linea);
		ss << linea;
		ss >> numTortugas;
	}
	
	tCasilla casilla; char caracter = ' '; int idtort = 0;

	for (int i = 0; i < DIMENSION; ++i) {
		getline(flujo, linea);

		for (int j = 0; j < DIMENSION; ++j) {
			
			caracter = linea[j];

			if (caracter == 'U' || caracter == 'D' || caracter == 'R' || caracter == 'L') {
				++idtort;
				chartoCasilla(casilla, caracter, idtort);
			}
			else chartoCasilla(casilla, caracter);

			tablero[i][j] = casilla;
		}
	}
	
}

void laser(tTablero & tablero, tCoordenada const & coordtort, tDir dirtort) {
	bool interceptado = false;
	tCoordenada coordlaser = coordtort;
	coordlaser.x += incF[dirtort];
	coordlaser.y += incC[dirtort];

	while (comprobarCoord(coordlaser)&& !interceptado) {
		if (tablero[coordlaser.x][coordlaser.y].estado != VACIA) {
			interceptado = true;
			if (tablero[coordlaser.x][coordlaser.y].estado == HIELO) tablero[coordlaser.x][coordlaser.y].estado = VACIA;
		}
		coordlaser.x += incF[dirtort];
		coordlaser.y += incC[dirtort];
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    
	// leer los datos de la entrada
    std::string linea;
    getline(std::cin, linea);
    std::stringstream ss; ss << linea;
    int numJugadores;
    ss >> numJugadores;
    if (numJugadores == 0) return false;
    int numTortuga;
	
    ss >> numTortuga;
    tTablero tablero(DIMENSION,std::vector<tCasilla>(DIMENSION));
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
    // LLamada a la función laser
    laser(tablero,coor,tablero[coor.x][coor.y].tortuga.dir);
    // Mostrar tablero de salida
    std::cout << tablero <<'\n';
    // Para leer los tableros que no se han usado.
    // Son tableros del caso que se encuentran despues del tablero que se carga
    getline(std::cin, linea);
    while (std::cin && linea != "---") getline(std::cin, linea);
    return true;
}


int main() {
    // Estas instrucciones sirven para poder probar los problemas
    // utilizando un fichero en lugar de teclear los datos
    // Crear un fichero que se llame datos.txt
    // Copiar en este fichero la entrada de datos que se quiera
    // Estas instrucciones redireccionan la entrada por cin para que busque los
    // datos en el fichero en lugar de pedirlos por el teclado.
    // Para ejecutar en el juez no hay que cambiar nada porque el juez no ejecuta las instrucciones de redireccionamiento.
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




