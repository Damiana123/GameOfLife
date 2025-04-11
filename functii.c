#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

void push(Stack **top, int nr, List *list_head)
{
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    if (newNode == NULL)
        exit(1);

    newNode->nr_gen = nr;
    newNode->head = copyList(list_head); // copia profunda a listei
    newNode->next = *top;
    *top = newNode;
}
List *copyList(List *head)
{
    if (head == NULL)
        return NULL;
    List *newHead = (List *)malloc(sizeof(List));
    if (newHead == NULL)
        exit(1);

    newHead->linie = head->linie; // primul nod copiat din lista
    newHead->coloana = head->coloana;
    newHead->next = NULL;

    List *i = newHead;
    List *j = head->next;
    while (j != NULL) // fac cate o copie profunda a fiecarui nod din lista
    {
        List *newNode = (List *)malloc(sizeof(List));
        if (newNode == NULL)
            exit(1);

        newNode->linie = j->linie;
        newNode->coloana = j->coloana;
        newNode->next = NULL;

        i->next = newNode; // leg primul nod de urmatorul si tot asa
        i = newNode;
        j = j->next;
    }
    return newHead;
}
void deleteStack(Stack **top)
{
    while (*top != NULL)
    {
        Stack *temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}
void addToList(List **head, int linie, int coloana)
{
    List *newNode = (List *)malloc(sizeof(List));
    if (newNode == NULL)
        exit(1);
    newNode->linie = linie;
    newNode->coloana = coloana;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return; // sa verific in curs!!!!
    }
    List *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}
void deleteList(List **head)
{
    while (*head != NULL)
    {
        List *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void citeste_matrice_fisier(FILE *file_in, int *nr_test, int *n, int *m, int *k, char ***matrice)
{
    int i, j;
    fscanf(file_in, "%d", nr_test);
    fscanf(file_in, "%d %d", n, m);
    fscanf(file_in, "%d", k);
    fgetc(file_in);

    *matrice = (char **)malloc((*n) * sizeof(char *));
    if (*matrice == NULL)
    {
        printf("Eroare la alocarea memoriei pentru matrice");
        exit(1);
    }
    for (i = 0; i < *n; i++)
    {
        (*matrice)[i] = (char *)malloc((*m) * sizeof(char));
        if ((*matrice)[i] == NULL)
        {
            printf("Eroare la alocarea memoriei pentru matrice");
            exit(1);
        }
    }
    for (i = 0; i < *n; i++)
        for (j = 0; j < *m; j++)
        {
            fscanf(file_in, " %c", &(*matrice)[i][j]);
        }
}

void creare_matrice(char **matrice_init, int n, int m, List **head)
{
    int i, j;
    char **matrice_noua;
    matrice_noua = (char **)malloc(n * sizeof(char *));
    if (matrice_noua == NULL)
    {
        printf("Alocare esuata");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        matrice_noua[i] = (char *)malloc(m * sizeof(char));
        if (matrice_noua[i] == NULL)
        {
            printf("Alocare esuata");
            exit(1);
        }
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (matrice_init[i][j] == 'X')
            {
                int nr_v = 0;
                if (i > 0 && j < m - 1 && matrice_init[i - 1][j + 1] == 'X')
                    nr_v++;
                if (i > 0 && matrice_init[i - 1][j] == 'X')
                    nr_v++;
                if (i > 0 && j > 0 && matrice_init[i - 1][j - 1] == 'X')
                    nr_v++;
                if (j > 0 && matrice_init[i][j - 1] == 'X')
                    nr_v++;
                if (j < m - 1 && matrice_init[i][j + 1] == 'X')
                    nr_v++;
                if (i < n - 1 && j > 0 && matrice_init[i + 1][j - 1] == 'X')
                    nr_v++;
                if (i < n - 1 && matrice_init[i + 1][j] == 'X')
                    nr_v++;
                if (i < n - 1 && j < m - 1 && matrice_init[i + 1][j + 1] == 'X')
                    nr_v++;

                if (nr_v < 2 || nr_v > 3)
                {
                    matrice_noua[i][j] = '+';
                    addToList(head, i, j);
                }
                else
                    matrice_noua[i][j] = 'X';
            }
            else if (matrice_init[i][j] == '+')
            {
                int nr_v = 0;
                if (i > 0 && j < m - 1 && matrice_init[i - 1][j + 1] == 'X')
                    nr_v++;
                if (i > 0 && matrice_init[i - 1][j] == 'X')
                    nr_v++;
                if (i > 0 && j > 0 && matrice_init[i - 1][j - 1] == 'X')
                    nr_v++;
                if (j > 0 && matrice_init[i][j - 1] == 'X')
                    nr_v++;
                if (j < m - 1 && matrice_init[i][j + 1] == 'X')
                    nr_v++;
                if (i < n - 1 && j > 0 && matrice_init[i + 1][j - 1] == 'X')
                    nr_v++;
                if (i < n - 1 && matrice_init[i + 1][j] == 'X')
                    nr_v++;
                if (i < n - 1 && j < m - 1 && matrice_init[i + 1][j + 1] == 'X')
                    nr_v++;

                if (nr_v == 3)
                {
                    matrice_noua[i][j] = 'X';
                    addToList(head, i, j);
                }
                else

                    matrice_noua[i][j] = '+';
            }
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            matrice_init[i][j] = matrice_noua[i][j];
    for (i = 0; i < n; i++)
        free(matrice_noua[i]);
    free(matrice_noua);
}
void scrie_matrice_in_fisier(FILE *file_out, char **matrice, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            fprintf(file_out, "%c", matrice[i][j]);
            fflush(file_out);
        }
        fprintf(file_out, "%c", '\n');
        fflush(file_out);
    }
    fprintf(file_out, "%c", '\n');
    fflush(file_out);
}
void scrie_stiva_in_fisier(FILE *file_out, Stack *top)
{
    Stack *temp, *copie = NULL;

    while (top != NULL)
    {
        push(&copie, top->nr_gen, top->head);
        deleteList(&(top->head));
        temp = top;
        top = top->next;
        free(temp);
    }
    while (copie != NULL) // afisam elementele in ordine inversa
    {
        fprintf(file_out, "%d", copie->nr_gen);
        List *aux = copie->head; // parcurg lista din stiva
        while (aux != NULL)
        {
            fprintf(file_out, " %d %d", aux->linie, aux->coloana);
            aux = aux->next;
        }
        fprintf(file_out, "\n");
        deleteList(&(copie->head)); // pe masura ce parcurg stiva, eliberez listele
        temp = copie;
        copie = copie->next;
        free(temp);
    }

    fflush(file_out);
}