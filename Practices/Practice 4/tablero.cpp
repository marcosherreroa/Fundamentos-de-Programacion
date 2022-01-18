//Marcos Herrero

#include "tablero.h"
#include "checkML.h"

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void chartoCasilla(tCasilla & casilla, char caracter, int idtort ){
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

void casillatoString(std::string & cadena, tCasilla const & casilla) {

	switch (casilla.estado) {
	case VACIA: {cadena = "  "; break; }
	case HIELO: {cadena = "**"; break; }
	case  MURO: {cadena = "||"; break; }
	case  CAJA: {cadena = "[]"; break; }
	case  JOYA: {cadena = "00"; break; }
	case  TORTUGA: {
		switch (casilla.tortuga.dir) {
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
	colorFondo(PALETA[casilla.estado + casilla.tortuga.id]);  
	flujo << cadena;
	colorFondo(0);
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

// incremento prefijo
tDir operator++(tDir & dir) {
	dir = tDir((int(dir) + 1) % NUM_DIRECCIONES);
	return dir;
}
// incremento posfijo
tDir operator++(tDir & dir, int) {
	tDir aux = dir;
	dir = tDir((int(dir) + 1) % NUM_DIRECCIONES);
	return aux;
}

// decremento prefijo
tDir operator--(tDir & dir){
	if (dir == UP) dir = LEFT;
    else dir = tDir(int(dir) - 1);
	return dir;
}

//decremento posfijo
tDir operator--(tDir & dir, int){
	tDir aux = dir;
	if (dir == UP) dir = LEFT;
	else dir = tDir(int(dir) - 1);
	return aux;
}

bool comprobarCoord(tCoordenada const & coord){
	return (coord.x >= 0 && coord.x < DIMENSION && coord.y >= 0 && coord.y < DIMENSION);
}

void avanzar(tTablero & tablero, tCoordenada const & coord, tDir const & direccion){
		tablero[coord.x + incF[direccion]][coord.y + incC[direccion]] = tablero[coord.x][coord.y];
		tablero[coord.x][coord.y].estado = VACIA;
		tablero[coord.x][coord.y].tortuga.id = 0;
}

bool comprobarMovimiento(tTablero const & tablero, tCoordenada const & coordtort, tDir dirtort){
	tCoordenada coordCasilla;
	coordCasilla.x = coordtort.x + incF[dirtort];
	coordCasilla.y = coordtort.y + incC[dirtort];

	if (!comprobarCoord(coordCasilla)) return false;
	else {
		tCasilla casilla = tablero[coordCasilla.x][coordCasilla.y];
		tCoordenada coordCasillaSig;
		coordCasillaSig.x = coordCasilla.x + incF[dirtort];
		coordCasillaSig.y = coordCasilla.y + incC[dirtort];

		if (casilla.estado == VACIA || casilla.estado == JOYA) return true;
		else if (casilla.estado == CAJA) {
			return (comprobarCoord(coordCasillaSig) && tablero[coordCasillaSig.x][coordCasillaSig.y].estado == VACIA);
		}
		else return false;


	}
}

void cargarTablero(tTablero & tablero, std::vector<tCoordenada> & coordstorts, std::istream & flujo, int numJugadores) {
	std::string linea = "";
	getline(flujo, linea);
	std::stringstream ss; ss << linea;
	int numTortugas;
	ss >> numTortugas;

	while (numTortugas != numJugadores) {
		for (int i = 0; i < DIMENSION; ++i) getline(flujo, linea);
		ss.clear();
		getline(flujo, linea);
		ss << linea;
		ss >> numTortugas;
	}

	char caracter = ' '; int idtort = 0;

	for (int i = 0; i < DIMENSION; ++i) {
		getline(flujo, linea);

		for (int j = 0; j < DIMENSION; ++j) {
			caracter = linea[j];

			if (caracter == 'U' || caracter == 'D' || caracter == 'R' || caracter == 'L') {
				chartoCasilla(tablero[i][j], caracter, idtort);
				coordstorts[idtort].x = i;
				coordstorts[idtort].y = j;
				++idtort;
			}
			else chartoCasilla(tablero[i][j], caracter);

		}
	}

}

void laser(tTablero & tablero, tCoordenada const & coordtort, tDir dirtort) {
	bool interceptado = false;
	tCoordenada coordlaser = coordtort;
	coordlaser.x += incF[dirtort];
	coordlaser.y += incC[dirtort];

	while (comprobarCoord(coordlaser) && !interceptado) {
		if (tablero[coordlaser.x][coordlaser.y].estado != VACIA) {
			interceptado = true;
			if (tablero[coordlaser.x][coordlaser.y].estado == HIELO) tablero[coordlaser.x][coordlaser.y].estado = VACIA;
		}
		coordlaser.x += incF[dirtort];
		coordlaser.y += incC[dirtort];
	}
}
