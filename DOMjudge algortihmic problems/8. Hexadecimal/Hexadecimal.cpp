// Nombre del alumno Marcos Herrero
// Usuario del Juez DG11
#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int resolver(char dig1, char dig2 ) {
	int sol = 0, a = 0, b = 0;
	if (int(dig1) >= int('A'))a = 10+int(dig1) - int('A');
	else a = int(dig1) - int('0');

	if (int(dig2) >= int('A'))b = 10+int(dig2) - int('A');
	else b = int(dig2) - int('0');

	sol = 16 * a + b;
	return sol;   
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	char dig1=' ',dig2=' ';
	std::cin >> dig1 >> dig2;

	if (dig1 == '0' && dig2 == '0') return false;
    
    int sol = resolver(dig1,dig2);
    // escribir sol
	std::cout << sol << '\n';
    return true;
    
}

int main() {
  
   
    
    
    while (resuelveCaso())
        ;

    
    
   
    
    return 0;
}