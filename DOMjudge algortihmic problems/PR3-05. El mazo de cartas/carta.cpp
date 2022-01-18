#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include <algorithm>
#include <utility>


#include "carta.h"

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
		flujo << mazo.baraja[(mazo.inicio + i) % mazo.baraja.size()] << ' ';
	}
	return flujo;
}

void crearMazo(tMazo & mazo, int nA, int nGI, int nGD, int nL) {

	for (int i = 0; i < nA; ++i) mazo.baraja.push_back(AVANZAR);
	for (int i = 0; i < nGI; ++i) mazo.baraja.push_back(GIROIZQUIERDA);
	for (int i = 0; i < nGD; ++i) mazo.baraja.push_back(GIRODERECHA);
	for (int i = 0; i < nL; ++i) mazo.baraja.push_back(LASER);

	mazo.ncartas = nA + nGI + nGD + nL;
	mazo.inicio = 0;
	mazo.fin = 0;

}

bool cogerCarta(tMazo &  mazo, tCarta & carta) {
	if (mazo.ncartas == 0) return false;

	carta = mazo.baraja[mazo.inicio];
	--mazo.ncartas;
	++mazo.inicio;
	mazo.inicio %= mazo.baraja.size();

	return true;
}

void devolverCarta(tMazo & mazo, tVCartas & vcartas) {

	for (int i = 0; i < vcartas.size(); ++i) {
		mazo.baraja[(mazo.fin + i) % mazo.baraja.size()] = vcartas[i];
	}

	mazo.ncartas += vcartas.size();
	mazo.fin += vcartas.size();
	mazo.fin %= mazo.baraja.size();
	vcartas.clear();
}



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int cartasAvanza; int cartasGI; int cartasGD; int cartasPL;
    std::cin >> cartasAvanza >> cartasGI >> cartasGD >> cartasPL;
    if (!std::cin) return false;
	tMazo mazo;
	crearMazo(mazo, cartasAvanza, cartasGI, cartasGD, cartasPL);
    int numMovimientos;
    std::cin >> numMovimientos;
    tVCartas v;
    for (int i = 0; i < numMovimientos; ++i) {
        int tipoMov;
        std::cin >> tipoMov;
        if (tipoMov == 1) {
            tCarta carta;
            bool ok = cogerCarta(mazo, carta);
            if (ok) v.push_back(carta);
        }
        else devolverCarta(mazo, v);
    }
    
    std::cout << mazo<<'\n';
    
    return true;
    
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());
    ;
    

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}
