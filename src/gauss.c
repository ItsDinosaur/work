#include "gauss.h"
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int i,j = 0,k = 0;

	// odwolanie do komorki w macierzy to: mat->data[i][j], gdzie i to wiersz a j to kolumna
	for (j = 0;j < mat->c; j++){
		//wybieram pivota ustawiajac wartosc zmiennej pivot na numer wiersza w ktorym sie on znajduje (bo wiadomo ze w kolumnie j)
		double pivot = fabs(mat->data[0][j]);
		for (k = 0; k < mat->r; k++){
			if (fabs(mat->data[k][j]) > pivot) pivot = k;
		}

	// zamieniam kolejnosc wiersza gornego dla tej diagonali oraz tego z pivotem
	zamienWiersze(&(mat->data[(int)(pivot + 1e-6)]), &(mat->data[j]));
	
	// zamieniam rowniez wiersze w macierzy b
	zamienWiersze(&(b->data[(int)(pivot + 1e-6)]), &(b->data[j]));

	// dokonuje eliminacji elementow pod gornym wierszem diagonali pod warunkiem, ze macierz nie jest osobliwa
	if (wspolczynnik(mat->data[j][j], mat->data[k][j]) == NULL){
	for (k = j;k < mat->r; ++k){
		mat->data[k][j] -= mat->data[j][j]*wspolczynnik(mat->data[j][j], mat->data[k][j]);
	}
	}
	}
		return 0;
}

void zamienWiersze(double**a, double**b){
	double** tmp = *b;
	*b = *a;
	*a = tmp;
}

double wspolczynnik (double gorny, double dolny){
	double wspolczynnik;
	/*dolny = wspolczynnik * gorny
	jezeli po zamianie (bo tam bedzie uzywana ta funckja) okaze sie, ze najwiekszym co do modulu wartosci wspolczynnikiem jest 0, to znaczy
	ze cala rolumna jest zerami, zatem macierz jest osobliwa */
	if (fabs(gorny) < 1e-6){
		return NULL;
	}
	else {
		return dolny/gorny;
	}
}
