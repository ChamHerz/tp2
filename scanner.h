#ifndef SCANNER_H_
#define SCANNER_H_

#define COLUMNAS 12
#define FILAS 15

typedef struct tablaSimbolos TablaSimbolos;

struct tablaSimbolos {
	char* IDENTIFICADOR;
	int ES_RESERVADA;
};

typedef struct scanner Scanner;

struct scanner {
	//PROPIEDADES
	int** TABLA_TRANSICIONES;
	TablaSimbolos* TABLA_SIMBOLOS;
	int SIZE_TABLA_SIMBOLOS;
	int* ARRAY_TOKENS;
	int SIZE_ARRAY_TOKENS;
};

//CONSTRUCTOR
Scanner* newScanner();

//DESTRUCTOR
void destroyScanner(Scanner* scanner);

//METODOS
void cargar_tabla_transicion(Scanner* scanner);

void mostrar_tabla_transicion(Scanner* scanner);

void escanear_cadena(Scanner* scanner, char* file_chain);

void crear_tabla_simbolos(Scanner* scanner);

#endif /* SCANNER_H_ */
