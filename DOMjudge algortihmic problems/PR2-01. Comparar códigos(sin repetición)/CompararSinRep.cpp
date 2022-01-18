// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

enum tColor { ROJO, AZUL, VERDE, AMARILLO, MARRON, BLANCO, INCORRECTO };
const int TAM_CODIGO = 4;
using tCodigo = std::vector<tColor>;

tColor char2color(char letra) {
	switch (toupper(letra)) {
	case 'R': return ROJO;
	case 'Z': return AZUL;
	case 'V': return VERDE;
	case 'A': return AMARILLO;
	case 'M': return MARRON;
	case 'B': return BLANCO;
	}
	return INCORRECTO;
}

// función que resuelve el problema
void compararCodigos(tCodigo const & codigo, tCodigo const & hipotesis, int & colocados, int & descolocados) {

	for (int i = 0; i < TAM_CODIGO; ++i) if (codigo[i] == hipotesis[i]) ++colocados;
	
	bool encontrado = false;
	for (int i = 0; i < TAM_CODIGO; ++i) {
		if (codigo[i]!=hipotesis[i]) {
			encontrado = false;
			for (int j = 0; j < TAM_CODIGO && !encontrado; ++j) {
				if (codigo[i] == hipotesis[j]) {
					++descolocados;
					encontrado = true;
				}
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	std::string scodigo = "", shipotesis = "";
	std::cin >> scodigo >> shipotesis;
    if (scodigo=="X" && shipotesis=="X")
        return false;
    
	tCodigo codigo(TAM_CODIGO), hipotesis(TAM_CODIGO);
	for (int i = 0; i < TAM_CODIGO; ++i) {
		codigo[i] = char2color(scodigo[i]);
		hipotesis[i] = char2color(shipotesis[i]);
	}

	int colocados = 0, descolocados = 0;
    compararCodigos(codigo, hipotesis, colocados, descolocados);
    
    // escribir sol

	std::cout << colocados << ' ' << descolocados<<'\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
 //   #ifndef DOMJUDGE
 //    std::ifstream in("datos1.txt");
 //    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
  //   #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
  //   #ifndef DOMJUDGE // para dejar todo como estaba al principio
 //    std::cin.rdbuf(cinbuf);
     system("PAUSE");
 //    #endif
    
    return 0;
}