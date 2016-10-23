#include "tp2.h"
#include "file.h"
#include <stdlib.h>

//CONSTRUCTOR
Tp2* newTp2(){
	Tp2* t;
	t = malloc(sizeof(struct tp2));
	t->SCANNER = newScanner();
	return t;
}

//DESTRUCTOR
void destroyTp2(Tp2* tp2){
	free(tp2);
}

//METODOS
void iniciarTrabajo(Tp2* tp2){

	cargar_tabla_transicion(tp2->SCANNER);

	mostrar_tabla_transicion(tp2->SCANNER);

	tp2->FILE_CHAIN = leer_archivo("programa.micro");

	int ok;

}
