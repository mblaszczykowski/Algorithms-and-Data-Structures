#include <stdio.h>

// funkcja do zamiany elementów
void swap(int * a, int * b) {
    int t = * a;
    * a = * b;
    * b = t;
}

// funkcja do znalezienia pozycji partycji
int partition(int array[], int low, int high) {

    // wybierz element najbardziej wysunięty na prawo jako element przestawny
    int pivot = array[high];

    // wskaźnik na większy element
    int i = (low - 1);

    // przechodzenie przez każdy element tablicy
    // porównaj je z osią
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            // jeśli zostanie znaleziony element mniejszy niż przestawny
            // zamień go na większy element wskazany przez i
            i++;

            // zamień element w i z elementem w j
            swap( & array[i], & array[j]);
        }
    }

    // zamień element przestawny na większy element w i
    swap( & array[i + 1], & array[high]);

    // zwróć punkt partycji
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {

        // znajdź taki element przestawny, że
        // elementy mniejsze od osi obrotu znajdują się po lewej stronie osi obrotu
        // elementy większe niż przestawne znajdują się po prawej stronie przestawnej
        int pi = partition(array, low, high);

        // wywołanie rekurencyjne po lewej stronie osi obrotu
        quickSort(array, low, pi - 1);

        // wywołanie rekurencyjne po prawej stronie obrotu
        quickSort(array, pi + 1, high);
    }
}

// funkcja do drukowania elementów tablicy
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        if (i%10==0) {
            printf("\n");
        }
        printf("%d  ", array[i]);
    }
    printf("\n\n");
}

// funkcja glowna
int main() {
    printf("QUICK SORT\n\n");

    // tablica
    int data[] = {
        1,
        44,
        2,
        733,
        222,
        115,
        35,
        501,
        176,
        23,
        37,
        77,
        32,
        8,
        345,
        201,
        205,
        502,
        503,
        101
    };
    // rozmiar tablicy
    int n = sizeof(data) / sizeof(data[0]);

    printf("Tablica nieposortowana: \n");
    printArray(data, n);

    // przeprowadz QuickSort
    quickSort(data, 0, n - 1);

    // wyswietl tablice
    printf("Tablica posortowana: \n");
    printArray(data, n);

    printf("\n");
    return 0;
}