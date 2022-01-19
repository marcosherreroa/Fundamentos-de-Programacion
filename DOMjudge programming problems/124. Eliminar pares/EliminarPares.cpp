//Marcos Herrero
// NO CORREGIR, no es evaluación continua
//El válido es el problema 23

#include <iostream>

int sinPares(int num){
	if (num == 0) return 0;
	else if (num % 2 == 0) sinPares(num / 10);
	else return num % 10 + 10* sinPares(num/10);
}

bool resuelveCaso(){
	int num;
	std::cin >> num;
	if (!std::cin) return false;

	std::cout << sinPares(num)<<'\n';

	return true;
}

int main(){
	while (resuelveCaso());
	return 0;
}