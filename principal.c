#include "tp2.h"
#include <stdio.h>

int main(){

	char c = 'Z';
	printf("%d",c);

	Tp2* tp2;

	tp2 = newTp2();

	iniciarTrabajo(tp2);

	destroyTp2(tp2);

	return 0;
}
