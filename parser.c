#include "parser.h"

//CONSTRUCTOR
Parser* newParser(){
	Parser* p;
	p = malloc(sizeof(struct parser));
	return p;
}

//DESTRUCTOR
void destroyParser(Parser* parser){
	free(parser);
}

//METODOS
void cargar_tabla_transicion_parser(Parser* parser){
	parser->TABLA_TRANSICIONES = (int**)calloc(FILAS_PARSER, sizeof(int*));
	int fila;
	for(fila=0;fila<FILAS_PARSER;fila++)
		parser->TABLA_TRANSICIONES[fila] = (int*)calloc(COLUMNAS_PARSER, sizeof(int));

	int columna;
	for(fila=0;fila<FILAS_PARSER;fila++)
		for(columna=0;columna<COLUMNAS_PARSER;columna++)
			parser->TABLA_TRANSICIONES[fila][columna] = -1;

	parser->TABLA_TRANSICIONES[0][0] = 15; //INICIO
	parser->TABLA_TRANSICIONES[0][1] = 3; //IDENTIFICADOR
	parser->TABLA_TRANSICIONES[0][2] = 13; //ASIGNACION
	parser->TABLA_TRANSICIONES[0][3] = 20; //EXPRESION VALIDA
	parser->TABLA_TRANSICIONES[0][4] = 11; //PUNTO Y COMA
	parser->TABLA_TRANSICIONES[0][5] = 17; //LEER
	parser->TABLA_TRANSICIONES[0][6] = 8; //PARENTESIS IZQUIERDO
	parser->TABLA_TRANSICIONES[0][7] = 10; //COMA
	parser->TABLA_TRANSICIONES[0][8] = 9; //PARENTESIS DERECHO
	parser->TABLA_TRANSICIONES[0][9] = 18; //ESCRIBIR
	parser->TABLA_TRANSICIONES[0][10] = 16; //FINAL

	parser->TABLA_TRANSICIONES[1][0] = 2;

	parser->TABLA_TRANSICIONES[2][1] = 3;
	parser->TABLA_TRANSICIONES[2][5] = 6;
	parser->TABLA_TRANSICIONES[2][9] = 10;

	parser->TABLA_TRANSICIONES[3][2] = 4;

	parser->TABLA_TRANSICIONES[4][3] = 5;

	parser->TABLA_TRANSICIONES[5][4] = 14;

	parser->TABLA_TRANSICIONES[6][6] = 7;

	parser->TABLA_TRANSICIONES[7][1] = 8;

	parser->TABLA_TRANSICIONES[8][7] = 7;
	parser->TABLA_TRANSICIONES[8][8] = 9;

	parser->TABLA_TRANSICIONES[9][4] = 14;

	parser->TABLA_TRANSICIONES[10][6] = 11;

	parser->TABLA_TRANSICIONES[11][3] = 12;

	parser->TABLA_TRANSICIONES[12][7] = 11;
	parser->TABLA_TRANSICIONES[12][8] = 13;

	parser->TABLA_TRANSICIONES[13][4] = 14;

	parser->TABLA_TRANSICIONES[14][1] = 3;
	parser->TABLA_TRANSICIONES[14][5] = 6;
	parser->TABLA_TRANSICIONES[14][9] = 10;
	parser->TABLA_TRANSICIONES[14][10] = 15;

}

void mostrar_tabla_transicion_parser(Parser* parser){
	printf("\nTABLA DE TRANSICIONES DEL PARSER\n");
	printf("===== == ============ === ======\n");
	int fila;
	int columna;
	printf("\n");
	for (fila = 0;fila < FILAS_PARSER; fila++){
		for(columna = 0;columna < COLUMNAS_PARSER;columna++){
			if(parser->TABLA_TRANSICIONES[fila][columna] >=0 && parser->TABLA_TRANSICIONES[fila][columna] < 10)
				printf("  %d  ",parser->TABLA_TRANSICIONES[fila][columna]);
			else
				printf(" %d  ",parser->TABLA_TRANSICIONES[fila][columna]);
		}
		printf("\n");
	}
}

int verificarExpresion(Parser* parser,int* arrayToken,int* indexToken,int sizeArrayToken){
	int estado_actual = 1;
	int pilaParentesis = 0;

	int fila(int token){
		int columna = 0;
		int** matrix = parser->TABLA_MOV_PILA;
		while(columna < COLUMNAS_PILA){
			if(matrix[0][columna] == token){

				//Apilar
				if(estado_actual== 1 && token == 8){
					pilaParentesis++;
					return matrix[estado_actual][columna];
				}

				//Desapilar
				if(token == 9 && (estado_actual == 2 | estado_actual == 3)){
					if(pilaParentesis > 0){
						pilaParentesis--;
						return 3;
					}
					else{
						return 4;
					}
				}
				//irse si la pila esta vacia token centinela
				if (matrix[estado_actual][columna] == 4){
					if (pilaParentesis != 0){
						return -1;
					}
				}

				return matrix[estado_actual][columna];
			}
			columna++;
		}
		return -1; //expresion invalida
	}

	int index_token_actual = *indexToken;
	int token_actual;
	while (estado_actual != -1 && index_token_actual < sizeArrayToken) {
		token_actual = arrayToken[index_token_actual];
		estado_actual = fila(token_actual);
		if (estado_actual == 4){ //cadena correcta
			*indexToken = index_token_actual - 1; //mantengo el index acualizado
									//le resto uno para volver a pasar al centinela
			return 20; //para que el parse continue
		}
		index_token_actual++;
	}
}

void escanear_token(Parser* parser,int* array_token,int size_array_token){
	int estado_actual = 1;

	int fila(int token){
		int columna = 0;
		int** matrix = parser->TABLA_TRANSICIONES;
		while(columna < COLUMNAS_PARSER){
			if(matrix[0][columna] == token){
				return matrix[estado_actual][columna];
			}
			columna++;
		}
		return -1; //token invalido
	}

	int index_token_actual = 0;
	int token_actual;
	while (estado_actual != -1 && index_token_actual < size_array_token) {
		if (estado_actual == 4 | estado_actual == 11) {
			//se verifica la expresion con un automata de pila
			token_actual = verificarExpresion(parser,array_token,&index_token_actual,size_array_token);
		}
		else {
			token_actual = array_token[index_token_actual];
		}
		estado_actual = fila(token_actual);
		index_token_actual++;
	}
	if (estado_actual == 15){
		printf("programa correcto");
	}
	else{
		printf("error en el parser");
	}
}

void cargar_tabla_mov_pila(Parser* parser){
	parser->TABLA_MOV_PILA = (int**)calloc(FILAS_PILA, sizeof(int*));
	int fila;
	for(fila=0;fila<FILAS_PILA;fila++)
		parser->TABLA_MOV_PILA[fila] = (int*)calloc(COLUMNAS_PILA, sizeof(int));

	int columna;
	for(fila=0;fila<FILAS_PILA;fila++)
		for(columna=0;columna<COLUMNAS_PILA;columna++)
			parser->TABLA_MOV_PILA[fila][columna] = -1;

	parser->TABLA_MOV_PILA[0][0] = 3; //IDENTIFICADOR
	parser->TABLA_MOV_PILA[0][1] = 5; //CONSTANTE
	parser->TABLA_MOV_PILA[0][2] = 6; //SUMA
	parser->TABLA_MOV_PILA[0][3] = 7; //RESTA
	parser->TABLA_MOV_PILA[0][4] = 8; //PARENTESIS IZQUIEDO
	parser->TABLA_MOV_PILA[0][5] = 9; //PARENTESIS DERECHO
	parser->TABLA_MOV_PILA[0][6] = 11; //PUNO Y COMA
	parser->TABLA_MOV_PILA[0][7] = 10; //COMA

	parser->TABLA_MOV_PILA[1][0] = 2;
	parser->TABLA_MOV_PILA[1][1] = 2;

	parser->TABLA_MOV_PILA[1][4] = 1;

	parser->TABLA_MOV_PILA[2][2] = 1;
	parser->TABLA_MOV_PILA[2][3] = 1;
	parser->TABLA_MOV_PILA[2][5] = 4;
	parser->TABLA_MOV_PILA[2][6] = 4;
	parser->TABLA_MOV_PILA[2][7] = 4;

	parser->TABLA_MOV_PILA[3][2] = 1;
	parser->TABLA_MOV_PILA[3][3] = 1;
	parser->TABLA_MOV_PILA[3][5] = 4;
	parser->TABLA_MOV_PILA[3][6] = 4;
	parser->TABLA_MOV_PILA[3][7] = 4;
}

void mostrar_tabla_mov_pila(Parser* parser){
	printf("\nTABLA DE TRANSICIONES DEL AUTOMATA DE PILA\n");
	printf("===== == ============ === ======== == ====\n");
	int fila;
	int columna;
	printf("\n");
	for (fila = 0;fila < FILAS_PILA; fila++){
		for(columna = 0;columna < COLUMNAS_PILA;columna++){
			if(parser->TABLA_MOV_PILA[fila][columna] >=0 && parser->TABLA_MOV_PILA[fila][columna] < 10)
				printf("  %d  ",parser->TABLA_MOV_PILA[fila][columna]);
			else
				printf(" %d  ",parser->TABLA_MOV_PILA[fila][columna]);
		}
		printf("\n");
	}
}
