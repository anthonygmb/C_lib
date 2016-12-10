/*
 * =====================================================================================
 *
 *       Filename:  quicksort.c
 *
 *    Description:  Fpnction de tri rapide
 *
 *        Version:  1.0
 *        Created:  10/12/2016 17:28:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Anthony
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

void echanger(int a[], int i, int j){
	printf("\nechange des valeurs %d et %d", a[i], a[j]);
	int p = a[i];
	a[i]= a[j];
	a[j]= p;
}

int partition(int a[], int deb, int fin) {
	printf("\npartition : %d - %d", deb, fin);

	int x = a[deb];
	int i, j = deb;

	for(i = deb; i <= fin; i++) {
		if(a[i] < x) {
			j++;
			echanger(a, i, j);
		}
	}

	a[deb] = a[j];
	a[j] = x;
	return j;
}

void quicksort(int a[], int deb, int fin, int tTab) {

	printf("\ntableau : ");
	for(int i = 0; i < tTab; i++) {
		printf("%d - ", a[i]);
	}
	int j;

	if (deb < fin) {
		j = partition(a, deb, fin);
		printf("\nj = %d", j);
		quicksort(a, deb, j-1, tTab);
		quicksort(a, j + 1, fin, tTab);
	}
}

int main() {

	int tTab = 10;
	int vet[10] = {18,10,14,3,25,35,8,12,20,22};

	quicksort(vet, 0, 9, tTab);

	printf("\n");
}

