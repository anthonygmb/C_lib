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
#include "list_chain_lib.h"

#define INFINITE -1;
#define NIL -1;

typedef enum {ORIENTED, NON_ORIENTED} graph_type;

typedef struct graphL *graphL;

struct graphL {
	int size; // les sommets du graphe sont numérotés de 0 à size-1
	graph_type type; // ORIENTED ou NON_ORIENTED
	LISTE* adjacent; // le champ adjacent est le tableau des listes d'adjacence
};

/**
 * crée un graphe avec size sommets et de type graph_type
 * @param size : nombre de sommets
 * @param type : type de graphe (ORIENTED ou NON_ORIENTED)
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
 * ajoute à G un arc de source à dest
 */
void add_arc(graphL G, int source, int dest) {
	insert_tete(&(G -> adjacent[source]), dest);
	if (G -> type == NON_ORIENTED) {
		insert_tete(&(G->adjacent[dest]), source);
	}
}

/*
 * détruit G (en de-allouant la mémoire avec la fonction free)
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
 * pour chaque sommet s, la fonction imprime s et sa liste d’adjacence
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
 * Focntion de parcour en largeur d'un graphe
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

	while(vide(F) == FAUX) {
		tete_file(F, &u);
		tmp = G -> adjacent[u];

		while(tmp != NULL) {
			if (couleur[tmp -> info]) {
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
int main() {
	graphL graph1 = makegraph(4, ORIENTED);

	print_graph(graph1);
	printf("\n");

	add_arc(graph1, 0, 1);
	print_graph(graph1);

	destroy_graph(&graph1);

	if (graph1 == NULL) {
		printf("OK\n");
	}
}
*/
