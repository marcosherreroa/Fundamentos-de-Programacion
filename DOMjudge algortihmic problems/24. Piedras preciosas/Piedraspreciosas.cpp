// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

enum piedrasPreciosas { diamante, rubi, esmeralda, zafiro, jade };

struct tDatos{
    int numsecuencia;
    piedrasPreciosas tipo1;
    int numtipo1;
    piedrasPreciosas tipo2;
    int numtipo2;
};

std::istream& operator>> (std::istream& entrada, piedrasPreciosas& p) {
    char num;
    entrada >> num;
    switch (num) {
    case 'd': p = diamante; break;
    case 'r': p = rubi; break;
    case 'e': p = esmeralda; break;
    case 'z': p = zafiro; break;
    case 'j': p = jade; break;
    }
    return entrada;
}

// función que resuelve el problema
int resolver(std::vector<piedrasPreciosas> const & v, tDatos secuencia) {
    std::vector<int> piedrasventana(5); int cont = 0;

    for (int i = 0; i < secuencia.numsecuencia; ++i){
        ++piedrasventana[int(v[i])];
    }
	

	if (piedrasventana[int(secuencia.tipo1)] >= secuencia.numtipo1
		&& piedrasventana[int(secuencia.tipo2)] >= secuencia.numtipo2) ++cont;

	for (int i = secuencia.numsecuencia; i < v.size(); ++i){
		--piedrasventana[int(v[i-secuencia.numsecuencia])];
		++piedrasventana[int(v[i])];
		if (piedrasventana[int(secuencia.tipo1)] >= secuencia.numtipo1
			&& piedrasventana[int(secuencia.tipo2)] >= secuencia.numtipo2) ++cont;
	}
	return cont;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int numpiedras = 0; tDatos secuencia;
  

    std::cin >> numpiedras >> secuencia.numsecuencia >> secuencia.tipo1 >>
        secuencia.numtipo1 >> secuencia.tipo2 >> secuencia.numtipo2;

    std::vector<piedrasPreciosas> v(numpiedras);
	for (piedrasPreciosas& i : v) std::cin >> i;
    
    int sol = resolver(v, secuencia);
    // escribir sol
    std::cout << sol<< '\n';
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
//     std::ifstream in("datos1.txt");
//     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
//     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}