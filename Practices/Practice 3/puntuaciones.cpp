#include "puntuaciones.h"

std::istream &operator>>(std::istream & flujo, tpuntosJugador & puntosJugador) {
	flujo >> puntosJugador.nombre >> puntosJugador.puntos;
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tpuntosJugador const & puntosJugador) {
	flujo << puntosJugador.nombre <<' '<<puntosJugador.puntos;
	return flujo;
}

bool operator>(tpuntosJugador const & jugador1, tpuntosJugador const & jugador2) {
	if (jugador1.puntos > jugador2.puntos) return true;
	else return false;
}

bool cargarPuntuaciones(tPuntuaciones & puntuaciones) {
	std::ifstream entrada;

	entrada.open(FICHERO_PUNTUACIONES);
	if (!entrada.is_open()) return false;

	tpuntosJugador puntosJugador;
	entrada >> puntosJugador;    // se tiene que leer antes de comprobar para evitar incluir el EOF en el vector de puntuaciones
	while (!entrada.eof()) {     // para que el archivo no se salte el ultimo elemento, siempre habras una ultima linea en blanco en el fichero
		puntuaciones.push_back(puntosJugador);
		entrada >> puntosJugador;
	}

	entrada.close();
	return true;
}

bool guardarPuntuaciones(tPuntuaciones const & puntuaciones) {
	std::ofstream salida;

	salida.open(FICHERO_PUNTUACIONES);
	if (!salida.is_open()) return false;

	for (int i = 0; i < puntuaciones.size(); ++i) salida << puntuaciones[i]<<'\n'; // despues del ultimo jugador, hay una linea en blanco
	                                                                               // esencial para que se pueda leer todo el fichero y
	salida.close();                                                                // no haya problemas con EOF
	return true;
}

void mostrarPuntuaciones(tPuntuaciones const & puntuaciones) {
	if (puntuaciones.size() == 0) std::cout << "\nNo hay puntuaciones guardadas\n\n";
	else {
		std::cout << "\nPUNTUACIONES\n\n";

		for (int i = 0; i < puntuaciones.size(); ++i) std::cout << i+1 << ". " << puntuaciones[i] << '\n';
	}
	std::cout << '\n';
}

bool actualizarPuntuacion(tPuntuaciones & puntuaciones, std::string const & nombre, int nuevos) {
	bool encontrado = false;

	for (int i = 0; !encontrado && i < puntuaciones.size(); ++i) {
		if (puntuaciones[i].nombre == nombre) {
			encontrado = true;
			puntuaciones[i].puntos += nuevos;
		}
	}

	if (!encontrado) {
		tpuntosJugador puntosJugador;
		puntosJugador.nombre = nombre;
		puntosJugador.puntos = nuevos;
		puntuaciones.push_back(puntosJugador);
	}

	std::sort(puntuaciones.begin(), puntuaciones.end(), std::greater<tpuntosJugador>());
	return encontrado;
}