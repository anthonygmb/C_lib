/*
 * =====================================================================================
 *
 *       Filename:  graph_lib.c
 *
 *    Description:  Fonctions de manipulation des graphes
 *
 *        Version:  1.0
 *        Created:  13/10/2016 10:34:32
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

#define INFINITE -1;
#define NIL -1;

/**
 * Fonction de création de graphe avec size sommets et de type graph_type
 * @param size : nombre de sommets
 * @param type : type de graphe (ORIENTED ou NON_ORIENTED)
 * @return G : un graphe initialisé
 */
graphL makegraph(int size, graph_type type) {
	int i;
	graphL G = (graphL) malloc(sizeof(struct graphL));

	if (!G) {
		return NULL;
	}

	G -> size = size;
	G -> type = type;
	G -> adjacent = (LISTE*) malloc(size*sizeof(LISTE));

	if (!G -> adjacent) {
		free(G);
		return NULL;
	}

	for (i = 0; i < size; ++i) {
		G -> adjacent[i] = NULL;
	}

	return G;
}

/*
 * Fonction d'ajout d'arc de source à dest au graphe G
 * @param G : le graphe ou on doit ajouter un arc
 * @param source : le sommet de départ de l'arc
 * @param dest : le sommet de destination de l'arc
 */
void add_arc(graphL G, int source, int dest) {
	insert_tete(&(G -> adjacent[source]), dest);
	if (G -> type == NON_ORIENTED) {
		insert_tete(&(G->adjacent[dest]), source);
	}
}

/*
 * Fonction de destruction de graphe G (en de-allouant la mémoire avec la fonction free)
 * @param G : le graphe à détruire
 */
void destroy_graph(graphL *G) {
	for(int i = 0; i < (*G) -> size; i++) {
		efface(&(*G) -> adjacent[i]);
	}
	free((*G) -> adjacent);
	free(*G);
	*G = NULL;
}

/*
 * Fonction pour imprimer les sommets d'un graphe G
 * @param G : le graphe à imprimer
 */
void print_graph(graphL G) {
	if (G) {
		for (int i = 0; i < G -> size ; ++i) {
			printf("SOMMET %d : ", i);
			print(G -> adjacent[i]);
			printf("\n");
		}
	}
}

/*
 * Fonction de parcour en largeur d'un graphe
 * @param G : le graphe à parcourir
 * @param source : le sommet de début du parcours du graphe
 * @param couleur[] : tableau des couleurs des sommets
 * @param distance : distance d'un sommet depuis le sommet source
 * @param parent[] : tableau des sommets parents de chaque sommet
 */
void BFT(graphL G, int source, int couleur[], int distance[], int parent[]) {

	for (int i = 0; i < G -> size; ++i) {
		couleur[i] = 0;
		distance[i] = INFINITE;
		parent[i] = NIL;
	}

	MA_FILE F = make_file();
	LISTE tmp = NULL;
	couleur[source] = 1;
	enfile(F, source);
	distance[source] = 0;

	int u;

	while(vide(F) == false) {
		tete_file(F, &u);
		tmp = G -> adjacent[u];

		while(tmp != NULL) {
			if (couleur[tmp -> info] == 0) {
				couleur[tmp -> info] = 1;
				parent[tmp -> info] = u;
				distance[tmp -> info] = distance[u] + 1;
				enfile(F, tmp -> info);
			}
			tmp = tmp -> suivant;
		}
		couleur[u] = 2;
		defile(F);
	}
}

/*
 * Fonction de parcour en profondeur d'un graphe
 * @param G : le graphe à parcourir
 * @param source : le sommet de début du parcours du graphe
 * @param couleur[] : tableau des couleurs des sommets
 * @param distance : distance d'un sommet depuis le sommet source
 * @param parent[] : tableau des sommets parents de chaque sommet
 */
void DFT(graphL G, int source, int couleur[], int distance[], int parent[]) {
	//TODO
}

/*
 * Fonction de relachement pour le
 * calcul du plus court chemin dans un graphe
 * @param source : source de l'arc
 * @param dest : fin de l'arc
 */
void relax(int source, int dest) {
	//TODO
}

/*
 * Fonction de recherche de circuit dans
 * un graphe orienté
 * @param G : le graphe à tester
 */
bool recherche_circuit(graphL G) {
	int *color = (int*) malloc(G -> size * sizeof(int));
	bool CIRCUIT = false;
	for(int i = 0; i < G -> size; i++) {
		color[i] = 0;
	}
	for(int i = 0; i < G -> size; i++) {
		dft_recherche_circ(G, i, color, &CIRCUIT);
		if(CIRCUIT == true) {
			return true;
		}
	}
	return false;
}

/*
 * Fonction auxiliaire récursive de parcours
 * en profondeur utile pour la recherche de
 * circuit dans un graphe
 * @param G : le graphe à parcourir
 * @param source : le sommet de début du parcours du graphe
 * @param color : tableau des couleurs des sommets
 * @param CIRCUIT : booleen indicant si il y a un circuit
 */
void dft_recherche_circ (graphL G, int source, int*color, bool *CIRCUIT) {
	color[source] = 1;
	LISTE tmp = G -> adjacent[source];
	while (tmp != NULL){
		if (color[tmp -> info] == 0) {
			dft_recherche_circ(G, tmp -> info, color, CIRCUIT);
		}
		if (color[tmp -> info] == 1) {
			*CIRCUIT = true;
		}
		tmp = tmp -> suivant;
	}
	color[source] = 2;
}

/*
 * Fonction effectuant un tri topologique
 * sur un graphe
 * @param G : le graphe à trier
 */
LISTE topsort(graphL G) {
	int color[G -> size];
	for(int i = 0; i < G -> size; i++) {
		color[i] = 0;
	}
	LISTE tmp = NULL;
	for(int i = 0; i < G -> size; i++) {
		dft_top_sortDAG(G, i, color, &tmp);
	}
	return tmp;
}

/*
 * Fonction de dijkstra pour déterminer
 * le plus court chemin dans un graphe
 * @param G : le graphe à tester
 */
void dijkstra(graphL G) {
	//TODO
}

/*
 * Fonction de Bellman-Ford pour déterminer
 * le plus court chemin dans un graphe
 * orienté pondéré
 * @param G : le graphe à tester
 */
void bellman_ford(graphL G) {
	//TODO
}

/*
 * Fonction auxiliaire récursive de parcours
 * en profondeur utile pour le tri topologique
 * dans un graphe
 * @param G : le graphe à parcourir
 * @param source : le sommet de début du parcours du graphe
 * @param color : tableau des couleurs des sommets*
 * @param sorted : la liste triée
 */
void dft_top_sortDAG(graphL G, int source, int*color, LISTE *sorted) {
	if (color[source] != 2) {
		color[source] = 1;
		LISTE tmp = G -> adjacent[source];
		while (tmp != NULL){
			dft_top_sortDAG(G, tmp -> info, color, sorted);
			tmp = tmp -> suivant;
		}
		color[source] = 2;
		insert_tete(sorted, source);
	}
}

