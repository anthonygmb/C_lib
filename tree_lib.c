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
//#include "list_chain_lib.h"

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
		if (&(pc -> operateur) != NULL) {
			printf("%c", pc -> operateur);
		} else if (&(pc -> info) != NULL) {
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
			n2 -> filsDroit = construireArbreMulti(t, p_i);
			*p_i = *p_i + 1;
		}
		n2 -> filsDroit = construireArbreAddi(t, p_i);
	}
	else return n1;
}

/*
 * fonction de recherche de valeur
 * dans la liste
 */
NOEUD_QL recherche(NOEUD_QL *L, int n) {
	if(L != NULL) {
		L = ((L -> info) != n) ? recherche(L -> lFils, n) : L;
	}
	return L;
}

/*
 * Fonction d'ajout de mots dans un arbre
 * quelconque lexicographique
 */
void ajouterMot(NOEUD_QL *pinit, char *t, int i) {
	NOEUD_QL *p;
	p = recherche(pinit -> lFils, t[i]);
	if (p == NULL) {
		accrocher(pinit -> lFils, t, i);
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
void supprimerMot() {

}

/*
 * Fonction de suppression, prends la dernière feuille et la mets à la racine
 * (si on supprime la racine, sinon au noeud que l’on veut supprimer), puis
 * on permute la feuille avec les noeuds plus grands qu’elle pour reformer un tas
 */
void suppression_tas (int racine, int *t, int *ne) {
	int tmp, i, i_fg, i_fd, stop, ech, i_max;
	bool flag = false;
	i = 0;
	tmp = t[0];
	t[0] = t[*ne - 1];

	while (flag == false) {
		i_fg = 2 * i + 1;
		i_fd = 2 * i + 2;
		if (i_fg > *ne - 1 && i_fd > *ne - 1) {
			flag = true;
		} else if (i_fd > *ne - 1) {
			i_max = i_fg;
		} else {
			if (t[i_fg] > t[i_fd]) {
				i_max = i_fg;
			} else {
				i_max = i_fd;
			}
		}

		if (t[i] > t[i_max]) {
			stop = 1;
		} else {
			ech = t[i];
			t[i] = t[i_max];
			t[i_max] = ech;
			i = i_max;
		}
	}
}

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

// ===========================================================
// Methode 1 du tri par tas
// utiliser le fonctions filsG, filsD, permuter, entasser
// construire_tas, heapSort

int filsG(int n, int t[n]) {
	return t[2 * n + 2];
}

int filsD(int n, int t[n]) {
	return t[2 * n + 1];
}

void permuter (int t[] ,int i ,int j) {
	int tmp;
	tmp= t[i];
	t[i] = t[j];
	t[j] = tmp;
}

void entasser(int i, int n, int t[n]) {
	int iMax = i;

	if ((filsG(i, t) < n) && (t[filsG(i, t)] > t[iMax])) {
		iMax = filsG(i, t);
	}

	if ((filsD(i, t) < n) && (t[filsD(i, t)] > t[iMax])) {
		iMax = filsD(i, t);
	}

	if(iMax != i) {
		permuter(t, i, iMax);
		entasser(iMax, n, t);
	}
}

void construire_tas(int n, int t[n]) {
	int i;

	for(i = n / 2 - 1; i >= 0; i--) {
		entasser(i, n, t);
	}
}

/*
 * Fonction de transformation d'un tableau
 * non trié en tas
 */
void heapSort(int n, int t[n]) {
	int i;
	construire_tas(n, t);

	for(i = n - 1; i >= 1; i--) {
		permuter(t, 0, i);
		entasser(0, i, t);
	}
}

// ===========================================================
// Methode 2 du tri par tas
// utiliser le fonctions faire_monter, faire_descendre et deplace_racine_et_refait_tas

void faire_monter (int i, int *t) {
	int flag, ech, pere_i;
	flag = 0;
	pere_i = (i - 1) / 2;
	while (flag == 0 && pere_i >= 0) {
		if (t[pere_i] >= t[i]) {
			flag = 1;
		} else {
			ech = t[i];
			t[i] = t[pere_i];
			t[pere_i] = ech;
			i = pere_i;
			pere_i = (i - 1) / 2;
		}
	}
}

void faire_descendre (int i, int *t, int n) {
	int f_g, f_d, fmax, ech, flag;
	flag = 0;
	f_g = 2 * i + 1;
	f_d = 2 * i + 2;

	while (flag == 0 && f_g < n) {
		if (f_d > n) {
			fmax = f_g;
		} else {
			if (t[f_d] > t[f_g]) {
				fmax = f_d;
			} else {
				fmax = f_g;
			}
		}
		if (t[i] < t[fmax]) {
			ech = t[i];
			t[i] = t[fmax];
			t[fmax] = ech;
			i = fmax;
			f_g = 2 * i + 1;
			f_d = 2 * i + 2;
		} else {
			flag = 1;
		}
	}
}

void deplace_racine_et_refait_tas (int *t, int n) {
	int ech;
	ech = t[0];
	t[0] = t[n - 1];
	t[n - 1] = ech;
	faire_descendre(0, t, n - 1);
}

/*
 * Fonction de création de noeud
 */
NOEUD * creer_noeud (int val) {
	noeud *p;
	p = (noeud *) malloc(sizeof(noeud));
	p -> info = val;
	p -> fg = NULL; p -> fd = NULL;
	return p;
}

/*
 * Fonction d'ajout d'un noeud dans un arbre
 * binaire de recherche
 */
void ajout (NOEUD **pinit, int n) {
	noeud *pc ;
	int flag = 0 ;
	if (*pinit == NULL) {
		*pinit = n;
	} else {
		pc = *pinit;
		while (flag == 0) {
			if ( n < pc->info ) {
				if (pc-> fg == NULL ) {
					flag = 1;
					pc -> fg = creer_noeud(n);
				} else {
					pc = pc-> fg;
				}
			} else {
				if (pc-> fd == NULL) {
					flag = 1;
					pc -> fd = creer_noeud(n);
				} else {
					pc = pc -> fd;
				}
			}
		}
	}
}

/*
 * Fonction de recherche dans un arbre binaire de recherche
 */
int chercher(NOEUD *pinit, int x) {
	NOEUD* pc;
	int flag = 0;
	pc = pinit;
	while(flag == 0 && pc != NULL) {
		if (pc -> info == x) {
			flag = 1;
		} else {
			if (x < pc -> info) {
				pc = pc ->f_g;
			} else {
				pc = pc -> f_d;
			}
		}
	}
	return flag;
}


/*
   void main() {

   }
   */

