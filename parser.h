#ifndef PARSER_H_
#define PARSER_H_

#define COLUMNAS_PARSER 11
#define FILAS_PARSER 15

#define COLUMNAS_PILA 8
#define FILAS_PILA 4

typedef struct parser Parser;

struct parser {
	//PROPIEDADES
	int** TABLA_TRANSICIONES;
	int** TABLA_MOV_PILA;
};

//CONSTRUCTOR
Parser* newParser();

//DESTRUCTOR
void destroyParser(Parser* parser);

//METODOS
void cargar_tabla_transicion_parser(Parser* parser);

void mostrar_tabla_transicion_parser(Parser* parser);

void cargar_tabla_mov_pila(Parser* parser);

void mostrar_tabla_mov_pila(Parser* parser);

void escanear_token(Parser* parser,int* array_token,int size_array_token);

#endif /* PARSER_H_ */
