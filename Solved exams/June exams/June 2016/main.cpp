//Marcos Herrero

#include "ListaReproduccion.h"
#include "checkML.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));

	tListaTemas lmaestra;
	bool OK= cargar(lmaestra);
	if (!OK) std::cout << "No se ha podido cargar la lista\n\n";

	else {
		std::string nombre; int ntemas;
		
		std::cout << "Nombre: ";
		getline(std::cin, nombre);
		std::cout << "Numero de temas: ";
		std::cin >> ntemas;

		tListaReproduccion lista = nueva(nombre, ntemas);
		for (int i = 0; i < ntemas; ++i) {
			tElemento elemento;
			elemento.valoracion = rand() % 11;
			elemento.punt = lmaestra.v[rand() % lmaestra.cont];

			bool encontrado = buscar(lista, elemento.punt->titulo, 0);
			while (encontrado) {
				elemento.punt = lmaestra.v[rand() % lmaestra.cont];
				encontrado = buscar(lista, elemento.punt->titulo, 0);
			}
			
			insertar(lista, elemento);
		}

		mostrar(lista);
		
		std::cout << "Cambio de orden: ultimo al primero\n\n";
		modificarOrden(lista, lista.cont - 1, 0);
		mostrar(lista);

		std::cout << "Cambio de orden: segundo al ultimo\n\n";
		modificarOrden(lista, 1, lista.cont - 1);
		mostrar(lista);

		std::cout << "Cambio de orden: segundo al cuarto\n\n";
		modificarOrden(lista, 1, 3);
		mostrar(lista);

		destruir(lista);
		destruir(lmaestra);
	}

	system("PAUSE");
	return 0;
}