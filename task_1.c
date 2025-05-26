#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main(int argc, const char *argv[])
{
    FILE *file_in, *file_out;
    Stack *stackTop = NULL;
    Tree *root = NULL;
    int n, m, i, k, nr_test;
    char **matrice_init;
    file_in = fopen(argv[1], "rt");
    if (file_in == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }
    file_out = fopen(argv[2], "a+");
    if (file_out == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }
    citeste_matrice_fisier(file_in, &nr_test, &n, &m, &k, &matrice_init);

    if (nr_test == 1) // task 1
    {
        scrie_matrice_in_fisier(file_out, matrice_init, n, m);
        for (int iter = 1; iter <= k; iter++)
        {
            List *head = NULL;
            creare_matrice(matrice_init, n, m, &head);
            deleteList(&head);
            scrie_matrice_in_fisier(file_out, matrice_init, n, m);
        }
    }
    else if (nr_test == 2) // task 2
    {
        for (int iter = 1; iter <= k; iter++)
        {
            List *head1 = NULL;
            creare_matrice(matrice_init, n, m, &head1); // in head1 salvez coordonatele celulelor modificate (regula A)
            push(&stackTop, iter, head1);
            deleteList(&head1);
        }
        scrie_stiva_in_fisier(file_out, stackTop);
    }

    else if (nr_test == 3) // task 3
    {
        List *headRoot = NULL;
        createRootList(matrice_init, n, m, &headRoot); // lista pt radacina cu coordonatele celulelor vii initiale
        scrie_matrice_in_fisier(file_out, matrice_init, n, m);
        initTree(&root, headRoot); // am doar radacina in arbore
        createPreorderTree(&root, matrice_init, k, n, m, file_out);
        deleteList(&headRoot);
    }

    else if (nr_test == 4) // task 4
    {
        List *headRoot = NULL;
        createRootList(matrice_init, n, m, &headRoot); // lista pt radacina cu coordonatele celulelor vii initiale
        initTree(&root, headRoot);                     // am doar radacina in arbore
        hamiltonian(&root, matrice_init, k, n, m, file_out); // creez arborele la fel ca la task 3, aflu lantul ham. max, si l afisez
        deleteList(&headRoot);
    }
    

    deleteTree(&root);
    deleteStack(&stackTop);
    fclose(file_in);
    fclose(file_out);
    for (i = 0; i < n; i++)
        free(matrice_init[i]);
    free(matrice_init);
}