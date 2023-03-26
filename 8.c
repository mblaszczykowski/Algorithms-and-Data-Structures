#include <stdio.h>
#include <stdlib.h>

// funkcja mergujaca
void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    // Pętla scalająca tablice L i R w posortowanej kolejności
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    // Pętle przepisujące pozostałe elementy z tablic L i R do tablicy arr
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// glowna funkcja sortowania mergesort
void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// funkcja glowna
int main() {
    printf("MERGE SORT liczb z pliku we50.txt\n\n");
    int n = 0;
    int *arr;
    FILE *fp;
    fp = fopen("we50.txt", "r");
    if (fp == NULL) {
        printf("Nie znaleziono pliku we50.txt\n");
        return -1;
    }

    while (!feof(fp)) {
        int x;
        fscanf(fp, "%d\n", &x);
        n++;
    }

    rewind(fp);

    arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d\n", &arr[i]);
    }

    printf("Nieposortowana tablica:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    mergeSort(arr, 0, n - 1);

    printf("Posortowana tablica:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    fclose(fp);
    return 0;
}
