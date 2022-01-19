//Marcos Herrero

#include <iostream>

void mostrarBin(int num){
	if (num > 0){
		mostrarBin(num / 2);
		std::cout << num % 2;
	}
}

bool resuelveCaso(){
	int num;
	std::cin >> num;
	if (!std::cin) return false;
	mostrarBin(num);
	std::cout << '\n';

	return true;
}

int main(){
	while (resuelveCaso());
	return 0;
}