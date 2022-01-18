

#include <iostream>
#include <string>


// Escribir aqui la funcion leeOpcion.

int leeOpcion(std::string pregunta, std::string mensajeError, int valMin, int valMax){
	int opt = 0;
	std::cout << pregunta;
	std::cin >> opt;
	while (opt < valMin || opt> valMax){
		std::cout << mensajeError;
		std::cout << pregunta;
		std::cin >> opt;
	}
	return opt;
}

void resuelveCaso() {
	int a, b;
	std::cin >> a >> b;
	int res = leeOpcion("Introduce la opcion:", "Opcion incorrecta\n", a, b);
	std::cout << "La respuesta fue " << res << '\n';
}

int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	return 0;
}

