//---------------------------------------------------
//
// Plantilla para el problema DG2-10
//
// Febrero 2018
//
//---------------------------------------------------
// NO DISTRIBUIR
//---------------------------------------------------

// La solución ...

// Include y definiciones para las marcas
#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using tMatriz = std::vector<std::vector<int>>;


std::ostream & operator<<(std::ostream & flujo, tMatriz const& mat) {
	for (int i = 0; i < mat.size(); ++i) {
		flujo << mat[i][0];
		for (int j = 1; j < mat[i].size(); ++j) {
			flujo << ' ' << mat[i][j];
		}
		flujo << '\n';
	}
	return flujo;
}

void intercambiarFilas(tMatriz & matriz, int a, int b) {
	--a;
	--b;
	std::swap(matriz[a], matriz[b]);
}

void intercambiarCols(tMatriz & matriz, int a, int b) {
	--a;
	--b;
	for (int i = 0; i < matriz.size(); ++i) std::swap(matriz[i][a], matriz[i][b]);
	
}

void cruz(tMatriz & matriz, int f, int c, int d) {
	--f;
	--c;
	int i = f, j = c;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		matriz[i][j] = d;
		++i;
		++j;
	}

	 i = f, j = c;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		matriz[i][j] = d;
		--i;
		--j;
	}

	 i = f, j = c;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		matriz[i][j] = d;
		--i;
		++j;
	}

	 i = f, j = c;
	while (0 <= i && i < matriz.size() && 0 <= j && j < matriz[0].size()) {
		matriz[i][j] = d;
		++i;
		--j;
	}
}

void rotarFilaDerecha(tMatriz & matriz, int f) {
	--f;
	int aux = matriz[f][matriz[0].size()-1];
	for (int j = matriz[0].size()-1; j > 0; --j) matriz[f][j] = matriz[f][j - 1];
	matriz[f][0] = aux;
}

void rotarFilaIzquierda(tMatriz & matriz, int f) {
	--f;
	int aux = matriz[f][0];
	for (int j = 0; j < matriz[0].size() - 1; ++j) matriz[f][j] = matriz[f][j + 1];
	matriz[f][matriz[0].size() - 1] = aux;
}

void rotarColAbajo(tMatriz & matriz, int c) {
	--c;
	int aux = matriz[matriz.size() - 1][c];
	for (int i = matriz.size() - 1; i > 0; --i) matriz[i][c] = matriz[i - 1][c];
	matriz[0][c] = aux;
}

void rotarColArriba(tMatriz & matriz, int c) {
	--c;
	int aux = matriz[0][c];
	for (int i = 0; i < matriz.size() - 1; ++i) matriz[i][c] = matriz[i + 1][c];
	matriz[matriz.size()-1][c] = aux;
}

bool resuelveCaso() {
	int N, M;  // Dimensiones de la matriz

	std::cin >> N >> M;

	if (N == 0 && M == 0) return false;

	tMatriz mat(N, std::vector<int>(M));

	// leer matriz
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cin >> mat[i][j];
		}
	}

	// transformaciones
	int T;  // Numero de transformaciones
	std::cin >> T;

	std::string trans; int arg1, arg2, arg3;
	for (int t = 0; t < T; ++t) {
		
		std::cin >> trans;
		if (trans == "filas") {
			// Numeros de las filas a intercambiar. Numeradas del 1..N
			std::cin >> arg1 >> arg2;
			intercambiarFilas(mat, arg1, arg2);
		}
		else if (trans == "columnas") {
			// Numero de las columnas a intercambiar. Numeradas del 1 ..M
			std::cin >> arg1 >> arg2;
			intercambiarCols(mat, arg1, arg2);
		}
		else if (trans == "cruz") {
			// arg1, arg2: Numero de fila y columna del elemento. Numeradas del 1..N y del 1..M
			// arg3: Valor con el que debe rellenarse la cruz
			std::cin >> arg1 >> arg2 >> arg3;
			cruz(mat, arg1, arg2, arg3);
		}
		else if (trans == "rotarFila") {
			// Numero de fila a rotar. Numeradas del 1..N
			std::cin >> arg1;
			if (arg1 > 0) {
				rotarFilaDerecha(mat, arg1);
			}
			else {
				rotarFilaIzquierda(mat, -arg1);
			}
		}
		else if (trans == "rotarCol") {
			// Numero de columna a rotar. Numerada del 1..M
			std::cin >> arg1;
			if (arg1 > 0) {
				rotarColAbajo(mat, arg1);
			}
			else {
				rotarColArriba(mat, -arg1);
			}
		}
	}
	std::cout << mat;
	std::cout << "---\n";
	return true;
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	while (resuelveCaso());
	;

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
