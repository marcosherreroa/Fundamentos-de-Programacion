//Marcos Herrero

#include <iostream>

long long int numCifras(long long int num) {
	if (num < 10) return 1;
	else return 1+ numCifras(num/10);
}

bool resuelveCaso() {
	long long int num;
	std::cin >> num;
	if (!std::cin)return false;

	std::cout << numCifras(num) << '\n';

	return true;
}

int main() {
	while (resuelveCaso());
}