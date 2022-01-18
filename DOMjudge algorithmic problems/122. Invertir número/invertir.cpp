//Marcos Herrero

#include <iostream>

int invertir(int num, int & pot){
	if (num == 0) {
		pot = 1;
		return 0;
	}
	else {
		int aux = invertir(num / 10, pot);
		int sol = num % 10 *pot + aux;
		pot *= 10;
		return sol;
	}
}

bool resuelveCaso(){
	int num;
	std::cin >> num;
	if (!std::cin) return false;
	int pot = 1;
	std::cout << invertir(num, pot)<<'\n';

	return true;
}

int main(){
	while (resuelveCaso());
	system("PAUSE");
}