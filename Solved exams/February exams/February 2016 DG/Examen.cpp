#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

const int NUM_INTERVALOS = 5;
enum tTipo{PARTICULAR, PIME, INDUSTRIA};

struct tCliente{
	std::string identificador;
	float consumo;
	tTipo tipo;
};

struct tTabla {
	std::vector<int> intervalos;
	std::vector<float> frecuencias;
};



std::istream & operator>>(std::istream & flujo, tTipo & tipo) {
	int num = 0;
	flujo >> num;
	tipo = tTipo(num);

	return flujo;
}

bool cargarIntervalos(tTabla & tabla){
	std::ifstream archivoIntervalos; bool OK = true;

	archivoIntervalos.open("intervalos.txt");
	if (!archivoIntervalos.is_open()) OK = false;
	else{
		int intervalo = 0, i = 0;
		
		archivoIntervalos >> intervalo;
		if (intervalo != -1) {
			tabla.intervalos[0] = intervalo;
			archivoIntervalos >> intervalo;
			++i;

			while (OK) {
					tabla.intervalos[i] = intervalo;
					++i;
					archivoIntervalos >> intervalo;
					if (intervalo <= tabla.intervalos[i - 1]) OK = false;
			}
		}
		if (i != NUM_INTERVALOS)OK = false;
		archivoIntervalos.close();
	}
	return OK;
}

void mostrarTabla(tTabla const & tabla){
	std::cout << "Tabla de frecuencias por consumo de PIMES:\n";
	std::cout<<"De 0 a "<< tabla.intervalos[0]<<std::left<<std::setw(10)<<':'<<std::right<<std::setw(10)<< tabla.frecuencias[0]<<'\n';

	for (int i = 1; i < NUM_INTERVALOS; ++i){
		std::cout <<std::left<<"De " << tabla.intervalos[i - 1] << " a " << tabla.intervalos[i] << ':'<< std::right<<std::setw(10)
			<<tabla.frecuencias[i]<<'\n';
	}
}

bool buscarIntervalo(tTabla const & tabla, tCliente const & cliente, int & posicion){
	bool encontrado = false;

	for (int i = 0; !encontrado && i < NUM_INTERVALOS; ++i) {
		if (cliente.consumo<= tabla.intervalos[i]) {
			posicion = i;
			encontrado = true;
		}
	}
	return encontrado;
}

void frecuenciasConsumo(tTabla & tabla){
	std::ifstream archivoConsumo; tCliente cliente; int posicion = 0; bool encontrado = false;
	archivoConsumo.open("consumo.txt");

	getline(archivoConsumo, cliente.identificador);
	while (cliente.identificador != "XXX") {
		archivoConsumo >> cliente.consumo >> cliente.tipo;

		if (cliente.tipo == PIME) {
			encontrado= buscarIntervalo(tabla, cliente, posicion);
			if (encontrado) ++tabla.frecuencias[posicion];
			}

		archivoConsumo.ignore(2,'\n');
		getline(archivoConsumo, cliente.identificador);
		}

	archivoConsumo.close();
	}

int main() {
	tTabla tabla{ std::vector<int>(NUM_INTERVALOS),std::vector<float>(NUM_INTERVALOS) };
	bool OK = cargarIntervalos(tabla);
	if (OK) {
		frecuenciasConsumo(tabla);
		mostrarTabla(tabla);
	}
	system("PAUSE");
	return 0;
}