//Marcos Herrero

#ifndef PRENDA_H
#define PRENDA_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

struct tPrenda{
	std::string id;
	std::string tipo;
	long long int nunids;
	float costFab;
	float precioVent;
};

std::istream &operator>>(std::istream & flujo, tPrenda & prenda);
std::ostream &operator<<(std::ostream & flujo, tPrenda const & prenda);
std::string tipoPrenda(tPrenda const & prenda);
float precioPrenda(tPrenda const & prenda);
std::string identificador(tPrenda const & prenda);
float margen(tPrenda const & prenda);

struct Compmargen {
	bool operator()(tPrenda const & prenda1, tPrenda const & prenda2) {
		if (margen(prenda1) < margen(prenda2)) return true;
		else if (margen(prenda1) == margen(prenda2) && prenda1.id < prenda2.id) return true;
		else return false;
	}
};

struct Compprecio {
	bool operator()(tPrenda* prenda1, tPrenda* prenda2) {
		if (prenda1->precioVent < prenda2->precioVent) return true;
		else if (prenda1->precioVent == prenda2->precioVent && prenda1->id < prenda2->id) return true;
		else return false;
	}
};

#endif
