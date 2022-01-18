//Nombre: Marcos Herrero

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>


enum tColor{ROJO, AZUL, VERDE, AMARILLO, MARRON, BLANCO, NUMCOLORES, INCORRECTO};
const int TAM_CODIGO = 4;
const int MAX_INTENTOS = 15;
using tCodigo = std::vector<tColor>;

/*El programa sigue funcionando aunque con otros valores para las constantes TAM_CODIGO y MAX_INTENTOS 

Para añadir nuevos colores se debe ampliar el tipo enumerado ( colocar los nuevos colores antes de NUMCOLORES) y modificar 
las funciones color2char y char2color */

char color2char(tColor color){
	switch (color){
	case ROJO: return 'R';
	case AZUL: return 'Z';
	case VERDE: return 'V';
	case AMARILLO: return 'A';
	case MARRON: return 'M';
	case BLANCO: return 'B';
	}
}

tColor char2color(char letra){
	switch (toupper(letra)){
	case 'R': return ROJO;
	case 'Z': return AZUL;
	case 'V': return VERDE;
	case 'A': return AMARILLO;
	case 'M': return MARRON;
	case 'B': return BLANCO;
	}
	return INCORRECTO;
}

std::ostream & operator<<(std::ostream & flujo, tCodigo const & codigo) {
	for (int i = 0; i < TAM_CODIGO; ++i) std::cout << color2char(codigo[i]);
	return flujo;
}

std::istream & operator>>(std::istream & flujo, tCodigo & hipotesis) {
	std::string shipotesis = ""; bool OK = true;

	std::cout << "Introduce tu hipotesis: ";
	flujo >> shipotesis;

	if (shipotesis.size() != TAM_CODIGO) {
		std::cout << "La hipotesis no tiene la longitud adecuada\n\n";
		OK = false;
	}

	for (int i = 0; OK && i < TAM_CODIGO; ++i) {
		hipotesis[i] = char2color(shipotesis[i]);
		if (hipotesis[i] == INCORRECTO) {
			std::cout << "La hipotesis contiene caracteres no validos\n\n";
			OK = false;
		}
	}

	while (!OK) {
		OK = true;

		std::cout << "Introduce tu hipotesis: ";
		flujo >> shipotesis;

		if (shipotesis.size() != TAM_CODIGO) {
			std::cout << "La hipotesis no tiene la longitud adecuado\n\n";
			OK = false;
		}

		for (int i = 0; OK && i < TAM_CODIGO; ++i) {
			hipotesis[i] = char2color(shipotesis[i]);
			if (hipotesis[i] == INCORRECTO) {
				std::cout << "La hipotesis contiene caracteres no validos\n\n";
				OK = false;
			}
		}
	}
	return flujo;
}

int leeOpcion(std::string const & pregunta, std::string const & mensajeError, int valMin, int valMax) {
	int opt = 0;
	std::cout << pregunta;
	std::cin >> opt;

	while (std::cin.fail() || opt < valMin || opt> valMax) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		std::cout << mensajeError;
		std::cout << pregunta;
		std::cin >> opt;
	}
	return opt;
}

bool leerResultados(std::vector<int> & resultados) {
	std::ifstream entrada;
	entrada.open("partidas.txt");
	if (! entrada.is_open()) return false;

	int resultado = 0;
	entrada >> resultado;
    while (!entrada.eof()) {
			resultados.push_back(resultado);
			entrada >> resultado;
	}
	entrada.close();
	return true;
}

bool escribirResultados(std::vector<int> const & resultados) {
	std::ofstream salida;
	salida.open("partidas.txt");
	if (!salida.is_open()) return false;

	for (int i = 0; i < resultados.size(); ++i) {
		salida << resultados[i] << '\n';
	}
	salida.close();
	return true;
}

void mostrarResultados(std::vector<int> const & resultados) {
	if (resultados.size() == 0)std::cout << "No hay partidas registradas\n";
	else {
		std::cout << "\nResultado de las partidas jugadas:\n\n";

		for (int i = 0; i < resultados.size(); ++i) {
			if (resultados[i] == 1)std::cout << "Partida " << i + 1 << ": Resuelto en " << resultados[i] << " intento\n";
			else if (resultados[i] <= MAX_INTENTOS) std::cout << "Partida " << i + 1 << ": Resuelto en " << resultados[i] << " intentos\n";
			else std::cout << "Partida " << i + 1 << ": No consiguio resolverse\n";
		}
	}
}

void codigoAleatorio(tCodigo & codigo, bool admiteRepetidos) {
	std::vector<bool> repetidos(NUMCOLORES, false);

	for (int i = 0; i < TAM_CODIGO; ++i) {
		codigo[i] = tColor(rand() % NUMCOLORES);

		while (!admiteRepetidos && repetidos[codigo[i]]) {
			codigo[i] = tColor(rand() % NUMCOLORES);

		}
		repetidos[codigo[i]] = true;
	}
}

void compararCodigos(tCodigo const & codigo, tCodigo const & hipotesis, int & colocados, int & descolocados) {
	std::vector<bool> vcolocados(TAM_CODIGO, false);
	colocados = 0; descolocados = 0;

	for (int i = 0; i < TAM_CODIGO; ++i) {
		if (codigo[i] == hipotesis[i]) {
			vcolocados[i] = true;
			++colocados;
		}
	}

	bool encontrado = false;
	for (int i = 0; i < TAM_CODIGO; ++i) {
		if (codigo[i] != hipotesis[i]) {
			encontrado = false;

			for (int j = 0; !encontrado && j < TAM_CODIGO; ++j) {
				if (!vcolocados[j] && codigo[i] == hipotesis[j]) {
					++descolocados;
					vcolocados[j] = true;
					encontrado = true;
				}
			}
		}
	}
}

void juegaPartida(std::vector<int> & resultados, bool admiteRepetidos) {
	tCodigo codigo(TAM_CODIGO), hipotesis(TAM_CODIGO);
	int colocados = 0, descolocados = 0, numintentos = 1;
	bool OK = true, resuelto = false;

	codigoAleatorio(codigo, admiteRepetidos);
	// La siguiente linea es util para la depuracion. Comentarla para jugar seriamente:
	std::cout << "[Solucion: " << codigo << "]\n";

	while (!resuelto && numintentos <= MAX_INTENTOS) {
		std::cin>> hipotesis;
		compararCodigos(codigo, hipotesis, colocados, descolocados);
		std::cout << hipotesis << " Colocados: " << colocados << " ; Descolocados: " << descolocados<<'\n';
			 
		if (colocados == TAM_CODIGO) resuelto = true;
		else {
			if (MAX_INTENTOS - numintentos == 1) std::cout << "Te queda " << MAX_INTENTOS - numintentos << " intento\n\n";
			else std::cout << "Te quedan " << MAX_INTENTOS - numintentos << " intentos\n\n";
			++numintentos;
		}
	}
	if (resuelto) std::cout << "\nEnhorabuena! Has descubierto el codigo\nNumero de intentos: " << numintentos << "\n\n";
	else std::cout << "\nHas agotado el maximo de intentos.Vuelve a intentarlo\n\n";
	
	resultados.push_back(numintentos);
}

void presentacion() {
	std::cout << std::setw(120) << std::setfill('=') << '\n';
	std::cout << std::setw(50) << std::setfill(' ') << ' ' << "MASTERMIND de Marcos Herrero" << std::setw(41) << ' ' << '\n';
	std::cout << std::setw(120) << std::setfill('=') << "\n\n";
	
	std::cout << std::setfill(' ') << std::right
		<< std::setw(104) << "Bienvenido a Mastermind, un juego de ingenio y reflexion ideal para pasar un rato\n "
		<< std::setw(102) << "ameno y divertido. En cada partida, el programa elegira aleatoriamente un codigo\n "
		<< std::setw(23) << "de " << TAM_CODIGO << " colores( de entre " << NUMCOLORES << " colores posibles) y dispondras de " << MAX_INTENTOS << " intentos para\n "
		<< std::setw(104) << "averiguarlo. Tras cada intento fallido, el programa te dira cuantos de los colores\n "
		<< std::setw(101) << "de tu hipotesis estaban en el codigo original, clasificandotelos en colocados y\n "
		<< std::setw(35) << "descolocados.\n\n";
}

int main(){
	srand(time(NULL));

	std::vector<int>resultados;
	bool OK = leerResultados(resultados);
	if (!OK) std::cout << "No se encuentra el fichero de resultados anteriores";
	
	presentacion();
	
	std::string pregunta = "Introduce una opcion[0-3]: ",mensajeError = "La opcion introducida no es valida\n\n";
	bool menu = true;

	while (menu) {
		std::cout << "\nMENU PRINCIPAL\n\n1.Jugar con un codigo sin colores repetidos\n"
			<<"2.Jugar con un codigo con colores repetidos\n3.Mostrar partidas jugadas\n0.Salir\n\n";

		switch (leeOpcion(pregunta, mensajeError, 0, 3)) {
		case 1:juegaPartida(resultados, false); break;
		case 2:juegaPartida(resultados, true); break;
		case 3:mostrarResultados(resultados); break;
		case 0:menu = false; break;
		}
	}

	OK = escribirResultados(resultados);
	if (!OK) std::cout << "No se encuentra el fichero de resultados anteriores";
	
	system("PAUSE");
	return 0;
}