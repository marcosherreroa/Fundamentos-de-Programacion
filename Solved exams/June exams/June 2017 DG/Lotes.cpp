//Marcos Herrero

#include "Lotes.h"
#include "checkML.h"

bool operator<(tLotes const & lote1, tLotes const & lote2){
	if (lote1.tipo < lote2.tipo) return true;
	else if (lote1.tipo == lote2.tipo && lote1.id < lote2.id) return true;
	else return false;
}

bool operator==(tLotes const & lote1, tLotes const & lote2){
	return lote1.id == lote2.id;
}

std::istream &operator>>(std::istream & flujo, tLotes & lote) {
	flujo >> lote.id >> lote.tipo >> lote.peso >> lote.precio;
	return flujo;
}

void mostrarLote(tLotes const & lote){
	std::cout << "Lote: " << std::setw(10) << lote.id << std::setw(10)<<' '<<"Peso del lote: " << std::setprecision(2) << std::fixed << lote.peso
		<< "\nTipo: " << std::setw(10) << lote.tipo<< std::setw(10)<<' '<< "Precio de salida: " << std::setprecision(2)<<std::fixed<<lote.precio<<'\n';
}

void mostrarPrecio(tLotes const & lote){
	std::cout << "Lote: " << std::setw(10) << lote.id << std::setw(10) << ' ' << "Comprador: " << lote.idcomprador
		<< "\nTipo: " << std::setw(10) << lote.tipo << std::setw(10) << ' ' << "Precio de compra: " << std::setprecision(2)<<std::fixed<<lote.precio << '\n';
}

void modificarLote(tLotes & lote, long long int idcomprador, float precio){
	lote.idcomprador = idcomprador;
	lote.precio = precio;
}





