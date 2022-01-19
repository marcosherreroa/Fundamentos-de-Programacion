// Nombre del alumno Marcos Herrero
// Usuario del Juez DG-11


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int resolver(int num) {
	int cifra = 0, inverso = 0;
	while (num > 0){
		cifra = num % 10;
		num /= 10;
		inverso = 10 * inverso + cifra;
	}
	return inverso;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int num = 0;
	std::cin >> num;
    
    if (num==0)
        return false;
    
    int sol = resolver(num);
    // escribir sol

	std::cout << sol << '\n';
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
//    #ifndef DOMJUDGE
     //std::ifstream in("datos.txt");
     //auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
  //   #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
  //   #ifndef DOMJUDGE // para dejar todo como estaba al principio
     //std::cin.rdbuf(cinbuf);
     system("PAUSE");
 //    #endif
    
    return 0;
}