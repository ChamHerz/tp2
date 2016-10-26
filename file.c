#include "file.h"
#include <stdio.h>
#include <string.h>

Archivo* new_archivo(){
	Archivo* a;
	a = malloc(sizeof(struct archivo));
	return a;
}

void destroy_archivo(Archivo* archivo){
	free(archivo);
}

char* leer_archivo(Archivo* archivo){
	FILE* file = archivo->file;
	char* caracteres;
	caracteres = calloc(100,sizeof(char));
	file = fopen(archivo->path,archivo->modo);

	//printf("\nEl archivo contine lo siguiente:\n");

	char* cadena_file = calloc(200,sizeof(char));

	while(feof(file)==0){
		//fgets(caracteres,100,file);
		fread(caracteres,sizeof(char),100,file);
		strcat(cadena_file,caracteres);
	}

	archivo->size_file = strlen(cadena_file);

	fclose(file);

	return cadena_file;
}
