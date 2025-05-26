#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct list_node
{
    int linie, coloana;
    struct list_node *next;
} List;
typedef struct stack_node
{
    int nr_gen;
    List *head;
    struct stack_node *next;
} Stack;
typedef struct tree_node
{
    List *head;
    struct tree_node *left, *right;
} Tree;

typedef struct graph
{
    int v;   // nr varfuri
    int e;   // nr muchii
    int **a; // matrice de adiacenta
} Graph;

typedef struct celule
{
    int l, c;
} CeluleVii;

void push(Stack **top, int nr, List *list_head);
List *copyList(List *head);
void deleteStack(Stack **top);
void addToList(List **head, int linie, int coloana);
void deleteList(List **head);
void citeste_matrice_fisier(FILE *file_in, int *nr_test, int *n, int *m, int *k, char ***matrice);
void creare_matrice(char **matrice_init, int n, int m, List **head);
void scrie_matrice_in_fisier(FILE *file_out, char **matrice, int n, int m);
void scrie_stiva_in_fisier(FILE *file_out, Stack *top);
void createRootList(char **matrice_init, int n, int m, List **head2);
void initTree(Tree **root, List *head);
void createLeftList(char **matrice, List **hl, int n, int m);
void createRightList(char **matrice, List **hr, int n, int m);
void createPreorderTree(Tree **root, char **matrice, int k, int n, int m, FILE *file_out);
void extrag_celule_vii(CeluleVii *v, int *nr_cel, char **matrice, int n, int m);
int sunt_vecine(CeluleVii a, CeluleVii b);
void creare_matrice_adiacenta(int **a, CeluleVii *v, int nr_cel);
int comp_conexa_maxima(int **a, int v, int nod, int *vizitat);
void DFS_scan_hamiltonian_max(int **a, int v, int nod, int *vizitat, int *lant, int lungime, int *lantMax, int *lungimeMax, int *comp);
void hamiltonian(Tree **root, char **matrice, int k, int n, int m, FILE *file_out);
void deleteTree(Tree **root);

void citeste_stiva_matrice_fisier(Stack **stackTop, char ***matrice, int *n, int *m, FILE *file_in);
void generatie_0(Stack *copie, char **matrice);

