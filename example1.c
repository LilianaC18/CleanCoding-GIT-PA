#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa


typedef struct g {
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct s {
    int t;
    int scap;
    int *arr;
} STK;


NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}


void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}


GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}


void push(int pshd, STK *s) {
    if (s->t < s->scap - 1) {
        s->t++;
        s->arr[s->t] = pshd;
    }
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *aux = g->alst[v_nr];
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}


void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", edg_nr, g->v - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}


void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}


void canbe(GPH *g, int nrv, STK *s1, STK *s2) { // 0 sau 1 daca poate fi sau nu ajuns
    int ans = 0;
    for (int i = 0; i < nrv; i++) { // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
        for (int j = 0; j < nrv; j++) {
            wipe(g);
            DFS(g, s1, i);
            wipe(g);
            DFS(g, s2, j);

            for (int k = 0; k <= s1->t; k++) {
                for (int l = 0; l <= s2->t; l++) {
                    if (s1->arr[k] == j && s2->arr[l] == i) {
                        ans = 1;
                        break;
                    }
                }
                if (ans) break;
            }
            if (ans) break;
        }
        if (ans) break;
    }

    if (ans) {
        printf("Exista un drum intre cele doua noduri.\n");
    } else {
        printf("Nu exista un drum intre cele doua noduri.\n");
    }
}


int main() {
    int nrv, edg_nr;

    printf("Cate noduri are graful?\n");
    scanf("%d", &nrv);

    printf("Cate muchii are graful?\n");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr);

    canbe(g, nrv, s1, s2);

    free(s1->arr);
    free(s1);
    free(s2->arr);
    free(s2);
    for (int i = 0; i < nrv; i++) {
        NODE *aux = g->alst[i];
        while (aux != NULL) {
            NODE *temp = aux;
            aux = aux->next;
            free(temp);
        }
    }
    free(g->alst);
    free(g->vis);
    free(g);
    return 0;
}