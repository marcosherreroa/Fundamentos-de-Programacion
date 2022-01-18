#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

#include "ListaGrupos.h"

//#ifdef _DEBUG
//#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
//#define new DBG_NEW



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // Lectura del numero de grupos
    int numGrupos;
    std::cin >> numGrupos;
    if (!std::cin) return false;
    // Declaracion de la lista de grupos
    tListaGrupos lg;
    inicializarListaGrupos(lg);
    // Lectura de los datos de cada grupo
    int numAlumnos;
    for (int i = 0; i < numGrupos; ++i) {
        std::string id;
        std::string aux;
        getline(std::cin, aux);
        std::cin >> id; // identificacion del grupo
        std::cin >> numAlumnos;
        tListaEstudiantes le;
        inicializarListaEstudiantes(le);
        // Lectura de los estudiantes del grupo
        for (int j = 0; j < numAlumnos; ++j) {
            tEstudiante estudiante;
            getline(std::cin, aux);
            std::cin >> estudiante;
            insertar(le, estudiante);
        }
        insertar(lg, id, le);
    }
    // Alumnos de los que se desea saber el grupo
    std::cin >> numAlumnos;
    for (int i = 0; i < numAlumnos; ++i) {
        std::string NIF;
        std::cin >> NIF;
        mostrarNotas(lg, NIF);
    }
    // Grupos de los que se desea saber los suspensos
    std::cin >> numGrupos;
    for (int i = 0; i < numGrupos; ++i) {
        std::string idGrupo;
        std::cin >> idGrupo;
        mostrarSuspensos(lg, idGrupo);
    }
    // Liberar la memoria dinamica
    liberar(lg);
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    
    
    while (resuelveCaso());
    ;
    
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    //_CrtDumpMemoryLeaks();
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}

//#endif
