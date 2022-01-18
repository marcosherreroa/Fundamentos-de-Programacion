#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

const int NP = 5;

enum tClase{PAPELERIA, ALIMENTACION, LIMPIEZA, INFORMATICA, NUMCLASES};

struct tProv{
	std::string CIF;
	tClase clase;
	int npedidos;
	float neuros;
};

using vProv = std::vector<tProv>;
using vClases = std::vector<float>;

std::istream & operator>>(std::istream & flujo, tClase & clase){
	int num = 0;
	flujo >> num;
	clase = tClase(num);
	return flujo;
}

std::istream & operator>>(std::istream & flujo, tProv & proveedor){
	flujo >> proveedor.CIF >> proveedor.clase >> proveedor.npedidos >> proveedor.neuros;
	return flujo;
}

std::ostream & operator<<(std::ostream & flujo, tProv const & proveedor){
	flujo << proveedor.CIF << ' ' << proveedor.clase << ' ' << proveedor.npedidos << ' ' << proveedor.neuros;
	return flujo;
}

int leeOpcion(std::string const & pregunta, std::string const & mensajeError, int valmin, int valmax){
	int opt = 0;

	std::cout << pregunta;
	std::cin >> opt;
	while (valmin > opt || valmax < opt){
		std::cin.ignore(1000, '\n');
		std::cin.clear();
		std::cout << mensajeError << "\n\n";
		std::cout << pregunta << '\n';
		std::cin >> opt;
	}

	return opt;
}
bool cargar(vProv & proveedores){
	std::ifstream entrada;
	entrada.open("proveedores.txt");
	if (!entrada.is_open()) return false;

	tProv proveedor;
	entrada >> proveedor;
	int i = 0;
	while (proveedor.CIF!="X" && i < NP){
		proveedores[i] = proveedor;
		entrada >> proveedor;
		++i;
	}
	entrada.close();

	if (i < NP) return false;
	else return true;
}

bool guardar(vProv const & proveedores){
	std::ofstream salida;
	salida.open("proveedores.txt");
	if (!salida.is_open()) return false;

	for (int i = 0; i < NP; ++i) salida << proveedores[i] << '\n';
	salida << "X";

	salida.close();
	return true;
}

int buscarProveedor(vProv const & proveedores, std::string const & CIF){
	int posicion = -1; 

	for (int i = 0; posicion == -1 && i < NP; ++i){
		if (proveedores[i].CIF == CIF) posicion = i;
	}

	return posicion;
}

void nuevoPedido(vProv & proveedores, std::string const & CIF, float neuros){
	int posicion = 0;
	posicion= buscarProveedor(proveedores, CIF);

	if (posicion != -1){
		++proveedores[posicion].npedidos;
		proveedores[posicion].neuros += neuros;
	}
}

void mostrarXintervalo(vProv const & proveedores, int minimo, int maximo){
	for (int i = 0; i < NP; ++i){
		if (minimo <= proveedores[i].npedidos && proveedores[i].npedidos <= maximo) {
			switch (proveedores[i].clase){
			case PAPELERIA: std::cout << proveedores[i].CIF <<std::left<<std::setw(15)<< " Papeleria " << proveedores[i].npedidos << ' ' << proveedores[i].neuros<<'\n'; break;
			case ALIMENTACION: std::cout << proveedores[i].CIF <<std::left<<std::setw(15)<< " Alimentacion " << proveedores[i].npedidos << ' ' << proveedores[i].neuros<<'\n'; break;
			case LIMPIEZA: std::cout << proveedores[i].CIF <<std::left<<std::setw(15)<< " Limpieza " << proveedores[i].npedidos << ' ' << proveedores[i].neuros<<'\n'; break;
			case INFORMATICA: std::cout << proveedores[i].CIF <<std::left<<std::setw(15)<< " Informatica " << proveedores[i].npedidos << ' ' << proveedores[i].neuros<<'\n'; break;
			}
		}
	}
}

void totalesXclase(vProv const & proveedores, vClases & gastos){
	for (int i = 0; i < NP; ++i) gastos[proveedores[i].clase] += proveedores[i].neuros;
}

int main(){
	vProv proveedores(NP);   bool OK = true;

	OK=cargar(proveedores);
	if (!OK)std::cout << "No existe el archivo o hay menos de NP proveedores\n";
	else{
		std::string pregunta = "\nMENU\n\n1 - Nuevo pedido\n2 - Proveedores con numero de pedidos en un intervalo\n3 - Gastos por clase de proveedor\n\nIntroduzca una opcion[0-3]: ";
		std::string mensajeError = "La opcion introducida no es valida";

		bool menu = true;
		while (menu) {
			vClases gastos(NUMCLASES, 0.0);
			switch (leeOpcion(pregunta, mensajeError, 0, 3)) {
			case 1: {
				std::string CIF = "";

				std::cout << "Introduzca un CIF: ";
				std::cin >> CIF;
				if (buscarProveedor(proveedores, CIF) != -1) {
					float neuros = 0.0;

					std::cout << "Introduzca una cantidad de euros: ";
					std::cin >> neuros;
					nuevoPedido(proveedores, CIF, neuros);
				}
				else std::cout << "No se encuentra el CIF introducido\n";
				break;
			}
			case 2: {
				int minimo = 0, maximo = 0;

				std::cout << "Introduzca un minimo y un maximo:";
				std::cin >> minimo >> maximo;
				mostrarXintervalo(proveedores, minimo, maximo);
				break;
			}
			case 3: {
				totalesXclase(proveedores, gastos);
				for (int i = 0; i < NUMCLASES; ++i) {
					switch (i) {
					case PAPELERIA: std::cout << std::left << std::setw(15) << "Papeleria" << gastos[i] << " €\n"; break;
					case ALIMENTACION: std::cout << std::left << std::setw(15) << "Alimentacion" << gastos[i] << " €\n"; break;
					case LIMPIEZA: std::cout << std::left << std::setw(15) << "Limpieza" << gastos[i] << " €\n"; break;
					case INFORMATICA: std::cout << std::left << std::setw(15) << "Informatica" << gastos[i] << " €\n"; break;
					}
				}
				break;
			}
			case 0: menu = false;
			}
		}
		OK = guardar(proveedores);
		if (!OK) std::cout << "No existe el archivo\n";
	}

	system("PAUSE");
	return 0;
}