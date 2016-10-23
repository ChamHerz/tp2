#include "scanner.h"
#include <stdlib.h>
#include <stdio.h>

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
			scanner->TABLA_TRANSICIONES[fila][columna] = -1;

	scanner->TABLA_TRANSICIONES[0][0] = 48; //0
	scanner->TABLA_TRANSICIONES[0][1] = 49; //1
	scanner->TABLA_TRANSICIONES[0][2] = 50; //2
	scanner->TABLA_TRANSICIONES[0][3] = 51; //3
	scanner->TABLA_TRANSICIONES[0][4] = 52; //4
	scanner->TABLA_TRANSICIONES[0][5] = 53; //5
	scanner->TABLA_TRANSICIONES[0][6] = 54; //6
	scanner->TABLA_TRANSICIONES[0][7] = 55; //7
	scanner->TABLA_TRANSICIONES[0][8] = 56; //8
	scanner->TABLA_TRANSICIONES[0][9] = 57; //9
	scanner->TABLA_TRANSICIONES[0][10] = 117; //u
	scanner->TABLA_TRANSICIONES[0][11] = 85; //U
	scanner->TABLA_TRANSICIONES[0][12] = 108; //l
	scanner->TABLA_TRANSICIONES[0][13] = 76; //L

	//ESTADOS

	scanner->TABLA_TRANSICIONES[1][0] = 2;
	for(fila=1;fila<10;fila++)
		scanner->TABLA_TRANSICIONES[1][fila] = 6;
	scanner->TABLA_TRANSICIONES[2][10] = 3;
	scanner->TABLA_TRANSICIONES[2][11] = 3;
	scanner->TABLA_TRANSICIONES[2][12] = 4;
	scanner->TABLA_TRANSICIONES[2][13] = 4;
	scanner->TABLA_TRANSICIONES[3][12] = 5;
	scanner->TABLA_TRANSICIONES[3][13] = 5;
	scanner->TABLA_TRANSICIONES[4][10] = 5;
	scanner->TABLA_TRANSICIONES[4][11] = 5;
	for(fila=0;fila<10;fila++)
		scanner->TABLA_TRANSICIONES[6][fila] = 6;
	scanner->TABLA_TRANSICIONES[6][10] = 3;
	scanner->TABLA_TRANSICIONES[6][11] = 3;
	scanner->TABLA_TRANSICIONES[6][12] = 4;
	scanner->TABLA_TRANSICIONES[6][13] = 4;
}

void mostrar_tabla_transicion(Scanner* scanner){
	printf("\nTABLA DE TRANSICIONES\n");
	printf("===== == ============\n");
	int fila;
	int columna;
	for(columna = 0;columna < COLUMNAS;columna++){
		printf(" %c ",scanner->TABLA_TRANSICIONES[0][columna]);
	}
	printf("\n");
	for (fila = 1;fila < FILAS; fila++){
		for(columna = 0;columna < COLUMNAS;columna++){
			if(scanner->TABLA_TRANSICIONES[fila][columna] >=0)
				printf(" %d ",scanner->TABLA_TRANSICIONES[fila][columna]);
			else
				printf("%d ",scanner->TABLA_TRANSICIONES[fila][columna]);
		}
		printf("\n");
	}
}
