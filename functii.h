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

void push(Stack **top, int nr, List *list_head);
List* copyList(List *head);
void deleteStack(Stack **top);
void addToList(List **head, int linie, int coloana);
void deleteList(List **head);
void citeste_matrice_fisier(FILE *file_in, int *nr_test, int *n, int *m, int *k, char ***matrice);
void creare_matrice(char **matrice_init, int n, int m, List **head);
void scrie_matrice_in_fisier(FILE *file_out, char **matrice, int n, int m);
void scrie_stiva_in_fisier(FILE *file_out,Stack *top);
