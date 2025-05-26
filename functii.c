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

    if (*head == NULL) // daca lista e goala, adaug primul nod
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
                    addToList(hl, i, j);      // adaug coord celulelor modificate
                    matrice_noua[i][j] = 'X'; // salvez in alta matrice modificarile
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
    // fac copii la matrice (una pt S una pt D)
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

    // eliberez memoria cand termin generatiile
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
    createLeftList(copie1, &leftList, n, m);   // regula B (mi se modifica si matricile)
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

void extrag_celule_vii(CeluleVii *v, int *nr_cel, char **matrice, int n, int m)
{
    int i, j;
    *nr_cel = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (matrice[i][j] == 'X')
            {
                v[*nr_cel].l = i;
                v[*nr_cel++].c = j;
            }
}

int sunt_vecine(CeluleVii a, CeluleVii b)
{
    int x, y;
    // calculez distanta
    x = abs(a.l - b.l);
    y = abs(a.c - b.c);
    if (x <= 1 && y <= 1 && (x + y > 0))
        return 1;
    return 0;
}
void creare_matrice_adiacenta(int **a, CeluleVii v[], int nr_cel)
{
    int i, j;
    for (i = 0; i < nr_cel; i++)
        for (j = 0; j < nr_cel; j++)
            if (i != j && sunt_vecine(v[i], v[j]))
                a[i][j] = 1;
            else
                a[i][j] = 0;
}

int comp_conexa_maxima(int **a, int v, int nod, int *vizitat)
{
    int nr = 1;
    vizitat[nod] = 1;
    for (int i = 0; i < v; i++)
        if (a[nod][i] && vizitat[i] == 0)
            nr += comp_conexa_maxima(a, v, i, vizitat);

    return nr;
}

void DFS_scan_hamiltonian_max(int **a, int v, int nod, int *vizitat, int *lant, int lungime, int *lantMax, int *lungimeMax, int *comp)
{
    if(lungime>=v) return;
    int i;
    vizitat[nod] = 1;
    lant[lungime++] = nod;

    if (lungime > *lungimeMax)
    {
        *lungimeMax = lungime;
        for (i = 0; i < lungime; i++)
            lantMax[i] = lant[i];
    }

    for (i = 0; i < v; i++)
        if (a[nod][i] == 1 && vizitat[i] == 0 && comp[i])
            DFS_scan_hamiltonian_max(a, v, i, vizitat, lant, lungime, lantMax, lungimeMax, comp);
    vizitat[nod] = 0;
}

void hamiltonian(Tree **root, char **matrice, int k, int n, int m, FILE *file_out)
{
    CeluleVii  *v = malloc(n * m * sizeof(CeluleVii));
    int nr_cel;
    extrag_celule_vii(v, &nr_cel, matrice, n, m);

    // eliberez memoria cand termin generatiile
    if (k == 0)
        return;

    if (nr_cel > 0)
    {
        // construiesc matricea de adiacenta
        int **a = (int **)malloc(nr_cel * sizeof(int *));
        for (int i = 0; i < nr_cel; i++)
            a[i] = (int *)calloc(nr_cel, sizeof(int));
        creare_matrice_adiacenta(a, v, nr_cel);

        // caut componenta conexa maxima
        int *comp = calloc(nr_cel, sizeof(int));
        int max_comp_size = 0;
        for (int i = 0; i < nr_cel; i++)
        {
            int *temp_passed = calloc(nr_cel, sizeof(int));
            int comp_size = comp_conexa_maxima(a, nr_cel, i, temp_passed);

            if (comp_size > max_comp_size)
            {
                max_comp_size = comp_size;
                memcpy(comp, temp_passed, nr_cel * sizeof(int));
            }
            free(temp_passed);
        }

        int *vizitat = calloc(nr_cel, sizeof(int));
        int *lant = (int *)malloc(nr_cel * sizeof(int));
        int *lantMax = (int *)malloc(nr_cel * sizeof(int));
        int lungimeMax = 0;
        // caut lantul hamiltonian in componenta conexa maxima
        for (int start = 0; start < nr_cel; start++)
        {
            if (comp[start])
            {
                memset(vizitat, 0, nr_cel * sizeof(int));
                DFS_scan_hamiltonian_max(a, nr_cel, start, vizitat, lant, 0, lantMax, &lungimeMax, comp);
            }
        }
        // afisez
        fprintf(file_out, "%d\n", k);
        if (lungimeMax <= 1)
            fprintf(file_out, "-1\n");
        else
        {
            for (int i = 0; i < lungimeMax; i++)
                fprintf(file_out, "(%d,%d) ", v[lantMax[i]].l, v[lantMax[i]].c);
            fprintf(file_out, "\n");
        }
        // eliberez memoria
        for (int i = 0; i < nr_cel; i++)
            free(a[i]);
        free(v);
        free(a);
        free(comp);
        free(vizitat);
        free(lant);
        free(lantMax);

        // ma duc in subarbori
        List *leftList = NULL, *rightList = NULL;

        // fac copii la matrice (una pt S una pt D)
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

        createLeftList(copie1, &leftList, n, m);   // regula B (mi se modifica si matricile)
        createRightList(copie2, &rightList, n, m); // regula A

        int nr_cel_st = 0, nr_cel_dr = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (copie1[i][j] == 'X')
                    nr_cel_st++;
                if (copie2[i][j] == 'X')
                    nr_cel_dr++;
            }
        if (k - 1 > 0 && nr_cel_st > 0)
        {
            // merg in subarborele stang

            (*root)->left = (Tree *)malloc(sizeof(Tree));
            if ((*root)->left == NULL)
                exit(1);

            ((*root)->left)->head = copyList(leftList); // copie profunda
            deleteList(&leftList);
            leftList = NULL;
            ((*root)->left)->left = ((*root)->left)->right = NULL;

            hamiltonian(&((*root)->left), copie1, k - 1, n, m, file_out);
        }
        else
        {
            deleteList(&leftList);
            leftList = NULL;

            for (int i = 0; i < n; i++)
                free(copie1[i]);
            free(copie1);
            copie1 = NULL;
            if (*root)
                (*root)->left = NULL;
        }
        if (k - 1 > 0 && nr_cel_dr > 0)
        {
            // merg in subarborele drept

            (*root)->right = (Tree *)malloc(sizeof(Tree));
            if ((*root)->right == NULL)
                exit(1);

            ((*root)->right)->head = copyList(rightList);
            deleteList(&rightList);
            rightList = NULL;
            ((*root)->right)->left = ((*root)->right)->right = NULL;

            hamiltonian(&((*root)->right), copie2, k - 1, n, m, file_out);
        }
        else
        {
            deleteList(&rightList);
            rightList = NULL;

            for (int i = 0; i < n; i++)
                free(copie2[i]);
            free(copie2);
            copie2 = NULL;
            if (*root)
                (*root)->right = NULL;
        }
    }
    else // daca nu exista celule vii
    {
        fprintf(file_out, "%d\n-1\n", k);
        return;
    }
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

void citeste_stiva_matrice_fisier(Stack **stackTop, char ***matrice, int *n, int *m, FILE *file_in)
{
    char linie[1024];
    int v[1024], nr = 0, i;
    *n = 0;
    *m = 0;

    while (fgets(linie, sizeof(linie), file_in) != NULL) // citesc toata linia pana la '\n'
    {
        if (linie[0] >= '1' && linie[0] <= '9') // pentru stiva
        {
            char *sir = strtok(linie, " \n"); // iau primul grup de cifre
            while (sir != NULL)
            {
                // in v[] am toate numerele de pe linie
                v[nr++] = atoi(sir); // convertesc fiecare nr(char) la int
                sir = strtok(NULL, " \n");
            }

            List *head = NULL;
            for (i = 1; i < nr; i += 2)
                addToList(&head, v[i], v[i + 1]);

            push(stackTop, v[0], head);
            deleteList(&head);
            nr = 0;
        }
        else if (linie[0] == '+' || linie[0] == 'X') // pentru matrice
        {
            // copiez matricea din fisier in matrice[][]
            linie[strcspn(linie, "\n")] = '\0';
            (*n)++;
            *m = strlen(linie);

            // aloc memorie pentru matrice
            *matrice = (char **)realloc(*matrice, (*n) * sizeof(char *));
            if (*matrice == NULL)
            {
                printf("Eroare la alocarea memoriei pentru matrice");
                exit(1);
            }
            (*matrice)[*n - 1] = (char *)malloc((*m) * sizeof(char));
            if ((*matrice)[*n - 1] == NULL)
            {
                printf("Eroare la alocarea memoriei pentru matrice");
                exit(1);
            }

            for (i = 0; i < *m; i++)
                (*matrice)[*n - 1][i] = linie[i];
        }
    }
}

void generatie_0(Stack *copie, char **matrice)
{
    while (copie)
    {
        while (copie->head)
        {
            int l = (copie->head)->linie;
            int c = (copie->head)->coloana;
            if (matrice[l][c] == '+')
                matrice[l][c] = 'X';
            else
                matrice[l][c] = '+';
            copie->head = (copie->head)->next;
        }
        copie = copie->next;
    }
}
