/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  Fichier de test
 *
 *        Version:  1.0
 *        Created:  12/11/2016 15:03:00
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
 * Fonction principale de test
 */
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

	// création de liste avec la méthode make_file et vérification
	MA_FILE maFile = make_file();
	if(maFile != NULL && maFile -> deb == NULL && maFile -> fin == NULL) {
		printf("création de la liste réussie\n");
	} else {
		printf("échec de création de la liste\n");
	}

	// test de contenance de la liste avec la fonction vide
	if(vide(maFile) == true) {
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
	if (tete_file(maFile, pElement) == 1) {
		printf("Element trouvé : %d\n", *pElement);
	} else {
		printf("Element non trouvé\n");
	}

	// suppression du premier maillon de la file
	defile(maFile);
	print(maFile -> deb);
	printf("\n");

	graphL graph1 = makegraph(4, NON_ORIENTED);
	add_arc(graph1, 0, 1);
	add_arc(graph1, 1, 2);
	print_graph(graph1);

	/*
	   destroy_graph(&graph1);

	   if (graph1 == NULL) {
	   printf("OK\n");
	   }
	   */

	printf("%d\n", graph1 -> size);

	int* couleur = (int*) malloc(graph1 -> size * sizeof(int)) ;
	int* distance = (int*) malloc(graph1 -> size * sizeof(int)) ;
	int* parent = (int*) malloc(graph1 -> size * sizeof(int)) ;

	BFT(graph1, 0, couleur, distance, parent);

	for (int i = 0; i < graph1 -> size; ++i) {
		printf("\nSOMMET %d -----------------", i);
		printf("\ncouleur %d", couleur[i]);
		printf("\ndistance %d", distance[i]);
		printf("\nparent %d\n", parent[i]);
	}

	graphL graph2 = makegraph(4, ORIENTED);
	add_arc(graph2, 0, 1);
	add_arc(graph2, 1, 2);
	add_arc(graph2, 2, 3);
	add_arc(graph2, 3, 4);
	add_arc(graph2, 4, 2);

	print_graph(graph2);

	bool *CIRCUIT;

	if(recherche_circuit(graph2) == false) {
		printf("Pas de circuit détecté\n");
	} else {
		printf("Circuit détecté\n");
	}

	destroy_graph(&graph2);

	if (graph2 == NULL) {
		printf("graphe détruit\n");
	}

	graphL graph3 = makegraph(6, ORIENTED);

	add_arc(graph3, 0, 1);
	add_arc(graph3, 0, 3);
	add_arc(graph3, 1, 2);
	add_arc(graph3, 3, 2);
	add_arc(graph3, 3, 4);
	add_arc(graph3, 2, 5);
	add_arc(graph3, 3, 5);

	print_graph(graph3);

	LISTE liste_triee;

	liste_triee = topsort(graph3);

	print(liste_triee);
	printf("\n");

	return 0;
}

