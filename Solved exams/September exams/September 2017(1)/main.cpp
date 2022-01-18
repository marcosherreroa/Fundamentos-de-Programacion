//Marcos Herrero

#include "ListaTPrenda.h"

int leeOpcion(std::string const & pregunta, std::string const & mensajeError, int min, int max) {
	std::cout << pregunta;
	int op;
	std::cin >> op;
	while (std::cin.fail() || op<min || op>max) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << mensajeError;
		std::cout << pregunta;
		std::cin >> op;
	}

	return op;
}

int main() {
	tListaInventario inventario;
	cargar(inventario);

	std::string pregunta = "\nMENU\n\n1. Visualizar inventario\n2. Eliminar una prenda del inventario\n3. Mostrar la prenda con mayor margen\n4. Mostrar las prendas de un tipo\n0. Salir\n\nIntroduce una opcion[0-4]: ";
	std::string mensajeError = "\nLa opcion introducida no es valida\n\n";
	bool menu = true;

	while (menu) {
		switch (leeOpcion(pregunta, mensajeError, 0, 4)) {
		case 1:mostrar(inventario); break;
		case 2: {
			tPrenda prenda;
			std::cout << "Introduce el codigo de la prenda a eliminar: ";
			std::cin >> prenda.id;
			eliminar(inventario, prenda);
			std::cout << "Prenda eliminada\n\n";
			break;
		}
		case 3: {
			if (inventario.cont == 0) std::cout << "No hay prendas en el inventario\n";
			else {
				std::cout << "La prenda de mayor margen de beneficio es:\n" << inventario.punt[mayorMargen(inventario)];
				break;
			}
		}
		case 4: {
			tListaTPrenda lista;  std::string tipo;
			std::cout << "Introduce el tipo a mostrar: ";
			std::cin >> tipo;
			bool OK= generarLista(lista, inventario, tipo);

			if (!OK) std::cout << "No se encuentran prendas del tipo indicado\n\n";
			else {
				ordenar(lista);
				mostrar(lista);
			}

			liberar(lista);
			break;
		}
		case 0: menu = false; break;
		}
	}

	liberar(inventario);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	system("PAUSE");
	return 0;
}