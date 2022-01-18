//Marcos Herrero

#ifndef CONTACTO_H
#define CONTACTO_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

struct tContacto {
	std::string id;
	std::string nombre;
	std::string email;
	std::string telef;
};

std::istream &operator>>(std::istream & flujo, tContacto & contacto);
std::ostream &operator<<(std::ostream & flujo, tContacto const & contacto);

#endif
