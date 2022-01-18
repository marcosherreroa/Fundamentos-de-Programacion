#include "juego.h"

void incluirCarta(tMano & mano, tCarta carta) {
	++mano[carta];
}

tTecla leerTecla() {
	std::cin.sync();

	int dir = _getch();
	if (dir == 32) return ESPACIO;
	else if (dir == 13) return ENTER;
	if (dir == 0xe0) {
		dir = _getch();
		if (dir == 72) return ARRIBA;
		else if (dir == 80) return ABAJO;
		else if (dir == 75) return IZQUIERDA;
		else if (dir == 77) return DERECHA;
		else return OTRA;
	}
	else return OTRA;

}

std::ostream &operator<<(std::ostream & flujo, tMano const & mano) {
	for (int i = AVANZAR; i < NUMMOVIMIENTOS; ++i) {
		std::cout << ' ' << mano[i];
		colorFondo(PALETA[PALETA.size()-1]);
		switch (i) {
		case AVANZAR: flujo << " ^ "; break;
		case GIROIZQUIERDA: flujo << " < "; break;
		case GIRODERECHA: flujo << " > "; break;
		case LASER: flujo << " ~ "; break;
		}
		colorFondo(0);
	}

	return flujo;
}

bool cargarJuego(tJuego & juego){
	std::string nombreArchivo;
	std::cout << "Introduce el nombre del fichero del que se desea cargar el tablero: ";
	std::cin.ignore(1000, '\n'); // para evitar problemas con getline
	getline(std::cin, nombreArchivo);

	std::ifstream entrada;
	entrada.open(nombreArchivo);
	if (!entrada.is_open()){
		std::cout << "No se encuentra el archivo\n";
		return false;
	}

	std::cout << "Introduce el numero de jugadores ["<<MINJUGADORES<<'-'<<MAXJUGADORES<<"]: ";
	std::cin >> juego.numJugadores;
	if (std::cin.fail() ||juego.numJugadores < MINJUGADORES || juego.numJugadores > MAXJUGADORES){
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "El numero de jugadores introducido no es valido\n";
		return false;
	}

	std::vector<tCoordenada> coords(juego.numJugadores);
	cargarTablero(juego.tablero, coords, entrada, juego.numJugadores);
	std::cout << "Escribe los nombres de los jugadores (entre "<<MINLETRAS<<" y "<<MAXLETRAS<<" caracteres sin espacios) :\n";
	
    tCarta carta; bool OK = true;
	for (int i = 0; OK && i < juego.numJugadores; ++i){  
		                                                           // al declarar jugador, se da tamaño al vector mano.
		tJugador jugador{ std::vector<int>(NUMMOVIMIENTOS, 0) }; //es necesario redeclarar el jugador en cada iteracion. De otra manera quedan		         
															    // valores en mazo y mano que pasan al siguiente jugador

		std::cin.ignore(1000, '\n'); // para que no se pueda dar nombre a los jugadores antes de tiempo y cada jugador de el suyo)
		std::cout << i + 1 << ". ";
		std::cin>>jugador.nombre;  // no se permiten espacios en los nombres por no poder leerse bien del fichero

		while (jugador.nombre.size() < MINLETRAS || jugador.nombre.size() > MAXLETRAS) {                         //resulta apropiado establecer
			if (jugador.nombre.size() < MINLETRAS) std::cout << "El nombre introducido es demasiado corto\n";     // un minimo y maximo numero de caracteres
			else if (jugador.nombre.size() > MAXLETRAS) std::cout << "El nombre introducido es demasiado largo\n";// por nombre para poder dar un mejor formato 
																												  // (en mostrarJuego() se ve por que
			std::cin.ignore(1000, '\n');
			std::cout << i + 1 << ". ";
			std::cin>> jugador.nombre;
		}

		jugador.coord = coords[i];
		crearMazoAleatorio(jugador.mazo, NA_INICIAL, NGI_INICIAL, NGD_INICIAL, NL_INICIAL);
		
		for (int j = 0; OK && j < CARTASMANO_INICIAL; ++j) {
			OK = cogerCarta(jugador.mazo, carta);
		
			if (!OK) std::cout << "Error. El mazo inicial no puede ser menor que la mano inicial. Deben redefinirse las constantes\n";
			else incluirCarta(jugador.mano, carta);
		}
		if (OK) juego.jugadores.push_back(jugador);
	}

	juego.turno = 0;  // los jugadores van numerados de 0 a 3 a nivel de codigo. El que aqui llamamos jugador 0 es el que se muestra por
	return OK;        // pantalla como jugador 1
}

void mostrarJuego(tJuego const & juego) {
	system("cls");
	std::cout << juego.tablero<<"\n\n";

	std::cout << "JUGADORES:\n\n";
	for (int i = 0; i < juego.numJugadores; ++i) {
		colorFondo(PALETA[TORTUGA + i]);

		if (juego.turno == i)std::cout << '>';
		else std::cout << ' ';

		std::cout << i + 1 << '.' << std::setw(MAXLETRAS) << juego.jugadores[i].nombre << ':';  // aqui se ve por que se necesita un numero
		colorFondo(0);                                                                          // maximo de caracteres para que el formato
		std::cout << juego.jugadores[i].mano << '\n';                                           //sea adecuado
		
	}
	std::cout << '\n';
}

bool realizarMovimiento(tTablero & tablero, tCoordenada  & coord, tVCartas const & vcartas) {
	tCoordenada coordCasillasig;
	tCasilla casillasiguiente;
	bool joya = false;

	for (int i = 0; !joya && i < vcartas.size(); ++i) {
		switch (vcartas[i]) {
		case AVANZAR: {
			if (comprobarMovimiento(tablero, coord, tablero[coord.x][coord.y].tortuga.dir)) {
				coordCasillasig.x = coord.x + incF[tablero[coord.x][coord.y].tortuga.dir];
				coordCasillasig.y = coord.y + incC[tablero[coord.x][coord.y].tortuga.dir];
				casillasiguiente = tablero[coordCasillasig.x][coordCasillasig.y];

				if (casillasiguiente.estado == JOYA) {
					avanzar(tablero, coord, tablero[coord.x][coord.y].tortuga.dir);
					joya = true;
				}
				else if (casillasiguiente.estado == CAJA) {
					avanzar(tablero, coordCasillasig, tablero[coord.x][coord.y].tortuga.dir);
					avanzar(tablero, coord, tablero[coord.x][coord.y].tortuga.dir);
				}
				else avanzar(tablero, coord, tablero[coord.x][coord.y].tortuga.dir);

				coord = coordCasillasig;

			}
			break;
		}
		case GIROIZQUIERDA: {
			--tablero[coord.x][coord.y].tortuga.dir;
			break;
		}
		case GIRODERECHA: {
			++tablero[coord.x][coord.y].tortuga.dir;
			break;
		}
		case LASER: {
			laser(tablero, coord, tablero[coord.x][coord.y].tortuga.dir);
			break;
		}
		}
	}

	return joya;
}

bool ejecutarTurno(tJuego & juego) {
	bool finalizado = false, joya = false;

	std::cout << "Es el turno de " << juego.jugadores[juego.turno].nombre << "\n\n";

	while (!finalizado) {
		std::cout << "Selecciona el tipo de jugada [R= Robar, E= Ejecutar secuencia]: ";
		std::string jugada; // se utiliza un string  para vaciar completamente  la entrada y no dejar caracteres que puedan influir 
		getline(std::cin, jugada); // en turnos posteriores. La jugada solo es valida cuando el string tiene un unico caracter

		while (jugada.size() != 1 || (toupper(jugada[0]) != 'R' && toupper(jugada[0]) != 'E')) {
			std::cout << "La opcion introducida no es valida\n\n";
			std::cout << "Selecciona el tipo de jugada [R= Robar, E= Ejecutar secuencia]: ";
			getline(std::cin, jugada);
		}

		switch (toupper(jugada[0])) {  // se permiten R y E en mayuscula y minuscula
		case 'R': {
			tCarta carta;
			bool OK = cogerCarta(juego.jugadores[juego.turno].mazo, carta);
			if (!OK) std::cout << "No quedan cartas que robar\n\n";   // se ha optado por no permitir que se pase turno. Cuando un jugador no
			else {                                                  // puede robar tiene necesariamente que ejecutar una secuencia
				incluirCarta(juego.jugadores[juego.turno].mano, carta);
				finalizado = true;
			}
			break;
		}
		case 'E': 
			if (juego.jugadores[juego.turno].mano[AVANZAR] == 0 &&                     // se comprueba, antes de hacer nada,
				juego.jugadores[juego.turno].mano[GIROIZQUIERDA] == 0 &&              // si se dispone de las cartas necesarias
				juego.jugadores[juego.turno].mano[GIRODERECHA] == 0 &&
				juego.jugadores[juego.turno].mano[LASER] == 0)
				std::cout << "No tienes cartas. Tienes que robar\n\n";

			else switch (MODOEJECSEC) {
			case 1: {finalizado = ejecutarSecuenciaModo1(juego, joya); break; }
			case 2: {finalizado = ejecutarSecuenciaModo2(juego, joya); break; }
			}
		}
	}

	return joya;
}

bool ejecutarSecuenciaModo1(tJuego & juego, bool & joya) {//Comprueba los movimientos conforme se introducen
	tVCartas vcartas;
	std::cout << "Introduce la secuencia que desees ejecutar: ";

	tTecla tecla = leerTecla();
	while (tecla != ENTER) {
		switch (tecla) {
		case ARRIBA: {
			if (juego.jugadores[juego.turno].mano[AVANZAR] > 0) {
				--juego.jugadores[juego.turno].mano[AVANZAR];
				vcartas.push_back(AVANZAR);
				std::cout << '^';
			}
			else std::cout << "\nNo tienes cartas para realizar ese movimiento\n";
			break;
		}
		case IZQUIERDA: {
			if (juego.jugadores[juego.turno].mano[GIROIZQUIERDA] > 0) {
				--juego.jugadores[juego.turno].mano[GIROIZQUIERDA];
				vcartas.push_back(GIROIZQUIERDA);
				std::cout << '<';
			}
			else std::cout << "\nNo tienes cartas para realizar ese movimiento\n";
			break;
		}
		case DERECHA: {
			if (juego.jugadores[juego.turno].mano[GIRODERECHA] > 0) {
				--juego.jugadores[juego.turno].mano[GIRODERECHA];
				vcartas.push_back(GIRODERECHA);
				std::cout << '>';
			}
			else std::cout << "\nNo tienes cartas para realizar ese movimiento\n";
			break;
		}
		case ESPACIO: {
			if (juego.jugadores[juego.turno].mano[LASER] > 0) {
				--juego.jugadores[juego.turno].mano[LASER];
				vcartas.push_back(LASER);
				std::cout << '~';
			}
			else std::cout << "\nNo tienes cartas para realizar ese movimiento\n";
		}
		}
		tecla = leerTecla();
	}

	if (vcartas.size() == 0) {
		std::cout << "\nNo se permiten secuencias vacias\n\n";
		return false;
	}
	else {
		joya = realizarMovimiento(juego.tablero, juego.jugadores[juego.turno].coord, vcartas);
		devolverVector(juego.jugadores[juego.turno].mazo, vcartas);
		return true;

	}
}

bool ejecutarSecuenciaModo2(tJuego & juego, bool & joya) { // Comprueba todas al final
	tVCartas vcartas;
	std::cout << "Introduce la secuencia que desees ejecutar(pulsa ABAJO para cancelar): ";

	int nA = 0, nGI = 0, nGD = 0, nL = 0;
	tTecla tecla = leerTecla();
	while (tecla != ENTER && tecla != ABAJO) {
		switch (tecla) {
		case ARRIBA: {
			vcartas.push_back(AVANZAR);
			++nA;
			std::cout << '^';
			break;
		}
		case IZQUIERDA: {
			vcartas.push_back(GIROIZQUIERDA);
			++nGI;
			std::cout << '<';
			break;
		}
		case DERECHA: {
			vcartas.push_back(GIRODERECHA);
			++nGD;
			std::cout << '>';
			break;
		}
		case ESPACIO: {
			vcartas.push_back(LASER);
			++nL;
			std::cout << '~';
		}
		}
		tecla = leerTecla();
	}

	if (tecla == ABAJO) {
		std::cout << "\nSe ha cancelado la secuencia\n\n";
		return false;
	}

	else if (vcartas.size() == 0) {
		std::cout << "\nNo se permiten secuencias vacias\n\n";
		return false;
	}

	else if (nA > juego.jugadores[juego.turno].mano[AVANZAR] ||                     // se comprueba, antes de hacer nada,
		nGI > juego.jugadores[juego.turno].mano[GIROIZQUIERDA] ||              // si se dispone de las cartas necesarias
		nGD > juego.jugadores[juego.turno].mano[GIRODERECHA] ||
		nL > juego.jugadores[juego.turno].mano[LASER]) {
		std::cout << "\nNo tienes las cartas necesarias para ejecutar esa secuencia\n\n";
		return false;
	}

	else {
		juego.jugadores[juego.turno].mano[AVANZAR] -= nA;
		juego.jugadores[juego.turno].mano[GIROIZQUIERDA] -= nGI;
		juego.jugadores[juego.turno].mano[GIRODERECHA] -= nGD;
		juego.jugadores[juego.turno].mano[LASER] -= nL;

		joya = realizarMovimiento(juego.tablero, juego.jugadores[juego.turno].coord, vcartas);
		devolverVector(juego.jugadores[juego.turno].mazo, vcartas);

		return true;
	}
}



bool jugar(tPuntuaciones & puntuaciones) {
	tJuego juego{ tTablero(DIMENSION, std::vector<tCasilla>(DIMENSION)) };  // al declarar juego( se redeclara en cada partida)
	bool OK= cargarJuego(juego);                                            // se da tamaño al tablero
	if (!OK) return false;

	std::cin.ignore(1000, '\n'); //para evitar problemas con getline
	bool joya = false;
	while (!joya) {
		mostrarJuego(juego);
		joya = ejecutarTurno(juego);
		if (!joya) {
			++juego.turno;
			juego.turno %= juego.numJugadores;
		}
	}

	mostrarJuego(juego);
	bool encontrado = true;
	for (int i = 0; i < juego.numJugadores; ++i) {
		if (i == juego.turno) encontrado = actualizarPuntuacion(puntuaciones, juego.jugadores[i].nombre, juego.numJugadores);
		else actualizarPuntuacion(puntuaciones, juego.jugadores[i].nombre, 0);
	}

	colorFondo(PALETA[PALETA.size()-1]);
	if (encontrado) std::cout << "El jugador " << juego.jugadores[juego.turno].nombre << " ha vuelto a ganar. Enhorabuena!\n";
	else std::cout << "El jugador " << juego.jugadores[juego.turno].nombre << " ha ganado su primera partida. Enhorabuena!\n";
	std::cout << "Su puntuacion se incrementa en " << juego.numJugadores<<" \n\n";
	colorFondo(0);

	return true;
}
