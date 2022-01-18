//Marcos Herrero

#include "ListaCompradores.h"
#include "checkML.h"

std::ostream &operator<<(std::ostream & flujo, tComprador const & comprador) {
	flujo << "Comprador: "<<std::setw(10) << comprador.num <<std::setw(10)<<' '<< "Total: "<< comprador.importe;
	return flujo;
}

void inicializar(tListaComprador & lista) {
	lista.punt = new tComprador[CAPINICIAL];
	lista.capacidad = CAPINICIAL;
	lista.cont = 0;
}

void redimensionar(tListaComprador & lista) {
	lista.capacidad *= 2;
	tComprador* aux = lista.punt;
	lista.punt = new tComprador[lista.capacidad];

	for (int i = 0; i < lista.cont; ++i) lista.punt[i] = aux[i];
	delete[] aux;
}

void insertar(tListaComprador & lista, tComprador const & insertado) {
	int pos = 0;
	if (!buscar(lista, insertado.num, pos)) {
		if (lista.cont == lista.capacidad) redimensionar(lista);
		lista.punt[lista.cont] = insertado;
		++lista.cont;
	}
}

bool buscar(tListaComprador const & lista, int num, int & pos) {
	bool encontrado = false;
	for (int i = 0; !encontrado && i < lista.cont; ++i) {
		if (lista.punt[i].num == num) {
			encontrado = true;
			pos = i;
		}
	}

	return encontrado;
}

void mostrar(tListaComprador const & lista) {
	if (lista.cont == 0)std::cout << "No hay compradores en la lista\n\n";

	else for (int i = 0; i < lista.cont; ++i) std::cout << lista.punt[i]<<'\n';
}

void liberar(tListaComprador & lista) {
	delete[] lista.punt;
	lista.cont = 0;
	lista.capacidad = 0;
}