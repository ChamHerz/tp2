#include "scanner.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//CONSTRUCTOR
Scanner* newScanner(){
	Scanner* s;
	s = malloc(sizeof(struct scanner));
	return s;
}

//DESTRUCTOR
void destroyScanner(Scanner* scanner){
	free(scanner);
}

//METODOS
void cargar_tabla_transicion(Scanner* scanner){
	scanner->TABLA_TRANSICIONES = (int**)calloc(FILAS, sizeof(int*));
	int fila;
	for(fila=0;fila<FILAS;fila++)
		scanner->TABLA_TRANSICIONES[fila] = (int*)calloc(COLUMNAS, sizeof(int));

	int columna;
	for(fila=0;fila<FILAS;fila++)
		for(columna=0;columna<COLUMNAS;columna++)
			scanner->TABLA_TRANSICIONES[fila][columna] = 1;

	scanner->TABLA_TRANSICIONES[0][0] = 1; //A..Z a..z
	scanner->TABLA_TRANSICIONES[0][1] = 2; //0..9
	scanner->TABLA_TRANSICIONES[0][2] = 3; //+
	scanner->TABLA_TRANSICIONES[0][3] = 4; //-
	scanner->TABLA_TRANSICIONES[0][4] = 5; //(
	scanner->TABLA_TRANSICIONES[0][5] = 6; //)
	scanner->TABLA_TRANSICIONES[0][6] = 7; //,
	scanner->TABLA_TRANSICIONES[0][7] = 8; //;
	scanner->TABLA_TRANSICIONES[0][8] = 9; //:
	scanner->TABLA_TRANSICIONES[0][9] = 10; //=
	scanner->TABLA_TRANSICIONES[0][10] = 11; //fdt
	scanner->TABLA_TRANSICIONES[0][11] = 12; //sp

	//ESTADOS FILA 1
	scanner->TABLA_TRANSICIONES[1][0] = 2;
	scanner->TABLA_TRANSICIONES[1][1] = 4;
	scanner->TABLA_TRANSICIONES[1][2] = 6;
	scanner->TABLA_TRANSICIONES[1][3] = 7;
	scanner->TABLA_TRANSICIONES[1][4] = 8;
	scanner->TABLA_TRANSICIONES[1][5] = 9;
	scanner->TABLA_TRANSICIONES[1][6] = 10;
	scanner->TABLA_TRANSICIONES[1][7] = 11;
	scanner->TABLA_TRANSICIONES[1][8] = 12;
	scanner->TABLA_TRANSICIONES[1][9] = -2;
	scanner->TABLA_TRANSICIONES[1][10] = 14;
	scanner->TABLA_TRANSICIONES[1][11] = 1;

	scanner->TABLA_TRANSICIONES[2][0] = 2;
	scanner->TABLA_TRANSICIONES[2][1] = 2;
	for(columna=2;columna<COLUMNAS;columna++)
		scanner->TABLA_TRANSICIONES[2][columna] = 3;

	scanner->TABLA_TRANSICIONES[4][0] = 5;
	scanner->TABLA_TRANSICIONES[4][1] = 3;
	for(columna=2;columna<COLUMNAS;columna++)
		scanner->TABLA_TRANSICIONES[4][columna] = 5;

	for(columna=0;columna<COLUMNAS;columna++)
		scanner->TABLA_TRANSICIONES[12][columna] = -2;
	scanner->TABLA_TRANSICIONES[12][9] = 13;
}

void mostrar_tabla_transicion(Scanner* scanner){
	printf("\nTABLA DE TRANSICIONES\n");
	printf("===== == ============\n");
	int fila;
	int columna;
	//for(columna = 0;columna < COLUMNAS;columna++){
	//	printf(" %c ",scanner->TABLA_TRANSICIONES[0][columna]);
	//}
	printf("\n");
	for (fila = 0;fila < FILAS; fila++){
		for(columna = 0;columna < COLUMNAS;columna++){
			if(scanner->TABLA_TRANSICIONES[fila][columna] >=0 && scanner->TABLA_TRANSICIONES[fila][columna] < 10)
				printf("  %d  ",scanner->TABLA_TRANSICIONES[fila][columna]);
			else
				printf(" %d  ",scanner->TABLA_TRANSICIONES[fila][columna]);
		}
		printf("\n");
	}
}

void crear_tabla_simbolos(Scanner* scanner){
	//Se crea un array de 50 unidades.
	scanner->TABLA_SIMBOLOS = calloc(50,sizeof(struct tablaSimbolos));
	scanner->TABLA_SIMBOLOS[0].IDENTIFICADOR = "inicio\0";
	scanner->TABLA_SIMBOLOS[0].ES_RESERVADA = 15;
	scanner->TABLA_SIMBOLOS[1].IDENTIFICADOR = "final\0";
	scanner->TABLA_SIMBOLOS[1].ES_RESERVADA = 16;
	scanner->TABLA_SIMBOLOS[2].IDENTIFICADOR = "leer\0";
	scanner->TABLA_SIMBOLOS[2].ES_RESERVADA = 17;
	scanner->TABLA_SIMBOLOS[3].IDENTIFICADOR = "escribir\0";
	scanner->TABLA_SIMBOLOS[3].ES_RESERVADA = 18;
	scanner->SIZE_TABLA_SIMBOLOS = 4; //Actualmente con 4 elementos
}

int columna(char caracter){
	if (caracter >= 97 && caracter <= 122){ //de a a z
		return 1;
	}
	if (caracter >= 48 && caracter <= 57){ //de 0 a 9
		return 2;
	}
	if (caracter == 43){ // 61 = +
		return 3;
	}
	if (caracter == 45){ // 61 = -
		return 4;
	}
	if (caracter == 40){ // 40 = (
		return 5;
	}
	if (caracter == 41){ // 41 = )
		return 6;
	}
	if (caracter == 44){ // 44 = ,
		return 7;
	}
	if (caracter == 59){ // 59 = ;
		return 8;
	}
	if (caracter == 58){ // 58 = :
		return 9;
	}
	if (caracter == 61){ // 61 = =
		return 10;
	}
	if (caracter == '\n' | isspace(caracter)){
		return 12;
	}
}

int esEspacio(char caracter){
	if (caracter == '\n' | isspace(caracter)){
		return 1;
	}
	return 0;
}

int esEstadoFinal(int unEstado){
	switch (unEstado){
	case 1:
	case 2:
	case 4:
	case 12:
		return 0;
	default:
		return 1;
	}
}

char* imprimirToken(int unEstado){
	if (unEstado == 3) {
		return "INDENTIFICADOR\0";
	}
	if (unEstado == 5) {
		return "CONSTANTE\0";
	}
	if (unEstado == 6) {
		return "SUMA\0";
	}
	if (unEstado == 7) {
		return "RESTA\0";
	}
	if (unEstado == 8) {
		return "PAREN_IZQUIERDO\0";
	}
	if (unEstado == 9) {
		return "PAREN_DERECHO\0";
	}
	if (unEstado == 10) {
		return "COMA\0";
	}
	if (unEstado == 11) {
		return "PUNTO_Y_COMA\0";
	}
	if (unEstado == 13) {
		return "ASIGNACION\0";
	}
	if (unEstado == 15) {
		return "INICIO\0";
	}
	if (unEstado == 16) {
		return "FIN\0";
	}
	if (unEstado == 17) {
		return "LEER\0";
	}
	if (unEstado == 18) {
		return "ESCRIBIR\0";
	}
	return "\0";
}

int cambiarTokenIdentificador(Scanner* scanner,char* unIdentificador){
	int posicion = 0;
	int comparar_cadenas = 1;
	while (posicion < scanner->SIZE_TABLA_SIMBOLOS){
		comparar_cadenas = strcmp(scanner->TABLA_SIMBOLOS[posicion].IDENTIFICADOR,unIdentificador);
		if (comparar_cadenas == 0){
			return scanner->TABLA_SIMBOLOS[posicion].ES_RESERVADA;
		}
		posicion++;
	}
	return 3;
}

void agregarToken(Scanner* scanner,int numeroToken){
	scanner->ARRAY_TOKENS[scanner->SIZE_ARRAY_TOKENS] = numeroToken;
	scanner->SIZE_ARRAY_TOKENS++;
}

void escanear_cadena(Scanner* scanner, char* file_chain){
	int estado_final = -1;
	int estado_actual = 1;

	int fila(int caracter){
		int columna = 0;
		int** matrix = scanner->TABLA_TRANSICIONES;
		while(columna < COLUMNAS){
			if(matrix[0][columna] == caracter){
				return matrix[estado_actual][columna];
			}
			columna++;
		}
		return -1; //Caracter que no pertenece al alfabeto
	}

	scanner->ARRAY_TOKENS = calloc(200,sizeof(int)); //se crea un array para almacenar tokens
	scanner->SIZE_ARRAY_TOKENS = 0;

	char* sumador_caracteres = calloc(20,sizeof(char));

	int posicion = 0;
	int posicion_sumador = 0;
	int numero_token = 0;
	while (estado_actual != -1 && file_chain[posicion] != '\0'){
		estado_actual = fila(columna(file_chain[posicion]));
		if (esEstadoFinal(estado_actual)) {
			sumador_caracteres[posicion_sumador] = '\0';
			//printf("%s ",sumador_caracteres);
			numero_token = estado_actual;
			if (estado_actual == 3) { //es un identificador
				numero_token = cambiarTokenIdentificador(scanner,sumador_caracteres);
			}
			printf("%s \n",imprimirToken(numero_token));
			agregarToken(scanner,numero_token);
			posicion_sumador = 0;
			if (estado_actual != 3 && estado_actual != 5) { //es identificador o constante
				posicion++; //avanzo
			}
			estado_actual = 1;
		}else{
			if(!esEspacio(file_chain[posicion])){
				sumador_caracteres[posicion_sumador] = file_chain[posicion];
				posicion_sumador++;
			}
			posicion++; //avanzo
		}

		//estado_final = estado_actual;
	}
}
