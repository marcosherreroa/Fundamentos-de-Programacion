//*********************
//
// Declaracion de un estudiante
//
//****************************


#ifndef ESTUDIANTE
#define ESTUDIANTE

#include <iostream>
#include <string>

struct tEstudiante {
    std::string nombre;
    std::string NIF;
    std::string fechaMatricula;
    int nota;
};

// Lectura de datos
std::istream& operator>> (std::istream& entrada, tEstudiante & estudiante);

// Mostrar datos
std::ostream& operator<< (std::ostream& salida, tEstudiante const& estudiante);

#endif
