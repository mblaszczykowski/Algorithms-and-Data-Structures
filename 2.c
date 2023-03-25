#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char nazwisko[50];
    char imie[50];
    int nrtel;

    struct node* next;
    struct node* prev;
};

struct node* head;
struct node* tail;


//struktura sluzaca do dodawania elementu na koniec listy
void dodajNaKoniec(char x[], char y[], int z)
{
    struct node* newItem;
    newItem = (struct node*) malloc(sizeof(struct node));

    //ustawiamy nowe dane
    strcpy(newItem->nazwisko, x);
    strcpy(newItem->imie, y);
    newItem->nrtel = z;

    //jesli glowa nie istnieje
    if(head==NULL)
    {
        head=newItem;
        newItem->prev=NULL;
        newItem->next=NULL;
        tail=newItem;
    }
    else //jesli istnieje
    {
        newItem->prev=tail;
        tail->next=newItem;
        newItem->next=NULL;
        tail=newItem;
    }
}

//funkcja sluzaca do usuwania elementu na podstawie nazwiska
void usunItem(char x[])
{
    struct node* temp;
    temp=head;
    if(head==tail) //jesli glowa jednoczesnie jest ogonem
    {
        if(strcmp(head->nazwisko, x) != 0)
        {
            printf("Nie można było usunąć\n\n");
            return;
        }
        head=NULL;
        tail=NULL;
        free(temp);
        printf("Pomyślnie usunięto\n\n");
        return;
    }
    // jesli szukane nazwisko posiada glowa
    if(strcmp(head->nazwisko, x) == 0)
    {
        head=head->next;
        head->prev=NULL;
        free(temp);
        printf("Pomyślnie usunięto\n\n");
        return;
    }
    else if(strcmp(tail->nazwisko, x) == 0) //jesli szukane nazwisko posiada ogon 
    {
        temp=tail;
        tail=tail->prev;
        tail->next=NULL;
        free(temp);
        printf("Pomyślnie usunięto\n\n");
        return;
    }

    //petla przez wszystkie nazwiska
    while(strcmp(temp->nazwisko, x) != 0)
    {
        temp=temp->next;
        if(temp==NULL)
        {
            printf("Nie ma takiego nazwiska\n\n");
            return;
        }
    }

    temp->next->prev=temp->prev;
    temp->prev->next=temp->next;
    free(temp);

}

//struktura odpowiedzialna za wyszukiwanie elementu
struct node* znajdzItem(char x[])
{
    struct node* temp;
    temp=head;
    while(temp!=NULL) //petla przez wszystkie elementy listy
    {
        if(strcmp(temp->nazwisko, x) == 0)
        {
            return temp;
            break;
        }
        temp=temp->next;
    }
    return NULL;
}

void wypiszWizytowki()
{
    struct node* temp;
    temp=head;

    printf("\nTwoje wizytówki od początku: \n\n");
    while(temp!=NULL) //petla przez wszystkie elementy listy
    {
        printf("------------------\n");
        printf("Nazwisko: %s\n", temp->nazwisko);
        printf("Imie: %s\n", temp->imie);
        printf("Nr tel: %d\n", temp->nrtel);
        printf("------------------\n\n");

        temp=temp->next;
    }
}

void wypiszOdTylu()
{
    struct node* temp;
    temp=tail;

    printf("\nTwoje wizytówki od końca: \n");
    while(temp!=NULL) //petla przez wszystkie elementy listy od konca
    {   
        printf("------------------\n");
        printf("Nazwisko: %s\n", temp->nazwisko);
        printf("Imie: %s\n", temp->imie);
        printf("Nr tel: %d\n", temp->nrtel);
        printf("------------------\n\n");

        temp=temp->prev;
    }
}


int main()
{
    head=NULL;
    tail=NULL;

    printf("Witaj w wizytowniku!\n");
    printf("   Menu:\n");
    printf("kliknij:\n");
    printf("d - aby dodać wizytówkę\n");
    printf("s - aby znaleźć wizytówkę\n");
    printf("w - aby wypisać wizytówki od początku\n");
    printf("v - aby wypisać wizytówki od końca\n");
    printf("u - aby usunąć wizytówkę\n");
    printf("x - aby wyjść (ctrl-z także działa w konsoli)\n");

    char wybor;

    while(1)
    {   
        printf("   Twój wybór: ");
        scanf(" %c", &wybor);

        if(wybor=='d')
        {   
            char x[50], y[50];
            int z;
            printf("\n   Dodawanie nowej wizytówki\n");
            printf("Podaj nazwisko: ");
            scanf(" %s", x);
            printf("Podaj imię: ");
            scanf(" %s", y);
            printf("Podaj nr tel: ");
            scanf("%d", &z);
            dodajNaKoniec(x, y, z);

            printf("\nWizytówka została dodana\n\n");
        }
        else if(wybor=='s')
        {
            char x[50];
            printf("\nWpisz nazwisko do wyszukania: ");
            scanf(" %s", x);
            struct node* ans = znajdzItem(x);
            if(ans!=NULL) {
                printf("\nZnaleziono:  \n");
                printf("Nazwisko: %s\n", ans->nazwisko);
                printf("Imię: %s\n", ans->imie);
                printf("Nr tel: %d\n\n", ans->nrtel);
            }
            else {
                printf("\nNie znaleziono wizytówki o takim nazwisku\n\n");
            }
        }
        else if(wybor=='w')
        {
            wypiszWizytowki();
        }
        else if(wybor=='v')
        {
            wypiszOdTylu();
        }
        else if(wybor=='u')
        {
            char x[50];
            printf("\nPodaj nazwisko do usunięcia: ");
            scanf(" %s", x);
            usunItem(x);
        }
        else if(wybor=='x')
        {   
            printf("\nDo zobaczenia!\n\n");
            break;
        }
        else 
        {
            printf("Nie ma takiej opcji!\n");
        }

    }

    return 0;
}