#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int MAX_VIAJES = 10;
const int NUM_PREFERENCIAS = 3;

enum tCategoria{MOCHILERO, TURISTA, LUJO};

struct tViaje{
	std::string destino;
	int ndias;
	int nplazas;
	tCategoria categoria;
};

using tCatalogo = std::vector<tViaje>;
using tPreferencias = std::vector<std::string>;

std::istream & operator>>(std::istream & flujo, tCategoria & categoria){
	int num = 0;
	flujo >> num;
	categoria = tCategoria(num);
	return flujo;
}

std::istream & operator>>(std::istream & flujo, tViaje & viaje){
	flujo >> viaje.destino >> viaje.ndias >> viaje.nplazas >> viaje.categoria;
	return flujo;
}

std::ostream & operator<<(std::ostream & flujo, tViaje const & viaje){
	flujo << viaje.destino << ' ' << viaje.ndias << ' ' << viaje.nplazas << ' ' << viaje.categoria;
	return flujo;
}

bool cargarCatalogo(tCatalogo & catalogo){
	std::ifstream entrada;
	entrada.open("catalogoViajes.txt");
	if (!entrada.is_open()) return false;

	tViaje viaje;
	entrada >> viaje;
	for (int i = 0; viaje.destino !="XXX" && i < MAX_VIAJES; ++i){
		catalogo.push_back(viaje);
		entrada >> viaje;
	}

	entrada.close();
	return true;
}

void mostrarViajesEnCategoria(tCatalogo const & catalogo, tCategoria categoria){
	std::cout << "\nViajes en la categoria:\n\n";

	for (int i = 0; i < catalogo.size(); ++i){ 
		if (catalogo[i].categoria == categoria) std::cout << catalogo[i].destino << ", " << catalogo[i].ndias << " dia(s), " 
			<< catalogo[i].nplazas << " plaza(s) disponible(s)\n";
	}
	std::cout << '\n';
}

bool guardarCatalogo(tCatalogo const & catalogo){
	std::ofstream salida;
	salida.open("catalogoViajes.txt");
	if (!salida.is_open())return false;

	for (int i = 0; i < catalogo.size(); ++i)salida << catalogo[i] << '\n';
	salida << "XXX";

	salida.close();
	return true;
}

void leerPreferencias(tPreferencias & tabla){
	for (int i = 0; i < NUM_PREFERENCIAS; ++i) {
		std::cout << "Destino " << i+1 << ": ";
		std::cin >> tabla[i];
	}
}

int buscarDestino(tCatalogo const & catalogo, std::string const & destino, tCategoria categoria) {
	int posicion = -1; bool encontrado = false;
	for (int i = 0; posicion==-1 && i < catalogo.size(); ++i) {
		if (catalogo[i].destino == destino && catalogo[i].categoria == categoria && catalogo[i].nplazas > 0) posicion = i;
	}
	return posicion;
}

bool hacerReserva(tCatalogo & catalogo, tPreferencias const & tabla, tCategoria categoria, std::string & destinoReservado) {
	int posicion; bool encontrado = false;
	for (int i = 0; !encontrado && i < NUM_PREFERENCIAS; ++i) {
		posicion = buscarDestino(catalogo, tabla[i], categoria);

		if (posicion != -1) {
			encontrado = true;
			destinoReservado = catalogo[posicion].destino;
			--catalogo[posicion].nplazas;
		}
	}
	return encontrado;
}

int main() {
	tCatalogo catalogo;

	bool OK = cargarCatalogo(catalogo);
	if (!OK) std::cout << "No existe el archivo\n";
	else {
		tCategoria categoria;
		std::cout << "Introduzca una categoria[0 = MOCHILERO, 1 = TURISTA, 2 = LUJO]: ";
		std::cin >> categoria;
		mostrarViajesEnCategoria(catalogo, categoria);

		tPreferencias tabla(NUM_PREFERENCIAS);
		std::cout << "Introduzca sus " << NUM_PREFERENCIAS << " preferencias: \n";
		leerPreferencias(tabla);

		std::string destinoReservado = ""; bool encontrado = false;
		encontrado= hacerReserva(catalogo, tabla, categoria, destinoReservado);
		if(encontrado) std::cout << "\nReservado viaje a " << destinoReservado<<'\n';
		else std::cout << "\nNo hay disponibilidad con esas preferencias\n";

		OK = guardarCatalogo(catalogo);
		if (!OK)std::cout << "\nNo existe el archivo\n";
	}
	system("PAUSE");
	return 0;
}