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
        ● Inscripción de Atleta: Insertar un nuevo luchador en la lista dinámica de forma ordenada por victorias - derrotas.
        ● Generar Main Card: Copiar los primeros 5 luchadores de la lista dinámica a un arreglo estático
          para representar los combates estelares de la noche.
        ● Actualizar Récord: Buscar un luchador por ID y modificar su contador de victorias/derrotas.
        ● Guardar Gimnasio: Volcar la lista dinámica al archivo de disco.
        ● Cargar Gimnasio: Al iniciar, el programa debe leer el archivo y reconstruir la lista en memoria.
*/

// c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

struct strLuchador {
    int ID ;
    char nombre[35 + 1] ; 
    char apodo[35 + 1] ;
    int peso ;
    int victorias, derrotas ;
};
struct NODO {
    strLuchador info ;
    NODO *next ;
};

void agregar_a_pila(NODO *&topepila, strLuchador n) {
    NODO *nuevo = new NODO() ;

    nuevo->info.ID = n.ID ;
    strcpy(nuevo->info.nombre, n.nombre) ;
    strcpy(nuevo->info.apodo, n.apodo) ;
    nuevo->info.peso = n.peso ;
    nuevo->info.victorias = n.victorias ;
    nuevo->info.derrotas = n.derrotas ;

    topepila = nuevo ;
return ; }
// Agrega un Nodo a la pila

void quitar_de_pila(NODO *&TopePila, strLuchador &n) {
    NODO *aux = TopePila ;

    n.ID = aux->info.ID ;
    strcpy(n.nombre, aux->info.nombre) ;
    strcpy(n.apodo, aux->info.apodo) ;
    n.peso = aux->info.peso ;
    n.victorias = aux->info.victorias ;
    n.derrotas = aux->info.derrotas ; 

    TopePila = aux->next ;
    delete aux ;
return ; }
// Quita el último Nodo de la pila

void copiar_de_pila(NODO *TopePila, strLuchador &n) {

    n.ID = TopePila->info.ID ;
    strcpy(n.nombre, TopePila->info.nombre) ;
    strcpy(n.apodo, TopePila->info.apodo) ;
    n.peso = TopePila->info.peso ;
    n.victorias = TopePila->info.victorias ;
    n.derrotas = TopePila->info.derrotas ; 

return ; }
// Copia en la variable que se le pase la información del puntero de pila que se le pase
// No mueve el puntero de pila

void mover_de_pila(NODO *&TopePila1, NODO *&TopePila2) {
    strLuchador elem_a_mover ;
    quitar_de_pila (TopePila2, elem_a_mover) ; 
    agregar_a_pila (TopePila1, elem_a_mover) ;
return ; }
// Mueve un elemento de una pila a la otra
// Pila1 recibe el elemento, Pila2 entrega el elemento

void startUP(FILE *archivo, NODO *&topepila) {
    strLuchador luchador ;

    int PosActual = ftell(archivo) ;
    fseek(archivo, 0, SEEK_SET) ; // para leer desde el inicio

    while (fread(&luchador, sizeof(strLuchador), 1, archivo) ==1) { //verificacion lectura structt
        agregar_a_pila(topepila, luchador) ;
    }

    fseek(archivo, PosActual, SEEK_SET) ;

return ; }
// Carga el contenido del archivo a la lista dinámica

void GuardarListaDinamica(FILE *archivo, NODO *&topepila) {
    strLuchador luchador ;
    fseek(archivo, 0, SEEK_END) ; 

    while (topepila != NULL ) {
        quitar_de_pila(topepila, luchador) ;
        fwrite(&luchador, sizeof(strLuchador), 1, archivo) ;
    } 
return ;}
// Carga la lista dinámica al archivo binario

void MainCard(NODO *topepila, strLuchador CombatesEstelares[]) {
    NODO *aux = topepila ;
    for (int i = 0; i < 5; i++) {
        copiar_de_pila(aux, CombatesEstelares[i]) ;
        aux = aux -> next ;
    }
return ; }
// Copia los primeros cinco elementos de la pila a CombatesEstelares[]
// No mueve el tope de pila ni borra elementos



void OrdPila (NODO *&topepila) {
    strLuchador luchador ;
    NODO *SortPile = NULL ;
    quitar_de_pila (topepila, luchador) ;
    while ((topepila->info.victorias-topepila->info.derrotas)>=(luchador.victorias-luchador.derrotas)) {
        mover_de_pila (SortPile, topepila) ;
    }
    agregar_a_pila (topepila, luchador) ;
    while (SortPile!=NULL) {
        mover_de_pila (topepila, SortPile) ;
    }
return ; }
// Ordena un elemento en la pila por victorias - derrotas

void inscribir_atleta(NODO *&topepila, int &PosLuchador) {
    strLuchador nuevo ;

    cout << "Ingrese su atleta" << endl ;
    cout << "ID: " ;
    cin >> nuevo.ID ;
    cout << "Nombre: " ;
    cin.ignore() ;
    cin.getline(nuevo.nombre, 35 + 1, '\n') ;
    cout << "Apodo: " ;
    cin.ignore() ;
    cin.getline(nuevo.apodo, 35 + 1, '\n') ;
    cout << "Peso: " ;
    cin >> nuevo.peso ;
    cout << "Racha de Victorias: " ;
    cin >> nuevo.victorias ;
    cout << "Racha de Derrotas: " ;
    cin >> nuevo.derrotas ;

    agregar_a_pila (topepila, nuevo) ;
    PosLuchador++ ;
return ; }
// Añade un atleta a la pila 



void actualizar_record() { // HACER
    ;
}


int main() {

    NODO *topePila = NULL ; 

    FILE *archivo = fopen("GIMNASIO.dat", "wb+") ;
    strLuchador TOPLuchador[10], CombatesEstelares[5] ;

    int opcion, posLuchador = 0 ;
    do {
        cout << "____QUE DESEA HACER____" << endl ;
        cout << "0. Cargar Gimnasio" << endl ;
        cout << "1. Inscribir un atleta" << endl ;
        cout << "2. Generar Main Card" << endl ;
        cout << "3. Actualizar Record" << endl ;
        cout << "4. Guardar Gimnasio" << endl ;
        cout << "5. SALIR" << endl ;
        cout << "-> " ;
        cin >> opcion ;
        while (!((opcion >= 0)&&(opcion < 6))) { 
            if (cin.fail()) { cin.clear(); }
            cout << "Ingrese un input valido: "; cin >> opcion ;
        }
        
        switch (opcion) {
        case 0 :
            startUP(archivo, topePila) ;
            cout << "Archivo cargado" << endl ;
            break ;
        case 1 :
            inscribir_atleta (topePila, posLuchador) ;
//            OrdPila (topePila) ;
            break ;
        case 2 :
            MainCard(topePila, CombatesEstelares) ;
            cout << "Se realizo la Main Card" << endl ;
            break ;
        case 3 :
            ;
            break ;
        case 4 :
            GuardarListaDinamica(archivo, topePila) ;
            cout << "Archivo guardado" << endl ;
            break ;
        case 5 :
            break ;
        }
    } while (opcion != 5) ; 

    fclose(archivo) ;

return 0 ; }
