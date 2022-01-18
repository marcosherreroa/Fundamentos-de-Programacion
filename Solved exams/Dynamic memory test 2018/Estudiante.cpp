//*********************
//
// Declaracion de un estudiante
//
//****************************

#include "Estudiante.h"

// Lectura de datos
std::istream& operator>> (std::istream& entrada, tEstudiante & estudiante) {
    getline(entrada, estudiante.nombre);
    entrada >> estudiante.NIF >> estudiante.fechaMatricula >> estudiante.nota;
    return entrada;
}

// Mostrar datos
std::ostream& operator<< (std::ostream& salida, tEstudiante const& estudiante) {
    salida << estudiante.NIF << " - " << estudiante.fechaMatricula << " - " << estudiante.nota << " - " << estudiante.nombre << '\n';
    return salida;
}
