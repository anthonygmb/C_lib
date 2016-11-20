/*
 * =====================================================================================
 *
 *       Filename:  graph_lib.h
 *
 *    Description:  Fichier en tete de manipulation des graphes
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

#ifndef graph_lib
#define graph_lib

#include "list_chain_lib.h"

typedef enum {ORIENTED, NON_ORIENTED} graph_type;

typedef struct graphL *graphL;

struct graphL {
	int size; // les sommets du graphe sont numérotés de 0 à size-1
	graph_type type; // ORIENTED ou NON_ORIENTED
	LISTE* adjacent; // le champ adjacent est le tableau des listes d'adjacence
};

graphL makegraph(int size, graph_type type);
void add_arc(graphL G, int source, int dest);
void destroy_graph(graphL *G);
void print_graph(graphL G);
void BFT(graphL G, int source, int couleur[], int distance[], int parent[]);
void DFT(graphL G, int source, int couleur[], int distance[], int parent[]);
void relax(int source, int dest);
bool recherche_circuit(graphL G);
void dft_recherche_circ (graphL G, int source, int*color, bool *CIRCUIT);
LISTE topsort(graphL G);
void dijkstra(graphL G);
void bellman_ford(graphL G);
void dft_top_sortDAG(graphL G, int source, int*color, LISTE *sorted);

#endif
