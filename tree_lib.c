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

// structure de noeud d'arbre binaire arithmetique
typedef struct NOEUD_B {
	int info;
	char operateur;
	struct NOEUD_B* filsGauche;
	struct NOEUD_B* filsDroit;
} NOEUD_B;
NOEUD_B* pinit;

// structure de noeud d'arbre quelconque
typedef struct NOEUD_Q {
	int info;
	struct noeud* lFils; // liste des fils
	struct noeud* lFrere; // liste des frères
} NOEUD;

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
		if (pc -> filsGauche == NULL && pc -> filsDroit == NULL) {
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
		n2 -> filsGauche = construireArbre(t, p_i);
		return n2;
	} else {
		return n1;
	}
}

/*
 * Fonction d'ajout de mots dans un arbre
 * quelconque lexicographique
 */
ajouterMot() {

}

/*
 * Fonction de suppression de mots dans un arbre
 * quelconque lexicographique
 */
supprimerMot() {

}

/*
 * Fonction de recherche de mots dans un arbre
 * quelconque lexicographique
 */
rechercherMot() {

}

/*
void main() {

}
*/

