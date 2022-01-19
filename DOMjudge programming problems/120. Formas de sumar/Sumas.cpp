//Marcos Herrero

#include <iostream>
#include <vector>

int sumas(std::vector<int> const & v, int ini, int num) {
	if (ini >= v.size()) return 0;
	else if (num > v[ini])  return sumas(v, ini + 1, num - v[ini]) + sumas(v, ini + 1, num);
	else if (num == v[ini]) return 1 + sumas(v, ini + 1, num);
	else return sumas(v, ini + 1, num);
}

bool resuelveCaso(){
	int num, n;
	std::cin >> num >> n;
	if (!std::cin) return false;

	std::vector<int> v(n);
	for (int i = 0; i < n; ++i) std::cin >> v[i];

	std::cout << sumas(v, 0 , num) << '\n';
	return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}