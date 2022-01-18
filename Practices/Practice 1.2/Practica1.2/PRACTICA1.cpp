#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

const int MAX_VALORES = 5;
enum tElemento { PIEDRA, PAPEL, TIJERAS, LAGARTO, SPOCK };
enum tResultado{ HUMANO, COMPUTADORA, EMPATE};

tElemento fromString(std::string entrada) {
	if (entrada == "piedra") return PIEDRA;
	else if (entrada == "papel") return PAPEL;
	else if (entrada == "tijeras") return TIJERAS;
	else if (entrada == "lagarto") return LAGARTO;
	else return SPOCK;
}

std::string toString(tElemento jugada) {
		switch (jugada) {
		case PIEDRA: return "piedra";
		case PAPEL: return "papel";
		case TIJERAS: return "tijeras";
		case LAGARTO: return "lagarto";
		case SPOCK: return "Spock";
		}
	}

	int leeOpcion(std::string pregunta, std::string mensajeError, int valMin, int valMax) {
		int opt = 0;
		std::cout << pregunta;
		std::cin >> opt;

		while (std::cin.fail() || opt < valMin || opt> valMax) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			std::cout << mensajeError;
			std::cout << pregunta;
			std::cin >> opt;
		}
		return opt;
	}

bool check(std::string jugada) {
		return (jugada == "piedra" || jugada == "papel" || jugada == "tijeras"
			|| jugada == "lagarto" || jugada == "Spock");
	}

	tElemento leeJugada(std::string pregunta) {
		std::string entrada = "";
		std::cout << pregunta;
		std::cin >> entrada;
		while (!check(entrada)) {
			std::cout << pregunta;
			std::cin >> entrada;
		}
		return fromString(entrada);
	}

bool gana(tElemento jugador1, tElemento jugador2) {
		if (jugador1 == PIEDRA && (jugador2 == LAGARTO || jugador2 == TIJERAS)) return true;
		else if (jugador1 == PAPEL && (jugador2 == PIEDRA || jugador2 == SPOCK)) return true;
		else if (jugador1 == TIJERAS && (jugador2 == PAPEL || jugador2 == LAGARTO)) return true;
		else if (jugador1 == LAGARTO && (jugador2 == PAPEL || jugador2 == SPOCK)) return true;
		else if (jugador1 == SPOCK && (jugador2 == PIEDRA || jugador2 == TIJERAS)) return true;
		else return false;
	}

tResultado juegaPartida() {
		tElemento compchoice, playchoice;

		compchoice = tElemento(rand() % MAX_VALORES);
		playchoice = leeJugada("Elige elemento: ");

		std::cout << '\n';
		std::cout << "Eleccion computadora: " << toString(compchoice) << '\n';
		std::cout << "Tu eleccion: " << toString(playchoice) << '\n';
		std::cout << std::string(100,'-')<<'\n';

		if (gana(playchoice, compchoice)) return HUMANO;
		else if (gana(compchoice, playchoice)) return COMPUTADORA;
		else return EMPATE;
	}

bool escribeFichero(std::string nombreFichero, std::string marcaFin) {
		std::ifstream fichero; std::string linea = "";
		fichero.open(nombreFichero);
		if (!fichero.is_open()) return false;
		else {
			getline(fichero, linea);

			while (linea != marcaFin) {
				std::cout << linea << '\n';
				getline(fichero, linea);
			}
			fichero.close();
			system("PAUSE");
			return true;
		}
	}

void sesionDeJuego() {
	std::string pregunta = "\nMENU PRINCIPAL\n\n1 - Jugar\n2 - Ver reglas\n0 - Salir\n\nIntroduzca una opcion[0-2]: ";
	std::string mensajeError = "La opcion introducida no es valida\n";
	bool menu = true, OK = true;
	tResultado ganador;
    int partjugadas = 0, partganadas = 0, partperdidas = 0, partempatadas = 0;
    
	while (menu){ 
		switch (leeOpcion(pregunta, mensajeError, 0, 2)) {
		case 1:
			ganador = juegaPartida();
			switch (ganador) {
			case HUMANO: std::cout << "Has ganado\n"; ++partganadas; break;
			case COMPUTADORA: std::cout << "Ha ganado la computadora\n"; ++partperdidas; break;
			case EMPATE: std::cout << "Se ha producido un empate\n"; ++partempatadas; break;
			}
			++partjugadas; break;
		case 2:
			 OK = escribeFichero("reglas.txt","XXX");
			if (!OK)std::cout << "Error. No se encuentra el fichero de las reglas del juego\n";
			break;
		case 0: std::cout << "\nPartidas jugadas: " << partjugadas << '\n';
			std::cout << "Partidas ganadas: " << partganadas << '\n';
			std::cout << "Partidas perdidas: " << partperdidas << '\n';
			std::cout << "Partidas empatadas: " << partempatadas << "\n\n";
			menu= false;
		}
	}
}

bool localizacionJugador(std::string apodo) {
	std::ifstream registro; std::string nomregist = "";
	registro.open("registro.txt");
	if (!registro.is_open()) {
		std::cout << "Error. No se encuentra el registro de jugadores\n";
		return false;
	}
	else {
		getline(registro, nomregist);

		while (nomregist != "XXX" && nomregist != apodo) {
			getline(registro, nomregist);
		}
		registro.close();
		return (nomregist == apodo);
	}
}

void titulo(std::string frase) {
	std::cout << std::string(100, '=') << '\n';
	std::cout << frase << '\n';
	std::cout << std::string(100, '=') << '\n';
}

int main() {
	std::string apodo = ""; 
	srand(time(NULL));

	titulo("PIEDRA, PAPEL, TIJERA, LAGARTO, SPOCK de Marcos Herrero");
	std::cout << "Para jugar es necesario estar registrado\nPor favor, introduzca su apodo: ";
	getline(std::cin, apodo);

	if (localizacionJugador(apodo)) sesionDeJuego();
	else std::cout << "Apodo no encontrado\n";

	system("PAUSE");
	return 0;
}
