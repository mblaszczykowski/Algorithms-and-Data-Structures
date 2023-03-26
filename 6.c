#include <stdio.h>

// Funkcja zamieniająca pozycję dwóch elementów
void zamien(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funkcja tworząca kopiec binarny
void tworzKopiec(int arr[], int n, int i) {
    // Znajdź największy element spośród korzenia, lewego i prawego dziecka
    int najwiekszy = i;
    int lewe = 2 * i + 1;
    int prawe = 2 * i + 2;

    if (lewe < n && arr[lewe] > arr[najwiekszy])
        najwiekszy = lewe;

    if (prawe < n && arr[prawe] > arr[najwiekszy])
        najwiekszy = prawe;

    // Zamień elementy i kontynuuj tworzenie kopca, jeśli korzeń nie jest największy
    if (najwiekszy != i) {
        zamien(&arr[i], &arr[najwiekszy]);
        tworzKopiec(arr, n, najwiekszy);
    }
}

// Główna funkcja do sortowania przez kopcowanie
void sortowaniePrzezKopcowanie(int arr[], int n) {
    // Utwórz maksymalny kopiec
    for (int i = n / 2 - 1; i >= 0; i--)
        tworzKopiec(arr, n, i);

    // Sortowanie przez kopcowanie
    for (int i = n - 1; i >= 0; i--) {
        zamien(&arr[0], &arr[i]);

        // Tworzenie kopca dla korzenia, aby ponownie uzyskać najwyższy element
        tworzKopiec(arr, i, 0);
    }
}

// Funkcja wyświetlająca tablicę
void wyswietlTablice(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// Główny kod programu
int main() {
    int arr[] = {1, 12, 9, 5, 6, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortowaniePrzezKopcowanie(arr, n);

    printf("Posortowana tablica to \n");
    wyswietlTablice(arr, n);
}