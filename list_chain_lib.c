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

// déclaration de la structure maillon
typedef struct maillon {
	int info;
	struct maillon* suivant;
} MAILLON;

// déclaration d'une LISTE de type maillon
typedef MAILLON* LISTE;

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

// définition de la structure MA_FILE
typedef struct file {
	LISTE deb;
	LISTE fin;
} *MA_FILE;

// définition des types auxiliaires
typedef enum { FAUX, VRAI } booleen;
typedef enum { OK, ERROR } status;

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
booleen vide(MA_FILE f) {
	return (f -> deb == NULL && f -> fin == NULL) ? VRAI : FAUX;
}

/*
 * fonction de récupération de l'élément
 * en tete de file
 */
status tete_file(MA_FILE f, int *element) {
	status stat = ERROR;
	if(vide(f) == FAUX) {
		LISTE L = (f -> deb);
		*element = (L -> info);
		stat = OK;
	}
	return stat;
}

/*
 * fonction d'ajout d'élément en fin de file
 */
status enfile(MA_FILE f, int n) {
	if (f -> fin != NULL) {
		LISTE L = (f -> fin);
		insert_fin(&(f -> fin), n);
		f -> fin = L -> suivant;
	} else if (f -> deb != NULL) {
		LISTE L = (f -> deb);
		insert_fin(&(f -> deb), n);
		f -> fin = L -> suivant;
	} else {
		LISTE L2 = NULL;
		insert_tete(&L2, n);
		f -> deb = f -> fin = L2;
	}
	return OK;
}

/*
 * fonction de suppression de l'élément
 * en tete de file
 */
status defile(MA_FILE f) {
	status stat = ERROR;
	if(vide(f) == FAUX) {
		supprimer_premier(&(f -> deb));
		stat = OK;
	}
	return stat;
}

/*
int main() {
	// création d'une liste NULL et insertion de valeur en tete
	LISTE L = NULL;
	insert_tete(&L, 1);
	print(L);
	printf("\n");

	// insertion de valeur à la fin sur la liste L
	insert_fin(&L, 2);
	print(L);
	printf("\n");

	// insertion de valeur en tête sur la liste L
	insert_tete(&L, 0);
	print(L);
	printf("\n");

	// recherche de valeur
	int nbToSearch = 6;
	printf((recherche(L, nbToSearch) != NULL) ? "valeur trouvée" : "valeur non trouvée\n");

	// suppression de la première occurence de la liste
	supprimer_premier(&L);
	print(L);
	printf("\n");

	// suppression de la liste et insertion de dix valeurs
	L = NULL;
	for(int i = 0; i < 10; i++) {
		insert_tete(&L, i);
	}

	// recherche et suppression de l'occurence correspondante
	print(L);
	printf("\n");
	supprime(&L, 5);
	print(L);
	printf("\n");

	// effacement de toute la liste
	print(L);
	printf("\n");
	efface(&L);
	print(L);
	printf((L == NULL) ? "la liste est NULL\n" : "Erreur de suppression\n");
}
*/
/*
int main() {
	// création de liste avec la méthode make_file et vérification
	MA_FILE maFile = make_file();
	if(maFile != NULL && maFile -> deb == NULL && maFile -> fin == NULL) {
		printf("création de la liste réussie\n");
	} else {
		printf("échec de création de la liste\n");
	}

	// test de contenance de la liste avec la fonction vide
	if(vide(maFile) == VRAI) {
		printf("la liste est vide\n");
	} else {
		printf("la liste n'est pas vide\n");
	}

	// ajout d'un maillon quand la liste est NULL
	enfile(maFile, 7);
	print(maFile -> deb);
	printf("\n");
	// ajout d'un maillon quand la liste contient un maillon
	enfile(maFile, 2);
	print(maFile -> deb);
	printf("\n");

	// recherche d'un élément dans la liste
	int *pElement = malloc(sizeof(int));
	if (tete_file(maFile, pElement) == OK) {
		printf("Element trouvé : %d\n", *pElement);
	} else {
		printf("Element non trouvé\n");
	}

	// suppression du premier maillon de la file
	defile(maFile);
	print(maFile -> deb);
	printf("\n");

	return 0;
}
*/

