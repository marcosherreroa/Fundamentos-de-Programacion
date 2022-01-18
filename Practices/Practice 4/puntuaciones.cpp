//Marcos Herrero

#include "puntuaciones.h"
#include "checkML.h"

std::istream &operator>>(std::istream & flujo, tpuntosJugador & puntosJugador) {
	flujo >> puntosJugador.nombre >> puntosJugador.puntos;
	return flujo;
}

std::ostream &operator<<(std::ostream & flujo, tpuntosJugador const & puntosJugador) {
	flujo << puntosJugador.nombre <<' '<<puntosJugador.puntos;
	return flujo;
}

template<typename T>
void crearvDinam(vDinam<T> & v, int tamInicial){
	v.ptr = new T[tamInicial];
	v.cont = 0;
	v.capacidad = tamInicial;
}

template<typename T>
void redimensionar(vDinam<T> & v, int aum){
	v.capacidad += aum;
	T* aux = v.ptr;
	v.ptr = new T[v.capacidad];

	for (int i = 0; i < v.cont; ++i) v.ptr[i] = aux[i];
	delete[] aux;
}

void liberarPuntuaciones(tPuntuaciones & puntuaciones){
	for (int i = 0; i < puntuaciones.cont; ++i) delete puntuaciones.ptr[i];
	delete[] puntuaciones.ptr;
	puntuaciones.ptr = nullptr;
	puntuaciones.cont = 0;
	puntuaciones.capacidad = 0;
}

template <typename T, typename Comp>
void ordenarInsercion(std::vector<T> & v, Comp ord) {
	for (int i = 1; i < v.size(); ++i) {
		T elemento = v[i];
		int j = i;
		while (j > 0 && ord(elemento, v[j - 1])) {
			v[j] = v[j - 1];
			--j;
		}
		if(j!=i) v[j] = elemento;
	}
}

template<typename T, typename Comp>
bool buscarBinaria(vDinam<T> const & v, T buscado, int & pos, Comp ord) {
	int ini = 0, fin = v.cont, mitad;
	bool encontrado = false;

	while (!encontrado && ini < fin) {
		mitad = (ini + fin-1) / 2;
		if (ord(buscado, v.ptr[mitad])) fin = mitad;
		else if (ord(v.ptr[mitad], buscado)) ini = mitad + 1;
		else encontrado = true;
	}

	if (encontrado) pos = mitad;
	else pos = ini;
	return encontrado;
}

template<typename T, typename Comp>
bool insertarSinRep(vDinam<T> & v, T insertado, int aum, Comp ord) {
	int pos = 0;

	if (!buscarBinaria( v, insertado, pos, ord)) {
		if (v.cont == v.capacidad) redimensionar(v, aum);
		for (int i = v.cont; i > pos; --i) v.ptr[i] = v.ptr[i - 1];
		v.ptr[pos] = insertado;
		++v.cont;
		return true;
	}

	else return false;
}

bool cargarPuntuaciones(tPuntuaciones & puntuaciones) {
	crearvDinam(puntuaciones, TAM_INICIAL);
	std::ifstream entrada;

	entrada.open(FICHERO_PUNTUACIONES);
	if (!entrada.is_open()) return false;
	
	tpuntosJugador puntosJugador;
	entrada >> puntosJugador;    // se tiene que leer antes de comprobar para evitar incluir el EOF en el vector de puntuaciones
	while (!entrada.eof()) {     // para que el archivo no se salte el ultimo elemento, siempre habra una ultima linea en blanco en el fichero
		if (puntuaciones.cont == puntuaciones.capacidad) redimensionar(puntuaciones, AUM_REDIMENSION);
		puntuaciones.ptr[puntuaciones.cont]= new tpuntosJugador;
		*puntuaciones.ptr[puntuaciones.cont] = puntosJugador;
		++puntuaciones.cont;
		entrada >> puntosJugador;
	}

	entrada.close();
	return true;
}

bool guardarPuntuaciones(tPuntuaciones const & puntuaciones) {
	std::ofstream salida;

	salida.open(FICHERO_PUNTUACIONES);
	if (!salida.is_open()) return false;

	for (int i = 0; i < puntuaciones.cont; ++i) salida << *puntuaciones.ptr[i]<<'\n'; // despues del ultimo jugador, hay una linea en blanco
	                                                                               // esencial para que se pueda leer todo el fichero y
	salida.close();                                                                // no haya problemas con EOF
	return true;
}

void mostrarPuntuaciones(tPuntuaciones const & puntuaciones, tOrden comp) {
	system("cls");

	switch (comp) {
	case PORDEFECTO: {
		std::cout << "\nPUNTUACIONES\n\n";
		for (int i = 0; i < puntuaciones.cont; ++i) std::cout << i + 1 << ". " << *puntuaciones.ptr[i] << '\n';
		break;
	}
	case ALFAB: {
		std::vector<tpuntosJugador*> valfab(puntuaciones.cont);
		for (int i = 0; i < puntuaciones.cont; ++i) valfab[i] = puntuaciones.ptr[i];
		ordenarInsercion(valfab, Compalfab());
		std::cout << "\nPUNTUACIONES\n\n";

		for (int i = 0; i < puntuaciones.cont; ++i) std::cout << *valfab[i] << '\n';
		break;
	}
	}
	std::cout << '\n';
	system("PAUSE");
}

bool actualizarPuntuacion(tPuntuaciones & puntuaciones, std::string const & nombre, int nuevos) {
	bool encontrado = false; int pos = 0;

	for (int i = 0; !encontrado && i < puntuaciones.cont; ++i) {
		if (puntuaciones.ptr[i]->nombre == nombre) {
			encontrado = true;
			pos = i;
			puntuaciones.ptr[i]->puntos += nuevos;
		}
	}

	if (encontrado){
		tpuntosJugador* aux = puntuaciones.ptr[pos];
		while (pos < puntuaciones.cont - 1 && Comppordefecto()(puntuaciones.ptr[pos + 1],aux)) {
			puntuaciones.ptr[pos] = puntuaciones.ptr[pos + 1];
			++pos;
		}
		puntuaciones.ptr[pos] = aux;
	}

	else{
		tpuntosJugador* puntosJugador= new tpuntosJugador;
		puntosJugador->nombre = nombre;
		puntosJugador->puntos = nuevos;
		bool OK = insertarSinRep(puntuaciones, puntosJugador, AUM_REDIMENSION);
		if (!OK) {
			std::cout << "Error. No se ha podido insertar un jugador en la clasificacion\n\n";
			delete puntosJugador;
		}
	}

	return encontrado;
}