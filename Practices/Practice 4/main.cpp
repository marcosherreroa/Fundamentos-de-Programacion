//Marcos Herrero

#include "juego.h"
#include "checkML.h"

int leeOpcion(std::string const & pregunta, std::string const & mensajeError, int valmin, int valmax) {
	int opt;

	std::cout << pregunta;
	std::cin >> opt;
	while (std::cin.fail() || opt<valmin || opt> valmax) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		std::cout << mensajeError;
		std::cout << pregunta;
		std::cin >> opt;
	}

	return opt;
}

void presentacion() {
	std::cout <<"\n\n"<< std::setfill('=') << std::setw(119) << '='<<'\n';
	colorFondo(PALETA[3]);
	std::cout << std::setfill(' ')<< std::setw(40)<<"ROBOT TURTLES de Marcos Herrero\n";
	colorFondo(0);
	std::cout << std::setfill('=') << std::setw(119) << '=' << "\n\n";
	std::cout << std::setfill(' ');

	std::cout << "Robot Turtles se desarrolla en un tablero de " << DIMENSION << 'x' << DIMENSION << " casillas y pueden jugar entre "
		<< MINJUGADORES << " y " << MAXJUGADORES << " jugadores.  Cada jugador dispone \nde un mazo de " << CARTASMAZO_INICIAL << " cartas: "
		<< NA_INICIAL << " de avanzar, " << NGI_INICIAL << " de girar a la izquierdad, " << NGD_INICIAL << " de girar a la derecha y "
		<< NL_INICIAL << " de laser. La mano \ninicial de cada jugador consta de " << CARTASMANO_INICIAL << " cartas, pudiendo obtenerse mas "
		<< "robando cartas del mazo. Durante el juego, cada \njugador desplaza su tortuga por el tablero, utilizando para ello las cartas de "
		<< "su mano, que permiten a las tortugas \nrealizar " << int(NUMMOVIMIENTOS) << " movimientos diferentes. Gana el primer jugador que "
		<< "consiga situar su tortuga sobre una joya. Cuando un \njugador gana una partida, recibe una puntuacion que depende del numero de " 
		<<"participantes en dicho  juego. Todas las \npuntuaciones de partidas anteriores se encuentran almacenadas en el fichero " 
		<< FICHERO_PUNTUACIONES << "\n\n";

	system("PAUSE");
	system("cls");
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	presentacion();

	tPuntuaciones puntuaciones;
	bool OK= cargarPuntuaciones(puntuaciones);
	if (!OK) {
		std::cout<<"\nNo se ha encontrado el fichero de puntuaciones\n\n";
		system("PAUSE");
	}

	bool menu = true;
	while (menu) {
		system("cls");
		colorFondo(PALETA[9]);
		std::cout << "\nMENU\n\n1. Jugar\n2. Mostrar puntuaciones\n0. Salir\n\n";
		colorFondo(0);

		switch (leeOpcion("Introduce una opcion [0-2]: ","La opcion introducida no es valida\n\n" , 0, 2)) {
		case 1: {
			bool juego = jugar(puntuaciones);
			if (!juego) std::cout << "No se ha podido cargar el juego\n\n";
			system("PAUSE");
			break; 
		}
		case 2: {
			system("cls");
			if (puntuaciones.cont == 0) {
				std::cout << "\nNo hay puntuaciones guardadas\n\n";
				system("PAUSE");
			}
			else {
				colorFondo(PALETA[9]);
				std::cout << "En que orden desea visualizarlas?\n\n1.Por puntos\n2.En orden alfabetico\n0.Atras\n\n";
				colorFondo(0);

				switch (leeOpcion("Introduce una opcion [0-2]: ", "La opcion introducida no es valida\n\n", 0, 2)) {
				case 1: mostrarPuntuaciones(puntuaciones, PORDEFECTO); break;
				case 2: mostrarPuntuaciones(puntuaciones, ALFAB); break;
				}
			}

			break;
		}
		case 0: menu = false; break;
		}
	}

	system("cls");
	OK= guardarPuntuaciones(puntuaciones);
	if (!OK) {
		std::cout << "\nNo se ha podido acceder al fichero de puntuaciones\n\n";
		system("PAUSE");
	}
	
	liberarPuntuaciones(puntuaciones);
	return 0;
}