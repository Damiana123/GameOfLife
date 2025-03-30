#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void citeste_fisier(const char *argv[], int *nr_test, int *n, int *m, int *k, char ***matrice)
{
    int i, j;
    FILE *file_in;
    file_in = fopen(argv[1], "rt");
    if (file_in == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }
    fscanf(file_in, "%d", nr_test);
    fscanf(file_in, "%d %d", n, m);
    fscanf(file_in, "%d", k);
    fgetc(file_in);
    (*matrice) = (char **)malloc((*n) * sizeof(char *));
    for (i = 0; i < *n; i++)
        (*matrice)[i] = (char *)malloc((*m) * sizeof(char));

    for (i = 0; i < *n; i++)
        for (j = 0; j < *m; j++)
        {
            fscanf(file_in, " %c", &(*matrice)[i][j]);
        }

    fclose(file_in);
}

void creare_matrice(char ***matrice_init, int n, int m)
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
            if ((*matrice_init)[i][j] == 'X')
            {
                int nr_v = 0;
                if (i > 0 && j < m - 1 && (*matrice_init)[i - 1][j + 1] == 'X')
                    nr_v++;
                if (i > 0 && (*matrice_init)[i - 1][j] == 'X')
                    nr_v++;
                if (i > 0 && j > 0 && (*matrice_init)[i - 1][j - 1] == 'X')
                    nr_v++;
                if (j > 0 && (*matrice_init)[i][j - 1] == 'X')
                    nr_v++;
                if (j < m - 1 && (*matrice_init)[i][j + 1] == 'X')
                    nr_v++;
                if (i < n - 1 && j > 0 && (*matrice_init)[i + 1][j - 1] == 'X')
                    nr_v++;
                if (i < n - 1 && (*matrice_init)[i + 1][j] == 'X')
                    nr_v++;
                if (i < n - 1 && j < m - 1 && (*matrice_init)[i + 1][j + 1] == 'X')
                    nr_v++;

                if (nr_v < 2 || nr_v > 3)
                    matrice_noua[i][j] = '+';
                else if (nr_v == 2 || nr_v == 3)
                    matrice_noua[i][j] = 'X';
            }
            else if ((*matrice_init)[i][j] == '+')
            {
                int nr_v = 0;
                if (i > 0 && j < m - 1 && (*matrice_init)[i - 1][j + 1] == 'X')
                    nr_v++;
                if (i > 0 && (*matrice_init)[i - 1][j] == 'X')
                    nr_v++;
                if (i > 0 && j > 0 && (*matrice_init)[i - 1][j - 1] == 'X')
                    nr_v++;
                if (j > 0 && (*matrice_init)[i][j - 1] == 'X')
                    nr_v++;
                if (j < m - 1 && (*matrice_init)[i][j + 1] == 'X')
                    nr_v++;
                if (i < n - 1 && j > 0 && (*matrice_init)[i + 1][j - 1] == 'X')
                    nr_v++;
                if (i < n - 1 && (*matrice_init)[i + 1][j] == 'X')
                    nr_v++;
                if (i < n - 1 && j < m - 1 && (*matrice_init)[i + 1][j + 1] == 'X')
                    nr_v++;

                if (nr_v == 3)
                    matrice_noua[i][j] = 'X';
                else
                    matrice_noua[i][j] = '+';
            }
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            (*matrice_init)[i][j] = matrice_noua[i][j];
    for (i = 0; i < n; i++)
        free(matrice_noua[i]);
    free(matrice_noua);
}
void scrie_in_fisier(FILE *file_out, char **matrice, int n, int m)
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
int main(int argc, const char *argv[])
{
    FILE *file_in, *file_out;
    int n, m, i, j, k, nr_test;
    char **matrice_init, **matrice_noua;
    file_out = fopen(argv[2], "a+");
    if (file_out == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }
    citeste_fisier(argv, &nr_test, &n, &m, &k, &matrice_init);
    scrie_in_fisier(file_out, matrice_init, n, m);
    for (int iter = 0; iter < k; iter++)
    {
        creare_matrice(&matrice_init, n, m);
        scrie_in_fisier(file_out, matrice_init, n, m);
    }
    fclose(file_out);
    for (i = 0; i < n; i++)
        free(matrice_init[i]);
    free(matrice_init);
}