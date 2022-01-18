//Marcos Herrero

#include "Prenda.h"

std::istream &operator>>(std::istream & flujo, tPrenda & prenda){
	flujo >> prenda.id;
	flujo.ignore(1);
	getline(flujo, prenda.tipo);
	flujo >> prenda.nunids >> prenda.costFab >> prenda.precioVent;
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tPrenda const & prenda){
	flujo << std::left << std::setw(20) << prenda.id << std::setw(20)<< prenda.tipo << std::right<< std::setw(10) << prenda.nunids << " unidades\n"
		<< "Coste: " << std::setprecision(2) << std::fixed<< prenda.costFab << std::setw(20) << "Precio de venta: " << std::setprecision(2) << std::fixed << prenda.precioVent;
	return flujo;
}

std::string tipoPrenda(tPrenda const & prenda){
	return prenda.tipo;
}

float precioPrenda(tPrenda const & prenda){
	return prenda.precioVent;
}

std::string identificador(tPrenda const & prenda){
	return prenda.id;
}

float margen(tPrenda const & prenda){
	return prenda.precioVent - prenda.costFab;
}


