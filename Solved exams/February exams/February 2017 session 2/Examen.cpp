#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

const int N_ACC = 10;

enum tOperacion{ COMPRA, VENTA, ACTUALIZACION, FIN, INCORRECTO };

struct tAccion{
	std::string nombre;
	float precioAccion;
	int numAcciones;
};

tOperacion char2operacion(char caracter){
	switch (caracter){
	case 'C': return COMPRA;
	case 'V': return VENTA;
	case 'A': return ACTUALIZACION;
	case 'X': return FIN;
	}
	return INCORRECTO;
}

char operacion2char(tOperacion operacion){
	switch (operacion){
	case COMPRA: return 'C';
	case VENTA: return 'V';
	case ACTUALIZACION: return 'A';
	}
}

std::istream  & operator>>(std::istream & flujo, tAccion & accion){
	flujo >> accion.nombre >> accion.precioAccion >> accion.numAcciones;
	return flujo;
}

std::ostream & operator<<(std::ostream & flujo, tAccion const & accion){
	flujo << std::left << std::setw(10) << accion.nombre << std::right << std::setw(10) << accion.numAcciones << std::setw(10) << accion.precioAccion;
	return flujo;
}

std::istream & operator>>(std::istream & flujo, tOperacion & operacion){
	char caracter = ' ';

	flujo >> caracter;
	operacion = char2operacion(caracter);

	return flujo;
}

std::ostream & operator<<(std::ostream & flujo, tOperacion & operacion){
	flujo << operacion2char(operacion);  
	return flujo;
}

float valortotal(std::vector<tAccion> const & cartera){
	float sol = 0;
	for (int i = 0; i < N_ACC; ++i){
		sol += cartera[i].numAcciones* cartera[i].precioAccion;
	}
	return sol;
}

int encontrarEmpresa(std::vector<tAccion> const & cartera, std::string const & nombre){
	int posicion = -1;
	for (int i = 0; posicion==-1 && i < N_ACC; ++i){
		if (cartera[i].nombre == nombre) posicion = i;
	}
	return posicion;
}
bool cargar(std::vector<tAccion> & cartera){
	std::ifstream entrada;
	int numempresas = 0;
	entrada.open("cartera.txt");
	if (!entrada.is_open()) return false;

	tAccion accion;  int numacciones = 0;
	entrada >> accion;
	
	while (numacciones < N_ACC && accion.nombre != "#" ) {
		cartera[numacciones] = accion;
		++numacciones;
		entrada >> accion;
	}
	entrada.close();

	if (numacciones != N_ACC) return false;
	else return true;
}

void mostrar(std::vector<tAccion> const & cartera){
	std::cout<<'\n';
	for (int i = 0; i < N_ACC; ++i){
		std::cout << cartera[i]<<'\n';
	}
	std::cout << "Valor total: " << valortotal(cartera)<<"\n\n";
}

bool procesar(std::vector<tAccion> & cartera){
	std::ifstream entrada;
	entrada.open("semana.txt");
	if (!entrada.is_open())return false;

	tOperacion operacion; std::string nombre = ""; float numero = 0.0;  int posicion = 0;

	entrada >> operacion >> nombre >> numero;
	while (operacion!=FIN) {

		posicion = encontrarEmpresa(cartera, nombre);
		if (operacion == INCORRECTO) std::cout << operacion << ' ' << nombre << ' ' << numero << " Error: Operacion no existe\n";
		else if (posicion == -1) std::cout << operacion << ' ' << nombre << ' ' << numero << " Error: Empresa no existe\n";
		else {
			switch (operacion) {
			case COMPRA: {
				cartera[posicion].numAcciones += numero;
				std::cout << operacion << ' ' << nombre << ' ' << numero << " OK\n";
				break;
			}
			case VENTA: {
				if (cartera[posicion].numAcciones < numero)std::cout << operacion << ' ' << nombre << ' ' << numero << " Error: No hay suficientes acciones\n";
				else {
					cartera[posicion].numAcciones -= numero;
					std::cout << operacion << ' ' << nombre << ' ' << numero << " OK\n";
				}
				break;
			}
			case ACTUALIZACION: {
				cartera[posicion].precioAccion = numero;
				std::cout << operacion << ' ' << nombre << ' ' << numero << " OK\n";
				break;
			}
		}
	}
		entrada >> operacion >> nombre >> numero;
}
	entrada.close();
	return true;
}

bool guardar(std::vector<tAccion> const & cartera) {
	std::ofstream salida;
	salida.open("cartera.txt");
	if (!salida.is_open()) return false;

	for (int i = 0; i < N_ACC; ++i) {
		salida << cartera[i].nombre << ' ' << cartera[i].precioAccion << ' ' << cartera[i].numAcciones << '\n';
	}
	salida << "#";
	salida.close();
	return true;
}

int main() {
	std::vector<tAccion> cartera(N_ACC); bool OK = true;

	OK = cargar(cartera);
	if (!OK)std::cout << "No se ha podido cargar";
	else mostrar(cartera);

	OK = procesar(cartera);
	if (!OK)std::cout << "No se ha podido procesar";

	mostrar(cartera);
	OK = guardar(cartera);
	if (!OK)std::cout << "No se ha podido guardar la cartera";

	system("PAUSE");
	return 0;
}