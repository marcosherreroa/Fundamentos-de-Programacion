// Nombre del alumno Marcos Herrero
// Usuario del Juez DG11

#include <iostream>
#include <iomanip>
#include <fstream>

// función que resuelve el problema
int resolver(int num1, int num2) {
	int aux = 0, sol = 0;
	while (num2 != 0) {
		aux = num1;
		num1 = num2;
		num2 = aux % num2;
	}
	sol = num1;
	return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
	int num1 = 0, num2 = 0;
	std::cin >> num1 >> num2;
    if (num1 == 0 && num2 == 0)
        return false;
    
   int sol = resolver(num1,num2);
    // escribir sol
   std::cout << sol << '\n';
    return true;
    
}

int main() {
    while (resuelveCaso());    
     system("PAUSE");
    return 0;
}