//Marcos Herrero

#include "GrupoChat.h"
#include "checkML.h"

bool operator<(tElemento const & el1, tElemento const & el2) {
	return el1.punt->id < el2.punt->id;
}

tGrupoChat nuevo(std::string const & nombre, int dim) {
	tGrupoChat grupo;
	return { new tElemento[dim], 0, dim, nombre };
}

void destruir(tGrupoChat & grupo){
	delete[] grupo.v;
	grupo.cont = 0;
	grupo.capacidad = 0;
	grupo.nombre = "";
}

bool busqbinrecurs(tGrupoChat const & grupo, int ini, int fin, std::string const & idbuscado, int & pos) {
	if (ini == fin) {
		pos = ini;
		return false;
	}

	else {
		int mitad = (ini + fin - 1) / 2;
		if (idbuscado < grupo.v[mitad].punt->id) return busqbinrecurs(grupo, ini, mitad, idbuscado, pos);
		else if (grupo.v[mitad].punt->id < idbuscado) return busqbinrecurs(grupo, mitad + 1, fin, idbuscado, pos);
		else {
			pos = mitad;
			return true;
		}
	}
}

bool buscar(tGrupoChat const & grupo, std::string const & idbuscado, int & pos) {

	return busqbinrecurs(grupo, 0, grupo.cont, idbuscado, pos);
}

bool insertar(tGrupoChat & grupo, tElemento const elemento) {
	int pos = 0;
	if (buscar(grupo, elemento.punt->id, pos)) return false;
	else {
		for (int i = grupo.cont; i > pos; --i) grupo.v[i] = grupo.v[i - 1];
		grupo.v[pos] = elemento;
		++grupo.cont;
		return true;
	}
}

void mostrar(tGrupoChat const & grupo) {
	std::cout << std::setfill('-') << std::setw(30) << '-'<<'\n';
	std::cout << "Grupo de chat: " << grupo.nombre<<'\n';
	std::cout << std::setw(30) << '-' << '\n';;

	int mensajestot = 0;
	for (int i = 0; i < grupo.cont; ++i) {
		std::cout << *grupo.v[i].punt;
		std::cout << "Numero de mensajes: " << grupo.v[i].nmensajes<<'\n';
		mensajestot += grupo.v[i].nmensajes;
	}

	std::cout << "TOTAL MENSAJES: " << mensajestot << '\n';
}

tGrupoChat combinar(tGrupoChat const & A, tGrupoChat const & B) {
	tGrupoChat AyB = nuevo(A.nombre + " y " + B.nombre, A.capacidad + B.capacidad);

	int i = 0, j = 0;
	while (i < A.cont && j < B.cont) {
		if (A.v[i] < B.v[j]) {
			AyB.v[AyB.cont] = A.v[i];
			++i;
			++AyB.cont;
		}
		else if (B.v[j] < A.v[i]) {
			AyB.v[AyB.cont] = B.v[j];
			++j;
			++AyB.cont;
		}
		else {
			AyB.v[AyB.cont].punt = A.v[i].punt;
			AyB.v[AyB.cont].nmensajes = A.v[i].nmensajes + B.v[j].nmensajes;
			++i;
			++j;
			++AyB.cont;
		}
	}

	while (i < A.cont) {
		AyB.v[AyB.cont] = A.v[i];
		++i;
		++AyB.cont;
	}

	while (j < B.cont) {
		AyB.v[AyB.cont] = B.v[j];
		++j;
		++AyB.cont;
	}

	return AyB;
}