/*
 * =====================================================================================
 *
 *       Filename:  tree_lib.h
 *
 *    Description:  Fichier en tete des fonctions de manipulation des arbres
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

#ifndef tree_lib
#define tree_lib

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
	struct NOEUD_Q* lFils; // liste des fils
	struct NOEUD_Q* lFrere; // liste des frères
} NOEUD_Q;

// structure de noeud d'arbre quelconque lexicographique
typedef struct NOEUD_QL {
	char info;
	struct NOEUD_QL* lFils; // liste des fils
	struct NOEAU_QL* lFrere; // liste des frères
} NOEUD_QL;

// déclaration des fonction
void afficheDroite(NOEUD_B* pc);
void afficheArbre(NOEUD_B* pc);
bool feuille(NOEUD_B* p);
int calculeArbre(NOEUD_B* pc);
NOEUD_B* construireArbreAddi(char* t, int* p_i);
NOEUD_B* construireArbreMulti(char* t, int* p_i);
void ajouterMot(NOEUD_QL *pinit, char *t, int i);
void accrocher(NOEUD_QL *pinit, char *t, int i);
//supprimerMot();
//int rechinsertion(char mot[], NOEUD_QL n);
bool chercher_mot(NOEUD_QL *pinit, char *t, int i);
void ajout_tas (int *t, int *ne, int x);

#endif

