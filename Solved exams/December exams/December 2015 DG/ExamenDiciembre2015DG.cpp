#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

std::string modificarCadena(std::string & cadena, int despl) {
	for (int i = 0; i < cadena.size(); ++i){
		if (isalpha(cadena[i])){
			cadena[i] = char(int(tolower(cadena[i]))+ despl);
			if (cadena[i] > 'z') cadena[i]=char(int(cadena[i])-int('z')+ int('a')-1);
		}
	}
	return cadena;
}

bool producto(int numero){
	return(int(sqrt(numero))*int(sqrt(numero) + 1)==numero);
}

int modificarnumero(int numero){
	int cifra = 0, ncifra = 0;
    bool encontrado = false;

	for (int i = numero; !encontrado && i > 0; i/=10) {
		++ncifra;
		cifra = i % 10;
		if (cifra % 2 == 0) {
			encontrado = true;
			numero += pow(10, ncifra - 1);
		}
	}
	return numero;
}

void archivoCaracteres(std::ifstream & entrada, std::ofstream & salida) {
	int despl = 0; std::string cadena = "";
	entrada >> despl;
	entrada.ignore(1);
	getline(entrada, cadena);

	while (cadena != "XXX") {
		salida << modificarCadena(cadena, despl)<<'\n';
		getline(entrada, cadena);
	}
}

void archivoNumerico(std::ifstream & entrada, std::ofstream & salida) {
	int k1 = 0, k2 = 0, numero = 0;

	entrada >> k1 >> k2 >> numero;
	
	while (numero != 0) {
		if (k1 <= numero && numero <= k2 && !producto(numero)) salida << modificarnumero(numero) << '\n'; 
		entrada >> numero;
	}
}

int main(){
	std::string nombreArchivo; std::ifstream entrada; std::ofstream salida;
	int opcion = 0;

	std::cin >> nombreArchivo;
	entrada.open(nombreArchivo);
	salida.open("SALIDA.txt");

	entrada >> opcion;

	switch (opcion){
	case 1: {archivoCaracteres(entrada, salida);break;}
	case 2: {archivoNumerico(entrada, salida); break; }
	}
	entrada.close();
	salida.close();
	system("PAUSE");
}