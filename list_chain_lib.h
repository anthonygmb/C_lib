/*
 * =====================================================================================
 *
 *       Filename:  list_chain_lib.h
 *
 *    Description:  Ficher en tete des fonctions de listes chainées
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

#ifndef list_chain_lib
#define list_chain_lib

// déclaration de la structure maillon
typedef struct maillon {
	int info;
	struct maillon* suivant;
} MAILLON;

// déclaration d'une LISTE de type maillon
typedef MAILLON* LISTE;

// déclaration des fonctions
void insert_tete(LISTE* pL, int n);
void insert_fin(LISTE* pL, int n);
LISTE recherche(LISTE L, int n);
void print(LISTE L);
void supprimer_premier(LISTE *pL);
void supprime(LISTE* pL, int n);
void efface(LISTE* pL);

// définition de la structure MA_FILE
typedef struct file {
	LISTE deb;
	LISTE fin;
} *MA_FILE;

// définition des types auxiliaires
typedef enum { FAUX, VRAI } booleen;
typedef enum { OK, ERROR } status;

// déclaration des fonctions
MA_FILE make_file();
booleen vide(MA_FILE f);
status tete_file(MA_FILE f, int *element);
status enfile(MA_FILE f, int n);
status defile(MA_FILE f);

#endif

