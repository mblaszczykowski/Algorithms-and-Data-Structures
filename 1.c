#include <stdio.h>
#include <stdlib.h>
 
struct Node
{
    int liczba;
    struct Node* next;
};


void dodaj(struct Node** head_ref, int new_liczba)
{
    //alokujemy pamięć
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node *last = *head_ref;
 
    //umieszczamy dane
    new_node->liczba = new_liczba;
 
    // node będzie ostatni więc jego wskaźnik na następny element jest NULL
    new_node->next = NULL;
 
    // jeśli lista jest pusta to ustawiamy nowy node jako głowę
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    
    //przechodzimy do ostatniego elementu
    while (last->next != NULL)
    {
        last = last->next;
    }
    
    //ustawiamy wskaznik next ostatniego elementu na nowy node
    last->next = new_node;
    return;
}

void usunNode(struct Node** head_ref, int key)
{   
    // head_ref to wskaznik na glowe
    // key to Node ktory zostanie usuniety

    struct Node *temp = *head_ref, *prev;
 
    // jesli usuwamy glowe
    if (temp != NULL
        && temp->liczba == key) {
        // zmieniamy glowe
        *head_ref = temp->next;
        return;
    }

    // szukamy wartosci klucza do usuniecia, pamietamy poprzedni node zeby podmienic prev->next
    while (temp != NULL
           && temp->liczba != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // jesli klucza nie bylo w liscie
    if (temp == NULL)
        return;
 
    // odpinamy node od listy
    prev->next = temp->next;
}

void usunWartosciNieparzyste(struct Node** head_ref)
{
    struct Node* ptr = *head_ref;
 
    while (ptr != NULL) {
        // next = ptr->next;
        // If true, delete node 'ptr'
        if (ptr->liczba % 2 == 1)
            usunNode(head_ref,
                       ptr->liczba);
        ptr = ptr->next;
    }
}

void wypiszListe(struct Node* node)
{
	printf("Zawartość listy:\n");
    while (node != NULL) {
        printf("%d ", node->liczba);
        node = node->next;
    }
}

void srednia(struct Node* node)
{
	int wynik;
	int suma = 0;
	int licznosc = 0;

    while (node != NULL) {
        suma += node->liczba;
        node = node->next;
        licznosc++;
    }
    wynik = suma/licznosc;

    printf("\nŚrednia z wartości umieszczonych w liście: %d\n",wynik);
}


int main()
{
    struct Node* head = NULL;

    // wypelnienie listy kolejnymi wartosciami 1..100
    for (int i=1; i<=100; ++i) {
        dodaj(&head, i);
    }

    // wyswietlenie zawartosci listy
    wypiszListe(head);

    // obliczenie i wyswietlenie sredniej z wartosci umieszczonych w liscie
    srednia(head);
 	
 	// usuniecie z listy wartosci nieparzystych
 	printf("\nUsuwam z listy wartości nieparzyste\n\n");
    usunWartosciNieparzyste(&head);

	// wyswietlenie zawartosci listy
    wypiszListe(head);

    // obliczenie i wyswietlenie sredniej z wartosci umieszczonych w liscie
    srednia(head);

    printf("\n");
    return 0;
}