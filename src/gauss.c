#include "gauss.h"
#include <math.h>
#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int i,j = 0,k = 0,l = 0;
	double wsp;
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
	if (wspolczynnik(mat->data[j][j], mat->data[k][j]) == -10000){
		return 1;
	}
	
	else {
		/*
		i - wskazanie na rzad ktory ma sie nie zmienic juz
		j - wskazanie na zerowana kolumne
		k - obenie przetwarzana kolumna (do zerowania elementow w rzedzie l)
		l - obenie przetwarzany rzad (gdzie a lj bedzie zerem)
		*/
	for (i = j; i < mat->r; i++){
		if (i+1 < mat->r){
		for (l = i+1; l < mat->r; l++){
		wsp = wspolczynnik(mat->data[j][j], mat->data[l][j]); //jak nie bedzie dzialac to nie j j tylko i j
		for (k = j; k < mat->c; k++){
			mat->data[l][k] -= wsp*(mat->data[i][k]);
		}
		b->data[l][0] -= wsp*(b->data[i][0]);
		}
		}
	}
	return 0;
	}
}
}

void zamienWiersze(double**a, double**b){
	double** tmp = *b;
	*b = *a;
	*a = tmp;
}

double wspolczynnik (double gorny, double dolny){
	/*dolny = wspolczynnik * gorny
	jezeli po zamianie (bo tam bedzie uzywana ta funckja) okaze sie, ze najwiekszym co do modulu wartosci wspolczynnikiem jest 0, to znaczy
	ze cala rolumna jest zerami, zatem macierz jest osobliwa */
	if (fabs(gorny) < 1e-6){
		return -10000;
	}
	else {
		return dolny/gorny;
	}
}
