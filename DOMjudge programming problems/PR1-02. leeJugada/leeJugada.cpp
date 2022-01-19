

#include <iostream>
#include <string>

// Escribe aqui el tipo enumerado
// Escribir aqui las funciones leeJugada y fromString.
enum tElemento{PIEDRA, PAPEL, TIJERAS, LAGARTO, SPOCK};

bool check(std::string jugada){
	return (jugada == "piedra" || jugada =="papel" || jugada=="tijeras"
		|| jugada=="lagarto"||jugada=="Spock");
}

tElemento fromString(std::string entrada){
	if (entrada == "piedra") return PIEDRA;
	if (entrada == "papel") return PAPEL;
	if (entrada == "tijeras") return TIJERAS;
	if (entrada == "lagarto") return LAGARTO;
	if (entrada == "Spock") return SPOCK;
}

tElemento leeJugada(std::string pregunta){
	std::string entrada="";
	tElemento jugada;
	std::cout << pregunta;
	std::cin >> entrada;
	while (!check(entrada)){
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

void resuelveCaso() {
    tElemento jugada = leeJugada("");
    std::cout << "Jugaste " << toString(jugada) << '\n';
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	return 0;
}

