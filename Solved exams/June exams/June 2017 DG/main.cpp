//Marcos Herrero

#include "ListaLonja.h"
#include "ListaCompradores.h"
#include "checkML.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	tListaLonja listaLonja;
	bool OK = cargar(listaLonja);
	if (!OK) std::cout << "No se ha podido cargar la lista de lotes\n\n";

	else {
		tListaComprador listaComprador;
		inicializar(listaComprador);

		long long int num; float precio; int pos = 0;
		for (int i = 0; i < listaLonja.cont; ++i) {
			mostrarLote(*listaLonja.v[i]);
			std::cout << "Introduzca el numero de comprador y el precio de compra:\n";
			std::cin >> num >> precio;
			listaLonja.v[i]->idcomprador = num;
			listaLonja.v[i]->precio = precio;

			if (buscar(listaComprador, num, pos)) {
				listaComprador.punt[pos].importe += precio;
			}
			else {
				tComprador comprador{ num, precio };
				insertar(listaComprador, comprador);
			}
		}

		mostrar(listaComprador);
		mostrar(listaLonja);
		liberar(listaLonja);
		liberar(listaComprador);
	}

	system("PAUSE");
	return 0;
}