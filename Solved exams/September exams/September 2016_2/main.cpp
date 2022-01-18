//Marcos Herrero

#include "GrupoChat.h"
#include "checkML.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(1);

	std::ifstream entrada;
	entrada.open("contactos.txt");
	if (!entrada.is_open()) std::cout << "No se encuentra el archivo\n";

	else {
		tListaContactos lista;
		cargar(lista, entrada);

		std::string nombre; int numContactos;
		std::cout << "Nombre del grupo: ";
		std::cin >> nombre;
		std::cout << "Numero de contactos: ";
		std::cin >> numContactos;

		tGrupoChat A = nuevo(nombre, numContactos);
		for (int i = 0; i < numContactos; ++i) {
			tElemento elemento;
			elemento.nmensajes = rand() % 100;

			elemento.punt= lista.v[rand() % lista.cont];
			bool OK = insertar(A , elemento);
			while (!OK) {
				elemento.punt = lista.v[rand() % lista.cont];
				OK = insertar(A, elemento);
			}
		}

		std::cout << "Nombre del grupo: ";
		std::cin >> nombre;
		std::cout << "Numero de contactos: ";
		std::cin >> numContactos;

		tGrupoChat B = nuevo(nombre, numContactos);
		for (int i = 0; i < numContactos; ++i) {
			tElemento elemento;
			elemento.nmensajes = rand() % 100;

			elemento.punt = lista.v[rand() % lista.cont];
			bool OK = insertar(B, elemento);
			while (!OK) {
				elemento.punt = lista.v[rand() % lista.cont];
				OK = insertar(B, elemento);
			}
		}

		tGrupoChat AyB = combinar(A, B);
		mostrar(A);
		mostrar(B);
		mostrar(AyB);

		destruir(A);
		destruir(B);
		destruir(AyB);
		destruir(lista);
	}

	system("PAUSE");
	return 0;
}