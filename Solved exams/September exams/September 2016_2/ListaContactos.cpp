//Marcos Herrero

#include "ListaContactos.h"
#include "checkML.h"

void crear(tListaContactos & lista) {
	lista.cont = 0;
}

void destruir(tListaContactos & lista) {
	for (int i = 0; i < lista.cont; ++i) delete lista.v[i];
	lista.cont = 0;
}

void cargar(tListaContactos & lista, std::istream & flujo) {
	crear(lista);

	int num;
	flujo >> num;
	flujo.ignore(1);
	
	for (int i = 0; i < num; ++i) {
		lista.v[i] = new tContacto;
		flujo >> *lista.v[i];
	}
	lista.cont = num;

}
