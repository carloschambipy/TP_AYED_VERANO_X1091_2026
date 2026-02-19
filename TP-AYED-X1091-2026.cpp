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
void mostrarpila (NODO *&topepila, int cantElem) ;
void mover_de_pila (NODO *&TopePila1, NODO *&TopePila2) ;
void vaciar_pila (NODO *&topepila) ;
void startUP (FILE *archivo, NODO *&topepila) ;
void GuardarListaDinamica (FILE *archivo, NODO *&topepila) ;
void MainCard (NODO *topepila, strLuchador CombatesEstelares[]) ;
void OrdPila (NODO *&topepila) ;
void inscribir_atleta (NODO *&topepila, int &PosLuchador) ;
void actualizar_record (NODO *topepila) ;



int main() { 
    NODO *topePila = NULL ; 
    strLuchador TOPLuchador[10], CombatesEstelares[5] ;
    FILE *archivo = fopen ("GIMNASIO.dat", "rb+") ;
        if (archivo==NULL) { archivo = fopen ("GIMNASIO.dat", "wb") ; }
    
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
        cin >> opcion , posLuchador = 0 ;
        while (!((opcion>=0) && (opcion<6))) { 
            if (cin.fail()) { cin.clear(); }
            cout << "Ingrese un input valido: "; cin >> opcion ;
        }
        switch (opcion) {
            case 0 :
                startUP (archivo, topePila) ;
                cout << "Archivo cargado" << endl ;
                break ;
            case 1 :
                inscribir_atleta (topePila, posLuchador) ;
                cout << topePila->info.apodo << " inscripto" << endl ;
                break ;
            case 2 :
                MainCard (topePila, CombatesEstelares) ;
                cout << "Se realizo la Main Card" << endl ;
                break ;
            case 3 :
                actualizar_record (topePila) ;
                break ;
            case 4 :
                GuardarListaDinamica (archivo, topePila) ;
                cout << "Archivo guardado" << endl ;
                break ;
            case 5 :
                cout << "Vaciando pila..." << endl ;
                vaciar_pila (topePila) ;  // Libera la memoria
                break ;
        }
    } while (opcion != 5) ; 

    fclose (archivo) ;

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

void copiar_de_pila (NODO *TopePila, strLuchador &n) {
    n.ID = TopePila->info.ID ;
    strcpy(n.nombre, TopePila->info.nombre) ;
    strcpy(n.apodo, TopePila->info.apodo) ;
    n.peso = TopePila->info.peso ;
    n.victorias = TopePila->info.victorias ;
    n.derrotas = TopePila->info.derrotas ; 
return ; }
// Copia en la variable que se le pase la información del puntero de pila que se le pase
// No mueve el puntero de pila

void mostrarpila (NODO *&topepila, int cantElem) {
    NODO *aux = topepila ;
    while ( aux != NULL ) {
        cout << "Registro: " << aux->info.ID << endl ;
        cout << "Nombre: " << aux->info.nombre << endl ;
        cout << "Nombre escenico: " << aux->info.apodo << endl ;
        cout << "Peso: " << aux->info.peso << endl ;
        cout << "Puntaje: " << aux->info.victorias - aux->info.derrotas << endl ;
        aux = aux->next ;
    }
    return ; }
// Muestra la pila del tope al fondo

void mover_de_pila (NODO *&TopePila1, NODO *&TopePila2) {
    strLuchador elem_a_mover ;
    quitar_de_pila (TopePila2, elem_a_mover) ; 
    agregar_a_pila (TopePila1, elem_a_mover) ;
return ; }
// Mueve un elemento de una pila a la otra
// Pila1 recibe el elemento, Pila2 entrega el elemento

void vaciar_pila (NODO *&topepila) {
    NODO *aux = topepila ;
    strLuchador erase ;
    while (aux!=NULL) {
        quitar_de_pila (aux, erase) ;
        aux = aux->next ;
    }
    delete aux ;
return ; }
// Vacia la pila

void startUP (FILE *archivo, NODO *&topepila) {
    strLuchador luchador ;

    if (archivo == NULL) { return; }

    fseek (archivo, 0, SEEK_SET) ;  // para leer desde el inicio
    while (fread (&luchador, sizeof(strLuchador), 1, archivo) == 1) {  // leer sólo cuando se obtuvo un registro completo
        agregar_a_pila(topepila, luchador) ;
        OrdPila (topepila) ;
    }
return ; }
// Carga el contenido del archivo a la lista dinámica

void GuardarListaDinamica (FILE *archivo, NODO *&topepila) {
    NODO *aux = topepila , *next ;
    strLuchador luchador ;

    fclose (archivo);
    archivo = fopen("GIMNASIO.dat", "wb");
    fseek (archivo, 0, SEEK_SET) ;

    while (aux != NULL) {
        copiar_de_pila (aux, luchador);
        fwrite (&luchador, sizeof(strLuchador), 1, archivo);
        next = aux->next ;
        aux = next;
    }

    fflush(archivo);
return ; }
// Carga la lista dinámica al archivo binario

void MainCard (NODO *topepila, strLuchador CombatesEstelares[]) {
    NODO *aux = topepila ;
    for (int i=0;i<5;i++) {
        if (aux==NULL) { return ; }
        copiar_de_pila(aux, CombatesEstelares[i]) ;
        cout << "Registro: " << aux->info.ID << endl ;
        cout << "Nombre: " << aux->info.nombre << endl ;
        cout << "Nombre escenico: " << aux->info.apodo << endl ;
        cout << "Peso: " << aux->info.peso << endl ;
        cout << "Puntaje: " << aux->info.victorias - aux->info.derrotas << endl ;
        aux = aux -> next ;
    }
return ; }
// Copia los primeros cinco elementos de la pila a CombatesEstelares[]
// No mueve el tope de pila ni borra elementos

void OrdPila (NODO *&topepila) {
    if (topepila == NULL || topepila->next == NULL) { return; } // nada que ordenar

    // extraigo el elemento a insertar
    strLuchador luchador ;
    quitar_de_pila(topepila, luchador) ;
    int puntajeLuch = luchador.victorias - luchador.derrotas ;

    NODO *SortPile = NULL ;

    // muevo los elementos con puntaje mayor arriba de la pila auxiliar
    while (topepila != NULL) {
        int puntajeTop = topepila->info.victorias - topepila->info.derrotas ;
        if (puntajeTop > puntajeLuch) {
            mover_de_pila(SortPile, topepila) ;
        } 
        else {
            break ;
        }
    }

    // inserto el elemento en su lugar
    agregar_a_pila(topepila, luchador) ;

    // vuelvo a poner los elementos movidos
    while (SortPile != NULL) {
        mover_de_pila(topepila, SortPile) ;
    }
return ; }
// Ordena un elemento en la pila por victorias - derrotas

void inscribir_atleta (NODO *&topepila, int &PosLuchador) {
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
    cout << "Racha de Victorias: " ;
    cin >> nuevo.victorias ;
    cout << "Racha de Derrotas: " ;
    cin >> nuevo.derrotas ;

    agregar_a_pila (topepila, nuevo) ;
    PosLuchador++ ;
    OrdPila (topepila) ;
return ; }
// Añade un atleta a la pila 

void actualizar_record (NODO *topepila) { 
    NODO *topeaux = topepila ;
    int IDatleta , victorias , derrotas , opcion ;
    cout << "Ingrese el ID del atleta: " ; cin >> IDatleta ;
    while (IDatleta!=topeaux->info.ID) {
        topeaux = topeaux->next ;
        if (topeaux==NULL) { cout << "ID No encontrado " << endl ; return ;}
    }
    cout << "Desea actualizar: " << endl ; 
    cout << "1. Numero de Victorias: " << endl ; 
    cout << "2. Numero de Derrotas: " << endl ; 
    cout << "3. Ambas: " << endl ; 
    cout << "-> " ; cin >> opcion ;
    if ((opcion==1)||(opcion==3)) { 
        cout << "Ingrese el numero de victorias: " ; cin >> victorias ; 
        topeaux->info.victorias = victorias ;
    }
    if ((opcion==2)||(opcion==3)) { 
        cout << "Ingrese el numero de derrotas: " ; cin >> derrotas ;
        topeaux->info.derrotas = derrotas ;
    }
return ; }
// Actualiza el numero de victorias y/o derrotas de un atleta en la pila
