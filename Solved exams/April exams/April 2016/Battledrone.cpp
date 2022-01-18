//Marcos Herrero

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

enum tContenido {AIRE , DRON};
struct tCasilla {
	tContenido contenido;
	bool visible;
};

struct tCoordenada {
	int x;
	int y;
};

using tTablero = std::vector<std::vector<tCasilla>>;

const int DIM = 9;
const int DISPAROSTOT = 20;
const int DRONES = 3;
const int CASILLASDRON = 3 * DRONES;
const tCoordenada POSFIJA = { 2, 3 };
const std::vector<int> incF{ -1, -1, 0, 1, 1, 1, 0, -1 };
const std::vector<int> incC{ 0, 1, 1, 1, 0, -1, -1 , -1 };

std::istream &operator>>(std::istream & flujo, tCoordenada & pos) {
	flujo >> pos.x >> pos.y;
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tContenido const & contenido) {
	switch (contenido) {
	case AIRE: flujo << '~'; break;
	case DRON: flujo << '#'; break;
	}

	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tCasilla const & casilla) {
	if (!casilla.visible) flujo << '.';
	else flujo << casilla.contenido;

	return flujo;
}

bool comprobarCoord(tCoordenada const & coord) {
	return (0 <= coord.x && coord.x < DIM && 0 <= coord.y && coord.y < DIM);
}

bool comprobarEspacio(tTablero const & tablero, tCoordenada const & coordpico) {
	bool OK = true; tCoordenada coordaux;
	for (int i = coordpico.x-1; OK && i <= coordpico.x+2; ++i) {
		for (int j = coordpico.y - 1; OK && j <= coordpico.y + 1; ++j) {
			coordaux.x = i;
			coordaux.y = j;
			if (comprobarCoord(coordaux) && tablero[coordaux.x][coordaux.y].contenido == DRON) OK = false;
		}
	}

	coordaux.y = coordpico.y + 2;;
	for (int i = coordpico.x - 1; OK && i <= coordpico.x + 1; ++i) {
		coordaux.x = i;
		if (comprobarCoord(coordaux) && tablero[coordaux.x][coordaux.y].contenido == DRON) OK = false;
	}
	
	return OK;
}

bool colocarDron(tTablero & tablero, tCoordenada const & coordpico) {
	tCoordenada coordala1{ coordpico.x + 1, coordpico.y }, coordala2{ coordpico.x, coordpico.y + 1 };

	if (comprobarEspacio(tablero,coordpico)){
		tablero[coordpico.x][coordpico.y].contenido = DRON;
		tablero[coordala1.x][coordala1.y].contenido = DRON;
		tablero[coordala2.x][coordala2.y].contenido = DRON;
		return true;
	}

	else return false;
}

void generarTableroFijo(tTablero & tablero) {
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			tablero[i][j].visible = false;
		}
	}

	colocarDron(tablero, POSFIJA);
}

void generarTableroAleatorio(tTablero & tablero) {
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			tablero[i][j].visible = false;
		}
	}

	bool OK = true;
	for (int i = 0; i < DRONES; ++i) {
		tCoordenada randomcoord;
		randomcoord.x = rand() % (DIM-1);
		randomcoord.y = rand() % (DIM-1);
		OK = colocarDron(tablero, randomcoord);

		while (!OK) {
			randomcoord.x = rand() % (DIM-1);
			randomcoord.y = rand() % (DIM-1);
			OK = colocarDron(tablero, randomcoord);
		}
	}
}

void mostrarTablero(tTablero const & tablero) {
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			std::cout << tablero[i][j]<<' ';
		}
		std::cout << '\n';
	}
}

void mostrarTableroVisible(tTablero const & tablero) {
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			std::cout << tablero[i][j].contenido<<' ';
		}
		std::cout << '\n';
	}
}

bool atacarCelda(tTablero & tablero, tCoordenada const & coord) {
	tablero[coord.x][coord.y].visible = true;
	if (tablero[coord.x][coord.y].contenido == DRON) return true;
	else return false;
}

void jugar(tTablero & tablero) {
	int casdrondest = 0, disparosrest = DISPAROSTOT;

	while (casdrondest < CASILLASDRON && disparosrest > 0) {
		system("cls");
		mostrarTablero(tablero);
		std::cout << "\nDisparos restantes: " << disparosrest;

		tCoordenada coord;
		std::cout << "\n\nIntroduzca una celda a atacar: ";
		std::cin >> coord;
		while (!comprobarCoord(coord) || tablero[coord.x][coord.y].visible) {
			std::cout << "La celda introducida no es valida\n\n";
			std::cout << "Introduzca una celda a atacar: ";
			std::cin >> coord;
		}

		bool dron = atacarCelda(tablero, coord);
		if (dron)  ++casdrondest;
		--disparosrest;
	}

	system("cls");
	mostrarTableroVisible(tablero);

	if (casdrondest == CASILLASDRON) std::cout << "Enhorabuena! Has ganado la partida!\n\n";
	else std::cout << "Has perdido. Vuelve a intentarlo!\n\n";
}

int main() {
	srand(time(NULL));
	tTablero tablero(DIM, std::vector<tCasilla>(DIM));
	generarTableroAleatorio(tablero);
	jugar(tablero);

	system("PAUSE");
	return 0;
}