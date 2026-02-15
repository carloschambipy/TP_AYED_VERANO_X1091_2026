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
    char nombre[35+1] ;
    char apodo[35+1] ; 
    int peso ; 
    int victorias , derrotas ;
};
struct NODO {
    int ID ;
    char nombre[35+1] ;
    char apodo[35+1] ; 
    int peso ; 
    int victorias , derrotas ;
    NODO *next ; 
};

void agregar_a_pila (NODO *&topepila, strLuchador n) {
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

void copiar_de_pila (NODO *&TopePila, strLuchador &n) {
    
    n.ID = TopePila -> ID ;
    strcpy (n.nombre,TopePila->nombre) ;
    strcpy (n.apodo,TopePila->apodo) ;
    n.peso = TopePila -> peso ;
    n.victorias = TopePila -> victorias ;
    n.derrotas = TopePila -> derrotas ;

return ; }
// Copia en la variable que se le pase la información del puntero de pila que se le pase

void startUP (FILE *archivo, NODO *&topepila) {
    strLuchador luchador ;
    
    int PosActual = ftell (archivo) ;
    fseek (archivo,0,SEEK_END) ; 

    while (fread(&luchador, sizeof(strLuchador), 1, archivo)) {
        agregar_a_pila (topepila, luchador) ;
    }
    
    fseek (archivo,PosActual,SEEK_SET) ; 

return ;
}
// Carga el contenido del archivo a la lista dinámica

void GuardarListaDinamica (FILE *archivo, NODO *&topepila) {
    strLuchador luchador ;
    fseek (archivo,0,SEEK_END) ; 

    while (topepila!=NULL) {
        quitar_de_pila (topepila, luchador) ;
        fwrite (&luchador, sizeof(strLuchador), 1 , archivo) ;
    }

return ;
}
// Carga la lista dinámica al archivo binario

void MainCard (NODO *topepila, strLuchador CombatesEstelares[]) {
    NODO *aux = topepila , *next ;
    for (int i=0;i<5;i++) {
        copiar_de_pila (aux, CombatesEstelares[i]) ;
        next = aux -> next ;
        aux = next ;
    }
return ; }
// Copia los primeros cinco elementos de la pila a CombatesEstelares[]
// No mueve el tope de pila ni borra elementos 

bool validacion(int opcion){
    if ((opcion>=0) && (opcion<6)) { return true ; }
return false ; }
// Valida el numero del menú



void inscribir_atleta (strLuchador luchadoresliga[] , int PosLuchador) {
    
    cout << "Ingrese su atleta" << endl;
    cout << "ID: "; cin >> luchadoresliga[PosLuchador].ID ;
    cout << "Nombre: ";
    cin.ignore();
    cin.getline(luchadoresliga[PosLuchador].nombre,35+1,'\n');
    cout << "Apodo: ";
    cin.ignore();
    cin.getline(luchadoresliga[PosLuchador].apodo,35+1,'\n');
    cout << "Peso: "; cin >> luchadoresliga[PosLuchador].peso ;
    cout << "Racha de Victorias: "; cin >> luchadoresliga[PosLuchador].victorias ;
    cout << "Racha de Derrotas: "; cin >> luchadoresliga[PosLuchador].derrotas ;

    PosLuchador++;

    OrdVector (luchadoresliga, PosLuchador) ;
    
return ; }
// PREGUNTAR
void OrdVector (strLuchador luchadoresliga[] , int PosLuchador) {
    strLuchador aux;
	for (int i=1; i < PosLuchador-1 ; i++){
		for (int j=1; j < PosLuchador-i ; j++){
			if((luchadoresliga[j-1].victorias-luchadoresliga[j-1].derrotas) < (luchadoresliga[j].victorias-luchadoresliga[j].derrotas)){
				aux = luchadoresliga[j-1];
				luchadoresliga[j-1]= luchadoresliga[j];
				luchadoresliga[j] = aux;
			}
		}
	}
return ; }
// Ordena el vector de luchadores por victorias - derrotas

void actualizar_record(){ // HACER
    ;
}



int main() {

    NODO *topePila = NULL ;

    FILE *archivo = fopen ( "GIMNASIO.dat" , "wb+" ) ;
    strLuchador TOPLuchador[10] , LuchadoresLiga[1000] , CombatesEstelares[5] ;
    
    int opcion , posLuchador = 0 ;
    do {
        cout << "____QUE DESEA HACER____" << endl ;
        cout << "0. Cargar Gimnasio" << endl ;
        cout << "1. Inscribir un atleta" << endl ;
        cout << "2. Generar Main Card" << endl ;
        cout << "3. Actualizar Record" << endl ;
        cout << "4. Guardar Gimnasio" << endl ;
        cout << "5. SALIR" << endl ;
        cout << "-> " ; cin >> opcion ;
        while (!validacion(opcion)) {  // Validación  
            if (cin.fail()) { cin.clear() ; }
            cout << "Ingrese un input valido: " ; cin >> opcion ;
        }
        switch (opcion) {
            case 0:
                startUP (archivo,topePila) ;
                break;
            case 1:
                ;
                break;
            case 2:
                MainCard (topePila, CombatesEstelares) ;
                break;            
            case 3:
                ;
                break;
            case 4:
            //  fclose (archivo) ;
            //  FILE *archivo = fopen ( "GIMNASIO.dat" , "wb" ) ;
            //  PREGUNTAR
                GuardarListaDinamica (archivo, topePila) ;
                break;
            default: break;            
        }
    } while (opcion!=5) ;  // MENU

    fclose (archivo) ;

return 0; }

