/*
 * =====================================================================================
 *
 *       Filename:  tree_lib.c
 *
 *    Description:  Fonctions de manipulation des arbres
 *
 *        Version:  1.0
 *        Created:  28/10/2016 09:27:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Anthony GUMB
 *   Organization:  L3 informatique MIAGE
 *          Notes:  Compiler ce fichier avec l'option -std=gnu99
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree_lib.h"
#include "list_chain_lib.h"

/*
 * Fonction d'affichage des NOEUD de droite
 * d'un arbre binaire
 */
void afficheDroite(NOEUD_B* pc) {
	while(pc != NULL) {
		printf("%d\n", pc -> info);
		pc = pc -> filsDroit;
	}
}

/*
 * Fonction pour déterminer si le noeud est une feuille
 */
bool feuille (NOEUD_B* p) {
	if (p -> filsGauche == NULL && p -> filsDroit == NULL) return true;
	else return false;
}

/*
 * Fonction d'affichage d'arbre binaire
 */
void afficheArbre(NOEUD_B* pc) {
	if (pc != NULL) {
		if (pc -> operateur != NULL) {
			printf("%c", pc -> operateur);
		} else if (pc -> info != NULL) {
			printf("%d", pc -> info);
		}
		afficheArbre(pc -> filsDroit);
		afficheArbre(pc -> filsGauche);
	}
}

/*
 * Fonction de calcul d'arbre binaire arithmetique
 */
int calculeArbre(NOEUD_B* pc) {
	if (pc != NULL) {
		if (feuille(pc) == true) {
			return (pc -> info);
		} else {
			int x1 = calculeArbre(pc -> filsGauche);
			int x2 = calculeArbre(pc -> filsDroit);
			if (pc -> operateur == '+') {
				return x1 + x2;
			} else {
				return x1 * x2;
			}
		}
	}
}

/*
 * Fonction de construction d'arbre binaire arithmetique
 * de type addition
 */
NOEUD_B* construireArbreAddi(char* t, int* p_i) {
	NOEUD_B* n1;
	NOEUD_B* n2;
	n1 = (NOEUD_B*) malloc(sizeof(NOEUD_B));
	n1 -> operateur = NULL;
	n1 -> info = t[*p_i];
	n1 -> filsGauche = NULL;
	n1 -> filsDroit = NULL;

	*p_i = *p_i + 1;
	if (t[*p_i] == '+') {
		n2 = (NOEUD_B*) malloc(sizeof(NOEUD_B));
		n2 -> operateur = t[*p_i];
		n2 -> filsGauche = n1;
		if (t[*p_i] == '*') {
			*p_i = *p_i - 1;
			n2 -> filsDroit = ConstruitArbreMult(t, p_i);
			*p_i = *p_i + 1;
		}
		n2 -> filsDroit = ConstruitArbreAddi(t, *p_i);
	}
	else return n1;
}

/*
 * Fonction de construction d'arbre binaire arithmetique
 * de type multiplication
 */
NOEUD_B* construireArbreMulti(char* t, int* p_i) {
	NOEUD_B* n1;
	NOEUD_B* n2;
	n1 = (NOEUD_B*) malloc(sizeof(NOEUD_B));
	n1 -> info = t[*p_i];
	n1 -> filsGauche = NULL;
	n1 -> filsDroit = NULL;

	*p_i = *p_i + 1;
	if (t[*p_i] == '*') {
		n2 = (NOEUD_B*) malloc(sizeof(NOEUD_B));
		n2 -> operateur = t[*p_i];
		n2 -> filsGauche = n1;
		*p_i = *p_i + 1;
		n2 -> filsGauche = construireArbreMulti(t, p_i);
		return n2;
	} else {
		return n1;
	}
}

/*
 * Fonction d'ajout de mots dans un arbre
 * quelconque lexicographique
 */
void ajouterMot(NOEUD_QL *pinit, char *t, int i) {
	NOEUD_QL *p;
	p = recherche(pinit -> lFils, t[i]);
	if (p == NULL) {
		accrocher(&pinit -> lFils, t, i);
	} else if (t[i] != '#') {
		chercher_mot (p -> lFils, t, i + 1);
	}
}

void accrocher(NOEUD_QL *pinit, char *t, int i) {
	NOEUD_QL *pdeb;
	pdeb = construire_list(t, i);
	pdeb -> lFrere = pinit -> lFils;
	pinit -> lFils = pdeb;
}

/*
 * Fonction de suppression de mots dans un arbre
 * quelconque lexicographique
 */
/*
   supprimerMot() {

   }
   */

/*
 * Fonction de recherche de mots dans un arbre
 * quelconque lexicographique
 */
bool chercher_mot(NOEUD_QL *pinit, char *t, int i) {
	NOEUD_QL *p;
	p = recherche(pinit -> lFils, t[i]);
	if (p == NULL) {
		return false;
	} else if (t[i] == '#') {
		return true;
	} else {
		return chercher_mot(p -> lFils, t, i + 1);
	}
}

/*
 * Fonction pour ajouter un noeud au tas
 */
void ajout_tas (int *t, int *ne, int x) {
	int k, tmp;
	bool flag = true;
	t[*ne] = x;
	k = *ne;
	while (k > 0 && flag == true) {
		if (t[k]%2 == 0) {
			if (t[k] > t[(k-2)/2]) {
				tmp = t[k];
				t[k] = t[(k-2)/2];
				t[(k-2)/2]=tmp;
			}
			else flag = false;
		}
		else {
			if (t[k] > t[(k-1)/2]) {
				tmp = t[k];
				t[k] = t[(k-1)/2];
				t[(k-2)/2]=tmp;
			}
			else flag = false;
		}
	}
}


/*
   void main() {

   }
   */

