

#include <iostream>
#include <string>

// Escribe aqui el tipo enumerado
// Escribir aqui la funcion toString, leeJuegada ygana.
enum tElemento { PIEDRA, PAPEL, TIJERAS, LAGARTO, SPOCK };
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
	else if (jugador1== SPOCK && (jugador2 == PIEDRA || jugador2 == TIJERAS)) return true;
	else return false;
}

void resuelveCaso() {
    tElemento jugada1, jugada2;
    jugada1 = leeJugada("");
    jugada2 = leeJugada("");
    
    if (gana(jugada1, jugada2)) {
		std::cout << "Gana " << toString(jugada1) << '\n';
    } else if (gana(jugada2, jugada1)) {
		std::cout << "Gana " << toString(jugada2) << '\n';
    } else {
		std::cout << "Empate\n";
    }
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	return 0;
}

