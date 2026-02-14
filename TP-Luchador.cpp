/*
A. Estructura Estática  
Definir un struct básico para el luchador y un arreglo (array) de tamaño fijo para el ranking 
del "Top 10" de una categoría. 
    ● Campos: id, nombre, apodo, peso, victorias, derrotas. 

B. Estructura Dinámica 
Para manejar la lista completa de todos los atletas de la liga (que son cientos y varían constantemente), se deberá 
implementar una Lista Enlazada Simple. 
    ● Esto permite "estirar" o ir  agregando nodos a medida que nuevos talentos firman contrato, con uso eficiente de la 
memoria, ordenado por puntaje (victorias -derrotas). 

C. Persistencia  
Los datos no pueden perderse al apagar el equipo Se requiere el uso de Archivos Binarios (.dat) para guardar y cargar 
el padrón de luchadores completo


Requerimientos Funcionales: 
    El programa deberá contar con un menú profesional: 
        ● Inscripción de Atleta: Insertar un nuevo luchador en la lista dinámica de forma ordenada por peso. 
        ● Generar Main Card: Copiar los primeros 5 luchadores de la lista dinámica a un arreglo estático 
          para representar los combates estelares de la noche. 
        ● Actualizar Récord: Buscar un luchador por ID y modificar su contador de victorias/derrotas. 
        ● Guardar Gimnasio: Volcar la lista dinámica al archivo de disco. 
        ● Cargar Gimnasio: Al iniciar, el programa debe leer el archivo y reconstruir la lista en memoria.
*/

//c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std; 

struct strLuchador {
    int ID ;
    char nombre[35] ;
    char apodo[35] ; 
    int peso ; 
    int victorias , derrotas ;
};

struct NODO {
    int ID ;
    char nombre[35] ;
    char apodo[35] ; 
    int peso ; 
    int victorias , derrotas ;
    NODO *next ; 
};

void agregarpila (NODO *&topepila, strLuchador n) {
    
    NODO *nuevo = new NODO ;
    
    nuevo -> ID = n.ID  ;
    strcpy (nuevo->nombre,n.nombre) ;
    strcpy (nuevo->apodo,n.apodo) ;
    nuevo -> peso = n.peso  ;
    nuevo -> victorias = n.victorias ;
    nuevo -> derrotas = n.derrotas ;
    
    topepila = nuevo ;

return ; }
// Agrega un Nodo a la pila

void quitar_de_pila (NODO *&TopePila, strLuchador &n) {
    
    NODO *aux = TopePila ;
    
    n.ID = aux -> ID ;
    strcpy (n.nombre,aux->nombre) ;
    strcpy (n.apodo,aux->apodo) ;
    n.peso = aux -> peso ;
    n.victorias = aux -> victorias ;
    n.derrotas = aux -> derrotas ;
    
    TopePila = aux -> next ;
    delete aux ;

return ; }
// Quita el último Nodo de la pila

/*

void mostrarpila (NODO *topepila) {
    NODO *aux = topepila ;

    while (aux!=NULL) {

        ;

        topepila = aux->next ;
        aux = topepila ;
    }

return ; }

HACER */




int main() {

    FILE *archivo = fopen ( "TOP_Luchadores.dat" , "wb+" ) ;
    strLuchador TOPLuchador[10] , LuchadoresLiga[1000] ;



    fclose (archivo) ;

return 0; }
