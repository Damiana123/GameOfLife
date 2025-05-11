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
List *copyList(List *head) // copie profunda a listei pentru a o putea salva in stiva
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

    if (*head == NULL) // daca lispa e goala, adaug primul nod
    {
        *head = newNode;
        return;
    }
    List *temp = *head;
    while (temp->next != NULL) // adaug la finalul listei
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

    while (top != NULL) // salvez nodurile stivei in ordine inversa in copie
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
        deleteList(&(copie->head)); // pe masura ce parcurg stiva, sterg listele
        temp = copie;
        copie = copie->next;
        free(temp);
    }

    fflush(file_out);
}
void createRootList(char **matrice_init, int n, int m, List **head2)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (matrice_init[i][j] == 'X')
                addToList(head2, i, j); // adaug doar coord. vii
}
void initTree(Tree **root, List *head)
{
    *root = (Tree *)malloc(sizeof(Tree));
    if (*root == NULL)
        exit(1);
    (*root)->left = (*root)->right = NULL;
    (*root)->head = copyList(head);
}

void createLeftList(char **matrice, List **hl, int n, int m) // salvez in lista pt stanga coord modificate dupa regula B si modific matricea
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
            matrice_noua[i][j] = matrice[i][j]; // fac o copie matricei initiale

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (matrice[i][j] == '+')
            {
                int nr_v = 0;
                if (i > 0 && j < m - 1 && matrice[i - 1][j + 1] == 'X')
                    nr_v++;
                if (i > 0 && matrice[i - 1][j] == 'X')
                    nr_v++;
                if (i > 0 && j > 0 && matrice[i - 1][j - 1] == 'X')
                    nr_v++;
                if (j > 0 && matrice[i][j - 1] == 'X')
                    nr_v++;
                if (j < m - 1 && matrice[i][j + 1] == 'X')
                    nr_v++;
                if (i < n - 1 && j > 0 && matrice[i + 1][j - 1] == 'X')
                    nr_v++;
                if (i < n - 1 && matrice[i + 1][j] == 'X')
                    nr_v++;
                if (i < n - 1 && j < m - 1 && matrice[i + 1][j + 1] == 'X')
                    nr_v++;

                if (nr_v == 2)
                {
                    addToList(hl, i, j);
                    matrice_noua[i][j] = 'X';
                }
            }
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            matrice[i][j] = matrice_noua[i][j]; // modific matricea initiala dupa regula B
    for (i = 0; i < n; i++)
        free(matrice_noua[i]);
    free(matrice_noua);
}

void createRightList(char **matrice, List **hr, int n, int m) // salvez in lista pt dreapta coord modificate dupa regula A si modific matricea
{
    creare_matrice(matrice, n, m, hr); // functia de la task 1 si 2; se modifica si matricea initiala
}

void createPreorderTree(Tree **root, char **matrice, int k, int n, int m, FILE *file_out)
{

    List *leftList = NULL, *rightList = NULL;
    char **copie1 = (char **)malloc(n * sizeof(char *));
    char **copie2 = (char **)malloc(n * sizeof(char *));

    if (copie1 == NULL || copie2 == NULL)
    {
        printf("Alocare esuata");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        copie1[i] = (char *)malloc(m * sizeof(char));
        copie2[i] = (char *)malloc(m * sizeof(char));

        if (copie1[i] == NULL || copie2[i] == NULL)
        {
            printf("Alocare esuata");
            exit(1);
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            copie1[i][j] = matrice[i][j];
            copie2[i][j] = matrice[i][j];
        }

    if (k == 0)
    {
        for (int i = 0; i < n; i++)
        {
            free(copie1[i]);
            free(copie2[i]);
        }
        free(copie1);
        free(copie2);
        return;
    }
    createLeftList(copie1, &leftList, n, m);   // regula B
    createRightList(copie2, &rightList, n, m); // regula A

    // merg in subarborele stang
    
        (*root)->left = (Tree *)malloc(sizeof(Tree));
        if ((*root)->left == NULL)
            exit(1);

        ((*root)->left)->head = copyList(leftList); // copie profunda
        deleteList(&leftList);
        leftList = NULL;
        ((*root)->left)->left = ((*root)->left)->right = NULL;
        scrie_matrice_in_fisier(file_out, copie1, n, m);
        createPreorderTree(&((*root)->left), copie1, k - 1, n, m, file_out);
    

    // merg in subarborele drept
    
        (*root)->right = (Tree *)malloc(sizeof(Tree));
        if ((*root)->right == NULL)
            exit(1);

        ((*root)->right)->head = copyList(rightList);
        deleteList(&rightList);
        rightList = NULL;
        ((*root)->right)->left = ((*root)->right)->right = NULL;
        scrie_matrice_in_fisier(file_out, copie2, n, m);
        createPreorderTree(&((*root)->right), copie2, k - 1, n, m, file_out);
    
    for (int i = 0; i < n; i++)
    {
        free(copie1[i]);
        free(copie2[i]);
    }
    free(copie1);
    free(copie2);
}

void deleteTree(Tree **root)
{
    if (*root == NULL)
        return;
    deleteTree(&((*root)->left));
    deleteTree(&((*root)->right));
    deleteList(&((*root)->head));
    free(*root);
    *root = NULL;
}