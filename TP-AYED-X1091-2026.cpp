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


* Este programa fue escrito en Visual Studio Code *
*/

// c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

struct strLuchador {
    int ID;
    char nombre[35 + 1];
    char apodo[35 + 1];
    int peso;
    int victorias;
    int derrotas;
};
struct NODO {
    strLuchador info;
    NODO *next;
};

// Prototipos
void agregar_a_pila (NODO *&topepila, strLuchador n) ;
void quitar_de_pila (NODO *&TopePila, strLuchador &n) ;
void copiar_de_pila (NODO *TopePila, strLuchador &n) ;
void mover_de_pila (NODO *&TopePila1, NODO *&TopePila2) ;
void vaciar_pila (NODO *&topepila) ;
void startUP (FILE *archivo, NODO *&topepila) ;
void GuardarListaDinamica (FILE *&archivo, NODO *&topepila) ;
void MainCard (NODO *&topepila, strLuchador CombatesEstelares[]) ;
void OrdPila (NODO *&topepila) ;
void inscribir_atleta (NODO *&topepila) ;
void actualizar_record (NODO *&topepila) ;



int main() { 
    NODO *topePila = NULL ; 
    strLuchador TOPLuchador[10], CombatesEstelares[5] ;
    FILE *archivo = fopen ("GIMNASIO.dat", "rb+") ;
        if (archivo==NULL) { archivo = fopen ("GIMNASIO.dat", "wb") ; }
    
    int opcion, posLuchador = 0 ;
    do {
        cout << "\n_____OCTAGON PRO_____" << endl ;
        cout << "0. Cargar Gimnasio" << endl ;
        cout << "1. Inscribir un atleta" << endl ;
        cout << "2. Generar Main Card" << endl ;
        cout << "3. Actualizar Record" << endl ;
        cout << "4. Guardar Gimnasio" << endl ;
        cout << "5. SALIR" << endl ;
        cout << "-> " ; cin >> opcion ;

        switch (opcion) {
            case 0 :
                startUP (archivo, topePila) ;
                cout << "Archivo cargado" << endl ;
                break ;
            case 1 :
                inscribir_atleta (topePila) ;
                break ;
            case 2 :
                MainCard (topePila, CombatesEstelares) ;
                cout << "Se realizo la Main Card" << endl ;
                break ;
            case 3 :
                actualizar_record (topePila) ;
                break ;
            case 4 :
                int seguro ;
                cout << "Guardar el archivo elimina toda informacion previa."
                << "\nSi esta seguro, ingrese [1]"  
                << "\nDe lo contrario ingrese [0] " << endl ;
                cout << "-> " ; cin >> seguro ;
                if (seguro==1) {
                    GuardarListaDinamica (archivo, topePila) ;
                    cout << "Archivo guardado" << endl ;
                }
                break ;
            case 5 :
                cout << "Vaciando pila..." << endl ;
                vaciar_pila (topePila) ;  // Libera la memoria
                break ;
        }
    } while (opcion != 5) ; 

    fclose (archivo) ;
    system("pause");

return 0 ; }



void agregar_a_pila (NODO *&topepila, strLuchador n) {
    NODO *nuevo = new NODO() ;

    nuevo->info.ID = n.ID ;
    strcpy(nuevo->info.nombre, n.nombre) ;
    strcpy(nuevo->info.apodo, n.apodo) ;
    nuevo->info.peso = n.peso ;
    nuevo->info.victorias = n.victorias ;
    nuevo->info.derrotas = n.derrotas ;

    nuevo -> next = topepila ;
    topepila = nuevo ;
return ; }
// Agrega un elemento a la pila

void quitar_de_pila (NODO *&TopePila, strLuchador &n) {
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

void mover_de_pila (NODO *&TopePila1, NODO *&TopePila2) {
    strLuchador elem_a_mover ;
    quitar_de_pila (TopePila2, elem_a_mover) ; 
    agregar_a_pila (TopePila1, elem_a_mover) ;
return ; }
// Mueve un elemento de una pila a la otra
// Pila1 recibe el elemento, Pila2 entrega el elemento

void vaciar_pila (NODO *&topepila) {
    strLuchador erase ;
    while (topepila!=NULL) { quitar_de_pila (topepila, erase) ; }
    delete topepila ;
return ; }
// Vacia la pila

void startUP (FILE *archivo, NODO *&topepila) {
    strLuchador luchador ;

    if (archivo == NULL) { return ; }

    fseek (archivo, 0, SEEK_SET) ; 
    while (fread (&luchador, sizeof(strLuchador), 1, archivo) == 1) { 
        agregar_a_pila(topepila, luchador) ;
        OrdPila (topepila) ;
    }
return ; }
// Carga el contenido del archivo a la lista dinámica

void GuardarListaDinamica (FILE *&archivo, NODO *&topepila) {
    strLuchador luchador ;

    fclose (archivo);
    archivo = fopen("GIMNASIO.dat", "wb+");

    while (topepila != NULL) {
        quitar_de_pila (topepila, luchador);
        fwrite (&luchador, sizeof(strLuchador), 1, archivo); 
    }

    fflush(archivo);
return ; }
// Carga la lista dinámica al archivo binario

void MainCard (NODO *&topepila, strLuchador CombatesEstelares[]) {
    NODO *aux = NULL ;
    cout << "\n_____MAIN CARD_____" << endl ;
    for (int i=0; (i<5) && (topepila!=NULL); i++) {
        quitar_de_pila(topepila, CombatesEstelares[i]) ;
        cout << "ID: " << CombatesEstelares[i].ID << endl ;
        cout << "Nombre: " << CombatesEstelares[i].nombre << endl ;
        cout << "Apodo: " << CombatesEstelares[i].apodo << endl ;
        cout << "Peso: " << CombatesEstelares[i].peso << endl ;
        cout << "Puntaje: " <<CombatesEstelares[i].victorias - CombatesEstelares[i].derrotas << endl ;
        cout << "\n" ;
        agregar_a_pila(aux, CombatesEstelares[i]) ;
    }
    while (aux!=NULL)  {
        mover_de_pila (topepila, aux) ;
    }
return ; }
// Copia los primeros cinco elementos de la pila a CombatesEstelares[]. No mueve el tope de pila ni borra elementos

void OrdPila (NODO *&topepila) {
    if (topepila == NULL) { return ; }
    if (topepila != NULL) { 
        strLuchador n ;
        quitar_de_pila (topepila, n) ;
        if (topepila == NULL) {
            agregar_a_pila (topepila, n) ;
            return ;
        }
        else { agregar_a_pila (topepila, n) ; }
    } // nada que ordenar

    // extraigo el elemento a insertar
    strLuchador luchador ;
    quitar_de_pila(topepila, luchador) ;
    int puntajeLuch = luchador.victorias - luchador.derrotas ;

    NODO *SortPile = NULL ;

    // muevo los elementos con puntaje mayor arriba de la pila auxiliar
    while (topepila != NULL) {
        strLuchador TOP ;
        quitar_de_pila (topepila, TOP) ;
        agregar_a_pila (topepila, TOP) ;
        int puntajeTop = TOP.victorias - TOP.derrotas ;
        if (puntajeTop > puntajeLuch) { mover_de_pila (SortPile, topepila) ; } 
        else { break ; }
    }

    // inserto el elemento en su lugar
    agregar_a_pila(topepila, luchador) ;

    // vuelvo a poner los elementos movidos
    while (SortPile != NULL) { mover_de_pila (topepila, SortPile) ; }
return ; }
// Ordena un elemento en la pila por victorias - derrotas

void inscribir_atleta (NODO *&topepila) {
    strLuchador nuevo ;

    cout << "Ingrese su atleta" << endl ;
    cout << "ID: " ;
    cin >> nuevo.ID ;
    cout << "Nombre: " ;
    cin.ignore() ;
    cin.getline(nuevo.nombre, 35 + 1, '\n') ;
    cout << "Apodo: " ;
    cin.getline(nuevo.apodo, 35 + 1, '\n') ;
    cout << "Peso: " ;
    cin >> nuevo.peso ;
    cout << "Victorias: " ;
    cin >> nuevo.victorias ;
    cout << "Derrotas: " ;
    cin >> nuevo.derrotas ;

    agregar_a_pila (topepila, nuevo) ;
    OrdPila (topepila) ;
return ; }
// Añade un atleta a la pila 

void actualizar_record (NODO *&topepila) { 
    NODO *topeaux = NULL ;
    strLuchador aux ;
    aux.ID = -1 ; // El ID -1 queda reservado para este control
    int IDatleta , victorias , derrotas , opcion ;
    cout << "Ingrese el ID del atleta: " ; cin >> IDatleta ;

    // buscar el ID, comprobando primero el puntero
    while (topepila != NULL && aux.ID != IDatleta) {
        quitar_de_pila (topepila, aux) ;
        agregar_a_pila (topeaux, aux) ;
    }

    if (aux.ID != IDatleta) {
        cout << "ID No encontrado " << endl ; 
        while (topeaux!=NULL)  { mover_de_pila (topepila, topeaux) ; }
        return ;
    }

    quitar_de_pila (topeaux, aux) ;

    cout << "Desea actualizar: " << endl ; 
    cout << "1. Numero de Victorias " << endl ; 
    cout << "2. Numero de Derrotas " << endl ; 
    cout << "3. Ambas " << endl ; 
    cout << "-> " ; cin >> opcion ;
    if ((opcion==1)||(opcion==3)) { 
        cout << "Ingrese el numero de victorias: " ; 
        cin >> victorias ; 
        aux.victorias = victorias ;
    }
    if ((opcion==2)||(opcion==3)) { 
        cout << "Ingrese el numero de derrotas: " ; 
        cin >> derrotas ;
        aux.derrotas = derrotas ;
    }

    while (topeaux!=NULL)  { mover_de_pila (topepila, topeaux) ; }

    agregar_a_pila (topepila, aux) ;
    OrdPila (topepila) ;
return ; }
// Actualiza el numero de victorias y/o derrotas de un atleta en la pila
