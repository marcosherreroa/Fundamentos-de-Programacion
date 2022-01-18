#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const int NUMENTEROS = 10;
const int VALMAX = 100;
const int VALMIN = 1;
const int PALABRASCOLUMNA = 10;
const int MAXINTENTOS = 7;


int leerOpcion(std::string const & pregunta, std::string const & mensajeError, int opmin, int opmax) {
	int opt = 0;

	std::cout << pregunta;
	std::cin >> opt;
	while (opt<opmin || opt>opmax) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << mensajeError;
		std::cin >> opt;
	}
	return opt;
}

void leer_numeros(std::vector<int> & vnumeros, bool & OK) {
	std::ifstream entrada; int numero = 0;

	entrada.open("numeros.txt");
	if (!entrada.is_open())OK = false;

	for (int i = 0; OK && i < NUMENTEROS; ++i) {
		entrada >> numero;
		vnumeros[i] = numero;
		if (numero<VALMIN || numero> VALMAX)OK = false;
	}
	entrada.close();
}

void leer_palabras(std::vector<std::string> & vpalc1, std::vector<std::string> & vpalc2, bool & OK) {
	std::ifstream entrada; std::string palabra = "";

	entrada.open("palabras.txt");
	if (!entrada.is_open()) OK = false;

	else {
		for (int i = 0; i < PALABRASCOLUMNA; ++i) {
			entrada >> palabra;
			vpalc1[i] = palabra;
			entrada >> palabra;
			vpalc2[i] = palabra;
		}
		entrada.close();
	}
}

int igual_palabras(std::vector <std::string> const & v1, std::vector<std::string> const & v2) {
	int posicion = -1;

	for (int i = 0; posicion== -1 && i < v1.size(); ++i) {
		for (int j = 0; posicion==-1 && j < v2.size(); ++j){
			if (v1[i] == v2[j])posicion = i;
		}
	}
	return posicion;
}

void adivina(std::vector<int> & vnumeros, int & numintentos, bool & acertado) {
	int posicion = 0, hipotesis = 0;

	std::cout << "\nDame una posicion entre 0 y " << NUMENTEROS - 1 <<": ";
	std::cin >> posicion;

	while (!acertado && numintentos < MAXINTENTOS) {
		std::cout << "\nHaz tu intento numero " << numintentos + 1 << " para adivinar un numero entre " << VALMIN << " y " << VALMAX << "\n";
		std::cout << "Te quedan " << MAXINTENTOS - numintentos << " intentos\n";
		std::cin >> hipotesis;

		if (vnumeros[posicion] < hipotesis) std::cout << "El valor que buscas es menor\n";
		else if (vnumeros[posicion] > hipotesis) std::cout << "El valor que buscas es mayor\n";
		else acertado = true;

		++numintentos;
	}
}

void jugar_numeros() {
	std::vector<int> vnumeros(NUMENTEROS); 
	int numintentos = 0;  bool OK = true, acertado = false;

	leer_numeros(vnumeros, OK);
	if (!OK) std::cout << "El fichero no existe o alguno de los valores no esta en el rango\n";

	else {
		adivina(vnumeros, numintentos, acertado);
		if (acertado) std::cout << "Enhorabuena, has acertado el numero en " << numintentos << " intentos\n";
		else std::cout << "Tras " << numintentos << " intentos, no has encontrado el numero\n";
	}
}

void jugar_palabras() {
	std::vector<std::string> vpalc1(PALABRASCOLUMNA); std::vector<std::string> vpalc2(PALABRASCOLUMNA);
	bool OK = true;

	leer_palabras(vpalc1, vpalc2, OK);
	if (!OK)std::cout << "El fichero no existe\n";
	else {
		std::cout << "Las palabras de la primera columna son: \n";
		for (int i = 0; i < PALABRASCOLUMNA; ++i) std::cout << vpalc1[i] << " ";

		std::cout << "\nLas palabras de la segunda columna son: \n";
		for (int i = 0; i < PALABRASCOLUMNA; ++i) std::cout << vpalc2[i] << " ";

		int posicion = igual_palabras(vpalc1, vpalc2);
		if (posicion == -1) std::cout << "\nNo se encuentran palabras que cumplan la condicion\n";
		else std::cout << "\nLa palabra " << vpalc1[posicion] << " es la primera palabra de las que aparecen en la primera columna que aparece en la segunda columna\n";
	}
}

int main() {
	std::string pregunta = "\nMENU\n\n1 - Numeros\n2 - Palabras\n0 - Salir\n\nIntroduce una opcion[0-2]: "; 
	std::string mensajeError = "La opcion introducida no es valida";
	bool menu = true;

	while (menu) {
		switch (leerOpcion(pregunta, mensajeError, 0, 2)) {
		case 1:jugar_numeros(); break;
		case 2:jugar_palabras(); break;
		case 0:menu = false; break;
		}
	}
	system("PAUSE");
	return 0;

}