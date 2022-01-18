#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

enum tElemento { PIEDRA, PAPEL, TIJERAS, LAGARTO, SPOCK };
enum tResultado{ HUMANO, COMPUTADORA, EMPATE};



int leeOpcion(std::string pregunta, std::string mensajeError, int valMin, int valMax) {
	int opt = 0;
	std::cout << pregunta;
	std::cin >> opt;
	while (opt < valMin || opt> valMax) {
		std::cout << mensajeError;
		std::cout << pregunta;
		std::cin >> opt;
	}
	return opt;
}

bool check(std::string jugada) {
	if (jugada == "piedra" || jugada == "papel" || jugada == "tijeras"
		|| jugada == "lagarto" || jugada == "Spock") return true;

	else return false;
}

tElemento fromString(std::string entrada) {
	if (entrada == "piedra") return PIEDRA;
	if (entrada == "papel") return PAPEL;
	if (entrada == "tijeras") return TIJERAS;
	if (entrada == "lagarto") return LAGARTO;
	if (entrada == "Spock") return SPOCK;
}

tElemento leeJugada(std::string pregunta) {
	std::string entrada = "";
	tElemento jugada;
	std::cout << pregunta;
	std::cin >> entrada;
	while (!check(entrada)) {
		std::cout << pregunta;
		std::cin >> entrada;
	}
	jugada = fromString(entrada);
	return jugada;
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

bool gana(tElemento jugador1, tElemento jugador2) {
	if (jugador1 == PIEDRA && (jugador2 == LAGARTO || jugador2 == TIJERAS)) return true;
	else if (jugador1 == PAPEL && (jugador2 == PIEDRA || jugador2 == SPOCK)) return true;
	else if (jugador1 == TIJERAS && (jugador2 == PAPEL || jugador2 == LAGARTO)) return true;
	else if (jugador1 == LAGARTO && (jugador2 == PAPEL || jugador2 == SPOCK)) return true;
	else if (jugador1 == SPOCK && (jugador2 == PIEDRA || jugador2 == TIJERAS)) return true;
	else return false;
}

int main() {
	tElemento compchoice, playchoice; bool again= true;
	int partjugadas = 0, partganadas = 0, partperdidas = 0, partempatadas = 0;

	while (again) {
		srand(time(NULL));
		compchoice = tElemento(rand() % 5);
		playchoice = leeJugada("Elige elemento: ");

		std::cout << '\n';
		std::cout << "Eleccion computadora: " << toString(compchoice)<<'\n';
		std::cout << "Tu eleccion: " << toString(playchoice) << '\n';
		std::cout << "-------------------------------------------------\n";

		if (gana(playchoice, compchoice)){
			std::cout << "Has ganado\n"; 
			++partganadas; 
		}
		else if (gana(compchoice, playchoice)) {
			std::cout << "Ha ganado la computadora\n";
			++partperdidas;
		}
		else {
			std::cout << "Se ha producido un empate\n";
			++partempatadas;
		}
		++partjugadas;
		if (leeOpcion("Desea continuar?\n 1-Si\n 2-No\n", "El valor introducido no es valido", 1, 2)==2)again = false;
	}
	std::cout << "Partidas jugadas: " << partjugadas<<'\n';
	std::cout << "Partidas ganadas: " << partganadas<<'\n';
	std::cout << "Partidas perdidas: " << partperdidas<<'\n';
	std::cout << "Partidas empatadas: " << partempatadas<<'\n';

	system("PAUSE");
	return 0;
}
