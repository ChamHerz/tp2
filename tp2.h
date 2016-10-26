/*
 * tp2.h
 *
 *  Created on: 13 oct. 2016
 *      Author: adrielchambi
 */

#ifndef TP2_H_
#define TP2_H_

#include "scanner.h"
#include "file.h"
#include "parser.h"

typedef struct tp2 Tp2;

struct tp2 {
	//PROPIEDADES
	char* FILE_CHAIN;
	Archivo* ARCHIVO;
	Scanner* SCANNER;
	Parser* PARSER;
};

//CONSTRUCTOR
Tp2* newTp2();

//DESTRUCTOR
void destroyTp2(Tp2* tp2);

//METODOS
void iniciarTrabajo(Tp2* tp2);

#endif /* TP2_H_ */
