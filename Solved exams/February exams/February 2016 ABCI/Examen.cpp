#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const unsigned int N = 8;

enum tEstado { EMBARCANDO, OPERADO, RETRASADO, SUSPENDIDO };

struct tVuelo {
	std::string numero;
	std::string destino;
	char terminal;
	int puerta;
	tEstado estado;
};

using tLista = std::vector<tVuelo>;

std::istream &operator>>(std::istream & flujo, tEstado & estado) {
	int num = 0;
	flujo >> num;
	estado = tEstado(num);
	return flujo;
}

std::istream &operator>>(std::istream & flujo, tVuelo & vuelo) {
	flujo >> vuelo.numero >> vuelo.terminal >> vuelo.puerta >> vuelo.estado;
	flujo.ignore(1);
	getline(flujo, vuelo.destino);
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tVuelo const & vuelo) {
	flujo << vuelo.numero << ' ' << vuelo.terminal << ' ' << vuelo.puerta << ' ' << vuelo.estado << ' ' << vuelo.destino;
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
		std::cin>>opt;
	}
	return opt;
}
bool cargar(tLista & lista) {
	std::ifstream entrada;
	entrada.open("salidas.txt");
	if (!entrada.is_open()) return false;

	tVuelo vuelo; int i = 0;
	entrada >> vuelo;
	while (vuelo.numero != "XXX" && i < N) {
		lista[i] = vuelo;
		++i;
		entrada >> vuelo;
	}
	entrada.close();
	if (i != N) return false;
	else return true;
}

bool guardar(tLista const & lista) {
	std::ofstream salida;
	salida.open("pendientes.txt");
	if (!salida.is_open()) return false;

	for (int i = 0; i < N; ++i) {
		if (lista[i].estado == RETRASADO || lista[i].estado == SUSPENDIDO) salida << lista[i]<<'\n';
	}
	salida.close();
	return true;
}

int buscarVuelo(tLista const & lista, std::string const & numero) {
	int posicion = -1; bool encontrado = false;

	for (int i = 0; !encontrado && i < N; ++i) {
		if (lista[i].numero == numero) {
			posicion = i;
			encontrado = true;
		}
	}
	return posicion;
}

void mostrarVuelo(tLista const & lista, std::string const & numero) {
	int posicion = buscarVuelo(lista, numero);

	if (posicion == -1) std::cout << "No existe el vuelo\n\n";
	else {
		std::cout << "\nNumero: " << lista[posicion].numero<<'\n';
		std::cout << "Destino: " << lista[posicion].destino<<'\n';
		std::cout << "Terminal: " << lista[posicion].terminal<<'\n';
		std::cout << "Puerta: " << lista[posicion].puerta<<'\n';
		switch (lista[posicion].estado) {
		case EMBARCANDO: std::cout << "Estado: Embarcando\n\n"; break;
		case OPERADO: std::cout << "Estado: Operado\n\n"; break;
		case RETRASADO: std::cout << "Estado: Retrasado\n\n"; break;
		case SUSPENDIDO: std::cout << "Estado: Suspendido\n"; break;
		}
	}
}

void actualizarVuelo(tLista & lista, int posicion, tEstado estado) {
	lista[posicion].estado = estado;
}

int main() {
	tLista lista(N);

	bool OK = cargar(lista);
	if (!OK) std::cout << "No se ha podido cargar la informacion del archivo salidas.txt\n\n";

	else {
		std::string pregunta = "\nMENU\n\n1.Obtener informacion de un vuelo\n2.Actualizar el estado de un vuelo\n3.Salir\n\nIntroduzca una opcion[1-3]: ";
		std::string mensajeError = "La opcion introducida no es valida\n\n";
		bool menu = true;
		while (menu) {
			switch (leeOpcion(pregunta, mensajeError, 1, 3)) {
			case 1: {
				std::string numero="";
				std::cout << "Introduzca un numero de vuelo: ";
				std::cin >> numero;
				mostrarVuelo(lista, numero);
				break;
			}
			case 2: {
				std::string numero = "";
				std::cout << "Introduzca un numero de vuelo: ";
				std::cin >> numero;

				int posicion= buscarVuelo(lista, numero);
				while (posicion == -1) {
					std::cout << "No existe el vuelo\n";
					std::cout << "Introduzca un numero de vuelo: ";
					std::cin >> numero;
					posicion = buscarVuelo(lista, numero);
				}
				tEstado estado;
				std::cout << "Introduzca el nuevo estado: ";
				std::cin >> estado;

				actualizarVuelo(lista, posicion, estado);
				break;
			}
			case 3: menu = false;
			}
		}
	}
	OK = guardar(lista);
	if (!OK)std::cout << "No se ha podido guardar la informacion en el archivo pendientes.txt\n\n";

	system("PAUSE");
	return 0;
}