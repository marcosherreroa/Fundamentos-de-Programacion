//Marcos Herrero

#ifndef TEMA_H
#define TEMA_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

struct tTema {
	std::string titulo;
	std::string interprete;
	int segundos;
};

std::istream &operator>>(std::istream & flujo, tTema & tema);
std::ostream &operator<<(std::ostream & flujo, tTema const & tema);

#endif


