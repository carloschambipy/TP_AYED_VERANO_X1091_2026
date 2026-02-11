//c++
#include <iostream>
using namespace std; 

/*
A. Estructura Estática  
Definir un struct básico para el luchador y un arreglo (array) de tamaño fijo para el ranking 
del "Top 10" de una categoría. 
● Campos: id, nombre, apodo, peso, victorias, derrotas.
*/
struct strLuchador {
    int ID ;
    char nombre[35] ;
    char apodo[35] ; 
    int peso ; 
    int victorias , derrotas ;
};

int main() {

    strLuchador TOPLuchador[10] ;



return 0; }