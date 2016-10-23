#ifndef SCANNER_H_
#define SCANNER_H_

#define COLUMNAS 14
#define FILAS 7

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

#endif /* SCANNER_H_ */
