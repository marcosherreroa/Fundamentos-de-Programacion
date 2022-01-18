//Marcos Herrero

#include "Tema.h"
#include "checkML.h"

std::istream &operator>>(std::istream & flujo, tTema & tema) {
	getline(flujo, tema.titulo);
	getline(flujo, tema.interprete);
	flujo >> tema.segundos;
	flujo.ignore(1);
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tTema const & tema) {
	flujo << std::setw(10) << tema.titulo << std::setw(15) << tema.interprete << std::setw(7) << tema.segundos << " seg.";
	return flujo;
}
