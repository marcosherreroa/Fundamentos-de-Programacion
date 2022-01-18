#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

const float K = 1.5;

bool leerficheroNumerico(std::string const & nombre, std::vector<float> & vnumeros, float & suma) {
	std::ifstream entrada;
	entrada.open(nombre);
	if (!entrada.is_open()) return false;

	float x = 0.0,y = 0.0;
	std::cout << "Escriba limites del intervalo numerico\n";
	std::cin >> x >> y;
	if (x > y)std::cout << "El intervalo es vacio\n";
	else {
		float num = 0.0;
		entrada >> num;
		if (num == 0 || entrada.eof()) std::cout << "El fichero es vacio\n";
		while (num != 0 && num <= y) {
			if (x <= num ) {
				vnumeros.push_back(num);
				suma += num;
			}
			entrada >> num;
		}
		if (vnumeros.size() == 0) std::cout << "No existen valores que cumplan la condicion\n";
	}

	return true;
}

void escribirSolucion(std::vector<float> const & solucion, float media) {
	std::cout << "\nExamen de diciembre. Solucion\n\n";

	for (int i = 0; i < solucion.size(); ++i) {
		std::cout << "Valor :" << std::setprecision(2) << std::fixed << std::setw(10) << solucion[i] << " Diferencia con la media"
			<< std::setw(10) << solucion[i] - media<<'\n';
	}
}

int numCifras(int num) {
	int cifras = 1;

	num /= 10;
	while (num != 0) {
		++cifras;
		num /= 10;
	}
	return cifras;
}

int obtenerCifras(int num, int ncifras) {
	int sol = 0; int potencia = 1;

	for (int i = 0; i < ncifras; ++i) {
		sol += num % 10 * potencia;
		potencia *= 10;
	}
	return sol;
}

bool curioso(int num) {
	int cuadrado = num*num;
	int ncifras = numCifras(num);
int cifras = obtenerCifras(cuadrado, ncifras);
	
	return(num == cifras);
}

void obtenerNumeros() {
	std::vector<float> vnumeros; float suma = 0.0;
	bool OK = leerficheroNumerico("archivoNumeros.txt", vnumeros, suma);
	if (!OK)std::cout << "No se encuentra el archivo de numeros\n";

	float media = suma / vnumeros.size();
	std::vector<float> solucion;
	for (int i = 0; i < vnumeros.size(); ++i) {
		if (abs(vnumeros[i] - media) < K && !curioso(trunc(vnumeros[i]))) solucion.push_back(vnumeros[i]);
	}

	escribirSolucion(solucion, media);
}

bool contieneCaracter(std::string const & palabra, char c1, char c2) {
	bool encontrado = false;

	for (int i = 0; !encontrado && i < palabra.size(); ++i) {
		if (c1 <= palabra[i] && palabra[i] <= c2) encontrado = true;
	}

	return encontrado;
}

void obtenerPalabras() {
	std::ifstream entrada;
	entrada.open("archivoCaracteres.txt");
	if (!entrada.is_open()) std::cout << "No se encuentra el archivo de caracteres\n";
	else {
		char c1 = ' ', c2 = ' ';
		std::cout << "Introduzca extremos del intervalo de caracteres\n";
		std::cin >> c1 >> c2;

		std::string palabra;
		entrada >> palabra;
		while (palabra != "A") {
			if (!contieneCaracter(palabra, c1, c2)) std::cout << palabra<<'\n';
			entrada >> palabra;
		}
	}
}

int main() {
	obtenerNumeros();
	obtenerPalabras();

	system("PAUSE");
	return 0;
}