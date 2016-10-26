#ifndef SCANNER_H_
#define SCANNER_H_

#define COLUMNAS 12
#define FILAS 15

typedef struct scanner Scanner;

struct scanner {
	//PROPIEDADES
	int** TABLA_TRANSICIONES;
};

//CONSTRUCTOR
Scanner* newScanner();

//DESTRUCTOR
void destroyScanner(Scanner* scanner);

//METODOS
void cargar_tabla_transicion(Scanner* scanner);

void mostrar_tabla_transicion(Scanner* scanner);

void escanear_cadena(Scanner* scanner, char* file_chain);

#endif /* SCANNER_H_ */
