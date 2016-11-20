/*
 * =====================================================================================
 *
 *       Filename:  list_chain_lib.c
 *
 *    Description:  Fonction de manipulation des listes chainées
 *
 *        Version:  1.0
 *        Created:  16/09/2016 10:52:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Anthony GUMB
 *   Organization:  L3 informatique MIAGE
 *          Notes:  Compiler ce fichier avec l'option -std=gnu99
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_chain_lib.h"
#include "graph_lib.h"

/*
 * fonction d'insertion de valeur
 * au début de la liste
 */
void insert_tete(LISTE* pL, int n) {
	LISTE L = (LISTE) malloc(sizeof(MAILLON));
	if(L) {
		L -> suivant = *pL;
		L -> info = n;
		*pL = L;
	}
}

/*
 * fonction d'insertion de valeur
 * à la fin de la liste
 */
void insert_fin(LISTE* pL, int n) {
	if(*pL == NULL) {
		insert_tete(pL, n);
	} else {
		insert_fin(&((*pL) -> suivant), n);
	}
}

/*
 * fonction de recherche de valeur
 * dans la liste
 */
LISTE recherche(LISTE L, int n) {
	if(L != NULL) {
		L = ((L -> info) != n) ? recherche(L -> suivant, n) : L;
	}
	return L;
}

/*
 * fonction pour afficher la liste
 */
void print(LISTE L) {
	if(L != NULL) {
		printf("%d - ", L -> info);
		print(L -> suivant);
	}
}

/*
 * fonction pour supprimer la
 * première occurence de la liste
 */
void supprimer_premier(LISTE *pL) {
	LISTE L = ((*pL) -> suivant);
	free(*pL);
	*pL = L;
}

/*
 * fonction pour supprimer une valeur
 * dans la liste
 */
void supprime(LISTE* pL, int n) {
	if(*pL != NULL && ((*pL) -> info) != n) {
		supprime(&((*pL) -> suivant), n);
	} else {
		supprimer_premier(pL);
	}
}

/*
 * fonction pour effacer toute la liste
 */
void efface(LISTE* pL) {
	if(*pL != NULL && ((*pL) -> suivant) != NULL) {
		efface(&((*pL) -> suivant));
		supprimer_premier(pL);
		*pL = NULL;
	}
}

/*
 * fonction make_file, retourne une file allouée
 * dynamiquement
 */
MA_FILE make_file() {
	MA_FILE MF = (MA_FILE) malloc(sizeof(MA_FILE));
	MF -> deb = NULL;
	MF -> fin = NULL;
	return MF;
}

/*
 * fonction de vérification de contenance
 * d'une file
 */
bool vide(MA_FILE f) {
	return (f -> deb == NULL && f -> fin == NULL) ? true : false;
}

/*
 * fonction de récupération de l'élément
 * en tete de file
 */
int tete_file(MA_FILE f, int *element) {
	int stat = 0;
	if(vide(f) == false) {
		LISTE L = (f -> deb);
		*element = (L -> info);
		stat = 1;
	}
	return stat;
}

/*
 * fonction d'ajout d'élément en fin de file
 */
int enfile(MA_FILE f, int n) {

	if (f -> deb == NULL) {
		insert_tete(&(f -> deb), n);
		f -> fin = f -> deb;
	} else {
		insert_tete(&(f-> fin -> suivant), n);
		f -> fin = f -> fin -> suivant;
	}
	return 1;
}

/*
 * fonction de suppression de l'élément
 * en tete de file
 */
int defile(MA_FILE f) {
	int stat = 0;
	if(vide(f) == false) {
		supprimer_premier(&(f -> deb));
		stat = 1;
		if (f -> deb == NULL) {
			f -> fin = NULL;
		}
	}
	return stat;
}

