//Marcos Herrero

#include "carta.h"
#include "checkML.h"

std::ostream &operator<<(std::ostream & flujo, tCarta carta) {
	switch (carta) {
	case AVANZAR: flujo << 'A'; break;
	case GIROIZQUIERDA: flujo << "GI"; break;
	case GIRODERECHA: flujo << "GD"; break;
	case LASER: flujo << 'L'; break;
	}
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tMazo const & mazo) {
	for (int i = 0; i < mazo.ncartas; ++i) {
		flujo << *mazo.baraja[(mazo.inicio + i) % CARTASMAZO_INICIAL] << ' ';
	}
	return flujo;
}

void liberarMazo(tMazo & mazo){ // liberar la memoria din?mica del mazo
	for (int i = 0; i < CARTASMAZO_INICIAL; ++i){
		delete mazo.baraja[i];
	}
}
void crearMazoAleatorio(tMazo & mazo, int nA, int nGI, int nGD, int nL) {
	
	for (int i = 0; i < nA; ++i){
		mazo.baraja[i] = new tCarta;
		*mazo.baraja[i] = AVANZAR;
	}

	for (int i = nA; i < nA + nGI; ++i){
		mazo.baraja[i] = new tCarta;
		*mazo.baraja[i] = GIROIZQUIERDA;
	}

	for (int i = nA + nGI; i < nA + nGI + nGD; ++i){
		mazo.baraja[i] = new tCarta;
		*mazo.baraja[i] = GIRODERECHA;
	}

	for (int i = nA + nGI + nGD; i < nA + nGI + nGD + nL; ++i) {
		mazo.baraja[i] = new tCarta;
		*mazo.baraja[i] = LASER;
	}

	mazo.ncartas = nA + nGI + nGD + nL;
	mazo.inicio = 0;
	mazo.fin = 0;

	std::random_shuffle(mazo.baraja, mazo.baraja + mazo.ncartas);
}

bool cogerCarta(tMazo &  mazo, tCarta & carta) {
	if (mazo.ncartas == 0) return false;

	carta = *mazo.baraja[mazo.inicio];
	--mazo.ncartas;
	++mazo.inicio;
	mazo.inicio %= CARTASMAZO_INICIAL;

	return true;
}

void devolverCarta(tMazo & mazo, tCarta carta){
	*mazo.baraja[mazo.fin]= carta;
	++mazo.ncartas;
	++mazo.fin;
	mazo.fin %= CARTASMAZO_INICIAL;
}

void devolverVector(tMazo & mazo, tVCartas & vcartas) {
	std::random_shuffle(vcartas.begin(), vcartas.end()); // se baraja el vector para que las cartas vuelvan al mazo desordenadas
	for (int i = 0; i < vcartas.size(); ++i) devolverCarta(mazo, vcartas[i]);
	
	vcartas.clear();   // el vector queda vacio
}


