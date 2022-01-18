//Marcos Herrero

#include "Contacto.h"
#include "checkML.h"

std::istream &operator>>(std::istream & flujo, tContacto & contacto) {
	getline(flujo, contacto.id);
	getline(flujo, contacto.nombre);
	getline(flujo, contacto.email);
	getline(flujo, contacto.telef);
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tContacto const & contacto) {
	flujo << std::setfill(' ')<< std::setw(10)<< "Contacto: " << contacto.id << " - " << contacto.nombre<<'\n';
	flujo << std::setw(10) << "email: " << contacto.email << " - " << contacto.telef << '\n';
	return flujo;
}
