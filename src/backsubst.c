#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	//sprawdzenie czy wymiary macierzy sa zgodne
	if(b->r != x->r || b->r != mat->r || x->r != mat->r || mat->c != mat->r){
		return 2;
	}
	//zaczynam od ostatniego wiersza i sie cofam
	for(int w = (b->r) - 1; w>=0; w--){
		double pom=0;
		//obliczam pom, gdzie ax + pom = b
		for(int k = w+1; k<(b->r); k++){
			pom+= mat->data[w][k] * x->data[k][0];
		}
		//sprawdzam czy a nie jest 0
		if((mat->data[w][w]) < 1e-6){
			return 1;
		}
		//podstawiam pod x, x=(b-pom) / a
		x->data[w][0] = (b->data[w][0] - pom) / (mat->data[w][w]);
	}

	return 0;
}


