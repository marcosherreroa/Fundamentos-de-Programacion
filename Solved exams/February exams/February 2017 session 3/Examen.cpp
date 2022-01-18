#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>


const unsigned int N = 10;
const unsigned int max_longitud = 8;
const unsigned int max_puntos = 3;
const unsigned int max_goles = 2;

struct tEquipo {
	std::string acronimo;
	int npuntos;
};

struct tPartido {
	tEquipo equipo1;
	tEquipo equipo2;
};

using tClasificacion = std::vector<tEquipo>;
using tJornada = std::vector<tPartido>;

std::istream &operator>>(std::istream & flujo, tEquipo & equipo) {
	flujo >> equipo.acronimo >> equipo.npuntos;
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tEquipo const & equipo) {
	flujo << equipo.acronimo << ' ' << equipo.npuntos;
	return flujo;
}

std::istream &operator>>(std::istream & flujo, tPartido & partido) {
	flujo >> partido.equipo1 >> partido.equipo2;
	return flujo;
}

int leeOpcion(std::string const & pregunta, std::string const & mensajeError, int valmin, int valmax) {
	int opt = 0;
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

int buscarEquipo(tClasificacion const & clasificacion, std::string const & acronimo) {
	bool encontrado = false; int posicion = -1;
	for (int i = 0; !encontrado && i < N; ++i) {
		if (clasificacion[i].acronimo == acronimo) {
			posicion = i;
			encontrado = true;
		}
	}
	return posicion;
}
bool cargarLiga(tClasificacion & clasificacion) {
	std::ifstream entrada;
	entrada.open("liga.txt");
	if (!entrada.is_open()) {
		std::cout << "El fichero no existe\n\n";
		return false;
	}

	for (int i = 0; i < N; ++i) entrada >> clasificacion[i];

	entrada.close();
	return true;
}

bool cargarJornada(tJornada & jornada) {
	std::ifstream entrada;
	entrada.open("jornada.txt");
	if (!entrada.is_open()) {
		std::cout << "El fichero no existe\n\n";
		return false;
	}

	tPartido partido; bool OK = true;
	for (int i = 0; OK && i < N / 2; ++i) {
		entrada >> partido;

		for (int j = 0; OK && j < i; ++j) {
			if (jornada[j].equipo1.acronimo == partido.equipo1.acronimo || jornada[j].equipo1.acronimo == partido.equipo2.acronimo
				|| jornada[j].equipo2.acronimo == partido.equipo1.acronimo || jornada[j].equipo2.acronimo == partido.equipo2.acronimo) {
				OK = false;
				std::cout << "Se repiten equipos\n\n";
			}
		}
		if (OK) jornada[i] = partido;
	}

	entrada.close();
	return OK;
}

void mostrarLiga(tClasificacion const & clasificacion) {
	if (clasificacion[N-1].acronimo == "") std::cout << "No hay ninguna clasificacion guardada\n\n";
	
	else {
		std::cout << "\nCLASIFICACION\n\n";
		for (int i = 0; i < N; ++i) {
			std::cout << std::left<< std::setw(max_longitud + 3) << clasificacion[i].acronimo
				<< std::right << std::setw(max_puntos + 3) << clasificacion[i].npuntos<<" puntos\n";
		}
	}
}

void mostrarJornada(tJornada const & jornada) {
	if (jornada[N / 2 - 1].equipo2.acronimo == "") std::cout << "No hay ninguna jornada guardada\n\n";
	else {
		std::cout << "\nJORNADA\n\n";
		for (int i = 0; i < N / 2; ++i) {
			std::cout << std::left << std::setw(max_longitud + 3) << jornada[i].equipo1.acronimo<< std::setw(max_goles + 3) << jornada[i].equipo1.npuntos
				<< std::setw(max_goles + 3) << jornada[i].equipo2.npuntos <<std::right<< std::setw(max_longitud + 3) << jornada[i].equipo2.acronimo<<'\n';
		}
	}
}

void actualizarLiga(tClasificacion & clasificacion, tJornada const & jornada) {
	if (clasificacion[N - 1].acronimo == "") std::cout << "No hay ninguna clasificacion guardada\n\n";
	else if (jornada[N / 2 - 1].equipo2.acronimo == "") std::cout << "No hay ninguna jornada guardada\n\n";

	else{
		for (int i = 0; i < N / 2; ++i) {
			int posicion1 = buscarEquipo(clasificacion, jornada[i].equipo1.acronimo);
			int posicion2 = buscarEquipo(clasificacion, jornada[i].equipo2.acronimo);

			if (posicion1 == -1 || posicion2 == -1) std::cout << "Uno de los equipos de la jornada no se encuentra en la clasificacion\n\n";
			else {

				if (jornada[i].equipo1.npuntos > jornada[i].equipo2.npuntos) clasificacion[posicion1].npuntos += 3;
				else if (jornada[i].equipo1.npuntos < jornada[i].equipo2.npuntos) clasificacion[posicion2].npuntos += 3;
				else { clasificacion[posicion1].npuntos++; clasificacion[posicion2].npuntos++; }

			}
		}
	}
}

void mostrarPrimero(tClasificacion const & clasificacion) {
	if (clasificacion[N - 1].acronimo == "") std::cout << "No hay ninguna clasificacion guardada\n\n";
	else {
		tEquipo primero; int maxpunt = 0;
		for (int i = 0; i < N; ++i) {
			if (clasificacion[i].npuntos > maxpunt) {
				primero = clasificacion[i];
				maxpunt = clasificacion[i].npuntos;
			}
		}
		std::cout << primero << " puntos\n\n";
	}
}

bool guardarLiga(tClasificacion const & clasificacion) {
	if (clasificacion[N - 1].acronimo == "") {
		std::cout << "No hay ninguna clasificacion guardada\n\n";
		return false;
	}
	
	std::ofstream salida;
	salida.open("liga.txt");
	if (!salida.is_open()) {
		std::cout << "El fichero no existe";
		return false;
	}

	for (int i = 0; i < N; ++i) salida << clasificacion[i]<<'\n';
	salida.close();
	return true;
}

int main() {
	std::string pregunta = "\nMENU\n\n1-Cargar liga\n2-Cargar jornada\n3-Mostrar clasificacion\n4-Mostrar jornada\n5-Actualizar clasificacion\n6-Mostrar primero\n7-Guardar liga\n0-Salir\n\nIntroduzca una opcion[0-7]: ";
	std::string mensajeError = "La opcion introducida no es valida\n";
	bool menu = true;

	tClasificacion clasificacion(N);
	tJornada jornada(N/2);

	while (menu) {
		switch (leeOpcion(pregunta, mensajeError, 0, 7)) {
		case 1: {
			bool OK= cargarLiga(clasificacion);
			if (!OK) std::cout << "No se ha podido cargar\n\n";
			break; 
		}
		case 2: {
			bool OK= cargarJornada(jornada);
			if (!OK) std::cout << "No se ha podido cargar\n\n";
			break;
		}
		case 3: {mostrarLiga(clasificacion); break; }
		case 4: {mostrarJornada(jornada); break; }
		case 5: {actualizarLiga(clasificacion, jornada); break; }
		case 6: { mostrarPrimero(clasificacion); break; }
		case 7: {
			bool OK= guardarLiga(clasificacion);
			if (!OK) std::cout << "No se ha podido cargar\n\n";
			break; 
		}
		case 0: menu = false;
		}
	}

	system("PAUSE");
	return 0;
}
