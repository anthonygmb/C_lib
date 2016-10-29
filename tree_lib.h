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
	struct noeud* lFils; // liste des fils
	struct noeud* lFrere; // liste des frères
} NOEUD;

// déclaration des fonction
void afficheDroite(NOEUD_B* pc);
void afficheArbre(NOEUD_B* pc);
int calculeArbre(NOEUD_B* pc);
NOEUD_B* construireArbreAddi(char* t, int* p_i);
NOEUD_B* construireArbreMulti(char* t, int* p_i);
ajouterMot();
supprimerMot();
rechercherMot();

#endif

